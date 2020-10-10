FLAG=-std=c++11 -ljsoncpp

libsearcher.so:searcher.cpp searcher.h
	g++ searcher.cpp -o libsearcher.so -shared -fPIC $(FLAG)

.PHONY:clean
clean:
	rm libsearcher.so
