#OBJS specifies the files to compile as part of the project
OBJS = main.cpp TestClass.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w supresses all warnings
COMPILER_FLAGS = -w -g

#LINKER_FLAGS specifies the libraties we;re linking against
LINKER_FLAGS = 

#OBJ_NAME specifies the name of our executable
OBJ_NAME = classes

#This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
