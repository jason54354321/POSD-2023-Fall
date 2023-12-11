#include <gtest/gtest.h>

#include "db_test.h"
#include "parser_test.h"

int main(int argc, char *argv[]) {
    system("cat test/db_test.h");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}