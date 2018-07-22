CC=em++
WOPTS=
CFLAGS=-std=c++11 $(WOPTS) --bind -s WASM=1 -s ASSERTIONS=1
OBJDIR=obj


SRCS=$(filter-out main.cpp, $(wildcard *.cpp */*.cpp))
OBJS=$(patsubst %.cpp,$(OBJDIR)/%.bc,$(SRCS))
EXEC=../out/M6808.js

all: $(EXEC)

%.cpp: %.hxx

$(OBJDIR)/%.bc: %.cpp
	$(CC) $(CFLAGS) $< -o $@

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJDIR)/*
	rm -f $(EXEC)