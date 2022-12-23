define COMPILE
$(3) : $(4) $(5)
	$(1) $(2) $(7) -c -o $(3) $(4) $(6)
endef

define SRC2OBJ
$(patsubst $(SRC)%,$(OBJ)%,$(F))
endef

define C2Convert
$(patsubst %.c,$(1),$(patsubst %.cpp,$(2),$(3)))
endef

define EACHFILE
$(foreach F,$(1),$(eval $(call COMPILE,$(2),$(3),$(call C2Convert,$(O),$(O),$(call SRC2OBJ)),$(F),$(call C2Convert,$(H),$(HPP),$(F)),$(4),$(5))))
endef

APP 	 := libFMOD.a
CCFLAGS  := -Wall -pedantic
CFLAGS	 := $(CCFLAGS)
H		 := %.h
O		 := %.o
HPP      := %.hpp
CCACHE   := ccache
CLANG	 := clang++
CC		 := g++
C		 := gcc
AR		 := ar
RANLIB	 := ranlib
ARFLAGS  := -crs
MKDIR 	 := mkdir -p
SRC		 := src
OBJ		 := obj
STD++	 := -std=c++20
STD		 := -std=c17

ifdef RELEASE
	CCFLAGS += -O3
	FLAGS += -O3
else
	CCFLAGS += -g
	CFLAGS += -g
endif

ALLCPPS    := $(shell find $(SRC)/ -type f -iname *.cpp)
ALLCS      := $(shell find $(SRC)/ -type f -iname *.c)
ALLOBJ	   := $(foreach F,$(ALLCPPS) $(ALLCS),$(call C2Convert,$(O),$(O),$(call SRC2OBJ)))
SUBDIRS    := $(shell find $(SRC)/ -type d)
OBJSUBDIRS := $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

.PHONY: dir clean play

$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(AR) $(ARFLAGS) $(APP) $(ALLOBJ)
	$(RANLIB) $(APP)

$(eval $(call EACHFILE,$(ALLCPPS),$(CCACHE),$(CC),$(CCFLAGS),$(STD++)))
$(eval $(call EACHFILE,$(ALLCS),$(CCACHE),$(C),$(CFLAGS),$(STD)))

dir:
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLCSOBJ))

clean:
	rm -f -r "./obj"

#play:
#	$(EXPTR) ./$(APP)

$(OBJSUBDIRS):
	$(MKDIR) $(OBJSUBDIRS)