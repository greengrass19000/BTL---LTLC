#ifdef MONSTER_H
#define MONSTER_H
#endif // MONSTER_H

SDL_Rect Mon[ 4 ][ 4 ][ 2 ][ 3 ];
//this include :[number][dirs][odd/even][state]

void initmonster() {
	for(int i = 0; i <= 150; i += 50) {
		int order = i / 50;
		int lRun = 0;
		int x = 17;
		int y = 214;
		for(int j = 0; j <= 350; j += 50) {
			int lDir = (j >> 1) & 1;
			Mon[order][lDir][lRun&1][1].x = x + i;
			Mon[order][lDir][lRun&1][1].y = y + j;
		}
	}
	for(int i = 0; i < 4; ++i) 
		for(int j = 0; j < 4; ++j) 
			for(int k = 0; k < 2; ++k) {
				Mon[i][j][k][0].x = 1;
				for(int l = 0; l < 3; ++l)
					Mon[i][j][k][l].w = Mon[i][j][k][l].h = 34;
			}
}
void Die(int number) {
	//change the MonsterState
	//MonsterState[number] ^= 1;
}

void Revived(int number) {
	//change the MonsterState
	//MonsterState[number] ^= 1;
}

//void 