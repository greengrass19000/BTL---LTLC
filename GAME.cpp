#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <SDL.h>
#include <stdlib.h>
#include <time.h> 
#include <iostream>
#include <vector>
#include "SDL2.h"
#include "map.h"
#include "pacman.h"
#include "monster.h"

void close() {
    gSrc.free();
    gMap.free();
    whitemap.free();
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
	Mix_Quit();
}

void loadMedia() {
    //Loading success flag
    gSrc.loadFromFile( "src/src.png" );
    whitemap.loadFromFile( "src/map.png" );
    circle.loadFromFile( "src/map3.png" );
    filler.loadFromFile( "src/map4.png" );
	gMap.loadFromFile( "src/map2.png" );
    //init other headers
    initmonster();
    initpacman();
    initwall();
    initdot();
    initdot2();
    initnumber();
    initsound();
    initbigdot();
    initway();
    initboxtrace();
}

void startgame(){
	SDL_Event e;
    int frame = 0;
	
    for(; ; ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) {
                exit(0);
            }
        }
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 ); SDL_RenderClear( gRenderer );
        gMap.render( 0, 0 );
        pstart(gSrc);
        gSrc.render(202, 325, &READY);
        for(int i = 0; i < 4; ++i) getmonster(gSrc, i, 0);
        showpoint2(gSrc);
        SDL_RenderPresent( gRenderer );
        ++frame;
        if(frame == 252) break;
	}
	return;
}

bool gameplay() {
    SDL_Event e;
    int frame = 0;
    Mix_PlayMusic(sghost1, -1);
	
    for(; ; ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) {
                exit(0);
            }
        }
        if(doteatean >= 240 && bigdoteaten >= 4) return true;
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 ); SDL_RenderClear( gRenderer );
        gMap.render( 0, 0 );
		showlive(gSrc);
		showpoint(gSrc, point, 68, 34);
		///just show something
        if(death) {
			if(death / 16 == 11) {
				death = 0;
				return false;
			}
			if(death == 108) {
				Mix_PlayMusic(sdead2, 0);
			}
			if(death == 119) {
				Mix_PlayMusic(sdead2, 0);
			}
			if(death <= 12 * 11) pdie(gSrc);
			++death;
			SDL_RenderPresent( gRenderer );
			++frame;
			continue;
        }
		///check if a ghost is 'being eaten'
		if(ghosteating) {
			showpoint2(gSrc);
			dot(gSrc);
			for(int i = 0; i < 4; ++i) if(scared[i]) { getmonster(gSrc, i, frame); }
			if((frame + (61 - ghosteating) % 24 < 12)) bigdot(gSrc);
			--ghosteating;
			if(!ghosteating) {
				if(beinggod) Mix_PlayMusic(chaos, -1);
				else switch (bigdoteaten) {
					case 1 : Mix_PlayMusic(sghost1, -1);
					case 2 :  Mix_PlayMusic(sghost2, -1);
					case 3 :  Mix_PlayMusic(sghost3, -1);
					case 4 :  Mix_PlayMusic(sghost4, -1);
					default : Mix_PlayMusic(sghost5, -1);
				}
			}
			SDL_RenderPresent( gRenderer );
			continue;
		}
        ///check 'beingod' pacman
		if(beinggod) {
			--beinggod;
			if(!beinggod) {
				for(int i = 0; i < 4; ++i) scared[i] = 0;
				switch (bigdoteaten) {
					case 1 : Mix_PlayMusic(sghost1, -1);
					case 2 :  Mix_PlayMusic(sghost2, -1);
					case 3 :  Mix_PlayMusic(sghost3, -1);
					case 4 :  Mix_PlayMusic(sghost4, -1);
					default : Mix_PlayMusic(sghost5, -1);
				}
			}
		}
		///usual
		showfruit(frame);
		checkfruit(gSrc, frame);
		scan();
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
		dot(gSrc);
		if(frame % 24 < 12) bigdot(gSrc);
		getpacman((frame / 4) % 4, gSrc);
		
		if(frame % 4 == 0) {
			checkdot(pacx, pacy);
			checkbigdot(pacx, pacy);
			if( currentKeyStates[ SDL_SCANCODE_UP ] ) {
				changedir(3);
			} else if( currentKeyStates[ SDL_SCANCODE_DOWN ] ) {
				changedir(1);
			} else if( currentKeyStates[ SDL_SCANCODE_LEFT ] ) {
				changedir(2);
			} else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ) {
				changedir(0);
			}
			getpacman((frame / 4) % 4, gSrc);
		}

		for(int i = 0; i < 4; ++i) if(scared[i]){ 
			if(frame % 5) mmove(i);
			getmonster(gSrc, i, frame); 
		} else {
			mmove(i);
			getmonster(gSrc, i, frame); 
			if(ms[i] && frame % 15 == 0) mmove(i);
			getmonster(gSrc, i, frame); 
		}
		unscan();
		if(stage == 0 && (frame % 200 < 140 || (frame % 200 >= 160 && frame % 200 <= 180))) {
			SDL_Rect a;
			if(pacy - 50 < 48) {
				a = {0, 98 - pacy, 128, 123};
				circle.render(pacx - 50, 48, &a);

				a = {0, pacy + 73, 447, 471 - pacy};
				filler.render(a.x, a.y, &a);

				a = {0, 48 , pacx - 49, 124 - 98 + pacy};
				filler.render(a.x, a.y, &a);

				a = {pacx + 74, 48, 447, 124 - 98 + pacy};
				filler.render(a.x, a.y, &a);
			} else if(pacy + 73 > 543) {
				a = {0, 0, 128, 124 - (pacy + 73 - 543)};
				circle.render(pacx - 50, pacy - 50, &a);
				a = {0, 48, 447, pacy - 50 - 48};
				filler.render(a.x, a.y, &a);

				a = {0, pacy - 50 , pacx - 49, 544 - pacy + 50};
				filler.render(a.x, a.y, &a);

				a = {pacx + 74, pacy - 50, 447, 544 - pacy + 50};
				filler.render(a.x, a.y, &a);
			} else {
				circle.render(pacx - 50, pacy - 50);
				a = {0, 48, 447, pacy - 50 - 48};
				filler.render(a.x, a.y, &a);

				a = {0, pacy + 73, 447, 471 - pacy};
				filler.render(a.x, a.y, &a);

				a = {0, pacy - 50 , pacx - 49, 124};
				filler.render(a.x, a.y, &a);

				a = {pacx + 74, pacy - 50, 447, 124};
				filler.render(a.x, a.y, &a);
			}
		}
        SDL_RenderPresent( gRenderer );
        ++frame;
    }
}

void endgame2() {
	SDL_Event e;
    int frame = 0;
    for(; ; ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) {
                exit(0);
            }
        }
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 ); SDL_RenderClear( gRenderer );
        gMap.render( 0, 0 );
        gSrc.render(185, 325, &GAMEOVER);
        showpoint(gSrc, point, 68, 34);
        SDL_RenderPresent( gRenderer );
        ++frame;
        if(frame == 252) return;
	}
}

void endgame() {
	Mix_PauseMusic();
	SDL_Event e;
    int frame = 0;
    for(; ; ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) {
                exit(0);
            }
        }
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 ); SDL_RenderClear( gRenderer );
        if(frame % 18 < 9) gMap.render( 0, 0 );
        else whitemap.render( 0, 0);
        pstart(gSrc);
        showpoint(gSrc, point, 68, 34);
        SDL_RenderPresent( gRenderer );
        ++frame;
        if(frame == 252) return;
	}
}

void thegame() {
	for(stage = 0; stage < 3; ++stage) {
		Mix_PlayMusic(sstart, -1);
		if(stage == 0) {
			chaseradius = 100;
		}
		while(lives) {
			reset();
			startgame();
			if(gameplay() == true) {
				break;
			} else {
				--lives;
			}
		}
		if(!lives) {
			endgame2();
			break;
		}
		endgame();
		resetmap();
	}
}

//void showpoint(LTexture &gSrc, int p, int lx, int ly) {
//	while(p) {
//		int tmp = p % 10;
//		p /= 10;
//		lx -= 8;
//		gSrc.render(lx, ly, &num[tmp]);
//	}
//}

///void initnumber() {
///	num[0] = {205, 378, 8, 8};
///	num[1] = {216, 378, 8, 8};
///	num[2] = {225, 378, 8, 8};
///	num[3] = {235, 378, 8, 8};
///	num[4] = {245, 378, 8, 8};
///	num[5] = {255, 378, 8, 8};
///	num[6] = {265, 378, 8, 8};
///	num[7] = {275, 378, 8, 8};
///	num[8] = {285, 378, 8, 8};
///	num[9] = {295, 378, 8, 8};
///}

//void congdiem() {
//	if(aasdfak) diem += asdfka;
//}
int main( int argc, char* args[] ) {
    init();
    loadMedia();
//    showpoint(gSrc, 4567, 100, 100);
//    SDL_RenderPresent( gRenderer );
//    SDL_Delay(2000);
    thegame();
    close();
	return 0;
}