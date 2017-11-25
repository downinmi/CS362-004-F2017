/***************************************************
** Random Tester for Adventurer Card
** Added to makefile:
** randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
**	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
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
	int deckCards[4] = {copper, gold, silver, adventurer};
	
	int currentPlayer;
	int handPos;
	int passed = 0;
	int testPassed = 0;
	
	//int deckSize;
	int handCount;
	int playerCount;
	int i, j, m;
	char * tempString = (char *) malloc(sizeof(char) * 15);
	memset(tempString, '\0', sizeof(char) * 15);
	
	//keeping track of failed test cases
	char * testFailed = (char *) malloc(sizeof(char) * 16384);
	memset(testFailed, '\0', sizeof(char) * 16384);
	
	time_t timeNow = time(NULL);
	
	srand(timeNow);
	
	printf ("TESTING adventurerCard():\n");
	
	/********************************************/
	printf("Running random card tests\n");
	//run 100 random tests
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
			//filling the deck with copper, silver, and gold
			//to increase code coverage
			for(j = 0; j < 10; j++){
				state.deck[i][j] = deckCards[rand() % 4];
				//printf("Card: %i\n", state.deck[i][j]);
			}
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
	
		int returnValue = cardEffect(adventurer, 0, 0, 0, &state, handPos, 0);
	
		//printf("Deck Count after call: %d\n", state.deckCount[currentPlayer]);
		//printf("Hand Count after call: %d\n", state.handCount[currentPlayer]);
		
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
		if(state.deckCount[currentPlayer] > (temp.deckCount[currentPlayer] - 2)){
			passed = 1;
			printf("Deck Count P1: %d, Expected: <= %d\n", state.deckCount[0], (temp.deckCount[currentPlayer] - 2));
		}
		
		//checking discard pile count
		//must be equal to previous hand count plus 10 (starting deck size) minus current hand size plus current deck count
		if(state.discardCount[currentPlayer] != ((10 + temp.handCount[currentPlayer]) - (state.deckCount[currentPlayer] + state.handCount[currentPlayer]))){
			passed = 1;
			printf("Discard count P%d: %d, Expected: %d\n", currentPlayer + 1, state.discardCount[currentPlayer], ((10 + temp.handCount[currentPlayer]) - (state.deckCount[currentPlayer] + state.handCount[currentPlayer])));
		}
		
		if(passed == 0){
			testPassed++;
		}
		else{
			sprintf(tempString, "%d; ", m);
			strcat(testFailed, tempString);
		}
	}
	
	printf("Passing Tests: %d/1000\n", testPassed);
	printf("Test failed: %s\n", testFailed);
	printf("Dominion Seed: 37\n");
	printf("Time as Seed: %ld\n", (long)timeNow);
	
	return 0;
}