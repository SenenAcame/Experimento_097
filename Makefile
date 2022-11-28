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

APP 	:= experiment_97
CCFLAGS := -Wall -pedantic
CFLAGS	:= $(CCFLAGS)
H		:= %.h
O		:= %.o
HPP     := %.hpp
CLANG	:= clang++
CC		:= g++
C		:= gcc
MKDIR 	:= mkdir -p
SRC		:= src
OBJ		:= obj
LIBS	:= -lX11
STD17	:= -std=c++17

ALLCPPS    := $(shell find $(SRC)/ -type f -iname *.cpp)
ALLCS      := $(shell find $(SRC)/ -type f -iname *.c)
ALLOBJ	   := $(foreach F,$(ALLCPPS) $(ALLCS),$(call C2Convert,$(O),$(O),$(call SRC2OBJ)))
SUBDIRS    := $(shell find $(SRC)/ -type d)
OBJSUBDIRS := $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

.PHONY: dir
.PHONY: clean

$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(CC) $(STD17) -o $(APP) $(ALLOBJ) $(LIBS)

$(eval $(call EACHFILE,$(ALLCPPS),$(CC),$(CCFLAGS),$(STD17)))
$(eval $(call EACHFILE,$(ALLCS),$(C),$(CFLAGS),))

dir:
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLCSOBJ))

clean:
	rm -f -r "./obj"

$(OBJSUBDIRS):
	$(MKDIR) $(OBJSUBDIRS)