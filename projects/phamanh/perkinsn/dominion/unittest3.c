#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define assertTrue(bool) if(bool) printf("TEST SUCCESSFULLY COMPLETED.\n"); else printf("TEST FAILED: '" #bool  "' on line %d.\n", __LINE__);

void copyState(struct gameState *dest, struct gameState *source) {
  memcpy(dest, source, sizeof(struct gameState));
}

int compareState(struct gameState *dest, struct gameState *source) {
  return memcmp(dest, source, sizeof(struct gameState));
}

void testGainCard() {
  int kingdomCards[10] = {smithy, adventurer, council_room, feast, gardens, mine, great_hall, minion, steward, outpost};
  struct gameState initial, before, after;

  initializeGame(2, kingdomCards, 1, &initial);
  copyState(&before, &initial);
  copyState(&after, &before);
  before.deck[0][before.deckCount[0]] = smithy;
  before.deckCount[0] += 1;
  before.hand[0][before.handCount[0]] = smithy;
  before.handCount[0] += 1;
  before.discard[0][before.discardCount[0]] = smithy;
  before.discardCount[0] += 1;
  before.supplyCount[smithy] -= 3;
  printf("Gain smithy for player 0 to discard, deck, hand piles. Expect state change to be equal.\n");
  gainCard(smithy, &after, 0, 0);
  gainCard(smithy, &after, 1, 0);
  gainCard(smithy, &after, 2, 0);
  assertTrue(compareState(&before, &after) == 0);
}

int main(int argc, char *argv[])
{
    testGainCard();
    return 0;
}