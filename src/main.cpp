#include "./hello.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv) {

  std::cout << sayHello("world") << '\n' << endl;
  std::cout << argc << endl;
  for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << endl;
  }

  return 0;
}
