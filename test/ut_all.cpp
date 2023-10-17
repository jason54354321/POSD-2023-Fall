#include "ut_folder.h"
#include "ut_folder_operation.h"
#include "ut_iterator_dfs.h"
#include "ut_visitor.h"
#include <gtest/gtest.h>

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
