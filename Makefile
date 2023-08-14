#CC=x86_64-w64-mingw32-g++
CC=g++
CCFLAGS = -c -g -MMD -std=c++17 -Wall 
LDFLAGS = -g -static -static-libgcc -static-libstdc++

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
	@$(CC) $(LDFLAGS) $^ -o $(OBJDIR)/$(APP)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp 
	@echo "== COMPILING SOURCE $< INTO $@"
	@mkdir -p $(@D)
	@$(CC) $(CCFLAGS) -o $@ $<

-include $(DEPENDENCIES)

test: $(TESTSRCDIR)/main.cpp $(OBJ)
	@echo "== COMPILING MAIN TEST"
	@$(CC) $(CCFLAGS) -o $(OBJDIR)/$(TEST).o $(TESTSRCDIR)/main.cpp
	@echo "== LINKING MAIN TEST"
	@$(CC) $(LDFLAGS) -o $(OBJDIR)/$(TEST) $(filter-out $(OBJDIR)/$(APP).o, $(OBJ))  $(OBJDIR)/$(TEST).o

clean:
	@rm -rf $(OBJDIR)