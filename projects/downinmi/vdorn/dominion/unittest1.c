#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

int assertequal(int a, int b)
{
    if (a == b)
    {
        return 1;
    } else {
         return 0;
     }
}

int main(int argc, char* argv[])
{
 
    int k[10]= { adventurer, council_room, feast, gardens, mine, 
        remodel, smithy, village, baron, great_hall };
    int seed = 12;
    int testSize = 100;
    int testPlayers = 4;
    struct gameState GameState;
    
    printf("Running Unit Test 1 - fullDeckCount()\n");

    initializeGame(testPlayers, k, seed, &GameState);

    struct gameState compareGame;

    memcpy(&compareGame, &GameState, sizeof(struct gameState));

    fullDeckCount(0, 1, &GameState);


  
    if(memcmp(&compareGame, &GameState, sizeof(struct gameState)) == 0) //If the compareGame struct exactly matches the GameState struct
    {
        printf("GameState remains unchanged after function call...PASSED\n");
    } else{
        printf("GameState remains unchanged after function call...UNIT TEST 1 FAILED\n");
        return 0;
    }
        

    for(int player = 0; player < testPlayers; player++)
    {
        printf("Testing Player %d...", player+1);
        GameState.deckCount[player] = testSize;
        GameState.handCount[player] = testSize;
        GameState.discardCount[player] = testSize;

        for(int i =0; i < testSize; i++)
        {
            GameState.deck[player][i] = 0;
        }

        int passed = 0, testCount = 0, cardsPassed = 0;


        for(int i = 0;i < 10; i++ )
        {

            passed = 0;
            testCount = 0;

            for(int x = 0; x < testSize; x++)
            {
                GameState.deck[player][x] = -1;
                GameState.hand[player][x] = -1;
                GameState.discard[player][x] = -1;
            }

            for(int j = 0; j < testSize; j++)
            {
            

                for(int pos= 0; pos <= j; pos++)
                {
            
                    GameState.deck[player][pos] = i;
                    GameState.hand[player][pos] = i;
                    GameState.discard[player][pos] = i;

                }
         
                int count = fullDeckCount(player, i, &GameState);

                testCount++;
            
                passed += assertequal((j+1)*3, count);      

            }
            if(passed == testCount)
            {
                cardsPassed++;
            }
            
        
        
        }   

        if(cardsPassed == 10)
        {
            printf("All Cards Passed\n");
        } else {
            printf("UNIT TEST 1 FAILED\n");
            return 0;
        }


    }
    printf("ALL TESTS PASSED.\n");

    
    
    return 0;
}