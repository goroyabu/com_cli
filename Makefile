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
ROOTCFLAGS = `root-config --cflags --ldflags`
ROOTGLIBS  = `root-config --glibs`
CXXFLAGS = $(ROOTCFLAGS) -std=c++11 -MMD -MP
CXXLIBS = $(ROOTGLIBS) -lreadline
#--------------------------------------------------

app = $(addprefix $(BUILD_DIR)/,$(APP))
lib = $(addprefix $(BUILD_DIR)/,$(LIB))
target = $(app) $(lib)
installed_app = $(subst $(BUILD_DIR),$(BIN_DIR),$(app))
installed_lib = $(subst $(BUILD_DIR),$(LIB_DIR),$(lib))

main :=
headers := $(shell find $(SOURCE_DIR) -name "*.hpp")
source_dirs := $(shell find $(SOURCE_DIR) -type d)
sources = $(foreach dir, $(source_dirs), $(wildcard $(dir)/*.cpp))

objects := $(subst $(SOURCE_DIR),$(BUILD_DIR),$(sources:%.cpp=%.o))
objects_dirs := $(addprefix $(BUILD_DIR)/, $(source_dirs)) 
dependency := $(objects:.o=.d)

include_flag := $(addprefix -I,$(source_dirs))
#--------------------------------------------------

all : $(BUILD_DIR) $(target)

.PHONY : install
install : $(target)
ifneq ($(APP),)
	mkdir -p $(BIN_DIR); install $(app) $(BIN_DIR)/
endif
ifneq ($(LIB),)
	mkdir -p $(LIB_DIR)
	install $(lib) $(LIB_DIR)/
	$(foreach temp, $(installed_lib), $(shell echo install_name_tool -id $(temp) $(temp)))
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
	$(CXX) $(CXXFLAGS) $(include_flag) -o $@ -c $<

.PHONY : clean
clean :
	rm -rf *~ $(BUILD_DIR)/* $(target)

.PHONY : cleanall
cleanall :
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(LIB_DIR) $(INCLUDE_DIR)

.PHONY : uninstall
uninstall :
	rm $(installed_app) $(installed_lib)

.PHONY : show
show :
	@echo $(sources)
	@echo $(objects)
	@echo $(headers)
#--------------------------------------------------

-include $(dependency)
