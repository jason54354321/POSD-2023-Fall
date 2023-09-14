#include "hello.h"
#include <string>

using namespace std;

Hello::Hello(){};

string Hello::sayHello(string content) { return "hello, " + content; }
