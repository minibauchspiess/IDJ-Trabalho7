#ifndef TITLESTATE_H
#define TITLESTATE_H

#define TEXT_TIMER 0.8

#include "State.h"
#include "StageState.h"

#include "Game.h"
#include "Gameobject.h"
#include "Sprite.h"

#include "Alien.h"

#include "InputManager.h"
#include "CameraFollower.h"
#include "Text.h"
#include "Timer.h"


class TitleState : public State
{
public:
    TitleState();
    ~TitleState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};

#endif // TITLESTATE_H
