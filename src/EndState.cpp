#include "EndState.h"

EndState::EndState()
{

    started = false;

}

EndState::~EndState(){}

void EndState::LoadAssets(){
    Resources::GetImage("assets/img/win.jpg");
    Resources::GetImage("assets/img/lose.jpg");
    Resources::GetMusic("assets/audio/endStateWin.ogg");
    Resources::GetMusic("assets/audio/endStateLose.ogg");
    Resources::GetFont("assets/font/Call me maybe.ttf", 36);
}

void EndState::Update(float dt){
    InputManager &input = InputManager::GetInstance();

    //Check input requests
    if(input.KeyPress(ESC)){
        this->quitRequested = true;
    }
    if(input.KeyPress(SPACE)){
        this->popRequested = true;
        //Title state is waiting in the first element of the states stack
    }

    UpdateArray(dt);
}

void EndState::Render(){

    RenderArray();
}

void EndState::Start(){

    LoadAssets();

    GameObject *endStGO = new GameObject();
    Sprite *bgSprite;
    //Test victory condition
    if(GameData::playerVictory){
        //Load victory sprite and music
        backgroundMusic = Music("assets/audio/endStateWin.ogg");
        bgSprite = new Sprite(*endStGO, "assets/img/win.jpg");
    }
    else{
        //Load lose sprite and music
        backgroundMusic = Music("assets/audio/endStateLose.ogg");
        bgSprite = new Sprite(*endStGO, "assets/img/lose.jpg");
    }

    endStGO->box.x = 0;
    endStGO->box.y = 0;
    endStGO->AddComponent(bgSprite);
    AddObject(endStGO);


    //Add text with instruction to play again
    GameObject *text = new GameObject();
    Text *endTxt = new Text(*text, "assets/font/Call me maybe.ttf", 36, Text::BLENDED, "Pressione espaco para jogar novamente", RED, TEXT_TIMER);
    text->box.x = Game::GetInstance().GetWindowWidth() * 0.5 - text->box.w/2;       //Centralize text in x axis
    text->box.y = Game::GetInstance().GetWindowHeight() * 0.85;
    text->AddComponent(endTxt);
    AddObject(text);

    backgroundMusic.Play();


    for(unsigned int i=0;i<objectArray.size();i++){
        objectArray[i]->Start();
    }

    started = true;
}

void EndState::Pause(){}

void EndState::Resume(){
    Camera::pos = Vec2(0,0);
}


