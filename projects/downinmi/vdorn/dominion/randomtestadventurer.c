#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void randomGameState(struct gameState *, int, int);
int countTreausres(int *, int);
int cardEffect(int ,int, int, int, struct gameState*, int, int*);

int main(int argc, char* argv[])
{
    const int DECK_TREASURES = 0, HAND_TREASURES = 1, DECK_DIS_COUNT = 3;
    int flags[3];

   
    int seed = 52;
    srand(seed);
    int testPlayers = 3;
    int numberOfTests = 50000;
    printf("Testing Adventure Card: %d Players  %d Tests\n", testPlayers, numberOfTests);
    
    for(int player = 0; player < testPlayers; player++)
    {
        printf("Testing Player %d...", player);
        flags[DECK_TREASURES] = 0;
        flags[HAND_TREASURES] = 0;
        flags[DECK_DIS_COUNT] = 0;

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


            int deckTreasuresBefore = countTreausres(GameState.deck[player], GameState.deckCount[player]) 
                                        + countTreausres(GameState.discard[player], GameState.discardCount[player]);
            int handTreasuresBefore = countTreausres(GameState.hand[player], GameState.handCount[player]);
            int deckDisBefore = GameState.discardCount[player] + GameState.deckCount[player];

            cardEffect(adventurer, 0, 0, 0, &GameState, handPos, NULL);
            int deckTreasuresAfter =  countTreausres(GameState.deck[player], GameState.deckCount[player]) + countTreausres(GameState.discard[player], GameState.discardCount[player]);    
            int handTreasuresAfter = countTreausres(GameState.hand[player], GameState.handCount[player]);
            int deckDisAfter = GameState.discardCount[player] + GameState.deckCount[player];
         

            if(deckTreasuresBefore - deckTreasuresAfter != 2)
            {
                flags[DECK_TREASURES]++;
            }

            if(handTreasuresAfter - handTreasuresBefore != 2)
            {
                flags[HAND_TREASURES]++;
            }

            if(deckDisBefore - deckDisAfter != 2)
            {
                flags[DECK_DIS_COUNT]++;
            }

    

        }
        if(flags[DECK_TREASURES] || flags[HAND_TREASURES] || flags[DECK_DIS_COUNT])
        {
            printf("\nErrors with Deck Treasure Counts: %d/%d \n", flags[DECK_TREASURES], numberOfTests );
            printf("Errors with Hand Treasure Counts: %d/%d \n", flags[HAND_TREASURES], numberOfTests );
            printf("Errors with Deck / Discard Count: %d/%d \n", flags[DECK_DIS_COUNT], numberOfTests );
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
        int deckNum = rand() % (MAX_DECK +1);
        int handNum = rand() % (MAX_HAND + 1);
        int discardNum = rand() % (MAX_HAND - 9) + 10;

        for(int i =0; i < deckNum; i++)
        {
            
                GameState->deck[player][i] = rand() % (treasure_map + 1);
            
        }
            GameState->deckCount[player] = deckNum;

        for(int i = GameState->handCount[player]; i < handNum; i++)
        {
            GameState->hand[player][i] = rand() % (treasure_map + 1);
    
        }
            GameState->handCount[player] = handNum;

        for(int i = GameState->discardCount[player]; i < discardNum; i++)
        {
            if(i < 3)
            {
                GameState->deck[player][i] = estate;
            } else if( i < 10)
            {
                GameState->deck[player][i] = copper;
            } else{
            GameState->discard[player][i] = rand() % (treasure_map + 1);
            }
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