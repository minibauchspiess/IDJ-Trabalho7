#ifndef RESOURCES_H
#define RESOURCES_H

#include <unordered_map>
#include "Game.h"
#include "Music.h"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

using namespace std;

class Resources
{
public:
    Resources();

    static shared_ptr<SDL_Texture> GetImage(string file);
    static void ClearImages();

    static shared_ptr<Mix_Music> GetMusic(string file);
    static void ClearMusics();

    static shared_ptr<Mix_Chunk> GetSound(string file);
    static void ClearSounds();

    static shared_ptr<TTF_Font> GetFont(string file, int ptsize);
    static void ClearFonts();


private:
    static unordered_map<string, shared_ptr<SDL_Texture>> imageTable;
    static unordered_map<string, shared_ptr<Mix_Music>> musicTable;
    static unordered_map<string, shared_ptr<Mix_Chunk>> soundTable;
    static unordered_map<string, shared_ptr<TTF_Font>> fontTable;
};

#endif // RESOURCES_H
