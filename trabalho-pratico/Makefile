CC=gcc

CFLAGS=-Wall -Iinclude

OBJFILES=src/programa-principal.o src/parser.o src/dataset_validator.o src/orderedList.o src/utility.o src/hotel.o src/reservation.o src/user.o src/airport.o src/flight.o src/hashtable.o src/hotelsManager.o src/reservationsManager.o src/usersManager.o src/airportsManager.o src/flightsManager.o src/catalogsManager.o src/interpreter.o src/output.o src/queries.o

all: programa-principal

programa-principal: $(OBJFILES)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJFILES): src/%.o : src/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f programa-principal programa-testes src/*.o

clean_results:
	rm -f Resultados/*.txt Resultados/*.csv
