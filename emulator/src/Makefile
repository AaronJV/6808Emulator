CC=em++
WOPTS=-s ERROR_ON_UNDEFINED_SYMBOLS=0
CFLAGS=-std=c++11 $(WOPTS) --bind -s WASM=1 -s ASSERTIONS=1
OBJDIR=obj


SRCS=$(filter-out main.cpp, $(wildcard *.cpp */*.cpp))
OBJS=$(patsubst %.cpp,$(OBJDIR)/%.bc,$(SRCS))
EXEC=/out/M6808.js

$(shell mkdir -p $(dir $(OBJS)) >/dev/null)

all: $(EXEC)

%.cpp: %.hxx

$(OBJDIR)/%.bc: %.cpp
	$(CC) $(CFLAGS) $< -o $@

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

clean:
	rm -rf $(OBJDIR)/*
	rm -f $(EXEC)