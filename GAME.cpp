#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <SDL.h>
#include "SDL2.h"
#include "map.h"
#include "pacman.h"
#include "monster.h"

LTexture gSrc;

bool pcanmove();
bool intersect();
void close() {
    gSrc.free();
    gMap.free();
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
	Mix_Quit();
}

void loadMedia() {
    //Loading success flag
    gSrc.loadFromFile( "src/src.png" );

    //init other headers
    initmonster();
    initpacman();
    initmap();
    initwall();
    initdot();
    initdot2();
    initnumber();
    initsound();
    initbigdot();
}
void gameplay() {
    SDL_Event e;

    int frame = 0;

    //While application is running
	Mix_PlayMusic(sghost1, -1);
    for(; ; ) {
        //Handle events on queue

        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) {
                return;
            }
        }
        if(beinggod) {
			--beinggod;
			if(!beinggod) {
				if(frame % 6000 < 1200) Mix_PlayMusic(sghost1, -1);
				else if(frame % 6000 < 2400) Mix_PlayMusic(sghost2, -1);
				else if(frame % 6000 < 3600) Mix_PlayMusic(sghost3, -1);
				else if(frame % 6000 < 4800) Mix_PlayMusic(sghost4, -1);
				else Mix_PlayMusic(sghost5, -1);
				
			}
        }
        checkdot(pacx, pacy);
		checkbigdot(pacx, pacy);
		checklastmove();
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
        if( currentKeyStates[ SDL_SCANCODE_UP ] ) {
            changedir(3);
        } else if( currentKeyStates[ SDL_SCANCODE_DOWN ] ) {
            changedir(1);
        } else if( currentKeyStates[ SDL_SCANCODE_LEFT ] ) {
            changedir(2);
        } else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ) {
            changedir(0);
        }
        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
        SDL_RenderClear( gRenderer );
        gMap.render( 0, 0 );
        showlive(gSrc);
		showpoint(gSrc, point);
		dot(gSrc);
		if(frame % 24 < 12) bigdot(gSrc);

        getpacman((frame / 4) % 4, gSrc);
        SDL_RenderPresent( gRenderer );
        ++frame;
    }
}
int main( int argc, char* args[] ) {
    //Start up SDL and create window
    init();
    loadMedia();
    gameplay();
    close();
    return 0;
}
