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
		
	pdead[0] = {98, 6, 25, 25};
	pdead[1] = {128, 6, 29, 25};
	pdead[2] = {160, 6, 29, 25};
	pdead[3] = {192, 6, 29, 25};
	pdead[4] = {224, 6, 29, 25};
	pdead[5] = {256, 6, 29, 25};
	pdead[6] = {288, 6, 29, 25};
	pdead[7] = {320, 6, 29, 25};
	pdead[8] = {352, 6, 29, 25};
	pdead[9] = {384, 6, 29, 25};
	pdead[10] = {421, 6, 29, 25};
}

bool pmove(int dir) {
	if(pcanmove(pacx + dpx[dir], pacy + dpy[dir], pacx + dpx[dir] + 25, pacy + dpy[dir] + 25)) {
		pacx += dpx[dir];
		pacy += dpy[dir];
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

void pdie(LTexture &gSrc) {
	gSrc.render(pacx, pacy + 3, &pdead[death / 12]);
}

void scan() {
	xy[0] = {pacx, pacy};
	dd[pacx + 26][pacy] = 1;
	cnt = 1;
	for(int times = 0; times < cnt; ++times) {
		int x = xy[times].first + 26;
		int y = xy[times].second;
		if(d[x][y] == chaseradius) break;
		for(int i = 0; i < 4; ++i) if(ve[x][y][i]) if(!dd[x + dpx[i]][y + dpy[i]]) {
			int x2 = x + dpx[i];
			if(x2 > SCREEN_WIDTH + 26) x2 = 0;
			else if(x2 < 0) x2 = SCREEN_WIDTH + 26;
			dd[x2][y + dpy[i]] = 1 + (i ^ 2);
			d[x2][y + dpy[i]] = d[x][y] + 1;
			xy[cnt++] = {x2 - 26, y + dpy[i]};
		}
	}
}

void unscan() {
	for(int i = 0; i < cnt; ++i) {
		dd[xy[i].first + 26][xy[i].second] = 0;
		d[xy[i].first + 26][xy[i].second] = 0;
	}
}

void pstart(LTexture &gSrc) {
	gSrc.render(pacx, pacy, &Pac[0][2]);
}