SRCS		:=
OBJS		:=
DEPS		:=
TMPS		:=
LIBS		:=
PROGRAMS	:=
TESTS		:=
#======================================================================
# MODULES
MODULES		:= src
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

#======================================================================
.PHONY: default build run all clean

all: $(OBJS) $(PROGRAMS)

run: $(PROGRAMS)
	@$<
#======================================================================
# unitTest
test: $(TESTS)



#mem_program: $(PROGRAMS)
#	valgrind --tool=memcheck --leak-check=full --undef-value-errors=no $(PROGRAMS)
	
clean:
	$(RM) $(OBJS) $(DEPS) $(PROGRAMS) $(TMPS) $(TESTS)
