CC=gcc

CFLAGS=-Wall -Iinclude

OBJFILES=src/programa-principal.o src/parser.o src/dataset_validator.o src/orderedList.o src/utility.o src/hotel.o src/reservation.o src/user.o src/hashtable.o src/hotelsManager.o src/reservationsManager.o src/usersManager.o

all: programa-principal

programa-principal: $(OBJFILES)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJFILES): src/%.o : src/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f programa-principal programa-testes src/*.o


#para testes manuais
#OBJFILESTEST=src/testes/testausers.o src/catalogsManager.o src/usersManager.o src/user.o src/utility.o src/hashtable.o
#OBJFILESTEST=src/testes/testahashtable.o src/hashtable.o
#OBJFILESTEST=src/testes/testareservations.o src/catalogsManager.o src/reservationsManager.o src/reservation.o src/hotel.o src/utility.o src/hashtable.o
#OBJFILESTEST=src/testes/testaflights.o src/catalogsManager.o src/flightsManager.o src/flight.o src/utility.o src/hashtable.o
#OBJFILESTEST=src/testes/testaordlists.o src/orderedList.o src/utility.o src/hotel.o src/reservation.o src/hashtable.o
#OBJFILESTEST=src/testes/testahotels.o src/orderedList.o src/utility.o src/hotel.o src/reservation.o src/hashtable.o
OBJFILESTEST=src/testes/testaCatalogs.o src/orderedList.o src/utility.o src/hotel.o src/reservation.o src/user.o src/hashtable.o src/hotelsManager.o src/reservationsManager.o src/usersManager.o
#OBJFILESTEST=src/testes/testaRadixSort.o

teste: test

test: $(OBJFILESTEST)
	$(CC) $(CFLAGS) -g $^ -o $@

$(OBJFILESTEST): src/%.o : src/%.c
	$(CC) $(CFLAGS) -c -g $^ -o $@

cleantest:
	rm -f test src/*.o src/testes/*.o
