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
LIBS	:= -lX11 -lGL -lm -lpthread -ldl -lrt -lfmod -lfmodstudio
INCS	:= -I . -I src/inc/FMOD/inc -L src/inc/FMOD/lib
EXPTR	:= export LD_LIBRARY_PATH=./src/inc/FMOD/lib:$$LD_LIBRARY_PATH
STD17	:= -std=c++17

ALLCPPS    := $(shell find $(SRC)/ -type f -iname *.cpp)
ALLCS      := $(shell find $(SRC)/ -type f -iname *.c)
ALLOBJ	   := $(foreach F,$(ALLCPPS) $(ALLCS),$(call C2Convert,$(O),$(O),$(call SRC2OBJ)))
SUBDIRS    := $(shell find $(SRC)/ -type d)
OBJSUBDIRS := $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

.PHONY: dir
.PHONY: clean
.PHONY: play
#.PHONY: fmod

$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(CC) $(STD17) -o $(APP) $(ALLOBJ) $(INCS) $(LIBS)
	$(EXPTR)

$(eval $(call EACHFILE,$(ALLCPPS),$(CC),$(CCFLAGS)))
$(eval $(call EACHFILE,$(ALLCS),$(C),$(CFLAGS)))

dir:
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLCSOBJ))

clean:
	rm -f -r "./obj"

play:
	./$(APP)

#fmod:
#	g++ -std=c++17 -o experiment_97 src/main.cpp src/man/entitymanager.cpp -I . -I src/inc/FMOD/inc -L src/inc/FMOD/lib -lfmod -lfmodstudio -lGL -lm -lpthread -ldl -lrt -lX11 && export LD_LIBRARY_PATH=./src/inc/FMOD/lib:$LD_LIBRARY_PATH 

$(OBJSUBDIRS):
	$(MKDIR) $(OBJSUBDIRS)