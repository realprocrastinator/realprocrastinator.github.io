# This is a very simple Makefile just enough to build the
# tutorial code with GCC, not dealing with configuration
# as well as the cross compiling. 

CC = g++
CCFLAGS = -Wall -Werror -g -O0 
AR = ar
RANLIB = ranlib

srcdir = .
builddir = ./build

LIB_DIR = $(addprefix $(srcdir)/, src/sort)
TEST_DIR = $(addprefix $(srcdir)/, src/test)
LIB_SRCS = $(sort $(wildcard $(addprefix $(srcdir)/, src/sort/*.cpp)))
TEST_SRCS = $(sort $(wildcard $(addprefix $(srcdir)/, src/test/*.cpp)))
ALL_SRCS = $(sort $(wildcard $(LIB_SRCS) $(TEST_SRCS)))
BASE_OBJS = $(addprefix $(builddir)/, $(patsubst $(srcdir)/src/%, %.o, $(basename $(ALL_SRCS))))
ALL_OBJS = $(sort $(BASE_OBJS))
LIB_OBJS = $(filter $(builddir)/sort/%, $(ALL_OBJS))
TEST_OBJS = $(filter $(builddir)/test/%, $(ALL_OBJS))

STATIC_LIB = $(builddir)/lib/sort.a
TEST = $(builddir)/testsort

all: $(STATIC_LIB) $(TEST)

BUILD_DIRS = $(sort $(patsubst %/, %, $(dir $(ALL_OBJS) $(STATIC_LIB))))

$(TEST) $(ALL_OBJS) $(STATIC_LIB): | $(BUILD_DIRS)

$(BUILD_DIRS):
	mkdir -p $@

$(TEST): $(ALL_OBJS)
	$(CC) $(CCFLAGS) $^ -o $@ 

$(TEST_OBJS): $(TEST_SRCS)
	$(CC) $(CCFLAGS) -I./include -c $< -o $@

$(STATIC_LIB): $(LIB_OBJS)
	rm -f $@
	$(AR) rc $@ $(LIB_OBJS)
	$(RANLIB) $@

$(LIB_OBJS): $(LIB_SRCS)
	$(CC) $(CCFLAGS) -I./include -c $< -o $@

clean:
	rm -rf $(builddir)