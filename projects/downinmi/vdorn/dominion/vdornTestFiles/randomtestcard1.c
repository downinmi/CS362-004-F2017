#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void randomGameState(struct gameState *, int, int);
int countTreausres(int *, int);
int cardEffect(int ,int, int, int, struct gameState*, int, int*);



int main(int argc, char* argv[])
{
    const int DECK_COUNT = 0, HAND_COUNT = 1;
    int flags[2];

   
    int seed = 52;
    srand(seed);
    int testPlayers = 3;
    int numberOfTests = 50000;
    printf("Testing Smithy Card: %d Players  %d Tests\n", testPlayers, numberOfTests);
    
    for(int player = 0; player < testPlayers; player++)
    {
        printf("Testing Player %d...", player);
        flags[DECK_COUNT] = 0;
        flags[HAND_COUNT] = 0;

        for(int i = 0; i < numberOfTests; i++)
        {
            struct gameState GameState;
            randomGameState(&GameState, testPlayers, seed);
  
    
            GameState.whoseTurn = player;

            //Make sure we don't try to divide by zero if handCount = zero;
            int handPos;
            if(GameState.handCount[player] == 0)
            {
                handPos = 0;
            } else {
                 handPos = rand() % (GameState.handCount[player]);
            }


            int deckBefore = GameState.deckCount[player] + GameState.discardCount[player];
            int handBefore = GameState.handCount[player];

            cardEffect(smithy, 0, 0, 0, &GameState, handPos, NULL);
         
            int deckAfter = GameState.deckCount[player] + GameState.discardCount[player];
            int handAfter = GameState.handCount[player];

            if(deckBefore - deckAfter != 3)
            {
                flags[DECK_COUNT]++;
            }

            if(handAfter - handBefore != 3)
            {
                flags[HAND_COUNT]++;
            }


        }
        if(flags[DECK_COUNT] || flags[HAND_COUNT])
        {
            printf("\nErrors with Deck Counts: %d/%d \n", flags[DECK_COUNT], numberOfTests );
            printf("Errors with Hand Counts: %d/%d \n", flags[HAND_COUNT], numberOfTests );
        } else {
            printf("ALL TESTS PASSED\n");
        }

    }



}

void randomGameState(struct gameState *GameState, int testPlayers, int seed)
{
    int k[10]= { adventurer, council_room, feast, gardens, mine, 
        remodel, smithy, village, baron, great_hall };
    

    initializeGame(testPlayers, k, seed, GameState);

    for(int player = 0; player < testPlayers; player++)
    {
        int deckNum = rand() % (MAX_DECK - 9) + 10;
        int handNum = rand() % (MAX_HAND + 1);
        int discardNum = rand() % (MAX_HAND + 1);

        for(int i =0; i < deckNum; i++)
        {
            if(i < 3)
            {
                GameState->deck[player][i] = estate;
            } else if( i < 10)
            {
                GameState->deck[player][i] = copper;
            } else{
                GameState->deck[player][i] = rand() % (treasure_map + 1);
            }
        }
            GameState->deckCount[player] = deckNum;

        for(int i = GameState->handCount[player]; i < handNum; i++)
        {
            GameState->hand[player][i] = rand() % (treasure_map + 1);
    
        }
            GameState->handCount[player] = handNum;

        for(int i = GameState->discardCount[player]; i < discardNum; i++)
        {
            GameState->discard[player][i] = rand() % (treasure_map + 1);
        }
            GameState->discardCount[player] = discardNum;
            
    }
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