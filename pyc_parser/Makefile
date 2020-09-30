#####################################################
#common settings
#####################################################
CC=g++
LINK=g++
INC_PREFIX=-I
LIB_PREFIX=-L
BUILD_PATH=./build
CFLAGS=-c
TARGET=pyc_parser
TEST_TARGET=test_$(TARGET)
CUNIT_PATH=/home/robert/CUnit

#####################################################
#settings for normal compile
#####################################################
SRC_PATH=./src
SRCS=$(wildcard $(SRC_PATH)/*.cpp)
OBJS=$(patsubst $(SRC_PATH)/%.cpp,$(BUILD_PATH)/%.o,$(SRCS))

INC_DIR=./include $(CUNIT_PATH)/include/CUnit
INCS=$(addprefix $(INC_PREFIX),$(INC_DIR))

#####################################################
#settings for compiling test cases
#####################################################
TEST_PATH=./test
TEST_SRCS=$(wildcard $(TEST_PATH)/*.cpp)
TEST_OBJS=$(patsubst $(TEST_PATH)/%.cpp,$(BUILD_PATH)/%.o,$(TEST_SRCS))

TEST_INC_DIR=$(INC_DIR) $(TEST_PATH) $(CUNIT_PATH)/include/CUnit
TEST_LIB_DIR=$(CUNIT_PATH)/lib
TEST_INCS=$(addprefix $(INC_PREFIX),$(TEST_INC_DIR))
TEST_LIB_PATHS=$(addprefix $(LIB_PREFIX),$(TEST_LIB_DIR))
TEST_LIBS=-lcunit

#####################################################
# set path or make
#####################################################
vpath %.cpp $(SRC_PATH)
vpath %.o $(BUILD_PATH)
vpath %.cpp $(TEST_PATH)

#####################################################
# normal compile
#####################################################
all : init $(TARGET)

$(TARGET) : $(OBJS)
	@echo "generate excutable file : $@"
	$(LINK) -o $@ $(OBJS)

$(OBJS) : $(BUILD_PATH)/%.o : $(SRC_PATH)/%.cpp
	$(CC) $(CFLAGS) $(INCS) -o $@ $<

init:
	@echo "create $(BUILD_PATH) dir"
	mkdir $(BUILD_PATH)


#####################################################
# compile for test
#####################################################
test: clean init compile_test run_test 

compile_test: $(OBJS) $(TEST_OBJS)
	@echo "generate excutable file for testing : $(TEST_TARGET)"
	$(LINK) $(TEST_LIBS) $(TEST_LIB_PATHS) -o $(TEST_TARGET) $(TEST_OBJS) $(filter-out %main.o,$(OBJS))

$(TEST_OBJS) : $(BUILD_PATH)/%.o : $(TEST_PATH)/%.cpp
	$(CC) $(CFLAGS) $(TEST_INCS) -o $@ $<

run_test:
	./test_main

#####################################################
# clean
#####################################################
clean:
	rm -rf $(BUILD_PATH)
	rm -f $(TEST_TARGET)
	rm -f $(TARGET) 

#####################################################
# robert's test
#####################################################
show:
	@echo "TEST_SRCS : $(TEST_SRCS)"
	@echo "TEST_INCS : $(TEST_INCS)"
	@echo "TEST_LIBS : $(TEST_LIBS)"
	@echo "TEST_OBJS : $(TEST_OBJS)"
	@echo "TEST_TARGET : $(TEST_TARGET)"
