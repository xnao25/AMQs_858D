all: bf blockedbf
blockedbf: main2.o blockedBloomFilter.o bit_vector.o
	g++ -g -o blockedbf main2.o blockedBloomFilter.o bit_vector.o --std=c++11
bf: main3.o bloomFilter.o bit_vector.o
	g++ -g -o bf main3.o bloomFilter.o bit_vector.o --std=c++11
main2.o: main2.cpp
	g++ -g -c main2.cpp --std=c++11
main3.o: main3.cpp
	g++ -g -c main3.cpp --std=c++11
blockedBloomFilter.o: blockedBloomFilter.cpp blockedBloomFilter.h
	g++ -g -c blockedBloomFilter.cpp --std=c++11
bloomFilter.o: bloomFilter.cpp bloomFilter.h
	g++ -g -c bloomFilter.cpp --std=c++11
bit_vector.o: bit_vector.cpp bit_vector.h
	g++ -g -c bit_vector.cpp --std=c++11
