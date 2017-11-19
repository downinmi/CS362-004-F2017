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
    int testHandSize = 10;
    struct gameState GameState, compareGame;
    int failCount= 0;
    printf("Running Unit Test 2 - handCard()\n");
    initializeGame(testPlayers, k, seed, &GameState);

    memcpy(&compareGame, &GameState, sizeof(struct gameState));
    
   handCard(4, &GameState);

    if(memcmp(&compareGame, &GameState, sizeof(struct gameState)) == 0) //If the compareGame struct exactly matches the GameState struct
    {
        printf("GameState remains unchanged after function call...PASSED\n");
    } else{
        failCount++;
        printf("GameState remains unchanged after function call...FAILED\n");
    }

    printf("Call on each position in a %d card hand...\n", testHandSize);
    int currentError = failCount;
    for(int player = 0; player < testPlayers; player++)
    {
        printf("Player %d...", player);
        GameState.whoseTurn = player; 
        GameState.handCount[player] = testHandSize;
        for(int i = 0; i < testHandSize; i++)
        {
            GameState.hand[player][i] = player;
        }

    

        for(int cardPos = 0; cardPos < GameState.handCount[player]; cardPos++)
        {
            int r = handCard(cardPos, &GameState);
           if(r != GameState.hand[player][cardPos])
           {
                failCount++;
           }

           if(r < curse || r > treasure_map)
           {
               failCount++;
               printf("RETURN VALUE OUTSIDE RANGE OF CARDS - FAIL\n");
           }

        }

        if(failCount == currentError)
        {   
            printf("PASSED\n");
        } else{
            printf("FAILED\n");
        }
        
    }

    printf("Call with -100...");
    GameState.whoseTurn = 0;
  
    int r = handCard(-100, &GameState);
    if(r != -1)  //If the card is outside the range, or doesn't = -1 (which would indicate an error)
    {
        printf("WARNING: RETURN VALUE NOT -1 - FUNCTION NOT ERROR CHECKING\n");
    }

    printf("Call with 100...");
    GameState.whoseTurn = 0;
  
    r = handCard(100, &GameState);
    if( r != -1)  //If the card is outside the range, or doesn't = -1 (which would indicate an error)
    {
       
        printf("WARNING: RETURN VALUE NOT -1 - FUNCTION NOT ERROR CHECKING\n");
    }

    if(failCount > 0)
    {
        printf("UNIT TEST 3 FAILED - Not all tests passed\n");
    } else {
        printf("ALL TESTS PASSED\n");
    }

    return 0;
}
