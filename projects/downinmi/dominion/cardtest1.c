#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

void printCards (struct gameState *);
int testAdventurer(struct gameState *GameState, int t, int o);
int countTreausres(int* array, int size );
void printFlags(int* flag);

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
    int flag[3] = {0, 0, 0};  // 0 = Bad Deck state, 1 = Bad Hand State, 2 = Bad Discard State

    struct gameState GameState;
    int failCount= 0;
    int errorStart = failCount;


    printf("Card Test 1 -  Adventurer\n");



    printf("Running 500 different seeds playing Adventurer first hand...");
    for(int i = 0; i < 500; i++)
    {
  
        
        seed = i + 10;
        initializeGame(testPlayers, k, seed, &GameState);
    
    
        int disResult, handResult, deckResult;
        int deckTreasures = countTreausres(&GameState.deck[0][0], GameState.deckCount[0]);
        int handTreasures = countTreausres(&GameState.hand[0][0], GameState.handCount[0]);
   
        //printf("Deck %d, Hand %d, Discard %d    ", deckTreasures, handTreasures, discardTreasures );
        cardEffect(adventurer, 0, 0, 0, &GameState, 1, NULL);
    
        deckResult = countTreausres(&GameState.deck[0][0], GameState.deckCount[0]);
        handResult = countTreausres(&GameState.hand[0][0], GameState.handCount[0]);
        disResult = countTreausres(&GameState.discard[0][0], GameState.discardCount[0]);
   
        if(deckTreasures - deckResult != 2)
        {
            if(noisy)
            {
                printf("Deck Not 2 Tresures Less - FAILED\n");
            }
            failCount++;
            flag[0] = 1;            
        }

        if(handResult - handTreasures != 2)
        {
            if(noisy)
            {
                printf("Hand Not 2 Tresures More - FAILED\n");
            }
            failCount++;
            flag[1] = 1;  
        }


        if(disResult != 0)
        {
            if(noisy)
            {
                printf("Discard Result Doesn't = 0 -  FAILED\n");
            }
            failCount++;
            flag[2] = 1;  
        }


         
        
     
    }
    if(failCount == errorStart)
    {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }

    //Run 50 tests where we swap the deck and discard first so we will need to shuffle
    errorStart = failCount;
    printf("Running 500 different seeds playing Adventurer with only 1 card in deck (requireing shuffle)...");
    
    for(int i = 0; i < 500; i++)
    {
      //  printf("Test %d:\n", i+1);
        errorStart = failCount;
        seed = i + 10;
        initializeGame(testPlayers, k, seed, &GameState);

        memcpy(GameState.discard[0], GameState.deck[0], sizeof(GameState.deck[0]));
        GameState.discardCount[0] = GameState.deckCount[0];
        GameState.deckCount[0] = 1;
    

    
        
        int disResult, handResult, deckResult;
        int deckTreasures = countTreausres(&GameState.deck[0][0], GameState.deckCount[0]);
        int handTreasures = countTreausres(&GameState.hand[0][0], GameState.handCount[0]);
        int discardTreasures = countTreausres(&GameState.discard[0][0], GameState.discardCount[0]);
   
        cardEffect(adventurer, 0, 0, 0, &GameState, 1, NULL);
    
        deckResult = countTreausres(&GameState.deck[0][0], GameState.deckCount[0]);
        handResult = countTreausres(&GameState.hand[0][0], GameState.handCount[0]);
        disResult = countTreausres(&GameState.discard[0][0], GameState.discardCount[0]);

        
   
        if((deckTreasures + discardTreasures) - deckResult  != 2)
        {
            if(noisy)
            {
                printf("Deck Not 2 Tresures Less - FAILED\n");
            }
            failCount++;
            flag[0] = 1;     
        }

        if(handResult - handTreasures != 2)
        {
            if(noisy)
            {
                printf("Hand Not 2 Tresures More - FAILED\n");
            }
            failCount++;
            flag[1] = 1;  
        }

        if(disResult != 0)
        {
            if(noisy)
            {
                printf("Discard Result Doesn't = 0 -  FAILED\n");
            }
            failCount++;
            flag[2] = 1;  
        }
        
     
    }

    if(failCount == errorStart)
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
        printf("Current Player Deck Correctly Contains Two Fewer TreasureCards - FAILED\n");
    } else {
        printf("Current Player Deck Correctly Contains Two Fewer Treasure Cards - PASSED\n");
    }


    if(flag[1])
    {
        printf("Current Player Hand Correctly Contains Two More Treasure Cards - FAILED\n");
    } else {
        printf("Current Player Deck Correctly Contains Two More Treasure Cards - PASSED\n");
    }

    if(flag[2])
    {
        printf("No Treausre Cards in Discard - FAILED\n");
    } else {
        printf("No Treausre Cards in Discard - PASSED\n");
    }

}



void printCards (struct gameState *GameState)
{
    printf("DECK:");
    for(int i = 0; i < GameState->deckCount[0]; i++)
    {
        printf("%d ", GameState->deck[0][i]);

    }
    printf("           ");

    printf("HAND:");
    for(int i = 0; i < GameState->handCount[0]; i++)
    {
        printf("%d ", GameState->hand[0][i]);
        
    }
    printf("           ");

    printf("DISCARD:");
    for(int i = 0; i < GameState->discardCount[0]; i++)
    {
        printf("%d ", GameState->discard[0][i]);
        
    }

    printf("\n");
}

     /*
        Treasure Cards:  4, 5, 6  =  copper, silver, gold
    */

    /****************FIRST TEST COPPER*******************
     *   1,1,4,4,7,7,7
     *  Should go through the sevens, discarding them, then put the 4s into the players
     * hand, leaving two 1s in the discard.
     * 
     * *****************************************************/  
int testAdventurer(struct gameState *GameState, int t, int o) // t = treasure, o = other
{
    int k[10]= { adventurer, council_room, feast, gardens, mine, 
        remodel, smithy, village, baron, great_hall };
    int seed = 12;
    int testPlayers = 4;
    initializeGame(testPlayers, k, seed, GameState);

    int failCount= 0;

    int startFail = failCount;
     GameState->deckCount[0] = 8;
    int firstInit[8] = {o,o,t,t,o,o,o};
    int hand[5] = {t,t,t,o,t};
    int disResultLength = 3, handResultLength = 7, deckResultLength = 2;
    int discardResult[3] = {o,o,o};
    int handResult[7] = {t,t,t,o,t,t,t};
    int deckResult[2] = {o,o};


    GameState->deckCount[0] = 8;
    memcpy(GameState->deck[0], firstInit, sizeof(firstInit));
    memcpy(GameState->hand[0], hand, sizeof(hand));

    cardEffect(adventurer, 0, 0, 0, GameState, 1, NULL);

        
    for(int i = 0; i < disResultLength; i++)
    {
        if(discardResult[i] != GameState->discard[0][i])
        {
            printf("Discard Pile Does Not Match Expected Value\n");
            failCount++;
        }
    }

    if(failCount == startFail)
    {
        printf("Discard Pile PASSED\n");
    }

    for(int i = 0; i < handResultLength; i++)
    {
        if(handResult[i] != GameState->hand[0][i])
        {
            printf("Hand Does Not Match Expected Value\n");
            failCount++;
        }
    }

    if(failCount == startFail)
    {
        printf("Hand PASSED\n");
    }


    for(int i = 0; i < deckResultLength; i++)
    {
        if(deckResult[i] != GameState->deck[0][i])
        {
            printf("Deck Does Not Match Expected Value\n");
            failCount++;
        }
    }

    if(failCount == startFail)
    {
        printf("Deck PASSED\n");
    }

    printf("\n");
    return failCount;
}

int countTreausres(int* array, int size )
{
    int count = 0;
    for(int i = 0; i < size; i++)
    {
        if(array[i] == 4 || array[i] == 5 || array[i] == 6)
        {
            count++;
        }
    }

    return count;
}