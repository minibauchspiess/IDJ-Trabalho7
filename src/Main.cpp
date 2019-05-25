//#define DEBUG

#include "Game.h"
#include "Rect.h"
#include "Vec2.h"
#include "Gameobject.h"

#include "TitleState.h"

#include <vector>

#include <iostream>

using namespace std;

void teste(shared_ptr<GameObject> a){
    cout<<a.use_count()<<endl;
}

int main(int argc, char** argv)
{


    Game& game = Game::GetInstance();
    TitleState *initState = new TitleState();

    game.Push(initState);
    game.Run();

    return 0;
}





