mydictionary: mydictionary.o mydictSearches.o
	g++ mydictionary.o mydictSearches.o -o mydictionary
mydictSearches.o: mydictSearches.cpp mydictSearches.h
	g++ -c mydictSearches.cpp
mydictionary.o: mydictionary.cpp
	g++ -c mydictionary.cpp
clean:
	rm *.o mydictionary