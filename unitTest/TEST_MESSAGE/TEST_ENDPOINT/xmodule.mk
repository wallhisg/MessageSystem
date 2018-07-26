LOCAL_BASE	:= unitTest/TEST_MESSAGE/TEST_ENDPOINT
LOCAL_MDLS	:=
LOCAL_BLDS	:= $(addprefix $(LOCAL_BASE)/, $(LOCAL_MDLS))

LOCAL_INCS	:= $(wildcard $(LOCAL_BASE)/*.h)
LOCAL_INCS	+= $(wildcard $(INCLUDE_DIRS)/$(LOCAL_MDLS)/*.h)

LOCAL_SRCS	:= $(wildcard $(LOCAL_BASE)/*.c)
LOCAL_SRCS	+= $(foreach sdir, $(LOCAL_BLDS), $(wildcard $(sdir)/*.c))

ENDPOINT_OBJS	:= $(patsubst %.c, %.o, $(LOCAL_SRCS))
LOCAL_DEPS	:= $(patsubst %.c, %.deps, $(LOCAL_SRCS))

TMPS		+= $(ENDPOINT_OBJS)
DEPS		+= $(LOCAL_DEPS)

TARGET		:= TEST_MESSAGE_ENDPOINT_EXE
TEST_ENDPOINT	:= $(addprefix $(LOCAL_BASE)/, $(TARGET))
TESTS		+= $(TEST_ENDPOINT)

$(LOCAL_DEPS): $(LOCAL_SRCS) $(LOCAL_INCS)
	@$(CC) -MM $< > $@

$(TEST_BUFF_OBJS): $(LOCAL_SRCS) $(LOCAL_DEPS)

$(TEST_ENDPOINT): $(ENDPOINT_OBJS) $(OBJS) $(LIBS)
	$(CC) $(ENDPOINT_OBJS) $(OBJS) $(LIBS) -o $@


