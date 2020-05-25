CC	= g++
# CFLAGS	= -g -std=c++17 -MMD -Wall -Ofast
# LDFLAGS = -Ofast -Wall
CFLAGS	= -g -std=c++17 -MMD -MP -Wall -Ofast -fopenmp
LDFLAGS = -Ofast -Wall -fopenmp
LIBS	= 
INCLUDE = -I ./include
SRC_DIR = ./source
OBJ_DIR = ./build
SOURCES = $(shell ls $(SRC_DIR)/*.cpp) 
OBJS		= $(subst $(SRC_DIR),$(OBJ_DIR), $(SOURCES:.cpp=.o))
TARGET	= SeedHack
DEPENDS = $(OBJS:.o=.d)

all: clean $(OBJS) $(TARGET)
$(TARGET): $(OBJS) $(LIBS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	@if [ ! -d $(OBJ_DIR) ]; \
		then echo "mkdir -p $(OBJ_DIR)"; mkdir -p $(OBJ_DIR); \
	fi
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	$(RM) $(OBJS) $(TARGET) $(DEPENDS)

-include $(DEPENDS)

.PHONY: all clean run
