#include "cbj.h"

char* printShape(Shapes* s) {
	switch (*s) {
		case SPADE: return "Spades"; break;
		case HEART: return "Hearts"; break;
		case DIAMOND: return "Diamonds"; break;
		case CLUB: return "Clubs"; break;
		default: return "Error"; break;
	}
}

char* printCard(int* s, char* card_buf) {
	switch (*s) {
		case 1: card_buf = "Ace"; break;
		case 11: card_buf = "Jack"; break;
		case 12: card_buf = "Queen"; break;
		case 13: card_buf = "King"; break;
		default: sprintf(card_buf, "%i", *s);
	}

	return card_buf;
}
