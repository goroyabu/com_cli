#---TARGET---

APP = 
LIB = libCOMCLI.so
#--------------------------------------------------

TOP_DIR := $(shell pwd)
SOURCE_DIR := $(TOP_DIR)/source
BUILD_DIR := $(TOP_DIR)/build
INSTALL_DIR := $(TOP_DIR)/bin
BIN_DIR := $(TOP_DIR)/bin
LIB_DIR := $(TOP_DIR)/lib
INCLUDE_DIR := $(TOP_DIR)/include

#--------------------------------------------------

CXX = g++
CXXFLAGS = -MMD -MP -Wall -Wextra -std=c++1z 
CXXLIBS = -lreadline
#--------------------------------------------------

app = $(addprefix $(BUILD_DIR)/,$(APP))
lib = $(addprefix $(BUILD_DIR)/,$(LIB))
target = $(app) $(lib)
installed_app = $(subst $(BUILD_DIR),$(BIN_DIR),$(app))
installed_lib = $(subst $(BUILD_DIR),$(LIB_DIR),$(lib))

main :=
headers := $(shell find $(SOURCE_DIR) -name "*.hpp") $(shell find $(SOURCE_DIR) -name "*.h")
source_dirs := $(shell find $(SOURCE_DIR) -type d)
sources = $(foreach dir, $(source_dirs), $(wildcard $(dir)/*.cpp))

objects := $(subst $(SOURCE_DIR),$(BUILD_DIR),$(sources:%.cpp=%.o))
objects_dirs := $(addprefix $(BUILD_DIR)/, $(source_dirs)) 
dependency := $(objects:.o=.d)

include_flag := $(addprefix -I,$(source_dirs))
#--------------------------------------------------

.PHONY : help
help : ## Print this message.
	@echo "Usage: make [options] [target] ..."
	@echo "Targets:"
	@grep -Eh '^[a-zA-Z_-]+ : .*?## .*$$' $(MAKEFILE_LIST) | sort | awk -F'[:##]' '{printf "  \033[0m%-25s\033[0m %s\n", $$1, $$4}'

.PHONY : show-structure
show-structure : ## Print the directory structure of this makefile.
	@echo "Directories:"
	@printf "./  %-25s%s\n" "" "This makefile is here."
	@printf "|-- %-25s%s\n" "source/" "All of C++ files in here will be compiled into object files."
	@printf "|   %-25s%s\n" "|-- src.hpp" ""
	@printf "|   %-25s%s\n" "|-- src.cpp" ""
	@printf "|   %-25s%s\n" "'-- subsrc/" "Files in the sub-directories of 'source' "
	@printf "|   %-25s%s\n" "    |-- sub_src.h" ""
	@printf "|   %-25s%s\n" "    '-- sub_src.cpp" ""
	@printf "|-- %-25s%s\n" "build/" ""
	@printf "|   %-25s%s\n" "|-- src.o" ""
	@printf "|   %-25s%s\n" "'-- subsrc/" ""
	@printf "|   %-25s%s\n" "    '-- sub_src.o" ""
	@printf "|-- %-25s%s\n" "include/" "The symbolic links of headers are created here."
	@printf "|   %-25s%s\n" "|-- src.hpp@ -> path/to/here/source/src.hpp" ""
	@printf "|   %-25s%s\n" "'-- sub_src.h@ -> path/to/here/source/subsrc/sub_src.h" ""
	@printf "|-- %-25s%s\n" "bin/" "The app is installed here."
	@printf "|   %-25s%s\n" "'-- app4example" ""
	@printf "'-- %-25s%s\n" "lib/" "The library is installed here."
	@printf "    %-25s%s\n" "'-- libSAMPLE.so" ""

all : $(BUILD_DIR) $(target) ## Find and compile all of the C++ files in the 'source' directory.

.PHONY : install
install : $(target) ## Install the app or the library into the install directories, 'bin' or 'lib'.
ifneq ($(APP),)
	mkdir -p $(BIN_DIR); install $(app) $(BIN_DIR)/
endif
ifneq ($(LIB),)
	mkdir -p $(LIB_DIR)
	install $(lib) $(LIB_DIR)/
ifeq ($(shell uname), Darwin)
	$(foreach temp, $(installed_lib), $(shell echo install_name_tool -id $(temp) $(temp)))
endif
endif

$(BUILD_DIR) :
	mkdir -p $@
#--------------------------------------------------

$(app) : $(main_obj) $(objects) $(dictionary_obj)
	$(CXX) $(CXXLIBS) $(CXXFLAGS) -o $@ $^

${lib} : ${objects} ${dictionary_obj}
	mkdir -p $(INCLUDE_DIR); cd $(INCLUDE_DIR); ln -sf $(addprefix ,$(headers)) .
	${CXX} ${CXXLIBS} ${CXXFLAGS} $(include_flag) -shared -fPIC -o $@ $^

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@echo $@
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) $(include_flag) -fPIC -o $@ -c $<

.PHONY : clean
clean : ## Delete the targets and the objects in the 'build' directory.
	rm -rf *~ $(BUILD_DIR)/* $(target)

.PHONY : cleanup
cleanup : ## Delete the directories made at the compilation, 'build', 'bin', 'lib' and 'include'.
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(LIB_DIR) $(INCLUDE_DIR)

.PHONY : uninstall 
uninstall : ## Uninstall the app or the lib from the install directories.
	rm $(installed_app) $(installed_lib)

.PHONY : show-files
show-files : ## Print all of the sources, objects and headers.
	@echo "Sources:"
	@$(foreach temp, $(sources), echo "  "$(temp);)
	@echo "Objects:"
	@$(foreach temp, $(objects), echo "  "$(temp);)
	@echo "Headers:"
	@$(foreach temp, $(headers), echo "  "$(temp);)
#--------------------------------------------------

-include $(dependency)
