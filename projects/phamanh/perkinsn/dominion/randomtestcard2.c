#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"

/*
** https://stackoverflow.com/questions/6127503/shuffle-array-in-c
*/
void shuffleArr(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void randomKingdomCards(int randomKingdomCards [], int size){
	/* Generates array of kingdom cards from {7...26} */
	int kingdomCards[20];
	int i;
	for(i = 0; i < 20; i++){
		kingdomCards[i] = i + 7;
	}

	/* Shuffles array of {7...26} and take first 10 cards */
	shuffleArr(kingdomCards, 20);
	for(i = 0; i < 10; i++){
		randomKingdomCards[i] = kingdomCards[i];
	}
}

/* Function to insert a specific card into kingdom cards array if it doesn't already exist */
void insertCard(int *array, int size, int card) {

	/* Find card in array */
	int i;
	int found = 0;
	for(i = 0; i < size; i++){
		if(array[i] == card){
			found = 1;
		}
	}

	/* If card doesn't exist, insert it into a random location */
	if(!found){
		array[rand() % 9] = card;
	}
}

/* https://stackoverflow.com/questions/1202687/how-do-i-get-a-specific-range-of-numbers-from-rand */
int randomInt(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

/* Randomizes hand, deck, and discard piles */
void randomizeState(int player, int kingdomCards [], struct gameState * state) {
	state->handCount[player] = randomInt(0, 20);
	state->deckCount[player] = randomInt(0, 20);
	state->discardCount[player] = randomInt(0, 20);

	int otherCards[] = {
		curse,
	   estate,
	   duchy,
	   province,
		copper,
		silver,
		gold
  	};

  	int i;
  	int totalCards[17];
  	for(i = 0; i < 10; i++) {
  		totalCards[i] = kingdomCards[i];
  	}
  	for(i = 0; i < 7; i++) {
  		totalCards[i+10] = otherCards[i];
  	}

  	/* Random hand */
  	for(i = 0; i < state->handCount[player]; i++) {
  		state->hand[player][i] = totalCards[rand() % 17];
  	}

  	/* Random deck */
  	for(i = 0; i < state->deckCount[player]; i++) {
  		state->deck[player][i] = totalCards[rand() % 17];
  	}

  	/* Random discard */
  	for(i = 0; i < state->discardCount[player]; i++) {
  		state->discard[player][i] = totalCards[rand() % 17];
  	}
}

void copyState(struct gameState *dest, struct gameState *source) {
  memcpy(dest, source, sizeof(struct gameState));
}

int main() {

	srand(time(0));

	SelectStream(rand() % 255);
	PutSeed(rand() % 4096);

	int i;
	for(i = 0; i < 5000; i++) {
		struct gameState game, after;
		int players = rand() % 4;
		int randomSeed = rand();

		int kingdomCards[10];
		randomKingdomCards(kingdomCards, 10);
		insertCard(kingdomCards, 10, village);

		int status = initializeGame(players, kingdomCards, randomSeed, &game);

		int curPlayer = whoseTurn(&game);
		randomizeState(curPlayer, kingdomCards, &game);

		int *bonus = NULL;
		int choice = rand() % 2;
		status = cardEffect(village, choice, choice, choice, &game, 0, bonus);

		assert(status == 0);
	}

	printf("Tests completed.\n");
}