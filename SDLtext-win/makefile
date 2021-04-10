#OBJS specifies the files to compile as part of the project
OBJS = main.cpp 

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS additional paths for includes
INCLUDE_PATHS = -IS:\Mutual\Code\Libraries\windows\SDL2-minGW\i686-w64-mingw32\include\SDL2 -IS:\Mutual\Code\Libraries\windows\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2

#LIBRARY_PATHS additional paths for libraries
LIBRARY_PATHS = -LS:\Mutual\Code\Libraries\windows\SDL2-minGW\i686-w64-mingw32\lib -LS:\Mutual\Code\Libraries\windows\SDL2_ttf-2.0.15\i686-w64-mingw32\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w supresses all warnings
COMPILER_FLAGS = -w -Wl,-subsystem,windows 

#LINKER_FLAGS specifies the libraties we;re linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

#OBJ_NAME specifies the name of our executable
OBJ_NAME = SDL_Text

#This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
