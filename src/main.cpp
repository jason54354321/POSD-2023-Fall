#include "hello.h"
#include <iostream>
using namespace std;

int main(void) {

  Hello hello;
  std::cout << hello.sayHello("world") << '\n';

  return 0;
}
