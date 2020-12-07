PROJECT_HOME = $(shell pwd)
SRC_HOME = $(PROJECT_HOME)/src
BUILD_HOME = $(PROJECT_HOME)/build

SRC_FILES = $(wildcard $(SRC_HOME)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_HOME)/%.cpp,$(BUILD_HOME)/%.o,$(SRC_FILES))

CC = g++
CFLAGS = -Wall -Wextra -O3
LDFLAGS =
LIBS = -lelf

simulator: $(OBJ_FILES)
	@$(CC) $(LDFLAGS) -o ./simulator $^ $(LIBS)

$(BUILD_HOME)/%.o: $(SRC_HOME)/%.cpp create_dirs
	@$(CC) $(CFLAGS) -c -o $@ $<

create_dirs:
	@mkdir -p $(BUILD_HOME)

clean:
	@rm -rf $(BUILD_HOME)
