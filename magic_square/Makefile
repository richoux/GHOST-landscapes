# Compiler flags
MYFLAGS=
CXXFIRSTFLAGS= -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-use-after-free

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CXX=g++
	CXXFLAGS= -std=c++17 $(CXXFIRSTFLAGS) $(MYFLAGS)
	LDFLAGS=-lghost_static -pthread
endif
ifeq ($(UNAME_S),Darwin)
	CXX=clang++
	CXXFLAGS= -std=c++17  -stdlib=libc++ $(CXXFIRSTFLAGS) $(MYFLAGS)
	LDFLAGS=-lghost_static -lc++ -lc++abi -pthread
endif

# Directories
SRCDIR=src
HPPDIR=src
OBJDIR=obj
BINDIR=bin

# Files
SOURCES=$(foreach sdir, $(SRCDIR), $(wildcard $(sdir)/*.cpp))
OBJECTS=$(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SOURCES)))

vpath %.cpp $(SRCDIR)
vpath %.o $(OBJDIR)

# Reminder, 'cause it is easy to forget makefile's fucked-up syntax...
# $@ is what triggered the rule, ie the target before :
# $^ is the whole dependencies list, ie everything after :
# $< is the first item in the dependencies list

# Rules

all: $(BINDIR)/magic_square $(BINDIR)/min_magic_square $(BINDIR)/magic_square_pure_csp $(BINDIR)/min_magic_square_pure_csp

$(BINDIR)/magic_square: $(OBJDIR)/magic_square.o $(OBJDIR)/builder_ms.o $(OBJDIR)/linear_eq.o $(OBJDIR)/alldifferent.o $(OBJDIR)/print_ms.o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BINDIR)/min_magic_square: $(OBJDIR)/min_magic_square.o $(OBJDIR)/min_builder_ms.o $(OBJDIR)/linear_eq.o $(OBJDIR)/alldifferent.o $(OBJDIR)/print_ms.o $(OBJDIR)/min_sum_corners.o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BINDIR)/magic_square_pure_csp: $(OBJDIR)/magic_square_pure_csp.o $(OBJDIR)/builder_ms_pure_csp.o $(OBJDIR)/linear_eq_pure_csp.o $(OBJDIR)/alldifferent_pure_csp.o $(OBJDIR)/print_ms.o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BINDIR)/min_magic_square_pure_csp: $(OBJDIR)/min_magic_square_pure_csp.o $(OBJDIR)/min_builder_ms_pure_csp.o $(OBJDIR)/linear_eq_pure_csp.o $(OBJDIR)/alldifferent_pure_csp.o $(OBJDIR)/print_ms.o $(OBJDIR)/min_sum_corners.o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/magic_square.o: $(OBJDIR)/builder_ms.o $(OBJDIR)/print_ms.o
	$(CXX) $(CXXFLAGS) -I$(HPPDIR) -c $(SRCDIR)/magic_square.cpp -o $@

$(OBJDIR)/min_magic_square.o: $(OBJDIR)/min_builder_ms.o $(OBJDIR)/print_ms.o
	$(CXX) $(CXXFLAGS) -I$(HPPDIR) -c $(SRCDIR)/magic_square.cpp -o $@

$(OBJDIR)/magic_square_pure_csp.o: $(OBJDIR)/builder_ms_pure_csp.o $(OBJDIR)/print_ms.o
	$(CXX) $(CXXFLAGS) -DPURE_CSP -I$(HPPDIR) -c $(SRCDIR)/magic_square.cpp -o $@

$(OBJDIR)/min_magic_square_pure_csp.o: $(OBJDIR)/min_builder_ms_pure_csp.o $(OBJDIR)/print_ms.o
	$(CXX) $(CXXFLAGS) -DPURE_CSP -I$(HPPDIR) -c $(SRCDIR)/magic_square.cpp -o $@

$(OBJDIR)/builder_ms.o: $(OBJDIR)/linear_eq.o $(OBJDIR)/alldifferent.o 
	$(CXX) $(CXXFLAGS) -I$(HPPDIR) -c $(SRCDIR)/builder_ms.cpp -o $@

$(OBJDIR)/min_builder_ms.o: $(OBJDIR)/linear_eq.o $(OBJDIR)/alldifferent.o $(OBJDIR)/min_sum_corners.o
	$(CXX) $(CXXFLAGS) -I$(HPPDIR) -DMINMS -c $(SRCDIR)/builder_ms.cpp -o $@

$(OBJDIR)/builder_ms_pure_csp.o: $(OBJDIR)/linear_eq_pure_csp.o $(OBJDIR)/alldifferent_pure_csp.o
	$(CXX) $(CXXFLAGS) -DPURE_CSP -I$(HPPDIR) -c $(SRCDIR)/builder_ms.cpp -o $@

$(OBJDIR)/min_builder_ms_pure_csp.o: $(OBJDIR)/linear_eq_pure_csp.o $(OBJDIR)/alldifferent_pure_csp.o $(OBJDIR)/min_sum_corners.o
	$(CXX) $(CXXFLAGS) -DPURE_CSP -I$(HPPDIR) -DMINMS -c $(SRCDIR)/builder_ms.cpp -o $@

$(OBJDIR)/print_ms.o:
	$(CXX) $(CXXFLAGS) -I$(HPPDIR) -c $(SRCDIR)/print_ms.cpp -o $@

$(OBJDIR)/linear_eq.o:
	$(CXX) $(CXXFLAGS) -I$(HPPDIR) -c $(SRCDIR)/linear_eq.cpp -o $@

$(OBJDIR)/alldifferent.o:
	$(CXX) $(CXXFLAGS) -I$(HPPDIR) -c $(SRCDIR)/alldifferent.cpp -o $@

$(OBJDIR)/linear_eq_pure_csp.o:
	$(CXX) $(CXXFLAGS) -I$(HPPDIR) -c $(SRCDIR)/linear_eq_pure_csp.cpp -o $@

$(OBJDIR)/alldifferent_pure_csp.o:
	$(CXX) $(CXXFLAGS) -I$(HPPDIR) -c $(SRCDIR)/alldifferent_pure_csp.cpp -o $@

$(OBJDIR)/min_sum_corners.o:
	$(CXX) $(CXXFLAGS) -I$(HPPDIR) -c $(SRCDIR)/min_sum_corners.cpp -o $@

.PHONY: clean

clean:
	rm -fr core $(BINDIR)/magic_square $(BINDIR)/min_magic_square $(BINDIR)/magic_square_pure_csp $(BINDIR)/min_magic_square_pure_csp $(OBJECTS) $(OBJDIR)/min_magic_square.o $(OBJDIR)/min_builder_ms.o $(OBJDIR)/min_magic_square_pure_csp.o $(OBJDIR)/min_builder_ms_pure_csp.o $(OBJDIR)/magic_square_pure_csp.o $(OBJDIR)/builder_ms_pure_csp.o
