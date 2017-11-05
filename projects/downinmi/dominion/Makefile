CFLAGS = -Wall -fpic -coverage -lm -std=c99


	

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)


unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	echo "Result for running dominion.c unit tests:" > unittestresults.out
	
	echo "\nunittest1.c:" >> unittestresults.out
	gcc -o unittest1 dominion.o rngs.o unittest1.c $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "\nunittest2.c:" >> unittestresults.out
	gcc -o unittest2 dominion.o rngs.o unittest2.c $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "\nunittest3.c:" >> unittestresults.out
	gcc -o unittest3 dominion.o rngs.o unittest3.c $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "\nunittest4.c:" >> unittestresults.out
	gcc -o unittest4 dominion.o rngs.o unittest4.c $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "\ncardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 dominion.o rngs.o cardtest1.c $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "\ncardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 dominion.o rngs.o cardtest2.c $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "\ncardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 dominion.o rngs.o cardtest3.c $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "\ncardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 dominion.o rngs.o cardtest4.c $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out


randomtestadventurer.out: randomtestadventurer.c dominion.o rngs.o
	echo "Result for running dominion.c random tests(Adventurer):" > randomtestadventurer.out

	echo "\nrandomtestadventurer.c:" >> randomtestadventurer.out
	gcc -o randomtestadventurer dominion.o rngs.o randomtestadventurer.c $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	
randomtestcard1.out: randomtestcard1.c dominion.o rngs.o
	echo "Result for running dominion.c random tests(Smithy):" > randomtestcard1.out
	echo "\nrandomtestcard1.c:" >> randomtestcard1.out
	gcc -o randomtestcard1 dominion.o rngs.o randomtestcard1.c $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out

randomtestcard2.out: randomtestcard2.c dominion.o rngs.o
	echo "Result for running dominion.c random tests(Council Room):" > randomtestcard2.out
	echo "\nrandomtestcard2.c:" >> randomtestcard2.out
	gcc -o randomtestcard2 dominion.o rngs.o randomtestcard2.c $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out


 

	
all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out randomtestadventurer randomtestcard1 randomtestcard2 randomtestadventurer.out randomtestcard1.out randomtestcard2.out testDrawCard testDrawCard.exe unittestresults.out unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
