HEADER= src/node.h \
				src/file.h \
				src/iterator.h \
				src/dfs_iterator.h \

TEST_HEADER= test/ut_folder.h \
						 test/ut_folder_operation.h \
						 test/ut_iterator_dfs.h \


OBJECTS= iterator.o

.PHONY: directories clean stat

# Leading in ifeq must be "Space" instead of tab
ifeq ($(OS),Windows_NT)
  $(info "THIS IS")
  $(info $(OS))
  SHELL := powershell.exe
  .SHELLFLAGS := -NoProfile -Command
  
  all: bin/ut_all
else
  all: directories bin/ut_all
endif



# bin/main: src/main.cpp $(OBJECTS) $(HEADER)
# 	g++ -g -std=c++14 src/main.cpp obj/* -o bin/main

bin/ut_all: test/ut_all.cpp $(OBJECTS) $(HEADER) $(TEST_HEADER)
	g++ -g -std=c++14 test/ut_all.cpp obj/* -o bin/ut_all -lgtest -lpthread

$(OBJECTS): src/iterator.cpp src/iterator.h $(HEADER)
	g++ -g -std=c++14 -c src/iterator.cpp -o obj/iterator.o

directories:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
	rm -f obj/*

stat:
	wc src/* test/*

