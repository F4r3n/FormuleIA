CC=gcc
BIN=bin/
SRC=src/
MANUBIN=~/Bureau/GrandPrix/drivers/


CFLAGS=-Wall -std=c99 -pedantic -O3

all: fatMobile

testManu: $(MANUBIN)fatMobile

fatMobile: $(BIN)test.o $(BIN)path.o $(BIN)pile.o $(BIN)fi.o $(BIN)communication.o
	$(CC) -o $@ $^ 

$(MANUBIN)fatMobile: $(BIN)test.o $(BIN)pile.o $(BIN)fi.o $(BIN)fonction.o $(BIN)communication.o
	$(CC) -o $@ $^ 

$(BIN)test.o: $(SRC)test.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(BIN)path.o: $(SRC)path.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(BIN)pile.o: $(SRC)pile.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(BIN)fi.o: $(SRC)file.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(BIN)communication.o: $(SRC)communication.c
	$(CC) -o $@ -c $^ $(CFLAGS)


clean:
	-rm $(BIN)*.o
	
