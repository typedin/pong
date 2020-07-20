#include "main.h"

int topEdgeBall(ball_t aBall) {
 return aBall.y;
}
int rightEdgeBall(ball_t aBall) {
 return aBall.x + aBall.w;
}
int bottomEdgeBall(ball_t aBall) {
 return  aBall.y + aBall.h;
}
int leftEdgeBall(ball_t aBall) {
    return aBall.x;
}


int topEdgePaddle(paddle_t aPaddle) {
    return aPaddle.y;
}
int rightEdgePaddle(paddle_t aPaddle) {
    return aPaddle.x;
}
int bottomEdgePaddle(paddle_t aPaddle) {
    return  aPaddle.y + aPaddle.h;
}
int leftEdgePaddle(paddle_t aPaddle) {
    return aPaddle.x;
}

int hasCollision(ball_t aBall, paddle_t aPaddle) {

	if (leftEdgeBall(aBall) > rightEdgePaddle(aPaddle)) {
		return 0;
	}

	if (rightEdgeBall(aBall) < leftEdgePaddle(aPaddle)) {
		return 0;
	}

	if (topEdgeBall(aBall) > bottomEdgePaddle(aPaddle)) {
		return 0;
	}

	if (bottomEdgeBall(aBall) < topEdgePaddle(aPaddle)) {
		return 0;
	}

	return 1;
}
