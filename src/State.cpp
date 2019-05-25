#include "State.h"

State::State()
{
    //Variable initialization
    popRequested = 0;
    quitRequested = 0;
    started = 0;
}

State::~State(){
    objectArray.clear();
}

weak_ptr<GameObject> State::AddObject(GameObject* go){
    //Create shared pointer with given pointer
    shared_ptr<GameObject> shgo(go);

    //Insert it in the vector of game objects
    objectArray.push_back(shgo);

    //Start the new object
    if(started) shgo->Start();

    //Return it as a weak pointer
    weak_ptr<GameObject> wgo(shgo);
    return wgo;
}


weak_ptr<GameObject> State::GetObjectPtr(GameObject *go){

    weak_ptr<GameObject> wgo;

    //Look for the game object in the vector of game objects
    for(unsigned i=0; i<objectArray.size(); i++) {
        if(objectArray[i].get() == go){
            wgo = objectArray[i];
            return wgo;
        }
    }

    return wgo;
}

void State::Start(){
    //Add state to the stack
}

void State::Pause(){
    //Pause state
}

void State::Resume(){
    //Resume state (when upper state is removed from stack)
}

void State::Update(float dt){}

void State::Render(){}

bool State::PopRequested(){
    return popRequested;
}

bool State::QuitRequested(){
    return quitRequested;
}

void State::StartArray(){
    for (unsigned int i=0; i<objectArray.size(); i++) {
        objectArray[i]->Start();
    }
}

void State::UpdateArray(float dt){
    for (unsigned int i=0; i<objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray(){
    for (unsigned int i=0; i<objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}







