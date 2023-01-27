##########################################
#####			  MACROS			 #####
##########################################

# $(1) : Compiler
# $(2) : Object file to generate
# $(3) : Source file
# $(4) : Additional dependencies
# $(5) : Compiler flags
define COMPILE
$(2) : $(3) $(4)
		$(1) -c -o $(2) $(3) $(5)
endef

# $(1)  : Source file
define C20
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%, $(OBJ)%,$(1))))
endef

#(1) 	: Source file
define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef

##########################################
#####			  CONFIG			 #####
##########################################


UNAME	:= $(shell uname)
APP		:= libimgui.a
CCFLAGS	:= -Wall -pedantic -std=c++11
CFLAGS	:= $(CCFLAGS)
CC		:= g++
C		:= gcc
AR 		:= ar
ARFLAGS := -crs
RANLIB	:= ranlib
MKDIR	:= mkdir -p
SRC		:= src
OBJ		:= obj


ifdef DEBUG
	CCFLAGS += -g
else ifdef SANITIZE
	CCFLAGS += -fsanitize=adress -fno-omit-frame-pointer -01 -g
else
endif

ALLCPPS 	:= $(shell find src/ -type f  -iname *.cpp)
ALLCS		:= $(shell find src/ -type f  -iname *.c)
ALLOBJ		:= $(foreach F,$(ALLCPPS) $(ALLCS),$(call C20,$(F)))
SUBDIRS		:= $(shell find $(SRC) -type d)
OBJSUBDIRS	:= $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

.PHONY: info

# Generate Library
$(APP)  :  $(OBJSUBDIRS) $(ALLOBJ)
		  $(AR) $(ARFLAGS) $(APP) $(ALLOBJ)
		  $(RANLIB) $(APP)

#Generate rules for all objects
$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CC),$(call C20,$(F)),$(F),,$(CCFLAGS))))
$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(C),$(call C20,$(F)),$(F),$(call C2H,$(F)),$(CCFLAGS))))


info: 
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLOBJ))

$(OBJSUBDIRS)  :
	$(MKDIR) $(OBJSUBDIRS)

lib-clean:
	$(MAKE) -C lib clean