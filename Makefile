#
# This is universal Makefile - without a need to add dependencies after
# adding of a new source file (dependencies are resolved automagically).
# This is for projects - when autotools/automake/autoconf is an overkill.
#
# It has a very basic unit test infrastructure (to test a function) - pass
# a symbol to the program (example: ./main mytest).
# Add the corresponding testing main under #ifdef - in the appropriate file
# and a line in this Makefile (taking ut1 as a template).
# This way - the main main() will be ignored and your main will be called.
# If we'll have many unit tests - we'll run them in a batch shell script.
#
#consider all *.c as sources  
SOURCES.c := $(wildcard *.c)
#main.c common.c utils.c

CCFLAGS= -ansi -mno-cygwin 

debug : CFLAGS = $(CCFLAGS) -g -Wall -Wundef -DAUDIT
pedantic : CFLAGS = $(CCFLAGS) -g -Wall -Wundef -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations
release : CFLAGS = $(CCFLAGS) -Wall -O2
#unit tests are here:
ut : CFLAGS = $(CCFLAGS) -g -DUNIT_TEST -DUTIL_UNIT_TEST
base64 : CFLAGS = $(CCFLAGS) -g -DUNIT_TEST -DBASE64_TEST
ut1 : CFLAGS = $(CCFLAGS) -g -DUNIT_TEST -DSOMETHING_ELSE

LFLAGS=-lm 

CC=gcc
BIN=nid
OBJS=$(SOURCES.c:.c=.o)
LINK=gcc $(CFLAGS)


.SUFFIXES:
.SUFFIXES: .d .o .h .c
.c.o: ; $(CC) $(CFLAGS) -MMD -c $*.c

.PHONY: clean

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

all release debug pedantic ut ut1: $(BIN)

$(BIN): $(OBJS)
	$(LINK) $(FLAGS) -o $(BIN) $(OBJS) $(LFLAGS)

clean:
	-rm -f $(BIN) $(OBJS) *.d


include $(sources:.c=.d)
