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

void testCardCouncilRoom() {
  int kingdomCards[10] = {smithy, adventurer, council_room, feast, gardens, mine, great_hall, minion, steward, outpost};
  struct gameState initial, before, after;

  initializeGame(2, kingdomCards, 1, &initial);
  copyState(&before, &initial);
  copyState(&after, &initial);

  /* Initial state

  Player 1
  Deck: 2 estate, 3 copper [1,1,4,4,4]. Count = 5
  Hand: 4 copper, 1 estate [4,4,4,4,1]. Count = 5
  Discard pile: []. Count = 0

  Player 2
  Deck: 10, [1,4,4,4,4,4,4,4,1,1]
  Hand: 0
  Discard: 0
  */

  int i, j;

  before.hand[0][before.handCount[0]] = council_room;
  before.handCount[0] += 1;
  copyState(&after, &before);
  before.handCount[0] -= 1;
  int deckCount = before.deckCount[0] - 1;
  for(i=0; i<4; i++){
  	before.hand[0][before.handCount[0]] = before.deck[0][deckCount];
  	before.handCount[0] += 1;
  	deckCount -= 1;
  }
  before.deckCount[0] -= 4;
  before.hand[1][before.handCount[1]] = before.deck[1][before.deckCount[1]-1];
  before.handCount[1] += 1;
  before.deckCount[1] -= 1;

  before.playedCards[before.playedCardCount] = council_room;
  before.playedCardCount += 1;

  int *bonus = NULL;
  cardEffect(council_room, 0, 0, 0, &after, 5, bonus);
  printf("Played Council Room. Expected to gain 4 cards, other player gains 1.\n");
  assertTrue(before.handCount[0] == 9);
  assertTrue(before.handCount[0] == after.handCount[0]);
  assertTrue(before.handCount[1] == after.handCount[1]);
  
  /* For debug, before state */
  if(DEBUG){
    for(j=0; j<2; j++){
      printf("BEFORE Player %d\n", j);
      printf("deckcount %d\n", before.deckCount[j]);
      for(i=0; i<before.deckCount[j]; i++){
        printf("%d, card %d\n", i, before.deck[j][i]);
      }
      printf("discardCount %d\n", before.discardCount[j]);
      for(i=0; i<before.discardCount[j]; i++){
        printf("%d, discard card %d\n", i, before.discard[j][i]);
      }
      printf("handCount %d\n", before.handCount[j]);
      for(i=0; i<before.handCount[j]; i++){
        printf("%d, hand card %d\n", i, before.hand[j][i]);
      }
      printf("played cards count %d\n", before.playedCardCount);
      for(i=0; i<before.playedCardCount; i++){
        printf("%d, played card %d\n", i, before.playedCards[i]);
      }
    }
  }

  /* For debug, after state */
  if(DEBUG) {
  	for(j=0; j<2; j++){
	    printf("AFTER Player %d\n", j);
	    printf("deckcount %d\n", after.deckCount[j]);
	    for(i=0; i<after.deckCount[j]; i++){
	      printf("%d, card %d\n", i, after.deck[j][i]);
	    }
	    printf("discardCount %d\n", after.discardCount[j]);
	    for(i=0; i<after.discardCount[j]; i++){
	      printf("%d, discard card %d\n", i, after.discard[j][i]);
	    }
	    printf("handCount %d\n", after.handCount[j]);
	    for(i=0; i<after.handCount[j]; i++){
	      printf("%d, hand card %d\n", i, after.hand[j][i]);
	    }
      printf("played cards count %d\n", after.playedCardCount);
      for(i=0; i<after.playedCardCount; i++){
        printf("%d, played card %d\n", i, after.playedCards[i]);
      }
  	}
  }
}

int main(int argc, char *argv[])
{
    testCardCouncilRoom();
    return 0;
}