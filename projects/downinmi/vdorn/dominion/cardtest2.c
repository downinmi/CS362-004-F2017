#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

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
    int flag[2] = {0,0}; // 0 - Deck not correct, 1 - Hand not correct

 
    struct gameState GameState;
    int failCount= 0;
    
    initializeGame(testPlayers, k, seed, &GameState);
    printf("Card Test 2 - Smithy\n");
    printf("Playing Smithy 500 times...");
    for(int i = 0; i < 500; i++)
    {
        seed = i + 10;
        initializeGame(testPlayers, k, seed, &GameState);
    
        int deckBefore = GameState.deckCount[0];
        int handBefore = GameState.handCount[0];

        cardEffect(smithy, 0, 0, 0, &GameState, 1, NULL);
    

        int deckAfter = GameState.deckCount[0];
        int handAfter = GameState.handCount[0];

        if(deckBefore - deckAfter != 3)
        {
            if(noisy)
            {
                printf("Deck Isn't Correctly missing three cards - FAILED\n");
            }
            flag[0] = 1;
            failCount++;
        }

        if(handAfter - handBefore != 2)
        {
            if(noisy)
            {
                printf("Hand Hasn't Correctly gained two cards - FAILED\n");
            }
            flag[1] = 1;
            failCount++;
        }

    }

    if(failCount == 0)
    {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }
    printFlags(flag);


    return 0;


}


void printFlags(int* flag)
{
    printf("Tests:\n");
    if(flag[0])
    {
        printf("Current Player Deck Correctly Decreased By Three - FAILED\n");
    } else {
        printf("Current Player Deck Correctly Decreased By Three - PASSED\n");
    }


    if(flag[1])
    {
        printf("Current Player Hand Correctly Increased By Two (Three - discard) - FAILED\n");
    } else {
        printf("Current Player Hand Correctly Increased By Two (Three - discard) - PASSED\n");
    }


}