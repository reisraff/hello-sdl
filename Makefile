# OBJS specifies which files to compile as part of the project
OBJS = main.cpp

# CC specifies which compiler we're using
CC = g++

# COMPILER_FLAGS specifies the additional compilation options we're using
#  -w suppresses all warnings
COMPILER_FLAGS = -w

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS_SDL2 = -lSDL2 -lSDL2_image

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = output.o

DIRS_SDL2 = sdl2/*-step
SUBDIRS_SDL2 := $(wildcard $(DIRS_SDL2))

sld2: $(SUBDIRS_SDL2)
$(SUBDIRS_SDL2):
	cd $@ && $(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS_SDL2) -o $(OBJ_NAME)

all:
	# sdl1
	sdl2

clean:
	rm $(DIRS)/$(OBJ_NAME)

.PHONY: $(TOPTARGETS) $(SUBDIRS_SDL2)
