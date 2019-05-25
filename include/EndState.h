#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "Gameobject.h"
#include "State.h"
#include "Music.h"
#include "Sprite.h"
#include "TitleState.h"

#include "Text.h"
#include "GameData.h"
#include "Resources.h"
#include "Music.h"
#include "InputManager.h"

using namespace std;

class EndState : public State
{
public:
    EndState();
    ~EndState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();

private:
    Music backgroundMusic;

};

#endif // ENDSTATE_H
