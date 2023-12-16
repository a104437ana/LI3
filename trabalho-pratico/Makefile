CC=gcc

CFLAGS=-Wall -Iinclude

OBJFILES=src/parser.o src/dataset_validator.o src/orderedList.o src/utility.o src/hotel.o src/reservation.o src/user.o src/airport.o src/flight.o src/hashtable.o src/hotelsManager.o src/reservationsManager.o src/usersManager.o src/airportsManager.o src/flightsManager.o src/catalogsManager.o src/interpreter.o src/output.o src/queries.o

all: programa-principal programa-testes

programa-principal: src/programa-principal.o $(OBJFILES)
	$(CC) $(CFLAGS) $^ -g -o $@

programa-testes: src/programa-testes.o $(OBJFILES)
	$(CC) $(CFLAGS) $^ -o $@

src/programa-principal.o : src/programa-principal.c
src/programa-testes.o : src/programa-testes.c

$(OBJFILES): src/%.o : src/%.c
	$(CC) $(CFLAGS) -g -c $^ -o $@

clean:
	rm -f programa-principal programa-testes src/*.o

clean_results:
	rm -f Resultados/*.txt Resultados/*.csv

clean_diffs:
	rm -f ./diffs.txt ./diffs/*.txt
