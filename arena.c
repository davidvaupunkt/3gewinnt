#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

// noch mehr includes..

char random_move(unsigned int slen){
	srand(time(NULL));
	return (char)(rand()%slen);
}

char getLandingId(char ** game, char stack, unsigned int slen){
	char row = 0;
	while(row < slen-1 && game[row+1][stack] == 0){
		row++;
	}
	return row;
}
/*
void fuzzyEvolveCounter(unsigned int *count, char **game, char coordX, char coordY, char d1, char d2 , char me) {
    char xOffs[2][4] = {{1, 1, 0, -1}, {-1,-1, 0, 1}};
    char yOffs[2][4] = {{0,-1,-1, -1}, { 0, 1, 1, 1}};

    if(0 <= coordX + xOffs[d1][d2] && coordX + xOffs[d1][d2] <= 8    &&     0 <= coordY + yOffs[d1][d2] && coordY + yOffs[d1][d2] <= 8) {
        if(game[coordX + xOffs[d1][d2]][coordY + yOffs[d1][d2]] == me) {
            *count += 1;
            fuzzyEvolveCounter(count, game, coordX + xOffs[d1][d2], coordY + yOffs[d1][d2], d1, d2, me);
        }
    }
}


char isWinningMove(char **game, char player, char move) {
    //A winning move must be valid
    if(!isValidMove(game, move))
        return 0;
        
    //Landing Coords
    char x = move;
    char y = getStackHeight(game, move) + 1;
    
    //check if this creates a win for player
    int counter[4] = {0,0,0,0};
    for(int dir = 0; dir <= 3; dir++) {
        fuzzyEvolveCounter(&counter[dir], game, x, y, 0, dir, player);
        fuzzyEvolveCounter(&counter[dir], game, x, y, 1, dir, player);
        if(counter[i] >= 3)
            return 1;
    }
    return 0;
}
*/

int check_for_game_end(unsigned int slen, char **sf, char player, char zug){
	if(rand()%4 == 0){
		return 1;
	}
	return 0;
}

int turn(char player, char zug, unsigned int slen, char**sf){
	if(sf[0][zug] != 0){
		return -1*player;
	}
	unsigned int row = getLandingId(sf,zug,slen);
	sf[row][zug] = player;
	return 1;
}

char get_turn(char player, unsigned int slen){
	return random_move(slen);
}

void print_spielfeld(unsigned int slen, char **sf){
	printf("\n");
	for(int k = 0; k<slen;k++){
			printf("%d ",k);
	}
	printf("\n");
	for(int k = 0; k<slen;k++){
			printf("__");
	}
	printf("\n");
	for(int i = 0; i<slen;i++){
		for(int k = 0; k<slen;k++){
			if(sf[i][k]==1){
				printf(RED "%d " RESET, sf[i][k]);
			}
			if(sf[i][k]==2){
				printf(GREEN "%d " RESET, sf[i][k]);
			}
			if(sf[i][k]==3){
				printf(YELLOW "%d " RESET, sf[i][k]);
			}
			if(sf[i][k]==0){
				printf(RESET "%d ", sf[i][k]);
			}
		}
		printf("\n");
	}
	for(int k = 0; k<slen;k++){
			printf("**");
	}
	printf("\n");
}

int main(int narg, char *argv[]){
	const unsigned int slen = 9;
	char ** spielfeld = malloc(sizeof(char*)*slen);
	for(int i = 0; i<slen;i++){
		spielfeld[i] = malloc(sizeof(char)*slen);
		for(int k = 0; k<slen;k++){
			spielfeld[i][k] = 0;
		}
	}
	print_spielfeld(slen,spielfeld);
	char player = 1;
	int reason = 0;
	char cturn = -1;
	char winner = 0;
	while(reason >= 0){
		cturn = get_turn(player,slen);
		reason = turn(player,cturn,slen,spielfeld);
		print_spielfeld(slen,spielfeld);
		winner = check_for_game_end(slen,spielfeld,player,cturn);
		if(winner > 0){	
			reason = winner;
			break;
		}
		sleep(1);
		player++;
		if(player > 3){
			player = 1;
		}
	}
	if(reason<0){
		printf("Das Spiel wurde abgebrochen, da Spieler %d einen ungültigen Zug getätigt hat.\n", -1*reason);
	}
	if(reason>0){
		printf("Das Spiel wurde beendet. Spieler %d gewinnt.\n", reason);
	}
	if(reason==0){
		printf("Irgendwas ist nicht so gelaufen wie es sollte. Irgendjemand trägt die Schuld hierfür, allerdings nicht der Autor dieses wunderbaren Programmes.\n");
	}
	return 0;
}

