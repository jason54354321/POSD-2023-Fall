#include "../src/beautify_visitor.h"
#include "../src/json_object.h"
#include "../src/json_parser.h"
#include "../src/string_value.h"
#include "../src/visitor.h"
#include <gtest/gtest.h>

class ParserSuite : public testing::Test {
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

TEST_F(ParserSuite, parser) {
    JsonScanner *scanner = new JsonScanner();
    JsonBuilder *builder = new JsonBuilder();
    JsonParser *parser = new JsonParser(scanner, builder);

    string input = "{\"books\": {"
                   "\"design patterns\": {"
                   "\"name\": \"Design Patterns: Elements of Reusable Object-Oriented Software\","
                   "\"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\""
                   "},"
                   "\"clean code\": {"
                   "\"name\": \"Clean Code\","
                   "\"author\": \"Robert C. Martin\""
                   "}"
                   "}}";

    parser->setInput(input);
    parser->parse();

    JsonObject *object = parser->getJsonObject();
    BeautifyVisitor *visitor = new BeautifyVisitor();
    object->accept(visitor);

    string expected = "{\n\
    \"books\": {\n\
        \"clean code\": {\n\
            \"author\": \"Robert C. Martin\",\n\
            \"name\": \"Clean Code\"\n\
        },\n\
        \"design patterns\": {\n\
            \"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\",\n\
            \"name\": \"Design Patterns: Elements of Reusable Object-Oriented Software\"\n\
        }\n\
    }\n\
}";
    EXPECT_EQ(expected, visitor->getResult());

    delete scanner;
    delete builder;
    delete parser;
}
