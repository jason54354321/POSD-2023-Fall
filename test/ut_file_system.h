#include <gtest/gtest.h>

#include "../src/file.h"
#include "../src/file_system_builder.h"
#include "../src/file_system_parser.h"
#include "../src/file_system_scanner.h"
#include "../src/folder.h"
#include "../src/node.h"
#include "../src/tree_visitor.h"

class FileSystemSuite : public ::testing::Test {
  protected:
    virtual void SetUp() {
        home = new Folder("structure/home");

        profile = new File("structure/home/my_profile");
        home->add(profile);

        hello1 = new File("structure/home/hello.txt");
        home->add(hello1);

        document = new Folder("structure/home/Documents");
        home->add(document);

        favorite = new Folder("structure/home/Documents/favorites");
        document->add(favorite);
        ddd = new File("structure/home/Documents/favorites/domain-driven-design.pdf");
        favorite->add(ddd);
        ca = new File("structure/home/Documents/favorites/clean-architecture.pdf");
        favorite->add(ca);
        cqrs = new File("structure/home/Documents/favorites/cqrs.pdf");
        favorite->add(cqrs);

        note = new File("structure/home/Documents/note.txt");
        document->add(note);

        hello2 = new File("structure/home/hello.txt");
        home->add(hello2);

        download = new Folder("structure/home/Downloads");
        home->add(download);

        funny = new File("structure/home/Downloads/funny.png");
        download->add(funny);

        visitor_folder = new Folder("structure/visitor");
        file1 = new File("structure/visitor/file1.txt");
        visitor_folder->add(file1);
        file2 = new File("structure/visitor/file2.txt");
        visitor_folder->add(file2);
        nested = new Folder("structure/visitor/nested");
        visitor_folder->add(nested);
        file3 = new File("structure/visitor/nested/file3.txt");
        nested->add(file3);
        file4 = new File("structure/visitor/nested/file4.txt");
        nested->add(file4);
    }

    void TearDown() {
        delete home;
        delete profile;
        delete download;
        delete document;
        delete note;
        delete favorite;
        delete ddd;
        delete ca;
        delete cqrs;
        delete funny;
        delete hello1;
        delete hello2;
        delete visitor_folder;
        delete file1;
        delete file2;
        delete nested;
        delete file3;
        delete file4;
    }

    Node *home;
    Node *profile;
    Node *download;
    Node *document;
    Node *note;
    Node *favorite;
    Node *ddd;
    Node *ca;
    Node *cqrs;
    Node *funny;
    Node *hello1;
    Node *hello2;

    Node *visitor_folder;
    Node *file1;
    Node *file2;
    Node *nested;
    Node *file3;
    Node *file4;
};

TEST_F(FileSystemSuite, Scanner) {
    FileSystemScanner *scanner = new FileSystemScanner();

    scanner->setPath("structure/home");

    vector<string> expectList;
    expectList.push_back(".");
    expectList.push_back("..");
    expectList.push_back("my_profile");
    expectList.push_back("hello.txt");
    expectList.push_back("Downloads");
    expectList.push_back("Documents");

    int counter = 0;
    while (!scanner->isDone()) {
        cout << scanner->currentNodeName() << endl;
        // find element in vector
        if (!(std::find(expectList.begin(), expectList.end(), scanner->currentNodeName()) !=
              expectList.end())) {
            FAIL();
        }
        scanner->nextNode();
        counter++;
    }
}

TEST_F(FileSystemSuite, ScannerTest2) {
    FileSystemScanner *scanner = new FileSystemScanner();

    scanner->setPath("structure/home/Documents/favorites");

    /* vector<string> expectList; */
    /* expectList.push_back("."); */
    /* expectList.push_back(".."); */
    /* expectList.push_back("my_profile"); */
    /* expectList.push_back("hello.txt"); */
    /* expectList.push_back("Downloads"); */
    /* expectList.push_back("Documents"); */

    while (!scanner->isDone()) {
        cout << scanner->currentNodeName() << endl;
        // find element in vector
        scanner->nextNode();
    }
}

TEST_F(FileSystemSuite, Parser) {
    FileSystemScanner *scanner = new FileSystemScanner();
    FileSystemBuilder *builder = new FileSystemBuilder();
    FileSystemParser *parser = new FileSystemParser(builder);

    parser->setPath("structure/home");

    parser->parse();

    Folder *root = parser->getRoot();
    EXPECT_EQ("home", root->name());

    string expected = ".\n\
├── Documents\n\
│   ├── favorites\n\
│   │   ├── clean-architecture.pdf\n\
│   │   ├── cqrs.pdf\n\
│   │   └── domain-driven-design.pdf\n\
│   ├── hello.txt\n\
│   └── note.txt\n\
├── Downloads\n\
│   └── funny.png\n\
├── hello.txt\n\
└── my_profile\n\
";

    TreeVisitor *visitor = new TreeVisitor(OrderBy::Name);
    root->accept(visitor);
    ASSERT_EQ(expected, visitor->getTree());
}
