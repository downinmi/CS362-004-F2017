#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int seed = 37;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
	int testPassed = 0;
	int passed = 0;
	
	printf ("TESTING smithyCard():\n");
	
	/********************************************/
	printf("Running card test 1.1: 2 Player Game, Player 1 Plays Smithy\n");
	//initializing game with 2 players and 10 cards
	//playing smithy from position 0 for player 1
	struct gameState state;
	initializeGame(2, k, seed, &state);
	
	//setting decks to 10
	state.deckCount[0] = 10;
	state.deckCount[1] = 10;
	
	//giving both players a fake smithy card
	state.handCount[0] = 1;
	state.handCount[1] = 1;
	
	//playing smithy card from position 0
	//int returnValue = smithyCard(0, &state, 0);
	int returnValue = cardEffect(smithy, 0, 0, 0, &state, 0, 0);
	//assert(state.deckCount[0] == 7);	//starting deck count - 3 cards drawn
	if(state.deckCount[0] != 7){
		passed = 1;
		printf("Deck Count P1: %d, Expected: %d\n", state.deckCount[0], 7);
	}
	
	//assert(returnValue == 0);
	if(returnValue != 0){
		passed = 1;
		printf("Card Effect Returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//assert(state.handCount[0] == 3);	//player 1 has 2 cards (draw 3 - 1 discarded)
	if(state.handCount[0] != 3){
		passed = 1;
		printf("Hand Count P1: %d, Expected: %d\n", state.handCount[0], 3);
	}
	
	//assert(state.handCount[1] == 1);	//player 2 has no cards in hand
	if(state.handCount[1] != 1){
		passed = 1;
		printf("Hand Count P2: %d, Expected: %d\n", state.handCount[1], 1);
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	/*******************************************/
	printf("Running card test 1.2: 2 Player Game, Player 2 Plays Smithy\n");
	passed = 0;
	//initializing game with 2 players and 4 cards
	//gaining smithy and playing smithy from position 0 for player 2
	initializeGame(2, k, seed, &state);
	
	//giving both players a fake smithy card
	state.handCount[0] = 1;
	state.handCount[1] = 1;
	
	//player 2
	state.whoseTurn++;
	
	//playing smithy card from position 0
	returnValue = cardEffect(smithy, 0, 0, 0, &state, 0, 0);
	//returnValue = smithyCard(1, &state, 1);
	
	//check deck count for player 2
	//printf("Deck count: %d\n", state.deckCount[1]);
	//assert(state.deckCount[1] == 7);	//starting deck count - 3 cards drawn
	if(state.deckCount[1] != 7){
		passed = 1;
		printf("Deck Count P2: %d, Expected: %d\n", state.deckCount[1], 7);
	}
	
	//assert(returnValue == 0);
	if(returnValue != 0){
		passed = 1;
		printf("Card Effect Returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//assert(state.handCount[1] == 3);	//player 2 has 3
	if(state.handCount[1] != 3){
		passed = 1;
		printf("Hand Count P2: %d, Expected: %d\n", state.handCount[1], 3);
	}
	
	//assert(state.handCount[0] == 1);	//player 1 has 1 = 0 cards in hand
	if(state.handCount[0] != 1){
		passed = 1;
		printf("Hand Count P1: %d, Expected: %d\n", state.handCount[0], 1);
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	/*******************************************/
	printf("Running card test 1.3: Continuation of 1.2 Game State, Player 1 Plays Smithy\n");
	passed = 0;
	//testing a second call to smithyCard()
	//setting players hand count to !0
	state.handCount[0] = 2;
	state.handCount[1] = 2;
	
	//playing smithy card from position 0
	returnValue = cardEffect(smithy, 0, 0, 0, &state, 0, 0);
	//returnValue = smithyCard(0, &state, 0);
	
	//printf("Deck count: %d\n", state.deckCount[1]);
	//assert(state.deckCount[1] == 4);	//starting deck count - 3 cards drawn - 3 cards drawn
	if(state.deckCount[1] != 4){
		passed = 1;
		printf("Deck Count P2: %d, Expected: %d\n", state.deckCount[1], 4);
	}
	
	//assert(returnValue == 0);
	if(returnValue != 0){
		passed = 1;
		printf("Card Effect Returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//printf("P2 handcount: %d\n", state.handCount[1]);
	//assert(state.handCount[1] == 4);	//player 2 has 2 cards 
	if(state.handCount[1] != 4){
		passed = 1;
		printf("Hand Count P2: %d, Expected: %d\n", state.handCount[1], 4);
	}
	
	//assert(state.handCount[0] == 2);	//player 1 has 4 cards (2 - 1 played + 3 drawn = 4)
	if(state.handCount[0] != 2){
		passed = 1;
		printf("Hand Count P1: %d, Expected: %d\n", state.handCount[0], 2);
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	/*******************************************/
	printf("Running card test 1.4: Continuation of 1.2 Game State, Player 2 Plays Smithy\n");
	passed = 0;
	//testing a third call to smithyCard()
	//setting players hand count to !0
	state.handCount[0] = 2;
	state.handCount[1] = 2;
	
	//playing smithy card from position 0
	returnValue = cardEffect(smithy, 0, 0, 0, &state, 0, 0);
	
	//assert(state.deckCount[1] == 1);	//starting deck count - 3 cards drawn - 3 cards drawn
	if(state.deckCount[1] != 1){
		passed = 1;
		printf("Deck Count P2: %d, Expected: %d\n", state.deckCount[1], 1);
	}
	
	//assert(returnValue == 0);
	if(returnValue != 0){
		passed = 1;
		printf("Card Effect Returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//assert(state.handCount[1] == 4);	//player 2 has 2 cards 
	if(state.handCount[1] != 4){
		passed = 1;
		printf("Hand Count P2: %d, Expected: %d\n", state.handCount[1], 4);
	}
	
	//assert(state.handCount[0] == 2);	//player 1 has 4 cards (2 - 1 played + 3 drawn = 4)
	if(state.handCount[0] != 2){
		passed = 1;
		printf("Hand Count P1: %d, Expected: %d\n", state.handCount[0], 2);
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	/*******************************************/
	printf("Running card test 1.5: Continuation of 1.2 Game State, Player 1 Plays Smithy\n");
	passed = 0;
	//testing a fourth call to smithyCard()
	//setting players hand count to !0
	state.handCount[0] = 2;
	state.handCount[1] = 2;
	
	//playing smithy card from position 0
	returnValue = cardEffect(smithy, 0, 0, 0, &state, 0, 0);
	
	//printf("Deck count: %d\n", state.deckCount[1]);
	//assert(state.deckCount[1] == 0);	//no cards in deck
	if(state.deckCount[1] != 0){
		passed = 1;
		printf("Deck Count P2: %d, Expected: %d\n", state.deckCount[1], 0);
	}
	
	//assert(returnValue == 0);
	if(returnValue != 0){
		passed = 1;
		printf("Card Effect Returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//assert(state.handCount[1] == 2);	//player 2 has 2 cards 
	if(state.handCount[1] != 2){
		passed = 1;
		printf("Hand Count P2: %d, Expected: %d\n", state.handCount[1], 2);
	}
	
	//assert(state.handCount[0] == 2);	//player 1 has 4 cards (2 - 1 played + 3 drawn = 4)
	if(state.handCount[0] != 2){
		passed = 1;
		printf("Hand Count P1: %d, Expected: %d\n", state.handCount[0], 2);
	}
	
	//playing smithy card from position 0
	returnValue = cardEffect(smithy, 0, 0, 0, &state, 0, 0);
	
	if(state.deckCount[1] != 0){
		passed = 1;
		printf("Deck Count P2: %d, Expected: %d\n", state.deckCount[1], 0);
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	printf("Passing Tests: %d/5\n", testPassed);
	
	return 0;
}