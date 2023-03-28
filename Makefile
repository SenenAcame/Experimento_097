define COMPILE
$(3) : $(4) $(5)
	$(1) $(2) $(7) -c -o $(3) $(4) $(6) $(8)
endef

define SRC2OBJ
$(patsubst $(SRC)%,$(OBJ)%,$(F))
endef

define C2Convert
$(patsubst %.c,$(1),$(patsubst %.cpp,$(2),$(3)))
endef

define EACHFILE
$(foreach F,$(1),$(eval $(call COMPILE,$(2),$(3),$(call C2Convert,$(O),$(O),$(call SRC2OBJ)),$(F),$(call C2Convert,$(H),$(HPP),$(F)),$(4),$(5),$(6))))
endef

APP 	 := experiment_97
CCFLAGS  := -Wall -pedantic
CFLAGS	 := $(CCFLAGS)
H		 := %.h
O		 := %.o
HPP      := %.hpp
#CCACHE   := ccache
CC		 := g++
C		 := gcc
MKDIR 	 := mkdir -p
SRC		 := src
OBJ		 := obj
#LIBS2	 := lib/FMOD/libFMOD.a -lX11 -lGL -lm -lpthread -ldl -lrt 
LIBS	 := -lfmod -lfmodstudio -lIrrlicht -limgui -lglfw -lGL -Llib/FMOD/lib -Llib/imgui
INCS	 := -Ilib
EXPTR	 := LD_LIBRARY_PATH=./lib/FMOD/lib
STD++	 := -std=c++20
STD		 := -std=c17
SANITIZE := -fsanitize=address
DINAMIC  := -Wl,-rpath=libs/

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

.PHONY: dir clean play lib lib-clean

$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(CC) $(STD++) -o $(APP) $(ALLOBJ) $(LIBS) $(SANITIZE) $(DINAMIC)

$(eval $(call EACHFILE,$(ALLCPPS),$(CCACHE),$(CC),$(CCFLAGS),$(STD++),$(INCS)))
$(eval $(call EACHFILE,$(ALLCS),$(CCACHE),$(C),$(CFLAGS),$(STD),$(INCS)))

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

lib:
	$(MAKE) -C lib

lib-clean:
	$(MAKE) -C lib clean

$(OBJSUBDIRS):
	$(MKDIR) $(OBJSUBDIRS)