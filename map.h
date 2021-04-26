void showpoint(LTexture &gSrc, int p, int lx, int ly) {
	while(p) {
		int tmp = p % 10;
		p /= 10;
		lx -= 8;
		gSrc.render(lx, ly, &num[tmp]);
	}
}

void showlive(LTexture &gSrc) {
	if(lives < 4) {
		int lx = 5;
		int ly = 547;
		for(int i = 0; i < lives; ++i) {
			gSrc.render(lx + i * 22, ly, &plives);
		}
	} else {
		gSrc.render(5, 547, &plives2);
		showpoint(gSrc, lives, 63, 554);
	}
}

void dot(LTexture &gSrc) {
	SDL_Rect tmp = {320, 59, 4, 4};
	for(int i = 1; i < 241; ++i) {
		gSrc.render(sdot[i].first, sdot[i].second + 47, &tmp);
	}
}

void initwall() {
	ob[0] = {-27, 47, 480, 58};
	ob[1] = {-27, 47, 10, 266};
	ob[2] = {437, 47, 480, 266};
	ob[3] = { 213, 58, 234, 122 };
	ob[4] = { 117, 85, 186, 122 };
	ob[5] = { 261, 85, 330, 122 };
	ob[6] = { 357, 85, 410, 122 };
	ob[7] = { 37, 149, 90, 170 };
	ob[8] = { 117, 149, 138, 266 };
	ob[9] = { 165, 149, 282, 170 };
	ob[10] = { 309, 149, 330, 266 };
	ob[11] = { 357, 149, 410, 170 };
	ob[12] = { -27, 197, 90, 266 };
	ob[13] = { 137, 197, 186, 218 };
	ob[14] = { 213, 170, 234, 218 };
	ob[15] = { 261, 197, 309, 218 };
	ob[16] = { 357, 197, 480, 266 };
	ob[22] = { -27, 293, 90, 362 };
	ob[23] = { -27, 293, 10, 546 };
	ob[24] = { 117, 293, 138, 362 };
	ob[25] = { 309, 293, 330, 362 };
	ob[26] = { 357, 293, 480, 362 };
	ob[27] = { 437, 293, 480, 546 };
	ob[28] = { 165, 341, 282, 362 };
	ob[29] = { 213, 362, 234, 410 };
	ob[30] = { 37, 389, 90, 410 };
	ob[31] = { 117, 389, 186, 410 };
	ob[32] = { 261, 389, 330, 410 };
	ob[33] = { 357, 389, 410, 410 };
	ob[34] = { 69, 410, 90, 458 };
	ob[35] = { 357, 410, 378, 458 };
	ob[36] = { 10, 437, 42, 458 };
	ob[37] = { 117, 437, 138, 485 };
	ob[38] = { 165, 437, 282, 458 };
	ob[39] = { 309, 437, 330, 485 };
	ob[17] = { 405, 437, 437, 458 };
	ob[18] = { 213, 458, 234, 506 };
	ob[19] = { 37, 485, 186, 506 };
	ob[20] = { 261, 485, 410, 506 };
	ob[21] = { -27, 533, 480, 546 };
	ob[40] = { 37, 85, 90, 122 };
}

bool mcanmove(int x, int y, int z, int t) {
	for(int i = 0; i < 41; ++i) 
		if(intersect(x, z, ob[i].x + 1, ob[i].z - 1) && intersect(y, t, ob[i].y + 1, ob[i].t - 1)) 
			return false;
	if(intersect(x, z, 166, 209) && intersect(y, t, 246, 258))
		return false;
	if(intersect(x, z, 238, 281) && intersect(y, t, 246, 258))
		return false;
	if(intersect(x, z, 166, 177) && intersect(y, t, 259, 313))
		return false;
	if(intersect(x, z, 270, 281) && intersect(y, t, 259, 313)) 
		return false;
	if(intersect(x, z, 166, 281) && intersect(y, t, 302, 313)) 
		return false;
	return true;
}

bool mcanmove2(int x, int y, int z, int t) {
	for(int i = 0; i < 41; ++i) 
		if(intersect(x, z, ob[i].x + 1, ob[i].z - 1) && intersect(y, t, ob[i].y + 1, ob[i].t - 1)) 
			return false;
	if(intersect(x, z, 166, 281) && intersect(y, t, 246, 313))
		return false;
	return true;
}

void initnumber() {
	num[0] = {205, 378, 8, 8};
	num[1] = {216, 378, 8, 8};
	num[2] = {225, 378, 8, 8};
	num[3] = {235, 378, 8, 8};
	num[4] = {245, 378, 8, 8};
	num[5] = {255, 378, 8, 8};
	num[6] = {265, 378, 8, 8};
	num[7] = {275, 378, 8, 8};
	num[8] = {285, 378, 8, 8};
	num[9] = {295, 378, 8, 8};
}


void checkdot(int pacx, int pacy) {
	pacy -= 47;
	pacx += 11;
	if(pacx >= 447 || pacx < 0) return;
	if(trace[pacx][pacy] ) {
		sdot[ trace[pacx][pacy] ] = {-10, -10};
		trace[pacx][pacy] = 0;
		point += 10;
		if(doteatean & 1) Mix_PlayChannel( -1, sodd, 0 );
		else Mix_PlayChannel(-1, seven, 0);
		++doteatean;
		return;
	}
	
	pacx -= 11;
	pacy += 10;
	if(pacx < 0) return;
	if(trace[pacx][pacy] ) {
		sdot[ trace[pacx][pacy] ] = {-10, -10};
		trace[pacx][pacy] = 0;
		point += 10;
		if(doteatean & 1) Mix_PlayChannel( -1, sodd, 0 );
		else Mix_PlayChannel(-1, seven, 0);
		++doteatean;
		return;
	}
	
	pacx+= 22;
	if(pacx >= 447) return;
	if(trace[pacx][pacy] ) {
		sdot[ trace[pacx][pacy] ] = {-10, -10};
		trace[pacx][pacy] = 0;
		point += 10;
		if(doteatean & 1) Mix_PlayChannel( -1, sodd, 0 );
		else Mix_PlayChannel(-1, seven, 0);
		++doteatean;
		return;
	}
	
	pacx -= 11;
	pacy += 11;
	if(trace[pacx][pacy] ) {
		sdot[ trace[pacx][pacy] ] = {-10, -10};
		trace[pacx][pacy] = 0;
		point += 10;
		if(doteatean & 1) Mix_PlayChannel( -1, sodd, 0 );
		else Mix_PlayChannel(-1, seven, 0);
		++doteatean;
		return;
	}
	
}