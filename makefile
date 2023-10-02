HEADER= src/node.h \
					src/file.h \
					src/iterator.h \
					test/ut_file.h \

OBJECTS= iterator.o

.PHONY: directories clean stat

all: clean directories bin/ut_all
# all: directories bin/ut_all bin/main

# bin/main: src/main.cpp
# 	g++ -std=c++11 src/main.cpp -o bin/main

bin/ut_all: test/ut_all.cpp $(OBJECTS) $(HEADER)
	g++ -std=c++11 test/ut_all.cpp obj/* -o bin/ut_all -lgtest -lpthread

iterator.o: src/iterator.cpp src/iterator.h $(HEADER)
	g++ -std=c++11 -c src/iterator.cpp -o obj/iterator.o


directories:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
	rm -f obj/*

stat:
	wc src/* test/*

