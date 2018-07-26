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
MODULES		+= src/json 
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
CFLAGS	+= -Wall -O1
CFLAGS	+= -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
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
include ./unitTest/TEST_DRIVER/TEST_RING_BUFFER/xmodule.mk
include ./unitTest/TEST_DRIVER/TEST_UART/xmodule.mk
# JSON
include ./unitTest/TEST_JSON/TEST_JSON_STRING/xmodule.mk
include ./unitTest/TEST_JSON/TEST_JSON_OBJECT/xmodule.mk
include ./unitTest/TEST_JSON/TEST_JSON_ARRAY/xmodule.mk
include ./unitTest/TEST_JSON/TEST_JSON_OBJECT_ARRAY/xmodule.mk
include ./unitTest/TEST_JSON/TEST_JSON_OBJECT_READ/xmodule.mk

#======================================================================
.PHONY: default build run all clean

all: $(OBJS) $(PROGRAMS) $(TESTS)

run: $(PROGRAMS)
	@$<
#======================================================================
# unitTest
test: $(OBJS) $(TMPS) $(TESTS)

# TEST MESSAGE
TEST_MESSAGE_ENDPOINT_EXE:
	@./unitTest/TEST_MESSAGE/TEST_ENDPOINT/TEST_MESSAGE_ENDPOINT_EXE

# TEST EVENT
TEST_EVENT_REACTOR_EXE:
	@./unitTest/TEST_EVENT/TEST_REACTOR/TEST_EVENT_REACTOR_EXE
	
TEST_HANDLE_EVENT_EXE:
	@./unitTest/TEST_EVENT/TEST_HANDLE_EVENT/TEST_HANDLE_EVENT_EXE
	
TEST_EVENT_DESCRIPTION_EXE:	
	@./unitTest/TEST_EVENT/TEST_EVENT_DESCRIPTION/TEST_EVENT_DESCRIPTION_EXE

# TEST DRIVER
TEST_RING_BUFFER_EXE:
	@./unitTest/TEST_DRIVER/TEST_RING_BUFFER/TEST_RING_BUFFER_EXE

TEST_UART_EXE:
	@./unitTest/TEST_DRIVER/TEST_UART/TEST_UART_EXE

# TEST JSON
TEST_JSON_STRING_EXE:
	@./unitTest/TEST_JSON/TEST_JSON_STRING/TEST_JSON_STRING_EXE
	
TEST_JSON_OBJECT_EXE:
	@./unitTest/TEST_JSON/TEST_JSON_OBJECT/TEST_JSON_OBJECT_EXE
	
TEST_JSON_ARRAY_EXE:
	@./unitTest/TEST_JSON/TEST_JSON_ARRAY/TEST_JSON_ARRAY_EXE

TEST_JSON_OBJECT_ARRAY_EXE:
	@./unitTest/TEST_JSON/TEST_JSON_OBJECT_ARRAY/TEST_JSON_OBJECT_ARRAY_EXE

TEST_JSON_OBJECT_READ_EXE:
	@./unitTest/TEST_JSON/TEST_JSON_OBJECT_READ/TEST_JSON_OBJECT_READ_EXE
# TEST MEM	
mem_program: $(PROGRAMS)
	valgrind --tool=memcheck --leak-check=full --undef-value-errors=no $(PROGRAMS)
	
mem_test: $(TEST_HANDLE_EVENT)
	valgrind --tool=memcheck --leak-check=full --undef-value-errors=no $(TEST_HANDLE_EVENT)	
clean:
	$(RM) $(OBJS) $(DEPS) $(PROGRAMS) $(TMPS) $(TESTS)

	
