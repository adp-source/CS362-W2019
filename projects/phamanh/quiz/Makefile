testme:
	gcc -o testme testme.c -g -coverage -lm -fpic
	./testme

gcov:
	gcov testme.c -b
	cat testme.c.gcov

clean:
	rm -rf testme *.gcov *.gcda *.gcno *.so *.out testme.dSYM
