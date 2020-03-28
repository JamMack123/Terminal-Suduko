CC=g++
OBJS=doubly_linked_lists.o test_program.o
CFLAGS=-c -O2 
LFLAGS=-static
PROGRAM=test_program

test_program: $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM) $(LFLAGS)

test_program.o: test_program.cpp
	$(CC) test_program.cpp -o test_program.o $(CFLAGS)

doubly_linked_list.o: doubly_linked_lists.cpp
	$(CC) doubly_linked_lists.cpp -o doubly_linked_lists.o $(CFLAGS)

clean:
	@rm -f $(OBJS)
	@rm -f $(PROGRAM)
  
