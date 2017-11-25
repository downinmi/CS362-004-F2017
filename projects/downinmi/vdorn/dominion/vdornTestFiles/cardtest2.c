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
	
	printf ("TESTING adventurerCard():\n");
	
	/********************************************/
	printf("Running card test 2.1: 2 Player Game, Player 1 Plays Adventurer\n");
	//initializing game with 2 players and 10 cards
	//playing adventurer for player 1
	struct gameState state;
	initializeGame(2, k, seed, &state);
	
	//setting decks to 10
	state.deckCount[0] = 10;
	state.deckCount[1] = 10;
	
	state.handCount[0] = 0;
	
	int returnValue = cardEffect(adventurer, 0, 0, 0, &state, 0, 0);
	//assert(returnValue == 0);
	if(returnValue != 0){
		passed = 1;
		printf("Card Effect Returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//assert(state.coins >= 2); //at least two coins/treasures were drawn from the deck
	if(state.coins < 2){
		passed = 1;
		printf("Coins: %d, Expected: >= 2\n", state.coins);
	}
	
	//assert(state.deckCount[0] <= 8); //at least two cards were drawn
	if(state.deckCount[0] > 8){
		passed = 1;
		printf("Deck Count P1: %d, Expected: <= 8\n", state.deckCount[0]);
	}
	
	//assert(state.discardCount[0] == (10 - (state.deckCount[0] + state.handCount[0])));
	if(state.discardCount[0] != (10 - (state.deckCount[0] + state.handCount[0]))){
		passed = 1;
		printf("Discard count P1: %d, Expected: %d\n", state.discardCount[0], (state.deckCount[0] + state.handCount[0]));
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	/********************************************/
	printf("Running card test 2.2: 2 Player Game, Player 2 Plays Adventurer\n");
	passed = 0;
	//initializing game with 2 players and 10 cards
	//playing adventurer for player 2
	initializeGame(2, k, seed, &state);
	
	state.handCount[1] = 0;
	
	//player 2
	state.whoseTurn++;
	
	//returnValue = adventurerCard(1, &state);
	returnValue = cardEffect(adventurer, 0, 0, 0, &state, 0, 0);
	//assert(returnValue == 0);
	if(returnValue != 0){
		passed = 1;
		printf("Card Effect Returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//assert(state.coins >= 2); //at least two coins/treasures were drawn from the deck
	if(state.coins < 2){
		passed = 1;
		printf("Coins: %d, Expected: >= 2\n", state.coins);
	}
	
	//assert(state.deckCount[1] <= 8); //at least two cards were drawns
	if(state.deckCount[1] > 8){
		passed = 1;
		printf("Deck Count P1: %d, Expected: <= 8\n", state.deckCount[1]);
	}
	
	//assert(state.discardCount[1] == (10 - (state.deckCount[1] + state.handCount[1])));	//discarded deck size - (deckcount + handcount)
	if(state.discardCount[1] != (10 - (state.deckCount[1] + state.handCount[1]))){
		passed = 1;
		printf("Discard count P1: %d, Expected: %d\n", state.discardCount[1], (state.deckCount[1] + state.handCount[1]));
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	/********************************************/
	printf("Running card test 2.3: 4 Player Game, Player 4 Plays Adventurer\n");
	passed = 0;
	//initializing game with 4 players and 10 cards
	//playing adventurer for player 4
	initializeGame(4, k, seed, &state);
	
	//giving player 4 zero cards
	state.handCount[3] = 0;
	
	//player 4
	state.whoseTurn = state.whoseTurn + 3;

	returnValue = cardEffect(adventurer, 0, 0, 0, &state, 0, 0);
	//assert(returnValue == 0);
	if(returnValue != 0){
		passed = 1;
		printf("Card Effect Returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//assert(state.coins >= 2); //at least two coins/treasures were drawn from the deck
	if(state.coins < 2){
		passed = 1;
		printf("Coins: %d, Expected: >= 2\n", state.coins);
	}
	
	//assert(state.deckCount[3] <= 8); //at least two cards were drawns
	if(state.deckCount[3] > 8){
		passed = 1;
		printf("Deck Count P4: %d, Expected: <= 8\n", state.deckCount[3]);
	}
	
	//assert(state.discardCount[3] == (10 - (state.deckCount[3] + state.handCount[3])));	//discarded deck size - (deckcount + handcount)
	if(state.discardCount[3] != (10 - (state.deckCount[3] + state.handCount[3]))){
		passed = 1;
		printf("Discard count P4: %d, Expected: %d\n", state.discardCount[3], (state.deckCount[3] + state.handCount[3]));
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	/********************************************/
	printf("Running card test 2.4: Continuation of 2.3 Game State, Player 4 Plays Adventurer Again\n");
	passed = 0;
	//playing adventurer for player 4 again
	
	returnValue = cardEffect(adventurer, 0, 0, 0, &state, 0, 0);
	
	//player 4
	state.whoseTurn--;
	
	//assert(returnValue == 0);
	if(returnValue != 0){
		passed = 1;
		printf("Card Effect Returned: %d, Expected: %d\n", returnValue, 0);
	}
	
	//assert(state.coins >= 2); //at least two coins/treasures were drawn from the deck
	if(state.coins < 2){
		passed = 1;
		printf("Coins: %d, Expected: >= 2\n", state.coins);
	}
	
	//assert(state.deckCount[3] <= 8); //at least two cards were drawns
	if(state.deckCount[3] > 8){
		passed = 1;
		printf("Deck Count P4: %d, Expected: <= 8\n", state.deckCount[3]);
	}
	
	//assert(state.discardCount[3] == (10 - (state.deckCount[3] + state.handCount[3])));	//discarded deck size - (deckcount + handcount)
	if(state.discardCount[3] != (10 - (state.deckCount[3] + state.handCount[3]))){
		passed = 1;
		printf("Discard count P4: %d, Expected: %d\n", state.discardCount[3], (state.deckCount[3] + state.handCount[3]));
	}
	
	if(passed == 0){
		testPassed++;
	}
	
	printf("Passing Tests: %d/4\n", testPassed);
	
	return 0;
}