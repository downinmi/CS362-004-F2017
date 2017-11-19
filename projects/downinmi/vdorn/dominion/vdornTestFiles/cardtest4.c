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
	
	printf ("TESTING councilRoomCard():\n");
	
	/********************************************/
	printf("Running card test 4.1: 2 Player Game, Player 1 Plays Council Room\n");
	//initializing game with 2 players and 10 cards
	//playing council_room for player 1
	struct gameState state;
	initializeGame(2, k, seed, &state);
	
	struct gameState temp;	//temp struct for the state
	memcpy(&temp, &state, sizeof(struct gameState));
	
	int returnValue = cardEffect(council_room, 0, 0, 0, &state, 0, 0);
	//assert(returnValue == 0);
	if(returnValue != 0){
		passed = 1;
		printf("Card Effect Returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//check card count for current player temp Card count + 4 - discard card
	//assert(state.handCount[0] == (temp.handCount[0] + 3));
	if(state.handCount[0] != (temp.handCount[0] + 3)){
		passed = 1;
		printf("Hand Count P1: %d, Expected: %d\n", state.handCount[0], (temp.handCount[0] + 3));
	}
	
	//check plus one buy for current player
	//assert(state.numBuys == (temp.numBuys + 1));
	if(state.numBuys != (temp.numBuys + 1)){
		passed = 1;
		printf("Num Buys: %d, Expected: %d\n", state.numBuys, (temp.numBuys + 1));
	}
	
	//check card count for every other player temp card count for each player plus 1
	//assert(state.handCount[1] == (temp.handCount[1] + 1));
	if(state.handCount[1] != (temp.handCount[1] + 1)){
		passed = 1;
		printf("Hand Count P2: %d, Expected: %d\n", state.handCount[1], (temp.handCount[1] + 1));
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	/********************************************/
	printf("Running card test 4.2: 4 Player Game, Player 1 Plays Council Room\n");
	passed = 0;
	//initializing game with 4 players and 10 cards
	//playing council_room for player 1
	initializeGame(4, k, seed, &state);
	
	memcpy(&temp, &state, sizeof(struct gameState));
	
	returnValue = cardEffect(council_room, 0, 0, 0, &state, 0, 0);
	//assert(returnValue == 0);
	if(returnValue != 0){
		passed = 1;
		printf("Card Effect Returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//check card count for current player temp Card count + 4 - discard card
	//assert(state.handCount[0] == (temp.handCount[0] + 3));
	if(state.handCount[0] != (temp.handCount[0] + 3)){
		passed = 1;
		printf("Hand Count P1: %d, Expected: %d\n", state.handCount[0], (temp.handCount[0] + 3));
	}
	
	//check plus one buy for current player
	//assert(state.numBuys == (temp.numBuys + 1));
	if(state.numBuys != (temp.numBuys + 1)){
		passed = 1;
		printf("Num Buys: %d, Expected: %d\n", state.numBuys, (temp.numBuys + 1));
	}
	
	//check card count for every other player temp card count for each player plus 1
	//assert(state.handCount[1] == (temp.handCount[1] + 1));
	if(state.handCount[1] != (temp.handCount[1] + 1)){
		passed = 1;
		printf("Hand Count P2: %d, Expected: %d\n", state.handCount[1], (temp.handCount[1] + 1));
	}
	
	//assert(state.handCount[2] == (temp.handCount[2] + 1));
	if(state.handCount[2] != (temp.handCount[2] + 1)){
		passed = 1;
		printf("Hand Count P3: %d, Expected: %d\n", state.handCount[2], (temp.handCount[2] + 1));
	}
	
	//assert(state.handCount[3] == (temp.handCount[3] + 1));
	if(state.handCount[3] != (temp.handCount[3] + 1)){
		passed = 1;
		printf("Hand Count P4: %d, Expected: %d\n", state.handCount[3], (temp.handCount[3] + 1));
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	/********************************************/
	printf("Running card test 4.3: Continuation of 4.2 Game State, Player 2 Plays Council Room\n");
	passed = 0;
	//initializing game with 4 players and 10 cards
	//playing council_room for player 2
	//calling a second time on same gamestate
	
	memcpy(&temp, &state, sizeof(struct gameState));
	
	//played by player 2
	state.whoseTurn = 1;
	returnValue = cardEffect(council_room, 0, 0, 0, &state, 0, 0);
	//assert(returnValue == 0);
	if(returnValue != 0){
		passed = 1;
		printf("Card Effect Returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//check card count for current player temp Card count + 4 - discard card
	//assert(state.handCount[1] == (temp.handCount[1] + 3));
	if(state.handCount[1] != (temp.handCount[1] + 3)){
		passed = 1;
		printf("Hand Count P2: %d, Expected: %d\n", state.handCount[1], (temp.handCount[1] + 3));
	}
	
	//check plus one buy for current player
	//assert(state.numBuys == (temp.numBuys + 1));
	if(state.numBuys != (temp.numBuys + 1)){
		passed = 1;
		printf("Num Buys: %d, Expected: %d\n", state.numBuys, (temp.numBuys + 1));
	}
	
	//check card count for every other player temp card count for each player plus 1
	//assert(state.handCount[0] == (temp.handCount[0] + 1));
	if(state.handCount[0] != (temp.handCount[0] + 1)){
		passed = 1;
		printf("Hand Count P1: %d, Expected: %d\n", state.handCount[0], (temp.handCount[0] + 1));
	}
	
	//assert(state.handCount[2] == (temp.handCount[2] + 1));
	if(state.handCount[2] != (temp.handCount[2] + 1)){
		passed = 1;
		printf("Hand Count P3: %d, Expected: %d\n", state.handCount[2], (temp.handCount[2] + 1));
	}
	
	//assert(state.handCount[3] == (temp.handCount[3] + 1));
	if(state.handCount[3] != (temp.handCount[3] + 1)){
		passed = 1;
		printf("Hand Count P4: %d, Expected: %d\n", state.handCount[3], (temp.handCount[3] + 1));
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	printf("Passing Tests: %d/3\n", testPassed);
	
	return 0;
}