define COMPILE
$(2) : $(3) $(4)
	$(1) $(6) -c -o $(2) $(3) $(5)
endef

define SRC2OBJ
$(patsubst $(SRC)%,$(OBJ)%,$(F))
endef

define C2Convert
$(patsubst %.c,$(1),$(patsubst %.cpp,$(2),$(3)))
endef

define EACHFILE
$(foreach F,$(1),$(eval $(call COMPILE,$(2),$(call C2Convert,$(O),$(O),$(call SRC2OBJ)),$(F),$(call C2Convert,$(H),$(HPP),$(F)),$(3),$(4))))
endef

APP 	 := experiment_97
CCFLAGS  := -Wall -pedantic
CFLAGS	 := $(CCFLAGS)
H		 := %.h
O		 := %.o
HPP      := %.hpp
CLANG	 := ccache clang++
CC		 := ccache g++
C		 := ccache gcc
MKDIR 	 := mkdir -p
SRC		 := src
OBJ		 := obj
LIBS	 := -lX11 -lGL -lm -lpthread -ldl -lrt -lfmod -lfmodstudio
INCS	 := -I src/inc/FMOD/inc -L src/inc/FMOD/lib
#EXPTR	 := export LD_LIBRARY_PATH=./src/inc/FMOD/lib:$$LD_LIBRARY_PATH
EXPTR	 := LD_LIBRARY_PATH=./src/inc/FMOD/lib
STD17	 := -std=c++17
STD20	 := -std=c++20
SANITIZE := -fsanitize=address
DINAMIC  := -Wl,-rpath=src/inc/lib


ALLCPPS    := $(shell find $(SRC)/ -type f -iname *.cpp)
ALLCS      := $(shell find $(SRC)/ -type f -iname *.c)
ALLOBJ	   := $(foreach F,$(ALLCPPS) $(ALLCS),$(call C2Convert,$(O),$(O),$(call SRC2OBJ)))
SUBDIRS    := $(shell find $(SRC)/ -type d)
OBJSUBDIRS := $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

.PHONY: dir
.PHONY: clean
.PHONY: play

$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(CLANG) $(STD20) -o $(APP) $(DINAMIC) $(ALLOBJ) $(INCS) $(LIBS) $(SANITIZE)

$(eval $(call EACHFILE,$(ALLCPPS),$(CLANG),$(CCFLAGS),$(STD20)))
$(eval $(call EACHFILE,$(ALLCS),$(C),$(CFLAGS),))

dir:
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLCSOBJ))

clean:
	rm -f -r "./obj"

play:
	$(EXPTR) ./$(APP)

$(OBJSUBDIRS):
	$(MKDIR) $(OBJSUBDIRS)