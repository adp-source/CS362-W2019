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

void testIsGameOver() {
  int kingdomCards[10] = {smithy, adventurer, council_room, feast, gardens, mine, great_hall, minion, steward, outpost};
  struct gameState initial, before;
  int i;

  initializeGame(2, kingdomCards, 1, &initial);
  printf("Starting game, expect game to not be over.\n");
  copyState(&before, &initial);
  assertTrue(isGameOver(&before) == 0);
  before.supplyCount[province] = 0;
  printf("Setting provinces to 0. Expect game to be over.\n");
  assertTrue(isGameOver(&before) == 1);

  copyState(&before, &initial);
  for(i = 0; i < 3; i++){
		before.supplyCount[i] = 0;
  }
  printf("Setting 3 supply piles to 0. Expect game to be over.\n");
  assertTrue(isGameOver(&before) == 1);
}

int main(int argc, char *argv[])
{
    testIsGameOver();
    return 0;
}