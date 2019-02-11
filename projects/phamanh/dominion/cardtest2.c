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

void testCardSmithy() {
  int kingdomCards[10] = {smithy, adventurer, council_room, feast, gardens, mine, great_hall, minion, steward, outpost};
  struct gameState initial, before, after;

  initializeGame(2, kingdomCards, 1, &initial);
  copyState(&before, &initial);

  /* Initial state
  Deck: 2 estate, 3 copper [1,1,4,4,4]. Count = 5
  Hand: 4 copper, 1 estate [4,4,4,4,1]. Count = 5
  Discard pile: []. Count = 0
  Draws card from end of deck first.
  */
  before.hand[0][before.handCount[0]] = smithy;
  before.handCount[0] += 1;
  copyState(&after, &before);
  before.playedCards[before.playedCardCount] = smithy;
  before.playedCardCount += 1;

  int i;

  int deckCount = before.deckCount[0] - 1;
  for(i=0; i<3; i++){
  	before.hand[0][before.handCount[0]-1+i] = before.deck[0][deckCount];
  	deckCount -= 1;
  }
  before.handCount[0] = 8;

  int *bonus = NULL;
  cardEffect(smithy, 0, 0, 0, &after, 5, bonus);
  printf("Played Smithy. Expected to gain 3 cards.\n");
  assertTrue(before.handCount[0] == 8);
  assertTrue(before.handCount[0] == after.handCount[0]);
  assertTrue(before.playedCards[before.playedCardCount-1] == after.playedCards[after.playedCardCount-1]);

  if(DEBUG){
    printf("BEFORE\n");
    printf("deckcount %d\n", before.deckCount[0]);
    for(i=0; i<before.deckCount[0]; i++){
      printf("%d, card %d\n", i, before.deck[0][i]);
    }
    printf("discardCount %d\n", before.discardCount[0]);
    for(i=0; i<before.discardCount[0]; i++){
      printf("%d, discard card %d\n", i, before.discard[0][i]);
    }
    printf("handCount %d\n", before.handCount[0]);
    for(i=0; i<before.handCount[0]; i++){
      printf("%d, hand card %d\n", i, before.hand[0][i]);
    }
    printf("played cards count %d\n", before.playedCardCount);
    for(i=0; i<before.playedCardCount; i++){
      printf("%d, played card %d\n", i, before.playedCards[i]);
    }
  }

  if(DEBUG){
	  printf("AFTER\n");
	  printf("deckcount %d\n", after.deckCount[0]);
	  for(i=0; i<after.deckCount[0]; i++){
	  	printf("%d, card %d\n", i, after.deck[0][i]);
	  }
	  printf("discardCount %d\n", after.discardCount[0]);
	  for(i=0; i<after.discardCount[0]; i++){
	  	printf("%d, discard card %d\n", i, after.discard[0][i]);
	  }
	  printf("handCount %d\n", after.handCount[0]);
	  for(i=0; i<after.handCount[0]; i++){
	  	printf("%d, hand card %d\n", i, after.hand[0][i]);
	  }
    printf("played cards count %d\n", after.playedCardCount);
    for(i=0; i<after.playedCardCount; i++){
      printf("%d, played card %d\n", i, after.playedCards[i]);
    }
	}
}

int main(int argc, char *argv[])
{
    testCardSmithy();
    return 0;
}