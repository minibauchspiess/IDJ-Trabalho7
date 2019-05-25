#include "TitleState.h"

TitleState::TitleState()
{
    //Create title object (the initial state of the game)
    GameObject *titleObj = new GameObject();
    Sprite *titleSprite = new Sprite(*titleObj, "assets/img/title.jpg");
    titleObj->AddComponent(titleSprite);
    CameraFollower *camFol = new CameraFollower(*titleObj);
    titleObj->AddComponent(camFol);

    titleObj->box.x = 0;
    titleObj->box.y = 0;
    AddObject(titleObj);


    //Text to start game
    GameObject *text = new GameObject();
    Text *startTxt = new Text(*text, "assets/font/Call me maybe.ttf", 36, Text::BLENDED, "Pressione espaco para comecar", RED, TEXT_TIMER);
    text->box.x = Game::GetInstance().GetWindowWidth() * 0.5 - text->box.w/2;
    text->box.y = Game::GetInstance().GetWindowHeight() * 0.85;
    text->AddComponent(startTxt);
    AddObject(text);


}

TitleState::~TitleState(){
    objectArray.clear();
}

void TitleState::LoadAssets(){
    Resources::GetImage("assets/img/title.jpg");
    Resources::GetFont("assets/font/Call me maybe.ttf", 36);
}

void TitleState::Update(float dt){
    InputManager &input = InputManager::GetInstance();

    //Check for user input, to start the game, or exit it
    if(input.KeyPress(ESC)) quitRequested=true;

    if(input.KeyPress(SPACE)){
        //Start the game, creating next state and putting it in the stack
        StageState *stageState = new StageState();
        Game::GetInstance().Push(stageState);
    }
    if(input.QuitRequested()){
        quitRequested = true;
    }

    UpdateArray(dt);
}

void TitleState::Render(){
    RenderArray();
}


void TitleState::Start(){
    LoadAssets();
}

void TitleState::Pause(){}

void TitleState::Resume(){
    LoadAssets();
    Camera::pos = Vec2(0,0);
}




