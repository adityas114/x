all:
	gcc rtnice.c test.c -o test
clean:
	$(RM) test
