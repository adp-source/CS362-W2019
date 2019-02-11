#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*
Game state reference:

struct gameState {
  int numPlayers; //number of players
  int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
  int embargoTokens[treasure_map+1];
  int outpostPlayed;
  int outpostTurn;
  int whoseTurn;
  int phase;
  int numActions; // Starts at 1 each turn
  int coins; // Use as you see fit!
  int numBuys; // Starts at 1 each turn
  int hand[MAX_PLAYERS][MAX_HAND];
  int handCount[MAX_PLAYERS];
  int deck[MAX_PLAYERS][MAX_DECK];
  int deckCount[MAX_PLAYERS];
  int discard[MAX_PLAYERS][MAX_DECK];
  int discardCount[MAX_PLAYERS];
  int playedCards[MAX_DECK];
  int playedCardCount;
};
*/

/* By Jonah Siekmann
** https://piazza.com/class/jpu18p346423vs?cid=159
*/
#define assertTrue(bool) if(bool) printf("TEST SUCCESSFULLY COMPLETED.\n"); else printf("TEST FAILED: '" #bool  "' on line %d.\n", __LINE__);

void copyState(struct gameState *dest, struct gameState *source) {
  memcpy(dest, source, sizeof(struct gameState));
}

int compareState(struct gameState *dest, struct gameState *source) {
  return memcmp(dest, source, sizeof(struct gameState));
}

void testUpdateCoins() {
  int kingdomCards[10] = {smithy, adventurer, council_room, feast, gardens, mine, great_hall, minion, steward, outpost};
  struct gameState initial, before, after;

  initializeGame(2, kingdomCards, 1, &initial);
  copyState(&before, &initial);
  before.handCount[0] = 3;
  before.hand[0][0] = copper;
  before.hand[0][1] = silver;
  before.hand[0][2] = gold;
  copyState(&after, &before);

  before.coins = 6;
  int updateCoinsStatus = updateCoins(0, &after, 0);
  printf("Testing coins, 1 copper, 1 silver, 1 gold. Expecting 6 coins.\n");
  assertTrue(compareState(&before, &after) == 0);

  copyState(&before, &initial);
  before.handCount[0] = 0;
  copyState(&after, &before);
  before.coins = 5;
  updateCoinsStatus = updateCoins(0, &after, 5);
  printf("Testing 0 treasures, 5 bonus. Expecting 5 coins.\n");
  assertTrue(compareState(&before, &after) == 0);
}

int main(int argc, char *argv[])
{
    testUpdateCoins();
    return 0;
}