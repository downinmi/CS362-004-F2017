#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printFlags(int*);



int main(int argc, char* argv[])
{
    int noisy = 0;
    if(argc == 2)
    {
        if(strcmp(argv[1], "-n") == 0);
        {
            noisy = 1;
        }
    }

    int k[10]= { adventurer, council_room, feast, gardens, mine, 
        remodel, smithy, village, baron, great_hall };
    int seed = 121;
    int testPlayers = 4;
  
    struct gameState GameState;
    int failCount= 0;
    int flag[4] = {0, 0, 0, 0};  // 0 = Bad Deck state, 1 = Bad Hand State, 2 = Actions not correct
    int *playerHands = (int*)malloc(sizeof(int)* GameState.numPlayers);    
    printf("Card Test 4 -  Great Hall\n");
    printf("Playing Great Hall 500 times...");
    for(int i = 0; i < 500; i++)
    {

        seed = i + 10;
        initializeGame(testPlayers, k, seed, &GameState);


        
        int deckBefore = GameState.deckCount[0];
        int handBefore = GameState.handCount[0];
        
  

        int actionsBefore = GameState.numActions;

        cardEffect(great_hall, 0, 0, 0, &GameState, 1, NULL);

    

        int deckAfter = GameState.deckCount[0];
        int handAfter = GameState.handCount[0];

        
    

        if(deckBefore - deckAfter != 1)
        {
            if(noisy)
            {
                printf("Deck Isn't Correctly missing one cards - FAILED\n");
            }
            flag[0] = 1;
            failCount++;
        }

        if(handAfter != handBefore )
        {
            if(noisy)
            {
                printf("Hand Hasn't Correctly gained one cards - FAILED\n");
            }
            flag[1] = 1;
            failCount++;
        }


        if(actionsBefore != GameState.numActions  - 1)
        {
            if(noisy)
            {
                printf("Current Player actions not increased by one- FAILED\n");
            }
            flag[2] = 1;
            failCount++;
        }

    }
    
    if(failCount == 0)
    {
        printf("PASSED\n");
    } else{
        printf("FAILED\n");
        printFlags(flag);
    }

    free(playerHands);
 
    return 0;
}

void printFlags(int* flag)
{
    printf("Tests:\n");
    if(flag[0])
    {
        printf("Current Player Deck Correctly Decreased By One - FAILED\n");
    } else {
        printf("Current Player Deck Correctly Decreased By One - PASSED\n");
    }


    if(flag[1])
    {
        printf("Current Player Hand Correctly Increased By Zero (One - discard) - FAILED\n");
    } else {
        printf("Current Player Hand Correctly Increased By Zero (One - discard) - PASSED\n");
    }


    if(flag[2])
    {
        printf("Current Player Actions Increased By One - FAILED\n");
    } else {
        printf("Current Player Actions Increased By One  - PASSED\n");
    }

}