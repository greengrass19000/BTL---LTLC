LTexture gMap;
SDL_Rect go = {0, 0, 0, 0};
SDL_Rect num[10];
SDL_Rect plives = {262, 36, 19, 21};

int lives = 3;
int point = 0;
int trace[447][576];
void showlive(LTexture &gSrc) {
	int lx = 5;
	int ly = 547;
	for(int i = 0; i < lives; ++i) {
		gSrc.render(lx + i * 22, ly, &plives);
	}
}

void initmap() {
	gMap.loadFromFile( "src/map2.png" );	
}

void showpoint() {

}

void showfruit() {

}

void gameover(LTexture &gSrc) {
//	gSrc.render(lx, ly, )
}
struct rect{int x, y, z, t;} ob[41];
pairr sdot[241];;

void initdot() {
	sdot[ 240 ] = { 22, 22};
	sdot[ 1 ] = { 38, 22};
	sdot[ 2 ] = { 54, 22};
	sdot[ 3 ] = { 70, 22};
	sdot[ 4 ] = { 86, 22};
	sdot[ 5 ] = { 102, 22};
	sdot[ 6 ] = { 118, 22};
	sdot[ 7 ] = { 134, 22};
	sdot[ 8 ] = { 150, 22};
	sdot[ 9 ] = { 166, 22};
	sdot[ 10 ] = { 182, 22};
	sdot[ 11 ] = { 198, 22};
	sdot[ 12 ] = { 246, 22};
	sdot[ 13 ] = { 262, 22};
	sdot[ 14 ] = { 278, 22};
	sdot[ 15 ] = { 294, 22};
	sdot[ 16 ] = { 310, 22};
	sdot[ 17 ] = { 326, 22};
	sdot[ 18 ] = { 342, 22};
	sdot[ 19 ] = { 358, 22};
	sdot[ 20 ] = { 374, 22};
	sdot[ 21 ] = { 390, 22};
	sdot[ 22 ] = { 406, 22};
	sdot[ 23 ] = { 422, 22};
	sdot[ 24 ] = { 22, 38};
	sdot[ 25 ] = { 102, 38};
	sdot[ 26 ] = { 198, 38};
	sdot[ 27 ] = { 246, 38};
	sdot[ 28 ] = { 342, 38};
	sdot[ 29 ] = { 422, 38};
	sdot[ 30 ] = { 22, 70};
	sdot[ 31] = { 102, 54};
	sdot[ 32 ] = { 198, 54};
	sdot[ 33 ] = { 246, 54};
	sdot[ 34 ] = { 342, 54};
	sdot[ 35 ] = { 422, 70};
	sdot[ 36 ] = { 102, 70};
	sdot[ 37 ] = { 198, 70};
	sdot[ 38 ] = { 246, 70};
	sdot[ 39 ] = { 342, 70};
	sdot[ 40 ] = { 22, 86};
	sdot[ 41 ] = { 38, 86};
	sdot[ 42 ] = { 54, 86};
	sdot[ 43 ] = { 70, 86};
	sdot[ 44 ] = { 86, 86};
	sdot[ 45 ] = { 102, 86};
	sdot[ 46 ] = { 118, 86};
	sdot[ 47 ] = { 134, 86};
	sdot[ 48 ] = { 150, 86};
	sdot[ 49 ] = { 166, 86};
	sdot[ 50 ] = { 182, 86};
	sdot[ 51 ] = { 198, 86};
	sdot[ 52 ] = { 214, 86};
	sdot[ 53 ] = { 230, 86};
	sdot[ 54 ] = { 246, 86};
	sdot[ 55 ] = { 262, 86};
	sdot[ 56 ] = { 278, 86};
	sdot[ 57 ] = { 294, 86};
	sdot[ 58 ] = { 310, 86};
	sdot[ 59 ] = { 326, 86};
	sdot[ 60 ] = { 342, 86};
	sdot[ 61 ] = { 358, 86};
	sdot[ 62 ] = { 374, 86};
	sdot[ 63 ] = { 390, 86};
	sdot[ 64 ] = { 406, 86};
	sdot[ 65 ] = { 422, 86};
	sdot[ 66 ] = { 22, 102};
	sdot[ 67 ] = { 102, 102};
	sdot[ 68 ] = { 150, 102};
	sdot[ 69 ] = { 294, 102};
	sdot[ 70 ] = { 342, 102};
	sdot[ 71 ] = { 422, 102};
	sdot[ 72 ] = { 22, 118};
	sdot[ 73 ] = { 102, 118};
	sdot[ 74 ] = { 150, 118};
	sdot[ 75 ] = { 294, 118};
	sdot[ 76 ] = { 342, 118};
	sdot[ 77 ] = { 422, 118};
	sdot[ 78 ] = { 22, 134};
	sdot[ 79 ] = { 38, 134};
	sdot[ 80 ] = { 54, 134};
	sdot[ 81 ] = { 70, 134};
	sdot[ 82 ] = { 86, 134};
	sdot[ 83 ] = { 102, 134};
	sdot[ 84 ] = { 150, 134};
	sdot[ 85 ] = { 166, 134};
	sdot[ 86 ] = { 182, 134};
	sdot[ 87 ] = { 198, 134};
	sdot[ 88 ] = { 422, 422};
	sdot[ 89 ] = { 406, 422};
	sdot[ 90 ] = { 246, 134};
	sdot[ 91 ] = { 262, 134};
	sdot[ 92 ] = { 278, 134};
	sdot[ 93 ] = { 294, 134};
	sdot[ 94 ] = { 342, 134};
	sdot[ 95 ] = { 358, 134};
	sdot[ 96 ] = { 374, 134};
	sdot[ 97 ] = { 390, 134};
	sdot[ 98 ] = { 406, 134};
	sdot[ 99 ] = { 422, 134};
	sdot[ 100 ] = { 102, 150};
	sdot[ 101 ] = { 342, 150};
	sdot[ 102 ] = { 102, 166};
	sdot[ 103 ] = { 342, 166};
	sdot[ 104 ] = { 102, 182};
	sdot[ 105 ] = { 342, 182};
	sdot[ 106 ] = { 102, 198};
	sdot[ 107 ] = { 342, 198};
	sdot[ 108 ] = { 102, 214};
	sdot[ 109 ] = { 342, 214};
	sdot[ 110 ] = { 102, 230};
	sdot[ 111 ] = { 342, 230};
	sdot[ 112 ] = { 102, 246};
	sdot[ 113 ] = { 342, 246};
	sdot[ 114 ] = { 102, 262};
	sdot[ 115 ] = { 342, 262};
	sdot[ 116 ] = { 102, 278};
	sdot[ 117 ] = { 342, 278};
	sdot[ 118 ] = { 102, 294};
	sdot[ 119 ] = { 342, 294};
	sdot[ 120 ] = { 102, 310};
	sdot[ 121 ] = { 342, 310};
	sdot[ 122 ] = { 390, 422};
	sdot[ 123 ] = { 374, 422};
	sdot[ 124 ] = { 358, 422};
	sdot[ 125 ] = { 22, 326};
	sdot[ 126 ] = { 38, 326};
	sdot[ 127 ] = { 54, 326};
	sdot[ 128 ] = { 70, 326};
	sdot[ 129 ] = { 86, 326};
	sdot[ 130 ] = { 102, 326};
	sdot[ 131 ] = { 150, 326};
	sdot[ 132 ] = { 166, 326};
	sdot[ 133 ] = { 182, 326};
	sdot[ 134 ] = { 198, 326};
	sdot[ 135 ] = { 246, 326};
	sdot[ 136 ] = { 262, 326};
	sdot[ 137 ] = { 278, 326};
	sdot[ 138 ] = { 294, 326};
	sdot[ 139 ] = { 326, 326};
	sdot[ 140 ] = { 358, 326};
	sdot[ 141 ] = { 374, 326};
	sdot[ 142 ] = { 390, 326};
	sdot[ 143 ] = { 406, 326};
	sdot[ 144 ] = { 422, 326};
	sdot[ 145 ] = { 22, 342};
	sdot[ 146 ] = { 102, 342};
	sdot[ 147 ] = { 198, 342};
	sdot[ 148 ] = { 246, 342};
	sdot[ 149 ] = { 342, 342};
	sdot[ 150 ] = { 422, 342};
	sdot[ 151 ] = { 22, 358};
	sdot[ 152 ] = { 102, 358};
	sdot[ 153 ] = { 198, 358};
	sdot[ 154 ] = { 246, 358};
	sdot[ 155 ] = { 342, 358};
	sdot[ 156 ] = { 422, 358};
	sdot[ 157 ] = { 38, 374};
	sdot[ 158 ] = { 102, 374};
	sdot[ 159 ] = { 326, 374};
	sdot[ 160 ] = { 246, 374};
	sdot[ 161 ] = { 342, 374};
	sdot[ 162 ] = { 342, 422};
	sdot[ 163 ] = { 294, 422};
	sdot[ 164 ] = { 54, 406};
	sdot[ 165 ] = { 102, 406};
	sdot[ 166 ] = { 150, 406};
	sdot[ 167 ] = { 294, 406};
	sdot[ 168 ] = { 342, 406};
	sdot[ 169 ] = { 390, 406};
	sdot[ 170 ] = { 54, 390};
	sdot[ 171 ] = { 102, 390};
	sdot[ 172 ] = { 150, 390};
	sdot[ 173 ] = { 294, 390};
	sdot[ 174 ] = { 342, 390};
	sdot[ 175 ] = { 390, 390};
	sdot[ 176 ] = { 22, 438};
	sdot[ 177 ] = { 198, 438};
	sdot[ 178 ] = { 246, 438};
	sdot[ 179 ] = { 422, 438};
	sdot[ 180 ] = { 22, 454};
	sdot[ 181 ] = { 198, 454};
	sdot[ 182 ] = { 278, 422};
	sdot[ 183 ] = { 262, 422};
	sdot[ 184 ] = { 246, 422};
	sdot[ 185 ] = { 198, 422};
	sdot[ 186 ] = { 182, 422};
	sdot[ 187 ] = { 166, 422};
	sdot[ 188 ] = { 150, 422};
	sdot[ 189 ] = { 102, 422};
	sdot[ 190 ] = { 86, 422};
	sdot[ 191 ] = { 70, 422};
	sdot[ 192 ] = { 54, 422};
	sdot[ 193 ] = { 38, 422};
	sdot[ 194 ] = { 22, 422};
	sdot[ 195 ] = { 118, 326};
	sdot[ 196 ] = { 134, 326};
	sdot[ 197 ] = { 310, 326};
	sdot[ 198 ] = { 342, 326};
	sdot[ 199 ] = { 118, 374};
	sdot[ 200 ] = { 54, 374};
	sdot[ 201 ] = { 198, 374};
	sdot[ 202 ] = { 294, 374};
	sdot[ 203 ] = { 310, 374};
	sdot[ 204 ] = { 390, 374};
	sdot[ 205 ] = { 406, 374};
	sdot[ 206 ] = { 326, 470};
	sdot[ 207 ] = { 342, 470};
	sdot[ 208 ] = { 358, 470};
	sdot[ 209 ] = { 374, 470};
	sdot[ 210 ] = { 390, 470};
	sdot[ 211 ] = { 406, 470};
	sdot[ 212 ] = { 422, 470};
	sdot[ 213 ] = { 246, 454};
	sdot[ 214 ] = { 422, 454};
	sdot[ 215 ] = { 22, 470};
	sdot[ 216 ] = { 38, 470};
	sdot[ 217 ] = { 54, 470};
	sdot[ 218 ] = { 70, 470};
	sdot[ 219 ] = { 86, 470};
	sdot[ 220 ] = { 102, 470};
	sdot[ 221 ] = { 118, 470};
	sdot[ 222 ] = { 134, 470};
	sdot[ 223 ] = { 150, 470};
	sdot[ 224 ] = { 166, 470};
	sdot[ 225 ] = { 182, 470};
	sdot[ 226 ] = { 198, 470};
	sdot[ 227 ] = { 214, 470};
	sdot[ 228 ] = { 230, 470};
	sdot[ 229 ] = { 246, 470};
	sdot[ 230 ] = { 262, 470};
	sdot[ 231 ] = { 278, 470};
	sdot[ 232 ] = { 294, 470};
	sdot[ 233 ] = { 310, 470};
	sdot[ 234 ] = { 134, 374};
	sdot[ 235 ] = { 150, 374};
	sdot[ 236 ] = { 166, 374};
	sdot[ 237 ] = { 182, 374};
	sdot[ 238 ] = { 263, 374};
	sdot[ 239 ] = { 278, 374};
}

void dot(LTexture &gSrc) {
	SDL_Rect tmp = {320, 59, 4, 4};
	for(int i = 1; i < 241; ++i) {
		gSrc.render(sdot[i].first, sdot[i].second + 47, &tmp);
	}
}
void initwall() {
	ob[0] = {1, 47, 447, 58};
	ob[1] = {1, 47, 10, 266};
	ob[2] = {437, 47, 447, 266};
	ob[3] = { 213, 58, 234, 122 };
	ob[4] = { 117, 85, 186, 122 };
	ob[5] = { 261, 85, 330, 122 };
	ob[6] = { 357, 85, 410, 122 };
	ob[7] = { 37, 149, 90, 170 };
	ob[8] = { 117, 149, 138, 266 };
	ob[9] = { 165, 149, 282, 170 };
	ob[10] = { 309, 149, 330, 266 };
	ob[11] = { 357, 149, 410, 170 };
	ob[12] = { 1, 197, 90, 266 };
	ob[13] = { 137, 197, 186, 218 };
	ob[14] = { 213, 170, 234, 218 };
	ob[15] = { 261, 197, 309, 218 };
	ob[16] = { 357, 197, 447, 266 };
	ob[22] = { 1, 293, 90, 362 };
	ob[23] = { 1, 293, 10, 546 };
	ob[24] = { 117, 293, 138, 362 };
	ob[25] = { 309, 293, 330, 362 };
	ob[26] = { 357, 293, 447, 362 };
	ob[27] = { 437, 293, 447, 546 };
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
	ob[21] = { 1, 533, 447, 546 };
	ob[40] = { 37, 85, 90, 122 };
}
bool intersect(int x, int y, int l, int r) {
	if(x > l) {
		int tmp = l;
		l = x;
		x = tmp;
		tmp = r;
		r = y;
		y = tmp;
	}
	if(l <= y) {
		return true;
	}
	return false;
}
bool pcanmove(int x, int y, int z, int t) {
	for(int i = 0; i < 41; ++i) 
		if(intersect(x, z, ob[i].x, ob[i].z) && intersect(y, t, ob[i].y, ob[i].t)) 
			return false;
	if(intersect(x, z, 165, 282) && intersect(y, t, 245, 314))
		return false;
	return true;
}
bool mcanmove(int x, int y, int z, int t) {
	for(int i = 0; i < 41; ++i) 
		if(intersect(x, z, ob[i].x, ob[i].z) && intersect(y, t, ob[i].y, ob[i].t)) 
			return false;
	if(intersect(x, z, 165, 210) && intersect(y, t, 245, 259))
		return false;
	if(intersect(x, z, 237, 282) && intersect(y, t, 245, 259))
		return false;
	if(intersect(x, z, 165, 178) && intersect(y, t, 258, 314))
		return false;
	if(intersect(x, z, 269, 282) && intersect(y, t, 258, 314)) 
		return false;
	if(intersect(x, z, 165, 282) && intersect(y, t, 301, 314)) 
		return false;
	return true;
}
void initdot2() {
	trace[ 22 ][ 22 ] = 240;
	trace[ 38 ][ 22 ] = 1;
	trace[ 54 ][ 22 ] = 2;
	trace[ 70 ][ 22 ] = 3;
	trace[ 86 ][ 22 ] = 4;
	trace[ 102 ][ 22 ] = 5;
	trace[ 118 ][ 22 ] = 6;
	trace[ 134 ][ 22 ] = 7;
	trace[ 150 ][ 22 ] = 8;
	trace[ 166 ][ 22 ] = 9;
	trace[ 182 ][ 22 ] = 10;
	trace[ 198 ][ 22 ] = 11;
	trace[ 246 ][ 22 ] = 12;
	trace[ 262 ][ 22 ] = 13;
	trace[ 278 ][ 22 ] = 14;
	trace[ 294 ][ 22 ] = 15;
	trace[ 310 ][ 22 ] = 16;
	trace[ 326 ][ 22 ] = 17;
	trace[ 342 ][ 22 ] = 18;
	trace[ 358 ][ 22 ] = 19;
	trace[ 374 ][ 22 ] = 20;
	trace[ 390 ][ 22 ] = 21;
	trace[ 406 ][ 22 ] = 22;
	trace[ 422 ][ 22 ] = 23;
	trace[ 22 ][ 38 ] = 24;
	trace[ 102 ][ 38 ] = 25;
	trace[ 198 ][ 38 ] = 26;
	trace[ 246 ][ 38 ] = 27;
	trace[ 342 ][ 38 ] = 28;
	trace[ 422 ][ 38 ] = 29;
	trace[ 22 ][ 70 ] = 30;
	trace[ 102 ][ 54 ] = 31;
	trace[ 198 ][ 54 ] = 32;
	trace[ 246 ][ 54 ] = 33;
	trace[ 342 ][ 54 ] = 34;
	trace[ 422 ][ 70 ] = 35;
	trace[ 102 ][ 70 ] = 36;
	trace[ 198 ][ 70 ] = 37;
	trace[ 246 ][ 70 ] = 38;
	trace[ 342 ][ 70 ] = 39;
	trace[ 22 ][ 86 ] = 40;
	trace[ 38 ][ 86 ] = 41;
	trace[ 54 ][ 86 ] = 42;
	trace[ 70 ][ 86 ] = 43;
	trace[ 86 ][ 86 ] = 44;
	trace[ 102 ][ 86 ] = 45;
	trace[ 118 ][ 86 ] = 46;
	trace[ 134 ][ 86 ] = 47;
	trace[ 150 ][ 86 ] = 48;
	trace[ 166 ][ 86 ] = 49;
	trace[ 182 ][ 86 ] = 50;
	trace[ 198 ][ 86 ] = 51;
	trace[ 214 ][ 86 ] = 52;
	trace[ 230 ][ 86 ] = 53;
	trace[ 246 ][ 86 ] = 54;
	trace[ 262 ][ 86 ] = 55;
	trace[ 278 ][ 86 ] = 56;
	trace[ 294 ][ 86 ] = 57;
	trace[ 310 ][ 86 ] = 58;
	trace[ 326 ][ 86 ] = 59;
	trace[ 342 ][ 86 ] = 60;
	trace[ 358 ][ 86 ] = 61;
	trace[ 374 ][ 86 ] = 62;
	trace[ 390 ][ 86 ] = 63;
	trace[ 406 ][ 86 ] = 64;
	trace[ 422 ][ 86 ] = 65;
	trace[ 22 ][ 102 ] = 66;
	trace[ 102 ][ 102 ] = 67;
	trace[ 150 ][ 102 ] = 68;
	trace[ 294 ][ 102 ] = 69;
	trace[ 342 ][ 102 ] = 70;
	trace[ 422 ][ 102 ] = 71;
	trace[ 22 ][ 118 ] = 72;
	trace[ 102 ][ 118 ] = 73;
	trace[ 150 ][ 118 ] = 74;
	trace[ 294 ][ 118 ] = 75;
	trace[ 342 ][ 118 ] = 76;
	trace[ 422 ][ 118 ] = 77;
	trace[ 22 ][ 134 ] = 78;
	trace[ 38 ][ 134 ] = 79;
	trace[ 54 ][ 134 ] = 80;
	trace[ 70 ][ 134 ] = 81;
	trace[ 86 ][ 134 ] = 82;
	trace[ 102 ][ 134 ] = 83;
	trace[ 150 ][ 134 ] = 84;
	trace[ 166 ][ 134 ] = 85;
	trace[ 182 ][ 134 ] = 86;
	trace[ 198 ][ 134 ] = 87;
	trace[ 422 ][ 422 ] = 88;
	trace[ 406 ][ 422 ] = 89;
	trace[ 246 ][ 134 ] = 90;
	trace[ 262 ][ 134 ] = 91;
	trace[ 278 ][ 134 ] = 92;
	trace[ 294 ][ 134 ] = 93;
	trace[ 342 ][ 134 ] = 94;
	trace[ 358 ][ 134 ] = 95;
	trace[ 374 ][ 134 ] = 96;
	trace[ 390 ][ 134 ] = 97;
	trace[ 406 ][ 134 ] = 98;
	trace[ 422 ][ 134 ] = 99;
	trace[ 102 ][ 150 ] = 100;
	trace[ 342 ][ 150 ] = 101;
	trace[ 102 ][ 166 ] = 102;
	trace[ 342 ][ 166 ] = 103;
	trace[ 102 ][ 182 ] = 104;
	trace[ 342 ][ 182 ] = 105;
	trace[ 102 ][ 198 ] = 106;
	trace[ 342 ][ 198 ] = 107;
	trace[ 102 ][ 214 ] = 108;
	trace[ 342 ][ 214 ] = 109;
	trace[ 102 ][ 230 ] = 110;
	trace[ 342 ][ 230 ] = 111;
	trace[ 102 ][ 246 ] = 112;
	trace[ 342 ][ 246 ] = 113;
	trace[ 102 ][ 262 ] = 114;
	trace[ 342 ][ 262 ] = 115;
	trace[ 102 ][ 278 ] = 116;
	trace[ 342 ][ 278 ] = 117;
	trace[ 102 ][ 294 ] = 118;
	trace[ 342 ][ 294 ] = 119;
	trace[ 102 ][ 310 ] = 120;
	trace[ 342 ][ 310 ] = 121;
	trace[ 390 ][ 422 ] = 122;
	trace[ 374 ][ 422 ] = 123;
	trace[ 358 ][ 422 ] = 124;
	trace[ 22 ][ 326 ] = 125;
	trace[ 38 ][ 326 ] = 126;
	trace[ 54 ][ 326 ] = 127;
	trace[ 70 ][ 326 ] = 128;
	trace[ 86 ][ 326 ] = 129;
	trace[ 102 ][ 326 ] = 130;
	trace[ 150 ][ 326 ] = 131;
	trace[ 166 ][ 326 ] = 132;
	trace[ 182 ][ 326 ] = 133;
	trace[ 198 ][ 326 ] = 134;
	trace[ 246 ][ 326 ] = 135;
	trace[ 262 ][ 326 ] = 136;
	trace[ 278 ][ 326 ] = 137;
	trace[ 294 ][ 326 ] = 138;
	trace[ 326 ][ 326 ] = 139;
	trace[ 358 ][ 326 ] = 140;
	trace[ 374 ][ 326 ] = 141;
	trace[ 390 ][ 326 ] = 142;
	trace[ 406 ][ 326 ] = 143;
	trace[ 422 ][ 326 ] = 144;
	trace[ 22 ][ 342 ] = 145;
	trace[ 102 ][ 342 ] = 146;
	trace[ 198 ][ 342 ] = 147;
	trace[ 246 ][ 342 ] = 148;
	trace[ 342 ][ 342 ] = 149;
	trace[ 422 ][ 342 ] = 150;
	trace[ 22 ][ 358 ] = 151;
	trace[ 102 ][ 358 ] = 152;
	trace[ 198 ][ 358 ] = 153;
	trace[ 246 ][ 358 ] = 154;
	trace[ 342 ][ 358 ] = 155;
	trace[ 422 ][ 358 ] = 156;
	trace[ 38 ][ 374 ] = 157;
	trace[ 102 ][ 374 ] = 158;
	trace[ 326 ][ 374 ] = 159;
	trace[ 246 ][ 374 ] = 160;
	trace[ 342 ][ 374 ] = 161;
	trace[ 342 ][ 422 ] = 162;
	trace[ 294 ][ 422 ] = 163;
	trace[ 54 ][ 406 ] = 164;
	trace[ 102 ][ 406 ] = 165;
	trace[ 150 ][ 406 ] = 166;
	trace[ 294 ][ 406 ] = 167;
	trace[ 342 ][ 406 ] = 168;
	trace[ 390 ][ 406 ] = 169;
	trace[ 54 ][ 390 ] = 170;
	trace[ 102 ][ 390 ] = 171;
	trace[ 150 ][ 390 ] = 172;
	trace[ 294 ][ 390 ] = 173;
	trace[ 342 ][ 390 ] = 174;
	trace[ 390 ][ 390 ] = 175;
	trace[ 22 ][ 438 ] = 176;
	trace[ 198 ][ 438 ] = 177;
	trace[ 246 ][ 438 ] = 178;
	trace[ 422 ][ 438 ] = 179;
	trace[ 22 ][ 454 ] = 180;
	trace[ 198 ][ 454 ] = 181;
	trace[ 278 ][ 422 ] = 182;
	trace[ 262 ][ 422 ] = 183;
	trace[ 246 ][ 422 ] = 184;
	trace[ 198 ][ 422 ] = 185;
	trace[ 182 ][ 422 ] = 186;
	trace[ 166 ][ 422 ] = 187;
	trace[ 150 ][ 422 ] = 188;
	trace[ 102 ][ 422 ] = 189;
	trace[ 86 ][ 422 ] = 190;
	trace[ 70 ][ 422 ] = 191;
	trace[ 54 ][ 422 ] = 192;
	trace[ 38 ][ 422 ] = 193;
	trace[ 22 ][ 422 ] = 194;
	trace[ 118 ][ 326 ] = 195;
	trace[ 134 ][ 326 ] = 196;
	trace[ 310 ][ 326 ] = 197;
	trace[ 342 ][ 326 ] = 198;
	trace[ 118 ][ 374 ] = 199;
	trace[ 54 ][ 374 ] = 200;
	trace[ 198 ][ 374 ] = 201;
	trace[ 294 ][ 374 ] = 202;
	trace[ 310 ][ 374 ] = 203;
	trace[ 390 ][ 374 ] = 204;
	trace[ 406 ][ 374 ] = 205;
	trace[ 326 ][ 470 ] = 206;
	trace[ 342 ][ 470 ] = 207;
	trace[ 358 ][ 470 ] = 208;
	trace[ 374 ][ 470 ] = 209;
	trace[ 390 ][ 470 ] = 210;
	trace[ 406 ][ 470 ] = 211;
	trace[ 422 ][ 470 ] = 212;
	trace[ 246 ][ 454 ] = 213;
	trace[ 422 ][ 454 ] = 214;
	trace[ 22 ][ 470 ] = 215;
	trace[ 38 ][ 470 ] = 216;
	trace[ 54 ][ 470 ] = 217;
	trace[ 70 ][ 470 ] = 218;
	trace[ 86 ][ 470 ] = 219;
	trace[ 102 ][ 470 ] = 220;
	trace[ 118 ][ 470 ] = 221;
	trace[ 134 ][ 470 ] = 222;
	trace[ 150 ][ 470 ] = 223;
	trace[ 166 ][ 470 ] = 224;
	trace[ 182 ][ 470 ] = 225;
	trace[ 198 ][ 470 ] = 226;
	trace[ 214 ][ 470 ] = 227;
	trace[ 230 ][ 470 ] = 228;
	trace[ 246 ][ 470 ] = 229;
	trace[ 262 ][ 470 ] = 230;
	trace[ 278 ][ 470 ] = 231;
	trace[ 294 ][ 470 ] = 232;
	trace[ 310 ][ 470 ] = 233;
	trace[ 134 ][ 374 ] = 234;
	trace[ 150 ][ 374 ] = 235;
	trace[ 166 ][ 374 ] = 236;
	trace[ 182 ][ 374 ] = 237;
	trace[ 263 ][ 374 ] = 238;
	trace[ 278 ][ 374 ] = 239;
}

void initnumber() {
	num[0] = {271, 341, 8, 11};
	num[1] = {282, 341, 4, 11};
	num[2] = {290, 341, 8, 11};
	num[3] = {301, 341, 8, 11};
	num[4] = {313, 341, 8, 11};
	num[5] = {324, 341, 8, 11};
	num[6] = {335, 341, 8, 11};
	num[7] = {346, 341, 8, 11};
	num[8] = {357, 341, 8, 11};
	num[9] = {369, 341, 8, 11};
}

void showpoint(LTexture &gSrc, int p) {
	int lx = 68;
	int ly = 34;
	while(p) {
		int tmp = p % 10;
		p /= 10;
		if(tmp == 1) lx -= 5;
		else lx -= 9;
		gSrc.render(lx, ly, &num[tmp]);
	}
}
int doteatean = 0;
void checkdot(int x, int y) {
	y -= 47;
	x += 11;
	if(x >= 447 || x < 0) return;
	if(trace[x][y] ) {
		int id = trace[x][y];
		sdot[ trace[x][y] ] = {-10, -10};
		trace[x][y] = 0;
		point += 10;
		if(doteatean & 1) Mix_PlayChannel( -1, sodd, 0 );
		else Mix_PlayChannel(-1, seven, 0);
		++doteatean;
		return;
	}
	
	x -= 11;
	y += 10;
	if(x < 0) return;
	if(trace[x][y] ) {
		int id = trace[x][y];
		sdot[ trace[x][y] ] = {-10, -10};
		trace[x][y] = 0;
		point += 10;
		if(doteatean & 1) Mix_PlayChannel( -1, sodd, 0 );
		else Mix_PlayChannel(-1, seven, 0);
		++doteatean;
		return;
	}
	
	x+= 22;
	if(x >= 447) return;
	if(trace[x][y] ) {
		int id = trace[x][y];
		sdot[ trace[x][y] ] = {-10, -10};
		trace[x][y] = 0;
		point += 10;
		if(doteatean & 1) Mix_PlayChannel( -1, sodd, 0 );
		else Mix_PlayChannel(-1, seven, 0);
		++doteatean;
		return;
	}
	
	x -= 11;
	y += 11;
	if(trace[x][y] ) {
		int id = trace[x][y];
		sdot[ trace[x][y] ] = {-10, -10};
		trace[x][y] = 0;
		point += 10;
		if(doteatean & 1) Mix_PlayChannel( -1, sodd, 0 );
		else Mix_PlayChannel(-1, seven, 0);
		++doteatean;
		return;
	}
	
}


