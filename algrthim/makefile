CC=g++
OBJS=algx.o test_program.o
CFLAGS=-c -O2 
LFLAGS=-static
PROGRAM=test_program

test_program: $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM) $(LFLAGS)

test_program.o: test_program.cpp
	$(CC) test_program.cpp -o test_program.o $(CFLAGS)

algx.o: algx.cpp
	$(CC) algx.cpp -o algx.o $(CFLAGS)

clean:
	@rm -f $(OBJS)
	@rm -f $(PROGRAM)
