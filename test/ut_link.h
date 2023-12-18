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
    virtual void SetUp() {
        home = new Folder("structure/home");

        profile = new File("structure/home/my_profile");
        home->add(profile);

        link = new Link("structure/home/mylink", profile);
        home->add(link);

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

        download = new Folder("structure/home/Downloads");
        home->add(download);

        funny = new File("structure/home/Downloads/funny.png");
        download->add(funny);

    }

    void TearDown() {
        delete home;
        home = nullptr;
        profile = nullptr;
        download = nullptr;
        document = nullptr;
        note = nullptr;
        favorite = nullptr;
        ddd = nullptr;
        ca = nullptr;
        cqrs = nullptr;
        funny = nullptr;
        link = nullptr;
    }
    
    Node * home;
    Node * profile;
    Node * download;
    Node * document;
    Node * note;
    Node * favorite;
    Node * ddd;
    Node * ca;
    Node * cqrs;
    Node * funny;
    Node * link;
};

TEST_F(LinkTestSuite, filelink_sanity) {
    ASSERT_EQ("mylink", link->name());
    ASSERT_EQ("structure/home/mylink", link->path());
}

TEST_F(LinkTestSuite, filelink_forward_action) {
    ASSERT_EQ(1 , link->numberOfFiles());
    ASSERT_EQ("my_profile", link->find("structure/home/my_profile")->name());
    ASSERT_EQ("structure/home/my_profile", link->findByName("my_profile").front());
    ASSERT_THROW(link->add(ca), string);
    ASSERT_THROW(link->remove("123"), string);
    ASSERT_EQ(nullptr, link->getChildByName("123"));
}

TEST_F(LinkTestSuite, filelink_tree_visitor) {
    Visitor *visitor = new TreeVisitor(OrderByNameIteratorFactory::instance());

    home->accept(visitor);

}