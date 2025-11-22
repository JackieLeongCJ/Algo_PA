# CC and CFLAGS are varilables
CC = gcc
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

all: bin/mps
	@echo -n ""

# $< means the first prerequisite
# $@ means the target file
# optimized version
bin/mps			: utils_opt.o main_opt.o 
			$(CC) $(OPTFLAGS) utils_opt.o main_opt.o -o $@ 
main_opt.o 	   	: src/main.c 
			$(CC) $(CFLAGS) $< -o $@
utils_opt.o		: src/utils.c src/utils.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

#debug version
# dbg : bin/mps
# 	@echo -n ""

# bin/mps 		: main_dbg.o 
# 			$(CC) $(DBGFLAGS) main_dbg.o -o bin/mps
# main_dbg.o 	   	: src/main.c 
# 			$(CC) $(CFLAGS) $< -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o bin/*
