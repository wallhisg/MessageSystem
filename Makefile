SRCS		:=
OBJS		:=
DEPS		:=
TMPS		:=
LIBS		:=
PROGRAMS	:=
TESTS		:=
#======================================================================
# MODULES
MODULES		:= src/system src/message src/event src/driver
# LIBS
MODULES		+=
# APP
MODULES 	+=
# TESTS
MODULES		+=

INCLUDE_DIRS	:= include
vpath %.h $(INCLUDE_DIRS)
#======================================================================
# select which tools to use as compiler, 
# librarian and linker
#======================================================================
CFLAGS	+= -Wall
CFLAGS	+= $(addprefix -I , $(INCLUDE_DIRS))
#======================================================================
# select which tools to use as compiler, librarian and linker
#======================================================================
AR = ar
ARFLAGS = rv
#======================================================================
# Enviroment
#======================================================================
MKDIR		:= mkdir -p
RM		:= rm -f
MV		:= mf -f
#======================================================================
# Common modules
include $(patsubst %, ./%/xmodule.mk, $(MODULES))
# Current program
include ./MessageSystem/xmodule.mk

# Unit test
include ./unitTest/TEST_MESSAGE/TEST_ENDPOINT/xmodule.mk
include ./unitTest/TEST_EVENT/TEST_REACTOR/xmodule.mk
include ./unitTest/TEST_EVENT/TEST_HANDLE_EVENT/xmodule.mk
include ./unitTest/TEST_EVENT/TEST_EVENT_DESCRIPTION/xmodule.mk

#======================================================================
.PHONY: default build run all clean

all: $(OBJS) $(PROGRAMS) $(TESTS)

run: $(PROGRAMS)
	@$<
#======================================================================
# unitTest
test: $(OBJS) $(TMPS) $(TESTS)

TEST_MESSAGE_ENDPOINT:
	@./unitTest/TEST_MESSAGE/TEST_ENDPOINT/TEST_MESSAGE_ENDPOINT

TEST_EVENT_REACTOR:
	@./unitTest/TEST_EVENT/TEST_REACTOR/TEST_EVENT_REACTOR
	
TEST_HANDLE_EVENT:
	@./unitTest/TEST_EVENT/TEST_HANDLE_EVENT/TEST_HANDLE_EVENT
	
TEST_EVENT_DESCRIPTION:	
	@./unitTest/TEST_EVENT/TEST_EVENT_DESCRIPTION/TEST_EVENT_DESCRIPTION
	
mem_program: $(PROGRAMS)
	valgrind --tool=memcheck --leak-check=full --undef-value-errors=no $(PROGRAMS)
	
mem_test: $(TESTS)
	valgrind --tool=memcheck --leak-check=full --undef-value-errors=no $(TESTS)	
clean:
	$(RM) $(OBJS) $(DEPS) $(PROGRAMS) $(TMPS) $(TESTS)

	
