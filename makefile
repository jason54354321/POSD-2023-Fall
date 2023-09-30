INCLUDES= src/node.h \
					src/file.h \
					test/ut_file.h \

.PHONY: directories clean stat

all: directories bin/ut_all
# all: directories bin/ut_all bin/main

# bin/main: src/main.cpp
# 	g++ -std=c++11 src/main.cpp -o bin/main

bin/ut_all: test/ut_all.cpp $(INCLUDES)
	g++ -std=c++11 test/ut_all.cpp -o bin/ut_all -lgtest -lpthread

directories:
	mkdir -p bin

clean:
	rm -f bin/*

stat:
	wc src/* test/*

