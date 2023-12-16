#include <gtest/gtest.h>
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator_factory.h"
#include "../src/iterator_factories.h"

class AbstractFactorySuite : public ::testing::Test{
protected:
    void SetUp() {
        home = new Folder("structure/home");

        profile = new File("structure/home/my_profile");
        home->add(profile);

        download = new Folder("structure/home/Downloads");
        home->add(download);

        document = new Folder("structure/home/Documents");
        home->add(document);

        note = new File("structure/home/Documents/note.txt");
        document->add(note);

        favorite = new Folder("structure/home/Documents/favorites");
        document->add(favorite);
        ddd = new File("structure/home/Documents/favorites/domain-driven-design.pdf");
        favorite->add(ddd);
        ca = new File("structure/home/Documents/favorites/clean-architecture.pdf");
        favorite->add(ca);
        cqrs = new File("structure/home/Documents/favorites/cqrs.pdf");
        favorite->add(cqrs);
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
};

TEST_F(AbstractFactorySuite, FolderIterator){
    IteratorFactory * factory = new FolderIteratorFactory();
    
    Iterator *it = home->createIterator(factory);
    it->first();
    ASSERT_EQ("my_profile", it->currentItem()->name());

    it->next();
    ASSERT_EQ("Downloads", it->currentItem()->name());

    it->next();
    ASSERT_EQ("Documents", it->currentItem()->name());
}