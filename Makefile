#Source files
OBJS = $(wildcard *.cpp)

#Compiler
CC = g++

#Compiler Flags
COMP_FLAG = -w

#Linker Flags
LINK_FLAG = -lGL -lGLU -lglut

#Name
NAME = build/memorama

#Targets
sifuc : $(OBJS)
	$(CC) $(OBJS) $(COMP_FLAG) $(LINK_FLAG) -o $(NAME)
