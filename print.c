#include "cbj.h"

char* printShape(Shapes* s) {
	switch (*s) {
		case SPADE: return "Sekop"; break;
		case HEART: return "Hati"; break;
		case DIAMOND: return "Wajik"; break;
		case CLUB: return "Keriting"; break;
		default: return "Error"; break;
	}
}

char* printCard(int* s, char* card_buf) {
	switch (*s) {
		case 1: card_buf = "As"; break;
		case 11: card_buf = "Jack"; break;
		case 12: card_buf = "Queen"; break;
		case 13: card_buf = "King"; break;
		default: sprintf(card_buf, "%i", *s);
	}

	return card_buf;
}
