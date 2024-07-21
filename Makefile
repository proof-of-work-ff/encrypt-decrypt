#compiler name
CC := gcc -g -Wall

#remove command
RM := rm -rf

#source files
SOURCES := project_provided.c Console_IO_Utility.c File_Input_Utility.c File_Output_Utility.c

%.o: %.c
	$(CC) -c $< -o $@
 
#object files
OBJS := $(SOURCES:.c=.o)

#main target
main: $(OBJS)
	$(CC) $^ -o $@

run: main
	./main

.PHONY: clean
clean:
	$(RM) *.o main