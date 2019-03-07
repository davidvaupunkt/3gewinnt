#include <stdio.h>

char isSafeMove(char **game, char player, char move);
char getNextPlayer(char player);
char isWinningMove(char **game, char player, char move);
char isMine(char **game, char CoordX, char CoordY, char me);
void fuzzyEvolveCounter(unsigned int *count, char **game, char coordX, char coordY, char d1, char d2 , char me);
char isValidMove(char **game, char move);
char getLandingId(char **game, char stack);


char isSafeMove(char **game, char player, char move) {
	
}

char getNextPlayer(char player) {
	return (player+1)%3;
}

char isWinningMove(char **game, char player, char move) {
	//A winning move must be valid
	if(!isValidMove(game, move))
		return 0;
		
	//Landing Coords
	char y = move;
	char x = getLandingId(game, move);
	
	//check if this creates a win for player
	int counter[4] = {0,0,0,0};
	for(int dir = 0; dir <= 3; dir++) {
		fuzzyEvolveCounter(&counter[dir], game, x, y, 0, dir, player);
		fuzzyEvolveCounter(&counter[dir], game, x, y, 1, dir, player);
		if(counter[dir] >= 2)
			return 1;
	}
	return 0;
}

char isMine(char **game, char CoordX, char CoordY, char me) {
	if(game[CoordX][CoordY] == me) 
		return 1;
	return 0;
}

void fuzzyEvolveCounter(unsigned int *count, char **game, char coordX, char coordY, char d1, char d2 , char me) {
	char xOffs[2][4] = {{1, 1, 0, -1}, {-1,-1, 0, 1}};
	char yOffs[2][4] = {{0,-1,-1, -1}, { 0, 1, 1, 1}};

	if(0 <= coordX + xOffs[d1][d2] && coordX + xOffs[d1][d2] <= 8	&& 	0 <= coordY + yOffs[d1][d2] && coordY + yOffs[d1][d2] <= 8) {
		if(game[coordX + xOffs[d1][d2]][coordY + yOffs[d1][d2]] == me) {
			*count += 1;
			fuzzyEvolveCounter(count, game, coordX + xOffs[d1][d2], coordY + yOffs[d1][d2], d1, d2, me);
		}
	}
}

char isValidMove(char **game, char move) {
	if(game[0][move] == 0)
		return 1;
	return 0;
}

char getLandingId(char **game, char stack) {
	unsigned char l = 0;
	while(l < 8 && game[l+1][stack] == 0)
		l++;
	return l;
}

char bot(char **game, char me) {

}

int main() {
	char game[9][9] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0},// 0
	{0, 0, 0, 0, 0, 0, 0, 0, 0},// 1
	{0, 0, 0, 0, 0, 0, 0, 0, 0},// 2
	{0, 0, 0, 0, 0, 0, 0, 0, 0},// 3
	{0, 0, 0, 0, 0, 0, 0, 0, 0},// 4
	{0, 0, 0, 0, 0, 0, 0, 0, 0},// 5
	{0, 0, 0, 0, 0, 0, 0, 0, 0},// 6
	{1, 2, 0, 0, 1, 0, 0, 0, 0},// 7
	{1, 1, 3, 0, 1, 1, 0, 0, 0}};//8
//   0  1  2  3  4  5  6  7  8
	char *g[9];
	for(int i = 0; i < 9; i++) 
		g[i] = game[i];
		
	for(int i = 0; i < 9; i++)
		printf("%d winning move for player one?:%d\n", i, isWinningMove(g, 1, i));
}







