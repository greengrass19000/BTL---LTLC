

//this include :[number][dirs][odd/even][state]
void Die(int num) { 
	ms[num] = 0; 
	Mix_PlayMusic(ghosteaten, 0);
	ghosteating = 60;
	point += stackpoint[stack++];
	scared[num] = 0;
	beingeatenghost = num;
}



void Revived(int num) { ms[num] = 1; }

void initmonster() {
	int x = 2;
	int y = 130;
	int w = 28;
	int h = 28;
	for(int i = 0; i <= 96; i += 32) {
		int order = i / 32;
		bool lrun = 0;
		for(int j = 0; j <= 224; j += 32) {
			int lDir = j / 64;
			lrun ^= 1;
			Mon[order][lDir][lrun&1][1] = {x + j, y + i, w, h};
		}
	}
	for(int i = 0; i < 4; ++i) {
		Mon[i][0][0][2] = {258, 130, 28, 28};
		Mon[i][0][1][2] = {290, 130, 28, 28};
		Mon[i][1][0][2] = {322, 130, 28, 28};
		Mon[i][1][1][2] = {354, 130, 28, 28};
	}
	for(int i = 0; i < 4; ++i) {
		Mon[i][0][0][0]  = {258, 162, 28, 28};
		Mon[i][1][0][0]  = {290, 162, 28, 28};
		Mon[i][2][0][0]  = {322, 162, 28, 28};
		Mon[i][3][0][0]  = {354, 162, 28, 28};
	}
	mx[0] = 210; my[0] = 218;
	mx[2] = 176; my[2] = 266;
	mx[1] = 210; my[1] = 266;
	mx[3] = 243; my[3] = 266;
	
	ghosteatenpoint[0] = {0, 266, 30, 14};
	ghosteatenpoint[1] = {32, 266, 30, 14};
	ghosteatenpoint[2] = {64, 266, 30, 14};
	ghosteatenpoint[3] = {96, 266, 32, 14};
	
	for(int i = 0; i < 8; ++i) 
		ifruit[i] = {68 + i * 32, 98, 24, 28};
	fruitpoint[0] = 100;
	fruitpoint[1] = 300;
	fruitpoint[2] = 500;
	fruitpoint[3] = 700;
	fruitpoint[4] = 1000;
	fruitpoint[5] = 2000;
	fruitpoint[6] = 3000;
	fruitpoint[7] = 5000;
}

void getmonster(LTexture &gSrc, int num, int frame) {
	if(abs(mx[num] - pacx + 1) + abs(my[num] - pacy + 1) < 2) {
		if(!scared[num] && ms[num] != 0){
			death = 1;
			Mix_PlayMusic(sdead1, 0);
		} else if(ms[num]) {
			Die(num);
		}
	} 
	if(!ms[num]) {
		gSrc.render(mx[num], my[num], &Mon[num][mdir[num]][0][0]);
	} else {
		if(scared[num]) {
			if(scared[num] && beinggod < 180 && (beinggod % 24 < 12)) gSrc.render(mx[num], my[num], &Mon[num][1][(frame / 10) & 1][2]);
			else gSrc.render(mx[num], my[num], &Mon[num][0][(frame / 10) & 1][2]);
		} else {
			gSrc.render(mx[num], my[num], &Mon[num][mdir[num]][(frame / 10) & 1][1]);
		}
	}
}

void mmove2(int num) {
	mx[num] += dmx[mdir[num]];
	my[num] += dmy[mdir[num]];
	if(mx[num] > SCREEN_WIDTH) mx[num] = -27;
	else if(mx[num] < -27) mx[num] = SCREEN_WIDTH;
}

bool mmove3(int num) {
	if(mcanmove(mx[num] + dmx[mdir[num]], my[num] + dmy[mdir[num]], mx[num] + 27 + dmx[mdir[num]], my[num] + 27 + dmy[mdir[num]])) {
		mx[num] += dmx[mdir[num]];
		my[num] += dmy[mdir[num]];
		return true;
	}
	return false;
}

void mmove(int num) {
//	165, 245, 282, 314 the box 
//  210 266 expected position if monster is in the box
	if(inbox(num)) {
		if(ms[num] == 0) {
			if(my[num] > 266) { mdir[num] = 2; mmove3(num); return;} 
			if(my[num] < 266) { mdir[num] = 3; mmove3(num); mmove3(num); mmove3(num); return;} 
			Revived(num);
			mdir[num] = 2; mmove3(num); return;
		}
		if(mx[num] < 210) { mdir[num] = 0; mmove3(num); return;} 
		if(mx[num] > 210) { mdir[num] = 1; mmove3(num); return;} 
		mdir[num] = 2; mmove3(num); return;
	}
	
	if(ms[num] == 0) {
		mdir[num] = convert[boxtrace[mx[num] + 27][my[num] + 1] - 1];
		mmove2(num);
		mdir[num] = convert[boxtrace[mx[num] + 27][my[num] + 1] - 1];
		mmove2(num);
		mdir[num] = convert[boxtrace[mx[num] + 27][my[num] + 1] - 1];
		mmove2(num);
		return;
	}
	
	if(!scared[num] && dd[mx[num]+27][my[num]+1]) {
		mdir[num] = convert[dd[mx[num]+27][my[num]+1] - 1];
		mmove2(num);
		return;
	}
	
	int tmp = 0;
	int qq[4];
	for(int i = 0; i < 4; ++i)  if(ve[mx[num]+27][my[num]+1][i]) qq[tmp++] = i;

	if(tmp == 2) {
		if(qq[0] != ( qq[1] ^ 2) ) {
			mdir[num] = convert[qq[rand() % 2]];
			mmove2(num);
			return;
		} else {
			if(mdir[num] != convert[qq[0]] && mdir[num] != convert[qq[1]]) 
				mdir[num] = convert[qq[rand()%2]];
			mmove2(num);
			return;
		}
	}
	int tmp2 = mdir[num] ^ 1;
	if(!tmp) return;
	do {
		mdir[num] = convert[qq[rand() % tmp]];
	} while(mdir[num] == tmp2);
	mmove2(num);
}