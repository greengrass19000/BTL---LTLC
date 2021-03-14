SDL_Rect Pac[ 4 ][ 4 ];
int pdir = 0;
int tmpdir = -1;
// int pacx = 209;
// int pacy = 411;
int pacx = 379;
int pacy = 411;
int dpx[] = {1, 0, -1, 0};
int dpy[] = {0, 1, 0, -1};
bool dirchanged = false;
SDL_Rect sdead[11];
void initpacman() {
	//left
	Pac[ 2 ][ 0 ].x =  2;
	Pac[ 2 ][ 0 ].y =  34;
	Pac[ 2 ][ 0 ].w =  26;
	Pac[ 2 ][ 0 ].h =  26;

	Pac[ 2 ][ 1 ].x =  34;
	Pac[ 2 ][ 1 ].y =  34;
	Pac[ 2 ][ 1 ].w =  26;
	Pac[ 2 ][ 1 ].h =  26;

	Pac[ 2 ][ 2 ].x =  66;
	Pac[ 2 ][ 2 ].y =  2;
	Pac[ 2 ][ 2 ].w =  26;
	Pac[ 2 ][ 2 ].h =  26;

	Pac[ 2 ][ 3 ].x = 34;
	Pac[ 2 ][ 3 ].y =  34;
	Pac[ 2 ][ 3 ].w =  26;
	Pac[ 2 ][ 3 ].h =  26;
	
	//right
	Pac[ 0 ][ 0 ].x =  2;
	Pac[ 0 ][ 0 ].y =  2;
	Pac[ 0 ][ 0 ].w =  26;
	Pac[ 0 ][ 0 ].h =  26;

	Pac[ 0 ][ 1 ].x =  34;
	Pac[ 0 ][ 1 ].y =  2;
	Pac[ 0 ][ 1 ].w =  26;
	Pac[ 0 ][ 1 ].h =  26;

	Pac[ 0 ][ 2 ].x =  66;
	Pac[ 0 ][ 2 ].y =  2;
	Pac[ 0 ][ 2 ].w =  26;
	Pac[ 0 ][ 2 ].h =  26;

	Pac[ 0 ][ 3 ].x = 34;
	Pac[ 0 ][ 3 ].y =  2;
	Pac[ 0 ][ 3 ].w =  26;
	Pac[ 0 ][ 3 ].h =  26;	
	
	//down
	Pac[ 1 ][ 0 ].x =  2;
	Pac[ 1 ][ 0 ].y =  98;
	Pac[ 1 ][ 0 ].w =  26;
	Pac[ 1 ][ 0 ].h =  26;

	Pac[ 1 ][ 1 ].x =  34;
	Pac[ 1 ][ 1 ].y =  98;
	Pac[ 1 ][ 1 ].w =  26;
	Pac[ 1 ][ 1 ].h =  26;

	Pac[ 1 ][ 2 ].x =  66;
	Pac[ 1 ][ 2 ].y =  2;
	Pac[ 1 ][ 2 ].w =  26;
	Pac[ 1 ][ 2 ].h =  26;

	Pac[ 1 ][ 3 ].x = 34;
	Pac[ 1 ][ 3 ].y =  98;
	Pac[ 1 ][ 3 ].w =  26;
	Pac[ 1 ][ 3 ].h =  26;	
	
	//up
	Pac[ 3 ][ 0 ].x =  2;
	Pac[ 3 ][ 0 ].y =  66;
	Pac[ 3 ][ 0 ].w =  26;
	Pac[ 3 ][ 0 ].h =  26;

	Pac[ 3 ][ 1 ].x =  34;
	Pac[ 3 ][ 1 ].y =  66;
	Pac[ 3 ][ 1 ].w =  26;
	Pac[ 3 ][ 1 ].h =  26;

	Pac[ 3 ][ 2 ].x =  66;
	Pac[ 3 ][ 2 ].y =  2;
	Pac[ 3 ][ 2 ].w =  26;
	Pac[ 3 ][ 2 ].h =  26;

	Pac[ 3 ][ 3 ].x = 34;
	Pac[ 3 ][ 3 ].y =  66;
	Pac[ 3 ][ 3 ].w =  26;
	Pac[ 3 ][ 3 ].h =  26;	
		
	sdead[0] = {98, 6, 25, 25};
	sdead[0] = {128, 6, 29, 25};
	sdead[0] = {160, 6, 29, 25};
	sdead[0] = {192, 6, 29, 25};
	sdead[0] = {224, 6, 29, 25};
	sdead[0] = {256, 6, 29, 25};
	sdead[0] = {290, 6, 29, 25};
}

bool check(int dir) {
	return true;
}

int px(int dir) {
	return dpx[dir];
}

int py(int dir) {
	return dpy[dir];
}

bool pmove(int dir) {
	if(pcanmove(pacx + px(dir), pacy + py(dir), pacx + px(dir) + 25, pacy + py(dir) + 25)) {
		pacx += px(dir);
		pacy += py(dir);
		return true;
	} 
	return false;
}
void getpacman(int frame, LTexture &gSrc) {
	if(!dirchanged && !pmove(pdir)) frame = 1;
	SDL_Rect* pacman = &Pac[ pdir ][ frame ];
	if(pacx > SCREEN_WIDTH) pacx = -26;
	else if(pacx < -26) pacx = SCREEN_WIDTH;
	gSrc.render( pacx, pacy, pacman);
	dirchanged = false;
	return;
}

void changedir(int newdir) {
	if(newdir == pdir) {
		return;
	}
	if(pmove(newdir)) {
		pdir = newdir;
		dirchanged = true;
		tmpdir = -1;
		return;
	}
	tmpdir = newdir;
	return;
}

void checklastmove() {
	if(tmpdir != -1 && pmove(tmpdir)) {
		pdir = tmpdir;
		dirchanged = true;
		tmpdir = -1;
	}
}


void Die() {
	Mix_PlayMusic(sdead, -1);
	
	//play die.mp3
	
	//display eploding pacman
	
	//lose a live
	
}

void Startup() {
	//spawn in the ball shape
	
}
