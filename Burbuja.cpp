#include "Burbuja.h"

Burbuja::Burbuja()
{
    //ctor
}

Burbuja::Burbuja(SDL_Surface* surface,SDL_Surface*screen,int x,int y)
{
    this->surface=surface;
    this->screen=screen;
    this->x=x;
    this->y=y;
    this->borrar=false;
}

Burbuja::~Burbuja()
{
    //dtor
}

void Burbuja::dibujar()
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( surface, NULL, screen, &offset );
}

void Burbuja::logica(int click_x, int click_y)
{
    x++;

    if(click_x >= this->x
        && click_x <= this->x + this->surface->w
        && click_y >= this->y
        && click_y <= this->y + this->surface->h)
    {
        borrar=true;
    }
}
