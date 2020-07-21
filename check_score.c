#include <stdio.h>
#ifndef MAX_SCORE
#define MAX_SCORE 10
#endif

int score[] = { 0, 0 };

int getScore(int player) {
    return score[player];
}

void increment_score(int player) {
    score[player] += 1;
}

void resetScores() {
    score[0] = 0;
    score[1] = 0;
}

int hasWinner(int scoreForAPlayer) {
    return scoreForAPlayer == MAX_SCORE;
}

int whoWin(int i) {
    return i == 0 ? 1 : 2;
}

int check_score() {
    int winner = 0;
	for(int i = 0; i < 2; i++) {
		if (hasWinner(score[i])) {
            winner = whoWin(i);
            resetScores();
		}
	}
	return winner;
}
