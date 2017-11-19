
    //if stack of Province cards is empty, the game ends
    //if three supply pile are at 0, the game ends

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
        printf("Running Unit Test 2 - isGameOver()\n");
        initializeGame(testPlayers, k, seed, &GameState);
        
            
        memcpy(&compareGame, &GameState, sizeof(struct gameState));
        
        isGameOver(&GameState);
        if(memcmp(&compareGame, &GameState, sizeof(struct gameState)) == 0) //If the compareGame struct exactly matches the GameState struct
        {
            printf("GameState remains unchanged after function call...PASSED\n");
        } else{
            failCount++;
            printf("GameState remains unchanged after function call...FAILED\n");
        }

        printf("Calling isGameOver() on new game...");
        int r = isGameOver(&GameState);
        
        
        if(r == 0)
        {
            printf("isGameOver() returned 0...PASSED\n");
        } else{
            failCount++;
            printf("isGameOver() returned 0...FAILED\n");
        }

        printf("Setting provinces to 0 an calling isGameOver()... ");
        GameState.supplyCount[province] = 0;
        r = isGameOver(&GameState);
        if(r == 1)
        {
            printf("isGameOver() returned 1...PASSED\n");
        } else{
            failCount++;
            printf("isGameOver() returned 1...FAILED\n");
         
        }
        
     
        int supplyZeroCount, rightAnswer;
        printf("Testing all supply cards...");
        int currentErrors = failCount;
        for(int a = 0; a < treasure_map ; a++)
        {
            for(int b = 0; b < treasure_map; b++)
            {
                for(int c = 0; c < treasure_map; c++)
                {
                    for(int i = 0; i < treasure_map; i++)
                    {
                        GameState.supplyCount[i] = 1;
                    }

                    GameState.supplyCount[a] = 0;
                    GameState.supplyCount[b] = 0;
                    GameState.supplyCount[c] = 0;

                    if(a == b)
                    {
                        if(a == c)
                        {
                            supplyZeroCount = 1;
                        } else {                        
                            supplyZeroCount = 2;
                        }
                    }
                        else if(b == c || c == a)
                        {
                            supplyZeroCount = 2;
                        } else {                        
                            supplyZeroCount = 3;
                        }

                    if(supplyZeroCount == 3)
                    {
                        rightAnswer = 1;
                    }   else {
                        rightAnswer = 0;
                    }

                    if(a == province || b == province || c == province)
                    {
                        rightAnswer = 1;
                    }
                    
                    r = isGameOver(&GameState);
        
                    
                  
                    if(r != rightAnswer)
                    
                      
                    {
                        //printf("Was Expecting %d, but isGameRunning() returned %d (Empty Supply Piles: %d, %d, %d) TEST FAILED\n",rightAnswer, r,  a, b, c);
                        failCount++;
                    }

               


                   
                        
                }

            }
        }
        if(failCount == currentErrors)
        {
            printf("PASSED\n");
        } else {
            printf("FAILED\n");
        }
        
        if(failCount > 0)
        {
            printf("UNIT TEST 2 FAILED - Not all tests passed\n");
        } else {
            printf("ALL TESTS PASSED\n");
        }
    
        return 0;
    }