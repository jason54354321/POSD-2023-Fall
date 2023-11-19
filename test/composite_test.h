#include "../src/json_object.h"
#include "../src/string_value.h"
#include "../src/value.h"
#include <gtest/gtest.h>

class CompositeSuite : public testing::Test {
  protected:
    JsonObject *object;
    StringValue *value1;
    StringValue *value2;

    void SetUp() override {
        object = new JsonObject();
        value1 = new StringValue("123");
        value2 = new StringValue("456");

        object->set("1", value1);
        object->set("2", value2);
    }

    void TearDown() override {
        delete object;
        delete value1;
        delete value2;
    }
};

TEST_F(CompositeSuite, composite) {
    ASSERT_EQ("\"123\"", object->getValue("1")->toString());
    ASSERT_EQ("\"456\"", object->getValue("2")->toString());
}

TEST_F(CompositeSuite, Iterator) {
    JsonIterator *it = object->createIterator();

    it->first();
    ASSERT_EQ("1", it->currentKey());
    ASSERT_EQ("\"123\"", it->currentValue()->toString());
    ASSERT_EQ(false, it->isDone());

    it->next();
    ASSERT_EQ("2", it->currentKey());
    ASSERT_EQ("\"456\"", it->currentValue()->toString());
    ASSERT_EQ(false, it->isDone());

    it->next();
    ASSERT_EQ(true, it->isDone());
}

TEST_F(CompositeSuite, NullIteraotr) {
    StringValue *string_value = new StringValue("123");

    JsonIterator *it = string_value->createIterator();
    ASSERT_THROW(it->first(), const char *);
    ASSERT_THROW(it->next(), const char *);
    ASSERT_THROW(it->isDone(), const char *);
    ASSERT_THROW(it->currentKey(), const char *);
    ASSERT_THROW(it->currentValue(), const char *);
}
