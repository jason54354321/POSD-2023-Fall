#include "../src/json_object.h"
#include "../src/string_value.h"
#include "../src/value.h"
#include <gtest/gtest.h>

TEST(CompositeSuite, composite) {
    JsonObject *object = new JsonObject();
    StringValue *value1 = new StringValue("123");
    StringValue *value2 = new StringValue("456");

    object->set("1", value1);
    object->set("2", value2);

    ASSERT_EQ("123", object->getValue("1")->toString());
    ASSERT_EQ("456", object->getValue("2")->toString());
}
