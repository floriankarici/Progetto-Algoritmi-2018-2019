# lista dei target da eseguire sempre
all: tests

# compila (grazie alla dipendenza) e esegue i test
tests: bin/edit_distance_tests
	bin/edit_distance_tests

#  compila (grazie alla dipendenza) e esegue ordered_array
exec: bin/edit_distance
	bin/edit_distance

# Flags per il compilatore -- su gcc -Weverything non esiste
#    sostituire con -Wall -Wpedantic
CFLAGS = -g -Wall -Wpedantic -Wno-padded 

# Lista degli header files
INCLUDES = src/*.h

# tutti i target vanno ricompilati se cambiano gli header o
# questo Makefile
COMMON_DEPS = $(INCLUDES) Makefile

# regola per compilare un .c in un .o
# viene applicata ogni volta che una dipendenza richiede di compilare un file in
#    `build` e con suffisso .o. Il simbolo % effettua pattern matching con quanto
#    compreso tra 'build/' e '.o', la stringa in questione viene quindi usata sul lato
#    destro della regola per indicare il file da compilare.
# Le variabili $< e $@ sono gestite automaticamente da `make` esse corrispondono:
#   $@ : l'intero target della regola (in questo caso: build/<nomefile>.o)
#   $< : la prima dipendenza della regola (in questo caso: src/<nomefile>.c)
build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/edit_distance: build/edit_distance.o $(COMMON_DEPS)
	$(CC) -o bin/edit_distnace build/edit_distance.o

bin/edit_distance_tests: build/edit_distance_tests.o build/edit_distance_dyn.o build/edit_distance.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/edit_distance_tests build/edit_distance_dyn.o  build/edit_distance_tests.o build/edit_distance.o build/unity.o

clean:
	rm -f build/* bin/*
