#CC=x86_64-w64-mingw32-g++
CC=g++

WX_CONFIG := wx-config
 
WX_CXXFLAGS := $(shell $(WX_CONFIG) --cxxflags)
WX_LIBS := $(shell $(WX_CONFIG) --libs)


CCFLAGS = -c -g -MMD -std=c++17
LDFLAGS = -g -lGL -lGLU

OBJDIR = build
SRCDIR = src
TESTSRCDIR = test

SRC = $(shell find $(SRCDIR) -name "*.cpp")
OBJ = $(SRC:$(SRCDIR)%.cpp=$(OBJDIR)%.o)
DEPENDENCIES = $(SRC:$(SRCDIR)%.cpp=$(OBJDIR)%.d)

APP = main
TEST = test

$(APP): $(OBJ)
	@echo "== LINKING EXECUTABLE $(OBJDIR)/$(APP)"
	@$(CC) -o $(OBJDIR)/$(APP) $^ $(LDFLAGS) $(WX_LIBS) $(LIBS) 

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp 
	@echo "== COMPILING SOURCE $< INTO $@"
	@mkdir -p $(@D)
	@$(CC) $(CCFLAGS) -o $@ $< $(WX_CXXFLAGS) 

-include $(DEPENDENCIES)

test: $(TESTSRCDIR)/main.cpp $(OBJ)
	@echo "== COMPILING MAIN TEST"
	@$(CC) $(CCFLAGS) -o $(OBJDIR)/$(TEST).o $(TESTSRCDIR)/main.cpp
	@echo "== LINKING MAIN TEST"
	@$(CC) $(LDFLAGS) -o $(OBJDIR)/$(TEST) $(filter-out $(OBJDIR)/$(APP).o, $(OBJ))  $(OBJDIR)/$(TEST).o

clean:
	@rm -rf $(OBJDIR)