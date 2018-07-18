LOCAL_BASE	:= unitTest/TEST_EVENT/TEST_EVENT_DESCRIPTION
LOCAL_MDLS	:=
LOCAL_BLDS	:= $(addprefix $(LOCAL_BASE)/, $(LOCAL_MDLS))

LOCAL_INCS	:= $(wildcard $(LOCAL_BASE)/*.h)
LOCAL_INCS	+= $(wildcard $(INCLUDE_DIRS)/$(LOCAL_MDLS)/*.h)

LOCAL_SRCS	:= $(wildcard $(LOCAL_BASE)/*.c)
LOCAL_SRCS	+= $(foreach sdir, $(LOCAL_BLDS), $(wildcard $(sdir)/*.c))

EVD_OBJS	:= $(patsubst %.c, %.o, $(LOCAL_SRCS))
LOCAL_DEPS	:= $(patsubst %.c, %.deps, $(LOCAL_SRCS))

TMPS		+= $(EVD_OBJS)
DEPS		+= $(LOCAL_DEPS)

TARGET		:= TEST_EVENT_DESCRIPTION
EV_DESCRIPTION	:= $(addprefix $(LOCAL_BASE)/, $(TARGET))
TESTS		+= $(EV_DESCRIPTION)

$(LOCAL_DEPS): $(LOCAL_SRCS) $(LOCAL_INCS)
	@$(CC) -MM $< > $@

$(TEST_BUFF_OBJS): $(LOCAL_SRCS) $(LOCAL_DEPS)

$(EV_DESCRIPTION): $(EVD_OBJS) $(OBJS) $(LIBS)
	$(CC) $(EVD_OBJS) $(OBJS) $(LIBS) -o $@


