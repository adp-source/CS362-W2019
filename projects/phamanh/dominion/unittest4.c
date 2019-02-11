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

void testSupplyCount() {
  int kingdomCards[10] = {smithy, adventurer, council_room, feast, gardens, mine, great_hall, minion, steward, outpost};
  struct gameState initial, before;

  initializeGame(2, kingdomCards, 1, &initial);
  copyState(&before, &initial);
  before.supplyCount[smithy] = 5;
  before.supplyCount[adventurer] = 3;
  printf("Expect supply count for Smithy to be 5 and Adventurer to be 3.\n");
  assertTrue((supplyCount(smithy, &before) == 5) && (supplyCount(adventurer, &before) == 3));
}

int main(int argc, char *argv[])
{
    testSupplyCount();
    return 0;
}