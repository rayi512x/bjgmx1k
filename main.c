#include "cbj.h"

extern void drawCard(Player* p, Player* op);
extern int game(Player* dealer, Player* user, char* card_buf, int* money);

static inline void replayPrep(Player* user, Player* dealer) {
	for (int i = 0; i < (user->total > 21 ? 11 : 12) + user->cards + dealer->cards; i++) {
		printf("\r\33[A\33[2K");
	}

	for (int i = 1; i <= user->cards; i++) {
		user->card[i].value = 0;
		user->card[i].shape = 0;
	}

	user->total = 0;
	user->cards = 0;

	for (int i = 1; i <= dealer->cards; i++) {
		dealer->card[i].value = 0;
		user->card[i].shape = 0;
	}

	dealer->total = 0;
	dealer->cards = 0;
}

int main(void) {
	printf("\33[?1049h\33[2J\33[H");
	printf("**********************************\n");
	printf("* BLACKJACK GACORR MAXWINN x1000 *\n");
	printf("*            rayi512x            *\n");
	printf("**********************************\n\n");

	srand(time(0));

	int money = 100;
	Player* dealer = (Player*)calloc(1, sizeof(Player));
	Player* user = (Player*)calloc(1, sizeof(Player));
	char* card_buf = (char*)malloc(6 * sizeof(char));
	bool finished = false;
	int exitcode;

	while (!finished) {
		drawCard(user, dealer);
		drawCard(dealer, user);
		drawCard(user, dealer);
		drawCard(dealer, user);

		exitcode = game(dealer, user, card_buf, &money);

		if (exitcode == 0) {
			printf("Press ENTER! ");
			while (getchar() != '\r' && getchar() != '\n');
			replayPrep(user, dealer);
		} else finished = true;
	}

	free(dealer);
	free(user);
	free(card_buf);

	printf("\33[2J\33[H\33[?1049l");

	if (exitcode == 2) {
		printf("You ran out of money.\n");
		return 1;
	}
	return 0;
}
