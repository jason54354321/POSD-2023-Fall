#include <gtest/gtest.h>
#include "../src/file.h"
#include "../src/node.h"
#include "../src/folder.h"
#include "../src/link.h"
#include "../src/visitor.h"
#include "../src/tree_visitor.h"
#include "../src/iterator_factory.h"
#include "../src/iterator_factories.h"

class LinkTestSuite: public ::testing::Test {
protected:
    void SetUp() {

        home = new Folder("structure2/home");

        profile = new File("structure2/home/my_profile");
        home->add(profile);

        link = new Link("structure2/home/mylink", profile);
        home->add(link);

        hello = new File("structure2/home/hello.txt");
        home->add(hello);

        download = new Folder("structure2/home/Downloads");
        home->add(download);
        funny = new File("structure2/home/Downloads/funny.png");
        download->add(funny);

        document = new Folder("structure2/home/Documents");
        home->add(document);

        note = new File("structure2/home/Documents/note.txt");
        document->add(note);
        hello2 = new File("structure2/home/Documents/hello.txt");
        document->add(hello2);

        programming = new Folder("structure2/home/Documents/programming");
        document->add(programming);
        cpp = new File("structure2/home/Documents/programming/cpp.pub");
        programming->add(cpp);
        oop = new File("structure2/home/Documents/programming/oop.pdf");
        programming->add(oop);
        python = new File("structure2/home/Documents/programming/python.pub");
        programming->add(python);

        ddd = new File("structure2/home/Documents/domain-driven-design.pub");
        document->add(ddd);
        ca = new File("structure2/home/Documents/clean-architecture.pdf");
        document->add(ca);
        ooad = new File("structure2/home/Documents/object-oriented-analysis-and-design.pdf");
        document->add(ooad);
    }

    void TearDown() {
        delete home;
        profile = nullptr;
        hello = nullptr;
        download = nullptr;
        funny = nullptr;
        document = nullptr;
        note = nullptr;
        hello2 = nullptr;
        programming = nullptr;
        cpp = nullptr;
        oop = nullptr;
        python = nullptr;
        ddd = nullptr;
        ca = nullptr;
        ooad = nullptr;
        link = nullptr;
    }
    
    Node * home;
    Node * profile;
    Node * hello;
    Node * download;
    Node * funny;
    Node * document;
    Node * note;
    Node * hello2;
    Node * programming;
    Node * cpp;
    Node * oop;
    Node * python;
    Node * ddd;
    Node * ca;
    Node * ooad;
    Node * link;

};

TEST_F(LinkTestSuite, filelink_sanity) {
    ASSERT_EQ("mylink", link->name());
    ASSERT_EQ("structure2/home/mylink", link->path());
}

TEST_F(LinkTestSuite, filelink_forward_action) {
    ASSERT_EQ(1 , link->numberOfFiles());
    ASSERT_EQ("my_profile", link->find("structure2/home/my_profile")->name());
    ASSERT_EQ("structure2/home/my_profile", link->findByName("my_profile").front());
    ASSERT_THROW(link->add(ca), string);
    ASSERT_THROW(link->remove("123"), string);
    ASSERT_EQ(nullptr, link->getChildByName("123"));
}

TEST_F(LinkTestSuite, filelink_tree_visitor_Name) {
    TreeVisitor *visitor = new TreeVisitor(OrderByNameIteratorFactory::instance());

    home->accept(visitor);

    string expected = 
    ".\n"
    "├── Documents\n"
    "│   ├── clean-architecture.pdf\n"
    "│   ├── domain-driven-design.pub\n"
    "│   ├── hello.txt\n"
    "│   ├── note.txt\n"
    "│   ├── object-oriented-analysis-and-design.pdf\n"
    "│   └── programming\n"
    "│       ├── cpp.pub\n"
    "│       ├── oop.pdf\n"
    "│       └── python.pub\n"
    "├── Downloads\n"
    "│   └── funny.png\n"
    "├── hello.txt\n"
    "├── my_profile\n"
    "└── mylink\n";

    ASSERT_EQ(expected, visitor->getTree());
}

TEST_F(LinkTestSuite, filelink_tree_visitor_Folder) {
    TreeVisitor *visitor = new TreeVisitor(OrderByNameWithFolderFirstIteratorFactory::instance());

    home->accept(visitor);

    string expected = 
    ".\n"
    "├── Documents\n"
    "│   ├── programming\n"
    "│   │   ├── cpp.pub\n"
    "│   │   ├── oop.pdf\n"
    "│   │   └── python.pub\n"
    "│   ├── clean-architecture.pdf\n"
    "│   ├── domain-driven-design.pub\n"
    "│   ├── hello.txt\n"
    "│   ├── note.txt\n"
    "│   └── object-oriented-analysis-and-design.pdf\n"
    "├── Downloads\n"
    "│   └── funny.png\n"
    "├── hello.txt\n"
    "├── my_profile\n"
    "└── mylink\n";

    ASSERT_EQ(expected, visitor->getTree());
}

TEST_F(LinkTestSuite, filelink_tree_visitor_Kind) {
    TreeVisitor *visitor = new TreeVisitor(OrderByKindIteratorFactory::instance());

    home->accept(visitor);

    string expected = 
    ".\n"
    "├── my_profile\n"
    "├── Documents\n"
    "│   ├── programming\n"
    "│   │   ├── oop.pdf\n"
    "│   │   ├── cpp.pub\n"
    "│   │   └── python.pub\n"
    "│   ├── clean-architecture.pdf\n"
    "│   ├── object-oriented-analysis-and-design.pdf\n"
    "│   ├── domain-driven-design.pub\n"
    "│   ├── hello.txt\n"
    "│   └── note.txt\n"
    "├── Downloads\n"
    "│   └── funny.png\n"
    "├── mylink\n"
    "└── hello.txt\n";

    ASSERT_EQ(expected, visitor->getTree());
}