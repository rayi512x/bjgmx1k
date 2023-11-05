#include "cbj.h"

static inline void countTotal(Player* p) {
	p->total = 0;
	bool hasAce = false;
	bool aceIsMoreThanOne = false;
	int aceValue = 0;

	for (int i = 1; i <= p->cards; i++) {
		if (p->card[i].value == 1) {
			if (hasAce) aceIsMoreThanOne = true;
			else hasAce = true;
		} else if (p->card[i].value > 10)
			p->total += 10;
		else p->total += p->card[i].value;
	}

	if (hasAce) {
		if (aceIsMoreThanOne) {
			for (int i = 1; i <= p->cards; i++)
				if (p->card[i].value == 1) aceValue++;
		} else if (p->total + 11 > 21) aceValue = 1;
		else aceValue = 11;
	}

	p->total += aceValue;
}

void drawCard(Player* p, Player* op) {
	bool hasDupe = true;
	p->cards++;

	while (hasDupe) {
		hasDupe = false;
		p->card[p->cards].value = rand() % 13 + 1;
		p->card[p->cards].shape = rand() % 4 + 1;

		for (int i = 1; i < p->cards; i++)
			if (p->card[p->cards].value == p->card[i].value && p->card[p->cards].shape == p->card[i].shape)
				hasDupe = true;
		for (int i = 1; i <= op->cards; i++)
			if (p->card[p->cards].value == op->card[i].value && p->card[p->cards].shape == op->card[i].shape)
				hasDupe = true;
	}

	countTotal(p);
}
