# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -g

objects = src/main.o src/system.o src/auth.o

atm : $(objects)
	cc -o atm $(objects)

# Pattern rule for compiling .c to .o
%.o : %.c
	cc -c $< -o $@

src/main.o : src/header.h
src/kbd.o : src/header.h
src/command.o : src/header.h
src/display.o : src/header.h
src/insert.o : src/header.h
src/search.o : src/header.h
src/files.o : src/header.h
src/utils.o : src/header.h

clean :
	rm -f $(objects) atm
