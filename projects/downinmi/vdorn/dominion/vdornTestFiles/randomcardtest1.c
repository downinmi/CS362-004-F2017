/***************************************************
** Random Tester for Village Card
** Added to makefile:
** randomcardtest1: randomcardtest1.c dominion.o rngs.o
**	gcc -o randomcardtest1 -g  randomcardtest1.c dominion.o rngs.o $(CFLAGS)
****************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int main() {
	int seed = 37;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
	
	int currentPlayer;
	int handPos;
	int passed = 0;
	int testPassed = 0;
	
	int handCount;
	int playerCount;
	int i, m;
	char * tempString = (char *) malloc(sizeof(char) * 15);
	memset(tempString, '\0', sizeof(char) * 15);
	
	//keeping track of failed test cases
	char * testFailed = (char *) malloc(sizeof(char) * 16384);
	memset(testFailed, '\0', sizeof(char) * 16384);
	
	time_t timeNow = time(NULL);
	
	srand(timeNow);
	
	printf ("TESTING villageCard():\n");
	
	for(m = 0; m < 1000; m++){
		passed = 0;
		printf("Run %d...\n", m);
		//initializing game with 2 players
		//Randomize player count
		playerCount = rand() % 4 + 1; //random player count between 1 and 4
		//printf("Player Count: %d\n", playerCount);
		struct gameState state;
		initializeGame(playerCount, k, seed, &state);
		
		//setting decks to 10
		//printf("Starting Deck Count: %d\n", 10);
		for(i = 0; i < playerCount; i++){
			state.deckCount[i] = 10;
		}
		
		//random hand counts between 1 and 5
		handCount = rand() % 5 + 1;
		//printf("Hand Count: %d\n", handCount);
		for(i = 0; i < playerCount; i++){
			state.handCount[i] = handCount;
		}
		
		handPos = rand() % handCount + 1;
		//printf("Hand Position: %d\n", handPos);
		
		//playing adventurer for player 1
		//Randomized who player the card out of playercount
		currentPlayer = rand() % playerCount;
		//printf("CurrentPlayer: %d\n", currentPlayer);
		
		//int returnValue = testAdventurer(state, currentPlayer, handPos);
		
		state.whoseTurn = currentPlayer;
		
		struct gameState temp;
		memcpy(&temp, &state, sizeof(struct gameState));
	
		int returnValue = cardEffect(village, 0, 0, 0, &state, handPos, 0);
		
		//check values here:
		if(state.deckCount[currentPlayer] != (temp.deckCount[currentPlayer]) - 1){
			passed = 1;
			printf("Deck Count P1: %d, Expected: %d\n", state.deckCount[currentPlayer], (temp.deckCount[currentPlayer]) - 1);
		}
		
		//assert(returnValue == 0);
		if(returnValue != 0){
			passed = 1;
			printf("Card Effect Returned: %d, Expected: %d\n", returnValue, 0);
		}
		
		//assert(state.handCount[0] == (temp.handCount[0]));	//current hand count is hand count (discarded card village)
		if(state.handCount[currentPlayer] != (temp.handCount[currentPlayer])){
			passed = 1;
			printf("Hand Count P1: %d, Expected: %d\n", state.handCount[currentPlayer], (temp.handCount[currentPlayer]));
		}
		
		//assert(state.numActions == 3);	//started with 1 then gaining two actions from village; playCard must be called to decrement numActions
		if(state.numActions != 3){
			passed = 1;
			printf("Num Actions: %d, Expected: %d\n", state.numActions, 3);
		}
		
		if(passed == 0){
			testPassed++;
		}
		else{
			sprintf(tempString, "%d; ", m + 1);
			strcat(testFailed, tempString);
			memset(tempString, '\0', sizeof(char) * 15);
		}
	}
	
	printf("Passing Tests: %d/1000\n", testPassed);
	printf("Test failed: %s\n", testFailed);
	printf("Dominion Seed: 37\n");
	printf("Time as Seed: %ld\n", (long)timeNow);
	
	return 0;
}