APP 	:= experiment_97
CCFLAGS := -Wall -pedantic
CFLAGS	:= $(CCFLAGS)
CC		:= g++
C		:= gcc
MKDIR 	:= mkdir -p
SRC		:= src
OBJ		:= obj
LIBS	:= -lX11

ALLCPPS    := $(shell find $(SRC)/ -type f -iname *.cpp)
ALLCPPSOBJ := $(patsubst %.cpp, %.o, $(ALLCS))
ALLCS      := $(shell find $(SRC)/ -type f -iname *.c)
ALLCSOBJ   := $(patsubst %.c, %.o, $(ALLCS))
SUBDIRS    := $(shell find $(SRC)/ -type d)
OBJSUBDIRS := $(patsubst $(SRC)%, $(OBJ)%, $(SUBDIRS))

.PHONY: dir

$(APP) : $(OBJSUBDIRS) $(ALLCSOBJ) $(ALLCPPSOBJ)
	$(CC) -o $(APP) $(patsubst $(SRC)%, $(OBJ)%, $(ALLCPPSOBJ) $(ALLCSOBJ)) $(LIBS)

%.o : %.c
	$(C) -o $(patsubst $(SRC)%, $(OBJ)%, $@) -c $^ $(CFLAGS)

%.o : %.cpp
	$(CC) -o $(patsubst $(SRC)%, $(OBJ)%, $@) -c $^ $(CCFLAGS)

dir:
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLCSOBJ))

$(OBJSUBDIRS):
	$(MKDIR) $(OBJSUBDIRS)
#APP 	:= experiment_97
#CCFLAGS := -Wall -pedantic
#CFLAGS  := $(CCFLAGS)
#CC 		:= g++
#C		:= gcc
#MKDIR	:= mkdir -p
#SRC 	:= src
#OBJ 	:= obj
#LIBS	:= -lXll -lXext
#
#ALLCPPS    := $(shell find src/ -type f -iname *.cpp)
#ALLCPPSOBJ := $(patsubst %.cpp,%.o,$(ALLCPPS))
#ALLCS 	   := $(shell find src/ -type f -iname *.c)
#ALLCSOBJ   := $(patsubst %.c,%.o,$(ALLCS))
#SUBDIRS    := $(shell find $(SRC) -type d)
#OBJSUBDIRS := $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))
#
#.PHONY: dir
#
#$(APP) : $(OBJSUBDIRS) $(ALLCSOBJ) $(ALLCPPSOBJ)
#	$(CC) -o $(APP) $(patsubst $(SRC)%,$(OBJ)%,$(ALLCPPSOBJ) $(ALLCSOBJ))
#
#%.o : %.c
#	$(C) -o $(patsubst $(SRC)%,$(OBJ)%,$@) -c $^ $(CFLAGS)
#
#%.o : %.cpp
#	$(CC) -o $(patsubst $(SRC)%,$(OBJ)%,$@) -c $^ $(CCFLAGS)
#
#dir:
#	$(info $(SUBDIRS))
#	$(info $(OBJSUBDIRS))
#	$(info $(ALLCPPS))
#	$(info $(ALLCS))
#	$(info $(ALLCSOBJ))
#
#
#$(OBJSUBDIRS) :
#	$(MKDIR) $(OBJSUBDIRS)