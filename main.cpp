/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include "Burbuja.h"
#include <list>
#include <stdlib.h>

using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

SDL_Surface *load_image( std::string filename )
{
    return IMG_Load( filename.c_str() );
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Press an Arrow Key", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the background image
    background = load_image( "background.png" );

    //Open the font
    font = TTF_OpenFont( "lazy.ttf", 72 );

    //If there was a problem in loading the background
    if( background == NULL )
    {
        return false;
    }

    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( background );

    //Close the font
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

void elJuego()
{
    srand (time(NULL));
    bool quit=false;
    list<Burbuja*>burbujas;
    //While the user hasn't quit
    int frame=0;
    while( quit == false )
    {
        frame++;
        if(frame%100==0)
        {
            burbujas.push_back(new Burbuja(load_image("burbuja.png"),
                screen,0,rand() % SCREEN_HEIGHT ));
        }
        int click_x=-1;
        int click_y=-1;
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }

            //If a mouse button was pressed
            if( event.type == SDL_MOUSEBUTTONDOWN )
            {
                //If the left mouse button was pressed
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    click_x=event.button.x;
                    click_y=event.button.y;
                }
            }
        }

        //Apply the background
        apply_surface( 0, 0, background, screen );

        list<Burbuja*>::iterator i=burbujas.begin();
        while(i!=burbujas.end())
        {
            if((*i)->borrar)
            {
                Burbuja*temp = (*i);
                i = burbujas.erase(i);
                delete temp;
            }else
            {
                (*i)->dibujar();
                (*i)->logica(click_x,click_y);
            }
            i++;
        }

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return;
        }
    }
}

void menu()
{
    int frame=0;
    SDL_Surface* menu_bg=load_image("menu.png");
    bool quit=false;
    while( quit == false )
    {
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
            if( event.type == SDL_KEYDOWN
                && event.key.keysym.sym == SDLK_RETURN)
            {
                elJuego();
            }
        }
        apply_surface( 0, 0, menu_bg, screen );
        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return;
        }
    }
}

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    //El juego
    menu();

    //Clean up
    clean_up();

    return 0;
}
