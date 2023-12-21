#include "../src/compound.h"
#include <vector>
#include "../src/shape_iterator_factory.h"

TEST(IteratorSuite, Iterator) {
    std::vector<Shape *> shapes = {new Triangle(1,1,1), new Triangle(5, 5, 5)};
    Shape * compound = new Compound(shapes);

    ShapeIterator * it = compound->createIterator();
    
    it->first();
    ASSERT_FALSE(it->isDone());
    ASSERT_DOUBLE_EQ(3.0, it->currentItem()->perimeter());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_DOUBLE_EQ(15.0, it->currentItem()->perimeter());

    it->next();
    ASSERT_TRUE(it->isDone());

    delete it;
    delete compound;
}

TEST(IteratorSuite, IteratorFactory) {
    std::vector<Shape *> shapes = {new Triangle(1,1,1), new Triangle(5, 5, 5)};
    Shape * compound = new Compound(shapes);

    IteratorFactory * iteratorFactory = new ShapeIteratorFactory(compound);
    ShapeIterator * it = compound->createIterator(iteratorFactory);

    it->first();
    ASSERT_FALSE(it->isDone());
    ASSERT_DOUBLE_EQ(3.0, it->currentItem()->perimeter());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_DOUBLE_EQ(15.0, it->currentItem()->perimeter());

    it->next();
    ASSERT_TRUE(it->isDone());

    delete it;
    delete iteratorFactory;
    delete compound;
}