
#ifndef GAME_H
#define GAME_H

#define ALIENS_NUMBER 4



#include <iostream>
#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

#include <stack>

#include "StageState.h"

#include <iostream>
using namespace std;

class Game
{
    private:
        Game(string title, int width, int height);
        void CalculateDeltaTime();

        int frameStart=0;
        float dt;

        static Game* instance;

        State* storedState;
        SDL_Window* window;
        SDL_Renderer* renderer;
        stack<unique_ptr<State>> stateStack;

        int wWidth;
        int wHeight;


    public:
        ~Game();

        static Game& GetInstance();
        SDL_Renderer* GetRenderer();
        State& GetCurrentState();

        void Push(State *state);

        void Run();

        float GetDeltaTime();


        int GetWindowWidth();
        int GetWindowHeight();

};

#endif
