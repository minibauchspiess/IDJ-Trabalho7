#ifndef TEXT_H
#define TEXT_H

//Defines de cores
#define BLACK {0,0,0,0}
#define WHITE {255,255,255,0}
#define RED {255,0,0,0}
#define GREEN {0,255,0,0}
#define BLUE {0,0,255,0}


#define INCLUDE_SDL_TTF
#include "SDL_include.h"

#include "Gameobject.h"
#include "Component.h"

#include "Vec2.h"
#include "Rect.h"
#include "Camera.h"
#include "Resources.h"
#include "Timer.h"

using namespace std;

class Text : public Component
{
public:
    enum TextStyle{SOLID, SHADED, BLENDED};

    Text(GameObject &associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color, float time=0);
    ~Text();

    void Update(float dt);
    void Render();
    bool Is(string type);


    void SetText(string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontFile(string fontFile);
    void SetFontSize(int fontSize);

    bool showText;

private:
    void RemakeTexture();

    shared_ptr<TTF_Font> font;
    SDL_Texture *texture;

    string text;
    TextStyle style;
    string fontFile;
    int fontSize;
    SDL_Color color;

    float time;
    Timer showTimer;
};

#endif // TEXT_H











