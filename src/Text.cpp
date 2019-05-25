#include "Text.h"



Text::Text(GameObject &associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color, float time) : Component (associated){
    //Variable initialization
    this->fontFile = fontFile;
    this->fontSize = fontSize;
    this->style = style;
    this->text = text;
    this->color = color;
    texture = nullptr;

    this->time = time;
    showTimer = Timer();
    showText = true;

    //Create texture
    RemakeTexture();
}

Text::~Text(){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt){
    if(time > 0){       //If a time (!=0) to blink was passed, update showText with the current time
        if(showTimer.Get() > time){
            showTimer.Restart();
            showText = !showText;
        }
        else {
            showTimer.Update(dt);
        }
    }
}

void Text::Render(){
    //Check if there is a texture to render
    if(texture==nullptr){return;}
    if(showText){
        //Set source clip
        SDL_Rect srcRect;
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = associated.box.w;
        srcRect.h = associated.box.h;
        //Set destination clip
        SDL_Rect dstRect;
        dstRect.x = associated.box.x - Camera::pos.x;
        dstRect.y = associated.box.y - Camera::pos.y;
        dstRect.w = associated.box.w;
        dstRect.h = associated.box.h;

        //Render text
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &srcRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    }

}

bool Text::Is(string type){
    return (!type.compare("Text"));
}


void Text::SetText(string text){
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color){
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style){
    this->style = style;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize){
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::SetFontFile(string fontFile){
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::RemakeTexture(){
    //Destroy possible existing texture
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }

    //Load new font
    font = Resources::GetFont(fontFile, fontSize);
    if(font == nullptr){   //Exit program if not able to load font
        exit(EXIT_FAILURE);
    }

    //Create texture from font
    SDL_Surface* surf;
    switch (style) {
        case SOLID:
            surf =  TTF_RenderText_Solid(font.get(), text.c_str(), color);
            break;
        case SHADED:
            surf =  TTF_RenderText_Shaded(font.get(), text.c_str(), color, BLACK);
            break;
        case BLENDED:
            surf =  TTF_RenderText_Blended(font.get(), text.c_str(), color);
            break;
    }

    //Get texture from surface
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surf);
    associated.box.w = surf->w;
    associated.box.h = surf->h;
    //Delete temporary surface
    SDL_FreeSurface(surf);
}







