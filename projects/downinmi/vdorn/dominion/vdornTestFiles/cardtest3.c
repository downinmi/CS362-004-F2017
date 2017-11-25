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
	
	int passed = 0;
	int testPassed = 0;
	
	printf ("TESTING villageCard():\n");
	
	/********************************************/
	printf("Running card test 3.1: 2 Player Game, Player 1 Plays Village\n");
	//initializing game with 2 players and 10 cards
	//playing village for player 1
	struct gameState state;
	initializeGame(2, k, seed, &state);
	
	struct gameState temp;	//temp struct for the state
	memcpy(&temp, &state, sizeof(struct gameState));
	
	int returnValue = cardEffect(village, 0, 0, 0, &state, 0, 0);
	//assert(state.deckCount[0] == (temp.deckCount[0] - 1));
	if(state.deckCount[0] != (temp.deckCount[0] - 1)){
		passed = 1;
		printf("Deck Count P1: %d, Expected: %d\n", state.deckCount[0], (temp.deckCount[0] - 1));
	}
	
	//assert(returnValue == 0);
	if(returnValue != 0){
		passed = 1;
		printf("Card Effect Returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//assert(state.handCount[0] == (temp.handCount[0]));	//current hand count is hand count (discarded card village)
	if(state.handCount[0] != (temp.handCount[0])){
		passed = 1;
		printf("Hand Count P1: %d, Expected: %d\n", state.handCount[0], (temp.handCount[0]));
	}
	
	//assert(state.numActions == 3);	//started with 1 then gaining two actions from village; playCard must be called to decrement numActions
	if(state.numActions != 3){
		passed = 1;
		printf("Num Actions: %d, Expected: %d\n", state.numActions, 3);
	}
	
	//assert(state.handCount[1] == 0);	//player 2 has no cards in hand
	if(state.handCount[1] != 0){
		passed = 1;
		printf("Hand Count P2: %d, Expected: %d\n", state.handCount[1], 0);
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	/********************************************/
	printf("Running card test 3.2: 2 Player Game, Player 2 Plays Village\n");
	passed = 0;
	//initializing game with 2 players and 10 cards
	//playing village for player 2
	initializeGame(2, k, seed, &state);
	
	memcpy(&temp, &state, sizeof(struct gameState));
	
	//player 2
	state.whoseTurn++;

	returnValue = cardEffect(village, 0, 0, 0, &state, 0, 0);
	//assert(state.deckCount[1] == (temp.deckCount[1] - 1));
	if(state.deckCount[1] != (temp.deckCount[1] - 1)){
		passed = 1;
		printf("Deck Count P1: %d, Expected: %d\n", state.deckCount[1], (temp.deckCount[1] - 1));
	}
	
	//assert(returnValue == 0);
	if(returnValue != 0){
		passed = 1;
		printf("Card Effect Returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//assert(state.handCount[1] == (temp.handCount[1]));	//current hand count is hand count (discarded card village)
	if(state.handCount[1] != (temp.handCount[1])){
		passed = 1;
		printf("Hand Count P2: %d, Expected: %d\n", state.handCount[1], (temp.handCount[1]));
	}
	
	//assert(state.numActions == 3);	//started with 1 then gaining two actions from village; playCard must be called to decrement numActions
	if(state.numActions != 3){
		passed = 1;
		printf("Num Actions: %d, Expected: %d\n", state.numActions, 3);
	}
	
	//assert(state.handCount[1] == 0);	//player 2 has no cards in hand
	if(state.handCount[1] != 0){
		passed = 1;
		printf("Hand Count P2: %d, Expected: %d\n", state.handCount[1], 0);
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	/********************************************/
	printf("Running card test 3.3: 4 Player Game, Player 3 Players Village\n");
	passed = 0;
	//initializing game with 4 players and 10 cards
	//playing village for player 3
	initializeGame(4, k, seed, &state);
	
	memcpy(&temp, &state, sizeof(struct gameState));
	
	//player 3
	state.whoseTurn = 0;
	state.whoseTurn = state.whoseTurn + 2;
	
	returnValue = cardEffect(village, 0, 0, 0, &state, 0, 0);
	//assert(state.deckCount[2] == (temp.deckCount[2] - 1));
	if(state.deckCount[2] != (temp.deckCount[2] - 1)){
		passed = 1;
		printf("Deck Count P1: %d, Expected: %d\n", state.deckCount[2], (temp.deckCount[2] - 1));
	}
	
	//assert(returnValue == 0);
	if(returnValue != 0){
		passed = 1;
		printf("Card Effect Returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//assert(state.handCount[2] == (temp.handCount[2]));	//current hand count is hand count (discarded card village)
	if(state.handCount[2] != (temp.handCount[2])){
		passed = 1;
		printf("Hand Count P3: %d, Expected: %d\n", state.handCount[2], (temp.handCount[2]));
	}
	
	//assert(state.numActions == 3);	//started with 1 then gaining two actions from village; playCard must be called to decrement numActions
	if(state.numActions != 3){
		passed = 1;
		printf("Num Actions: %d, Expected: %d\n", state.numActions, 3);
	}
	
	//assert(state.handCount[0] == 5);	//player 1 starts with 5 cards
	if(state.handCount[0] != 5){
		passed = 1;
		printf("Hand Count P1: %d, Expected: %d\n", state.handCount[0], 5);
	}
	
	//assert(state.handCount[1] == 0);	//player 2 has no cards in hand
	if(state.handCount[1] != 0){
		passed = 1;
		printf("Hand Count P1: %d, Expected: %d\n", state.handCount[1], 0);
	}
	
	//assert(state.handCount[3] == 0);	//player 4 has no cards in hand
	if(state.handCount[3] != 0){
		passed = 1;
		printf("Hand Count P1: %d, Expected: %d\n", state.handCount[3], 0);
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	printf("Passing Tests: %d/3\n", testPassed);
	
	return 0;
}