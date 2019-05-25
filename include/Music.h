
#ifndef MUSIC_H
#define MUSIC_H


#include <memory>
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

using namespace std;

class Music
{
public:
    Music();
    Music(std::string file);
    ~Music();
    void Play(int times=-1);
    void Stop(int msToStop=1500);
    void Open(std::string file);
    bool IsOpen();

private:
    shared_ptr<Mix_Music> music;
};

#endif
