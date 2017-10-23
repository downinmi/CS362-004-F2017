all: testme

testme: testme.o  
	gcc testme.o -o testme
	-./testme  

testme.o: testme.c
	gcc testme.c -c

clean:
	rm -f testme *.o