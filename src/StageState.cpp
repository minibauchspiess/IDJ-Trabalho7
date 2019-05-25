#include "StageState.h"
#include "dirent.h"
#include "Vec2.h"
#include "Rect.h"
#include "Face.h"
#include "Sound.h"

#define PI 3.14159265358979323846

using namespace std;



StageState::StageState()
{
    //Restart Alien counting, to the new game
    Alien::alienCount = 0;

    started = false;

    //Background object
    GameObject* bgObj = new GameObject();
    Sprite* bg = new Sprite(*bgObj, "assets/img/ocean.jpg");
    bgObj->AddComponent(bg);
    CameraFollower* bgCamera = new CameraFollower(*bgObj);
    bgObj->AddComponent(bgCamera);
    AddObject(bgObj);


    //TileMap object
    GameObject* tmObj = new GameObject(-1);                     //Layer -1 tels state it is the TileMap object
    TileSet* ts = new TileSet(*tmObj, 64, 64, "assets/img/tileset.png");
    TileMap* tm = new TileMap(*tmObj, "assets/map/tileMap.txt", ts);
    tmObj->AddComponent(tm);
    tmObj->box.x = 0;
    tmObj->box.y = 0;
    AddObject(tmObj);


    //Set position of every alien (ugly way to do it, but meh)
    Vec2 alienPos[ALIENS_NUMBER];
    alienPos[0] = Vec2(0,0);
    alienPos[1] = Vec2(1400,0);
    alienPos[2] = Vec2(0,1200);
    alienPos[3] = Vec2(1400,1200);


    //Generate aliens
    for (unsigned int i=0; i<ALIENS_NUMBER; i++) {
        GameObject* alObj = new GameObject();
        float offset = ((float)i/ALIENS_NUMBER)*ALIEN_REST_TIME;
        Alien* alien = new Alien(*alObj, (rand()%4)+2, offset);     //Alien has from 2 to 5 minions around it
        alObj->AddComponent(alien);
        alObj->box.x = alienPos[i].x;
        alObj->box.y = alienPos[i].y;
        AddObject(alObj);
    }


    //Penguin -> player
    GameObject *pgObj = new GameObject();
    PenguinBody *pg = new PenguinBody(*pgObj);
    pgObj->AddComponent(pg);
    pgObj->box.x = 704;
    pgObj->box.y = 640;
    AddObject(pgObj);
    Camera::Follow(pgObj);


    //life text
    GameObject *life = new GameObject();
    Text *lifeTxt = new Text(*life, "assets/font/Call me maybe.ttf", 36, Text::BLENDED, to_string(PenguinBody::player->GetHP()) + " HP", RED);
    CameraFollower* scoreFollow = new CameraFollower(*life);
    life->AddComponent(scoreFollow);
    life->AddComponent(lifeTxt);
    AddObject(life);



    quitRequested = false;

    backgroundMusic = Music("assets/audio/stageState.ogg");
    backgroundMusic.Play();
}

StageState::~StageState(){
    objectArray.clear();
}

void StageState::Start(){


    LoadAssets();

    //Calls Start of every object already in the vector
    for(unsigned int i=0;i<objectArray.size();i++){
        objectArray[i]->Start();
    }

    started = true;
}

void StageState::LoadAssets(){
    //Load things the game need
        //Images
    Resources::GetImage("assets/img/ocean.jpg");
    Resources::GetImage("assets/img/tileset.png");
    Resources::GetImage("assets/img/alien.png");
    Resources::GetImage("assets/img/aliendeath.png");
    Resources::GetImage("assets/img/minion.png");
    Resources::GetImage("assets/img/miniondeath.png");
    Resources::GetImage("assets/img/penguin.png");
    Resources::GetImage("assets/img/penguindeath.png");
    Resources::GetImage("assets/img/cubngun.png");
        //Sounds
    Resources::GetSound("assets/audio/boom.wav");
        //Music
    Resources::GetMusic("assets/audio/stageState.ogg");
}

void StageState::Update(float dt){
    InputManager& input = InputManager::GetInstance();

    //Update camera position
    Camera::Update(dt);

    //Check user request to end program
    if(input.QuitRequested()){
        quitRequested = true;
    }

    if(input.KeyPress(ESC)){
        popRequested = true;
    }

    for (unsigned int i = 0; i < objectArray.size();){
        //Update hp text
        Text *hp = (Text*)objectArray[i].get()->GetComponent("Text").get();
        if(hp != nullptr){
            if(PenguinBody::player != nullptr){
                hp->SetText(to_string(PenguinBody::player->GetHP()) + " HP");
            }
        }

        objectArray[i]->Update(dt);

        if (objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin()+i);
        }
        else{
            i++;
        }
    }

    for (unsigned int i = 0; i < objectArray.size();i++){
        for (unsigned int j=i+1;j<objectArray.size();j++) {
            Collider *colA = (Collider*)objectArray[i]->GetComponent("Collider").get();
            Collider *colB = (Collider*)objectArray[j]->GetComponent("Collider").get();
            if(colA && colB){
                if(Collision::IsColliding(colA->box, colB->box, objectArray[i]->angleDeg, objectArray[j]->angleDeg)){
                    objectArray[i]->NotifyCollision(*objectArray[j]);
                    objectArray[j]->NotifyCollision(*objectArray[i]);
                }
            }

        }
    }
    //Check winning and losing contitions
    if(Alien::alienCount == 0){
        GameData::playerVictory = true;
        popRequested = true;
        EndState *endState = new EndState();
        Game::GetInstance().Push(endState);
        //backgroundMusic.Stop();

    }
    if(PenguinBody::player == nullptr){
        GameData::playerVictory = false;
        popRequested = true;
        EndState *endState = new EndState();
        Game::GetInstance().Push(endState);
        //backgroundMusic.Stop();
    }
}

void StageState::Render(){
    for (int layer=0; layer<N_LAYERS;layer++) {         //Render objects with layer priority
        for (unsigned int i = 0; i < objectArray.size(); i++){
            if(objectArray[i]->layer == -1){            //TileMap, a multilayer GameObject
                objectArray[i]->layer = layer;
                objectArray[i]->Render();
            }
            else{
                if(layer == objectArray[i]->layer){
                    objectArray[i]->Render();
                }
            }

        }
    }

}

void StageState::Pause(){}

void StageState::Resume(){}
