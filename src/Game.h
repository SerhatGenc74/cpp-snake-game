#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include "CollisionHandler.h"

class Game
{
    public:
    Game();
    ~Game();
    enum direction {
        UP,
        DOWN,
        RIGHT,
        LEFT
    };

    bool Init(const char* title,int height,int width);
    void Run();
    void ShutDown();

    private:

    //variables
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;

    //Çizim şeysileri
    SDL_Rect head {500,500,10,10};

    //Vector
    struct Vec2 {float x{0.f},y{0.f}; };
    
    //Yılanın pozisyonu
    Vec2 SnakePos {100.f,100.f};
    //Yılanın Hızı
    Vec2 SnakeVelo {5.f,5.f};

    //resim oluşturmak için
    SDL_Texture* m_texture = nullptr;
    SDL_Surface* surface = nullptr;

    std::deque<SDL_Rect> snake_body;
    SDL_Rect m_apple{250,250,10,10};

    bool m_is_running = false;
    bool m_is_fullscreen = false;
    bool m_alive = true;
    int m_height = 1280;
    int m_width = 640;
    int m_size = 1;
    int m_dir;
    CollisionHandler collisionhandler;

    //Methods
    //Görüntüyü işleme
    void Render();

    //Fizik işlemleri
    void Update(float deltatime);

    //Oyun döngüsü
    void ProcessInput();
};

