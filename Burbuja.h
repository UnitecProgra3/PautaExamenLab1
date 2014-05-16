#ifndef BURBUJA_H
#define BURBUJA_H

#include <list>
#include <SDL/SDL.h>
using namespace std;

class Burbuja
{
    public:
        SDL_Surface* surface;
        SDL_Surface* screen;
        int x;
        int y;
        bool borrar;

        Burbuja();
        Burbuja(SDL_Surface*surface,SDL_Surface*screen,int x,int y);
        void dibujar();
        void logica(int click_x, int click_y);
        virtual ~Burbuja();
    protected:
    private:
};

#endif // BURBUJA_H
