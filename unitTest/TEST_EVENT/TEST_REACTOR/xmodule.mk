LOCAL_BASE	:= unitTest/TEST_EVENT/TEST_REACTOR
LOCAL_MDLS	:=
LOCAL_BLDS	:= $(addprefix $(LOCAL_BASE)/, $(LOCAL_MDLS))

LOCAL_INCS	:= $(wildcard $(LOCAL_BASE)/*.h)
LOCAL_INCS	+= $(wildcard $(INCLUDE_DIRS)/$(LOCAL_MDLS)/*.h)

LOCAL_SRCS	:= $(wildcard $(LOCAL_BASE)/*.c)
LOCAL_SRCS	+= $(foreach sdir, $(LOCAL_BLDS), $(wildcard $(sdir)/*.c))

REACTOR_OBJS	:= $(patsubst %.c, %.o, $(LOCAL_SRCS))
LOCAL_DEPS	:= $(patsubst %.c, %.deps, $(LOCAL_SRCS))

TMPS		+= $(REACTOR_OBJS)
DEPS		+= $(LOCAL_DEPS)

TARGET		:= TEST_EVENT_REACTOR
TEST_REACTOR	:= $(addprefix $(LOCAL_BASE)/, $(TARGET))
TESTS		+= $(TEST_REACTOR)

$(LOCAL_DEPS): $(LOCAL_SRCS) $(LOCAL_INCS)
	@$(CC) -MM $< > $@

$(TEST_BUFF_OBJS): $(LOCAL_SRCS) $(LOCAL_DEPS)

$(TEST_REACTOR): $(REACTOR_OBJS) $(OBJS) $(LIBS)
	$(CC) $(REACTOR_OBJS) $(OBJS) $(LIBS) -o $@


