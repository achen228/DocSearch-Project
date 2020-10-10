FLAG=-std=c++11 -ljsoncpp

.PHONY:all
all:index_test searcher_test 

index_test:index_test.cpp ../searcher/searcher.cpp
	g++ $^ -o $@ $(FLAG)

searcher_test:searcher_test.cpp ../searcher/searcher.cpp
	g++ $^ -o $@ $(FLAG)

.PHONY:clean
clean:
	rm index_test searcher_test
