#include "cbj.h"
#include <ctype.h>

extern void drawCard(Player* p, Player* op);
extern char* printShape(Shapes* s);
extern char* printCard(int* s, char* card_buf);

static int getOption(void) {
	char o;
	printf("\nd) Hit\ns) Stand\n: ");
	scanf(" %c", &o);
	o = tolower(o);
	switch (o) {
		case 'd': return 1; break;
		case 's': return 2; break;
		default: return 3; break;
	}
}

static int userTurn(Player* user, Player* dealer, char* card_buf) {
	bool finished = false;

	while (!finished) {
		printf("Your hand:\n");
		for (int i = 1; i <= user->cards; i++)
			printf("%s of %s\n", printCard(&user->card[i].value, card_buf), printShape(&user->card[i].shape));
		printf("Total: %i", user->total);
		if (user->total > 21) {
			printf(" BUST!");
			return 2;
		} else printf("\n");
		int o = getOption();
		switch (o) {
			case 1: for (int i = 0; i < 6 + user->cards; i++) printf("\r\33[A\33[2K"); drawCard(user, dealer); break;
			case 2: for (int i = 0; i < 5; i++) printf("\r\33[A\33[2K"); finished = true; break;
			case 3: return 1;
		}
	}

	return 0;
}

static int dealerTurn(Player* dealer, Player* user, char* card_buf, int* bet) {
	bool userHasBJ = false;
	int winner = 1;

	for (int i = 0; i < 4 + user->cards; i++)
		printf("\r\33[A\33[2K");

	while (dealer->total < 17)
		drawCard(dealer, user);

	for (int i = 1; i <= dealer->cards; i++)
		printf("%s of %s\n", printCard(&dealer->card[i].value, card_buf), printShape(&dealer->card[i].shape));

	printf("Total: %i", dealer->total);
	if (dealer->total > 21) {
		printf(" BUST!");
		winner = 0;
	}

	printf("\n\nYour hand:\n");
	for (int i = 1; i <= user->cards; i++)
		printf("%s of %s\n", printCard(&user->card[i].value, card_buf), printShape(&user->card[i].shape));
	printf("Total: %i\n", user->total);

	if (user->total == 21 && user->cards == 2) {
		userHasBJ = true;
		winner = 0;
	}

	if (user->total == dealer->total) {
		if (user->total == 21) {
			if (userHasBJ && dealer->cards == 2)
				winner = 2;
			else if (!userHasBJ && dealer->cards != 2)
				winner = 2;
		} else winner = 2;
	}

	if (user->total > dealer->total)
		winner = 0;

	switch (winner) {
		case 0: *bet = *bet * 2; if (userHasBJ) *bet += *bet / 2 / 2; break;
		case 1: *bet = 0; break;
		case 2: break;
	}

	return winner;
}

int game(Player* dealer, Player* user, char* card_buf, int* money) {
	int bet = 0;
	while (bet < 10) {
		if (*money >= 10) {
			printf("You have $%i\33[s\n", *money);
			printf("Enter bet (minimum is $10): $");
			if (scanf("%i", &bet)) {
				if (bet < 10)
					for (int i = 0; i < 3; i++) printf("\r\33[A\33[2K");
				else if (bet > *money) {
					for (int i = 0; i < 3; i++) printf("\r\33[A\33[2K");
					bet = 0;
				}
				printf("\n");
			} else return 1;
		} else return 2;
	}

	*money -= bet;

	printf("\33[u - $%i = $%i \33[s", bet, *money);
	printf("\n\n\n");

	printf("Dealer's hand:\n");
	printf("%s of %s\n", printCard(&dealer->card[1].value, card_buf), printShape(&dealer->card[1].shape));
	printf("and 1 more\n\n");

	int dtr;

	switch (userTurn(user, dealer, card_buf)) {
		case 0: dtr = dealerTurn(dealer, user, card_buf, &bet); break;
		case 1: return 1; break;
		case 2: printf("\n\nYou lose!\33[u"); goto userBust; break;
	}

	*money += bet;

	switch (dtr) {
		case 0: printf("\nYou win!\33[u+ $%i = $%i    \n", bet, *money); break;
		case 1: printf("\nYou lose!\33[u\n"); break;
		case 2: printf("\nPush!\33[u+ $%i = $%i    \n", bet, *money); break;
	}

userBust:
	for (int i = 0; i < 10 + dealer->cards + user->cards; i++)
		printf("\r\n");

	return 0;
}
