CC=gcc
CFLAGS = -Wall -Wextra -O2 -g -std=gnu99
LIBPATH = -Llib
USERLIBS = -lfdr
BIN=bin
INCL=include
LIB=lib
SRC=src
TARGET=main

all: mkbin compile run
	
compile: main.o komut.o islem.o siparis.o yardimci.o
	$(CC) $(CFLAGS) $(LIBPATH) $(LIB)/main.o $(LIB)/komut.o $(LIB)/islem.o $(LIB)/siparis.o $(LIB)/yardimci.o $(USERLIBS) -o $(BIN)/$(TARGET) 

run: 
	clear
	./$(BIN)/$(TARGET)
	
main.o: src/main.c include/komut.h include/islem.h include/jrb.h include/jval.h include/siparis.h include/yardimci.h
	$(CC) -I $(INCL) -c $(SRC)/main.c -o $(LIB)/main.o
komut.o: src/komut.c include/komut.h include/islem.h include/jrb.h include/jval.h include/siparis.h
	$(CC) -I $(INCL) -c $(SRC)/komut.c -o $(LIB)/komut.o
islem.o: src/islem.c include/islem.h include/jrb.h include/jval.h include/siparis.h include/fields.h include/komut.h include/islem.h include/yardimci.h
	$(CC) -I $(INCL) -c $(SRC)/islem.c -o $(LIB)/islem.o
siparis.o: src/siparis.c include/siparis.h
	$(CC) -I $(INCL) -c $(SRC)/siparis.c -o $(LIB)/siparis.o
yardimci.o: src/yardimci.c
	$(CC) -I $(INCL) -c $(SRC)/yardimci.c -o $(LIB)/yardimci.o

.PHONY: mkbin
mkbin:
	mkdir -p bin

.PHONY: clean
clean:
	rm -f $(BIN)/*
	rm -f $(LIB)/*.o
