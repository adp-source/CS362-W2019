# modify these variables to point to gcc and gcov
CC="/usr/local/Cellar/gcc/8.2.0/bin/gcc-8"
GCOV="/usr/local/Cellar/gcc/8.2.0/bin/gcov-8"
CFLAGS=-Wall -fpic -std=c99 -MMD -MP -fprofile-arcs -ftest-coverage 

# modify these variables as source/binary files are added or removed
SRCS=cards.c dominion.c interface.c rngs.c
OBJS=$(SRCS:.c=.o)
TESTS=testDrawCard testBuyCard testShuffle testInit
BINARIES=$(TESTS) playdom player

# default action to build all binaries
.PHONY=all
all: $(BINARIES)

# compiles all the binaries and generates dependencies
$(BINARIES): % : %.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ 

# build all the generated dependencies
-include $(wildcard *.d)

.PHONY=runtests
runtests: $(TESTS)
	rm -f unittestresult.out
	./testBuyCard  >> unittestresult.out
	echo >> unittestresult.out
	./testDrawCard >> unittestresult.out
	echo >> unittestresult.out
	./testShuffle  >> unittestresult.out
	echo >> unittestresult.out
	./testInit -1  >> unittestresult.out
	echo >> unittestresult.out
	$(GCOV) dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

.PHONY=unittestresults
unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c rngs.c cards.c
	echo "Unit test results" > unittestresults.out
	echo >> unittestresults.out
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 unittest1.c dominion.c rngs.c cards.c $(CFLAGS)
	./unittest1 >> unittestresults.out
	echo >> unittestresults.out
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 unittest2.c dominion.c rngs.c cards.c $(CFLAGS)
	./unittest2 >> unittestresults.out
	echo >> unittestresults.out
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 unittest3.c dominion.c rngs.c cards.c $(CFLAGS)
	./unittest3 >> unittestresults.out
	echo >> unittestresults.out
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 unittest4.c dominion.c rngs.c cards.c $(CFLAGS)
	./unittest4 >> unittestresults.out
	echo >> unittestresults.out
	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 cardtest1.c dominion.c rngs.c cards.c $(CFLAGS)
	./cardtest1 >> unittestresults.out
	echo >> unittestresults.out
	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 cardtest2.c dominion.c rngs.c cards.c $(CFLAGS)
	./cardtest2 >> unittestresults.out
	echo >> unittestresults.out
	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 cardtest3.c dominion.c rngs.c cards.c $(CFLAGS)
	./cardtest3 >> unittestresults.out
	echo >> unittestresults.out
	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 cardtest4.c dominion.c rngs.c cards.c $(CFLAGS)
	./cardtest4 >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c >> unittestresults.out

.PHONY=clean
clean:
	rm -f *.o *.exe *.gcov *.gcda *.gcno *.so *.out *.d
	rm -rf *.dSYM
	rm -f playdom player testDrawCard badTestDrawCard testBuyCard testInit testShuffle
