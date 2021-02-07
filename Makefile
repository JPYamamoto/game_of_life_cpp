# Directories
S_DIR=src
B_DIR=build

# Files
S_FILES=$(S_DIR)/*.cpp $(S_DIR)/*.h

# Output
EXEC=$(B_DIR)/game_of_life.out

# Build settings
CC=g++
# SDL options
CC_SDL=-lSDL2 -lSDL2_ttf `sdl-config --cflags --libs`


all:Build

Build:
	$(CC) $(S_FILES) -o $(EXEC) $(CC_SDL)

build_run:Build
	$(EXEC)

clean:
	rm -rf $(B_DIR)/*
