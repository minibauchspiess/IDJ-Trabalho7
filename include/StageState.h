
#ifndef STAGESTATE_H
#define STAGESTATE_H


#define N_LAYERS 2

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"

#include "State.h"
#include "EndState.h"
#include "Music.h"
#include "Sprite.h"
#include "Collider.h"
#include "Collision.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include <memory>

using namespace std;

class StageState : public State
{
public:
    StageState();
    ~StageState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();

private:
    TileSet* tileSet;
    Music backgroundMusic;
};

#endif
