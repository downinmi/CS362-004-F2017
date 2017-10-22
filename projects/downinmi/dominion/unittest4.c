#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>



int main(int argc, char* argv[])
{
 
    int k[10]= { adventurer, council_room, feast, gardens, mine, 
        remodel, smithy, village, baron, great_hall };
    int seed = 12;
    int testPlayers = 4;
    struct gameState GameState, compareGame;
    int failCount= 0;
    printf("Running Unit Test 4 - numHandCards()\n");
    initializeGame(testPlayers, k, seed, &GameState);

    memcpy(&compareGame, &GameState, sizeof(struct gameState));
    
    numHandCards(&GameState);

    if(memcmp(&compareGame, &GameState, sizeof(struct gameState)) == 0) //If the compareGame struct exactly matches the GameState struct
    {
        printf("GameState remains unchanged after function call...PASSED\n");
    } else{
        failCount++;
        printf("GameState remains unchanged after function call...FAILED\n");
    }

    printf("Test with every number of hands up to MAX_HAND:\n");
    int currentError = failCount;
    for(int player = 0; player < testPlayers; player++)
    {
        printf("Player %d...", player);
        GameState.whoseTurn = player; 
        for(int i = 0; i < MAX_HAND; i++)
        {
            GameState.handCount[player] = i;
            
            if( i != numHandCards(&GameState))
            {
                failCount++;
                printf("RETURN VALUE INCORRECT - FAILED\n");
            }
        }
        if(failCount == currentError)
        {
            printf("PASSED\n");
        } else {
            printf("FAILED\n");
        }
    }

    if(failCount > 0)
    {
        printf("UNIT TEST 2 FAILED - Not all tests passed\n");
    } else {
        printf("ALL TESTS PASSED\n");
    }

    return 0;
}
