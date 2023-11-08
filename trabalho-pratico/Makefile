CC=gcc

CFLAGS=-Wall -Iinclude

OBJFILES=src/programa-principal.o

all: programa-principal

programa-principal: $(OBJFILES)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJFILES): src/%.o : src/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f programa-principal programa-testes src/*.o


#para testes manuais
OBJFILESTEST=src/testes/testausers.o src/catalogsManager.o src/usersManager.o src/user.o src/utility.o src/hashtable.o
#OBJFILESTEST=src/testes/testahashtable.o src/hashtable.o

teste: test

test: $(OBJFILESTEST)
	$(CC) $(CFLAGS) -g $^ -o $@

$(OBJFILESTEST): src/%.o : src/%.c
	$(CC) $(CFLAGS) -c -g $^ -o $@

cleantest:
	rm -f test src/*.o src/testes/*.o
