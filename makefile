ifeq ($(OS),Windows_NT)
SHELL := powershell.exe
.SHELLFLAGS := -NoProfile -Command
endif

.PHONY: directories clean stat

all: directories bin/ut_all bin/main

bin/main: src/main.cpp src/hello.h
	g++ -std=c++14 src/main.cpp -o bin/main

bin/ut_all: test/ut_main.cpp test/ut_hello.h src/hello.h
	g++ -std=c++14 test/ut_main.cpp -o bin/ut_all -lgtest -lpthread

directories:
	mkdir -force bin

clean:
	rm -force bin/*

stat:
	wc src/* test/*
