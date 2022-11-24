define COMPILE
$(2) : $(3) $(4)
	$(1) -c -o $(2) $(3) $(5)
endef

define SRC2OBJ
$(patsubst $(SRC)%,$(OBJ)%,$(F))
endef

define C2Convert
$(patsubst %.c,$(1),$(patsubst %.cpp,$(2),$(3)))
endef

define EACHFILE
$(foreach F,$(1),$(eval $(call COMPILE,$(2),$(call C2Convert,$(O),$(O),$(call SRC2OBJ)),$(F),$(call C2Convert,$(H),$(HPP),$(F)),$(3))))
endef

APP 	:= experiment_97
CCFLAGS := -Wall -pedantic
CFLAGS	:= $(CCFLAGS)
H		:= %.h
O		:= %.o
HPP     := %.hpp
CC		:= g++
C		:= gcc
MKDIR 	:= mkdir -p
SRC		:= src
OBJ		:= obj
LIBS	:= -lX11

ALLCPPS    := $(shell find $(SRC)/ -type f -iname *.cpp)
ALLCS      := $(shell find $(SRC)/ -type f -iname *.c)
ALLOBJ	   := $(foreach F,$(ALLCPPS) $(ALLCS),$(call C2Convert,$(O),$(O),$(call SRC2OBJ)))
SUBDIRS    := $(shell find $(SRC)/ -type d)
OBJSUBDIRS := $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

.PHONY: dir
.PHONY: clean
.PHONY: fmod

$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(CC) -o $(APP) $(ALLOBJ) $(LIBS)

$(eval $(call EACHFILE,$(ALLCPPS),$(CC),$(CCFLAGS)))
$(eval $(call EACHFILE,$(ALLCS),$(C),$(CFLAGS)))

dir:
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLCSOBJ))

fmod:
	g++ -std=c++17 -o experiment_97 main.cpp -I . -I inc/FMOD/inc -L inc/FMOD/lib -lfmod -lfmodstudio -lGL -lm -lpthread -ldl -lrt -lX11 && cp -r assets bin/ && export LD_LIBRARY_PATH=./inc/FMOD/lib:$LD_LIBRARY_PATH && ./experiment_97

$(OBJSUBDIRS):
	$(MKDIR) $(OBJSUBDIRS)