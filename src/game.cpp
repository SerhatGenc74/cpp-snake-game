#include "Game.h"
#include "CollisionHandler.h"
#include <cstdlib>
#include <ctime>
Game::Game(){
    srand(time(nullptr)); // Random seed
}
Game::~Game(){ ShutDown();}

bool Game::Init(const char* title,int height,int width){

    m_is_running = true;

    m_window = SDL_CreateWindow(title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,height,
        SDL_WINDOW_SHOWN
    );

    if(m_window == nullptr)
    {
        m_is_running = false;
        std::cout << "pencere oluşturulurken bir hatayla karşılaşıldı " <<  SDL_GetError();
        return false;
    }

    bool renderer_flag = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED;

    m_renderer = SDL_CreateRenderer(m_window,-1,renderer_flag);

    if (m_renderer == nullptr)
    {
        m_is_running = false;
        std::cout << "renderer oluşturulurken bir hatayla karşılaşıldı " <<  SDL_GetError();
        return false;
    }
    
    return true;
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_renderer,0,0,0,255);
    SDL_RenderClear(m_renderer);

    // Yılan vücudunu çiz
    SDL_SetRenderDrawColor(m_renderer,0,255,0,255);
    for (auto& snake : snake_body)
    {
        SDL_RenderFillRect(m_renderer,&snake);
    }
    
    // Yılan kafasını çiz
    SDL_RenderFillRect(m_renderer,&head);

    // Elmayı çiz
    SDL_SetRenderDrawColor(m_renderer,255,0,0,255);
    SDL_RenderFillRect(m_renderer,&m_apple);

    SDL_RenderPresent(m_renderer);
    SDL_Delay(25);
}

void Game::ProcessInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_is_running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                m_is_running = false;
                break;
            case SDLK_F11:
                m_is_fullscreen = !m_is_fullscreen;
                if (m_is_fullscreen)
                {
                    SDL_SetWindowFullscreen(m_window,SDL_WINDOW_FULLSCREEN_DESKTOP);
                }
                if (!m_is_fullscreen)
                {
                    SDL_SetWindowFullscreen(m_window,0);
                }
                break;
                
            case SDLK_UP:
                m_dir = UP;
                break;

            case SDLK_DOWN:
                m_dir = DOWN;
                break;

            case SDLK_RIGHT:
                m_dir = RIGHT;
                break;

            case SDLK_LEFT:
                m_dir = LEFT;
                break;

            default:
                break;
            }
        case SDL_MOUSEMOTION:
            std::cout << "[EVENT] x: " << event.motion.x << " y: " << event.motion.y << std::endl;
          break;
        }
    }
    
}


void Game::ShutDown()
{
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if (m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
    
    SDL_Quit();
}
void Game::Run()
{   
    while (m_is_running)
    {
        ProcessInput();
        Update(0.0016f);
        Render();
    }
    
}

void Game::Update(float)
{
    // Yılanın eski head pozisyonunu kaydet
    snake_body.push_front(head);
    
    // Eğer yılan elmayı yemişse boyutu artır, yoksa kuyruğu kısalt
    if (snake_body.size() > m_size) {
        snake_body.pop_back();
    }
    
    switch (m_dir)
    {
    case UP:
        head.y -= SnakeVelo.y;
        break;
    case DOWN:
        head.y += SnakeVelo.y;
        break;
    case RIGHT:
        head.x += SnakeVelo.x;
        break;
    case LEFT:
        head.x -= SnakeVelo.x;                
        break;
    }
    
    // Elma ile çarpışma kontrolü
    if (collisionhandler.CheckCollision(head, m_apple))
    {
        m_size += 2;
        std::cout << "snake size: " << m_size << std::endl;
        
        // Yeni elma pozisyonu oluştur
        m_apple = {(rand() % 100) * 10, (rand() % 100) * 10, 10, 10};
    }
    // if (collisionhandler.CheckCollision(head,))
    // {
    //     /* code */
    // }
    
}