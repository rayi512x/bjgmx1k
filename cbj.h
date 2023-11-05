#ifndef CBJ_H
#define CBJ_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef enum {
	SPADE = 1, HEART, DIAMOND, CLUB
} Shapes;

typedef struct {
	int value;
	Shapes shape;
} Card;

typedef struct {
	int total, cards;
	Card card[12];
} Player;

#endif
