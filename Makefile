bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp

bin/testHashTable: testHashTable.cpp HashTable.h Dict.h TableEntry.h ../PRA_2627_P1/ListLinked.h ../PRA_2627_P1/List.h ../PRA_2627_P1/Node.h
	mkdir -p bin
	g++ -std=c++17 -o bin/testHashTable testHashTable.cpp

clean:
	rm -rf *.o *.gch *.pch bin
