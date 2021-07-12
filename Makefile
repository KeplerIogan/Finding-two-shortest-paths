OBJ = build/Main.o build/MinTree.o
C+ = g++
CFLAGS = -g3 -O0 -Wall

.PHONY: clean open gdb

MinTree: $(OBJ)
	$(C+) $(CFLAGS) -o MinTree $(OBJ)

build/MinTree.o: src/MinTree.cpp build
	$(C+) $(CFLAGS) -o build/MinTree.o -c src/MinTree.cpp

build/Main.o: src/Main.cpp build
	$(C+) $(CFLAGS) -o build/Main.o -c src/Main.cpp

build:
	mkdir build


clean :
	rm -rf build
open :
	/MinTree
gdb :
	gdb ./MinTree
