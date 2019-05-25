#include "Resources.h"

unordered_map<string, shared_ptr<SDL_Texture>> 	Resources::imageTable;
unordered_map<string, shared_ptr<Mix_Music>> 	Resources::musicTable;
unordered_map<string, shared_ptr<Mix_Chunk>> 	Resources::soundTable;
unordered_map<string, shared_ptr<TTF_Font>> Resources::fontTable;


Resources::Resources()
{

}

shared_ptr<SDL_Texture> Resources::GetImage(string file){

    unordered_map<string, shared_ptr<SDL_Texture>>::iterator i;
    SDL_Texture* texture;
    Game& instance = Game::GetInstance();

    i = imageTable.find(file);
    //If the file has already been opened, return its corresponding texture
    if(i!=imageTable.end()){
        return i->second;
    }
    //Or else, open file, create texture and alocate in imageTable
    texture = IMG_LoadTexture(instance.GetRenderer(), file.c_str());


    //Lambda function to destruct texture
    auto textDest = [](SDL_Texture* texture){
        SDL_DestroyTexture(texture);
    };

    //Create shared pointer with destructor in lambda function
    shared_ptr<SDL_Texture> shTexture(texture, textDest);


    if (shTexture == nullptr){
        cout<<"Error loading image"<<endl;
        cout<<SDL_GetError()<<endl;
    }
    else{
        imageTable[file] = shTexture;
    }

    return shTexture;
}

void Resources::ClearImages(){
    unordered_map<string, shared_ptr<SDL_Texture>>::iterator i;

    //Find and destroy unique pointers in the table
    for(i = imageTable.begin(); i != imageTable.end();){
        if (i->second.unique()) {
            i = imageTable.erase(i);
        }
        else{
            i++;
        }
    }
}

shared_ptr<TTF_Font> Resources::GetFont(string file, int ptsize){
    unordered_map<string, shared_ptr<TTF_Font>>::iterator i;
    TTF_Font* font;

    string tableFile = file + to_string(ptsize);    //Add the number to the file end, as it will be stored in the table

    i = fontTable.find(tableFile);
    //If the file has already been opened, return its corresponding font
    if(i!=fontTable.end()){
        return i->second;
    }


    //Or else, open file, create texture and alocate in fontTable
    font = TTF_OpenFont(file.c_str(), ptsize);

    //Lambda function to destruct font
    auto fontDest = [](TTF_Font* font){
        TTF_CloseFont(font);
    };

    //Create shared pointer with destructor in lambda function
    shared_ptr<TTF_Font> shFont(font, fontDest);

    if (shFont == nullptr){
        cout<<"Error loading font"<<endl;
        cout<<SDL_GetError()<<endl;
    }
    else{
        fontTable[tableFile] = shFont;
    }

    return shFont;
}



void Resources::ClearFonts(){
    unordered_map<string, shared_ptr<TTF_Font>>::iterator i;

    //Find and destroy unique pointers in the table
    for(i = fontTable.begin(); i != fontTable.end();){
        if (i->second.unique()) {
            i = fontTable.erase(i);
        }
        else{
            i++;
        }
    }
}



shared_ptr<Mix_Music> Resources::GetMusic(string file){
    unordered_map<string, shared_ptr<Mix_Music>>::iterator i;
    Mix_Music* music;

    i = musicTable.find(file);
    //If the file has already been opened, return its corresponding music
    if(i!=musicTable.end()){
        return i->second;
    }

    //Or else, open file, create music and alocate in musicTable
    music = Mix_LoadMUS(file.c_str());

    //Lambda function to destroy music
    auto musicDest = [](Mix_Music* music){
        Mix_FreeMusic(music);
    };

    //Create shared pointer with destructor in lambda function
    shared_ptr<Mix_Music> shMusic(music, musicDest);


    if (music == nullptr){
        cout<<"No music was loaded"<<endl;
    }
    else{
        musicTable[file] = shMusic;
    }

    return shMusic;
}

void Resources::ClearMusics(){
    unordered_map<string, shared_ptr<Mix_Music>>::iterator i;

    //Find and destroy unique pointers in the table
    for(i = musicTable.begin(); i != musicTable.end();){
        if (i->second.unique()) {
            i = musicTable.erase(i);
        }
        else{
            i++;
        }
    }
}

shared_ptr<Mix_Chunk> Resources::GetSound(string file){
    unordered_map<string, shared_ptr<Mix_Chunk>>::iterator i;
    Mix_Chunk* chunk;

    i = soundTable.find(file);
    //If the file has already been opened, return its corresponding sound
    if(i!=soundTable.end()){
        return i->second;
    }

    //Or else, open file, create sound and alocate in soundTable
    chunk = Mix_LoadWAV(file.c_str());

    //Lambda function to destroy sound
    auto soundDest = [](Mix_Chunk* sound){
        Mix_FreeChunk(sound);
    };

    //Create shared pointer with destructor in lambda function
    shared_ptr<Mix_Chunk> shSound(chunk, soundDest);



    if (chunk == nullptr){
        cout<<"Sound file "<<file<<" failed to open"<<endl;
    }
    else{
        soundTable[file] = shSound;
    }

    return shSound;
}

void Resources::ClearSounds(){
    unordered_map<string, shared_ptr<Mix_Chunk>>::iterator i;

    //Find and destroy unique pointers in the table
    for(i = soundTable.begin(); i != soundTable.end();){
        if (i->second.unique()) {
            i = soundTable.erase(i);
        }
        else{
            i++;
        }
    }
}


















