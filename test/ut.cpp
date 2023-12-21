#include <gtest/gtest.h>

#include "./triangle_test.h"
#include "./compound_test.h"
#include "./visitor_test.h"
#include "./parser_test.h"
#include "./iterator_test.h"
#include "./drawing_test.h"
#include "./db_test.h"

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}