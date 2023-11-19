#include "../src/beautify_visitor.h"
#include "../src/json_object.h"
#include "../src/string_value.h"
#include <gtest/gtest.h>

class VisitorSuite : public testing::Test {
  protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST(VisitorSuite, beautify_visitor) {
    JsonObject *home = new JsonObject();
    JsonObject *jo_books = new JsonObject();

    JsonObject *jo_clean_code = new JsonObject();
    JsonObject *jo_design_patterns = new JsonObject();

    StringValue *sv_robert = new StringValue("Robert C. Martin");
    StringValue *sv_clean = new StringValue("Clean Code");

    StringValue *sv_erich =
        new StringValue("Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides");
    StringValue *sv_design =
        new StringValue("Design Patterns Elements of Reusable Object-Oriented Software");

    home->set("books", jo_books);
    jo_books->set("clean code", jo_clean_code);
    jo_books->set("design pattern", jo_design_patterns);
    jo_clean_code->set("author", sv_robert);
    jo_clean_code->set("name", sv_clean);
    jo_design_patterns->set("author", sv_erich);
    jo_design_patterns->set("name", sv_design);

    string expected = "{\n\
    \"books\": {\n\
        \"clean code\": {\n\
            \"author\": \"Robert C. Martin\",\n\
            \"name\": \"Clean Code\"\n\
        },\n\
        \"design pattern\": {\n\
            \"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides\",\n\
            \"name\": \"Design Patterns Elements of Reusable Object-Oriented Software\"\n\
        }\n\
    }\n\
}";

    BeautifyVisitor *visitor = new BeautifyVisitor();
    home->accept(visitor);

    ASSERT_EQ(expected, visitor->getResult());

    delete home;
    delete jo_books;
    delete jo_clean_code;
    delete jo_design_patterns;
    delete sv_clean;
    delete sv_erich;
    delete sv_design;
    delete sv_robert;
    delete visitor;
}
