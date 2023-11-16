// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}

TEST(test_list) {
    List<int>* la = new List<int>;
    ASSERT_TRUE(la->empty());
    la->push_back(1);
    la->push_back(2);
    la->push_back(3);
    la->push_front(4);
    List<int>* lnew = new List<int>(*la);
    ASSERT_EQUAL(la->size(),4);
    ASSERT_EQUAL(la->front(),4);
    ASSERT_EQUAL(la->back(),3);
    la->pop_front();
    ASSERT_EQUAL(la->front(),1);
    ASSERT_EQUAL(la->back(),3);
    ASSERT_EQUAL(la->size(),3);
    la->pop_back();
    ASSERT_EQUAL(la->front(),1);
    ASSERT_EQUAL(la->back(),2);
    la->pop_back();
    la->pop_back();
    ASSERT_TRUE(la->empty());
    ASSERT_EQUAL(la->size(),0);
    *la = *lnew;
    ASSERT_EQUAL(lnew->size(),4);
    ASSERT_EQUAL(lnew->front(),4);
    ASSERT_EQUAL(lnew->back(),3);
    lnew->clear();
    ASSERT_TRUE(lnew->empty());
    ASSERT_EQUAL(lnew->size(),0);
    ASSERT_EQUAL(la->size(),4);
    ASSERT_EQUAL(la->front(),4);
    ASSERT_EQUAL(la->back(),3);
    
    delete la;
    delete lnew;
}

TEST(test_iterators) {
    List<int> *la = new List<int>;
    la->push_back(1);
    la->push_back(2);
    la->push_back(3);
    la->push_front(4);
    la->push_front(5);
    la->push_front(6);
    la->push_back(1);
    la->push_front(6);
    la->pop_back();
    la->pop_front();
    ASSERT_EQUAL(la->size(),6);
    List<int>::Iterator a = la->begin();
    ++a;
    ++a;
    la->erase(a);
    ASSERT_EQUAL(la->size(),5);
    ASSERT_EQUAL(la->front(),6);
    la->pop_front();
    ASSERT_EQUAL(la->front(),5);
    la->pop_front();
    ASSERT_EQUAL(la->front(),1);
    List<int>::Iterator b = la->begin();
    la->insert(b, 10);
    ASSERT_EQUAL(la->size(), 4);
    ASSERT_EQUAL(la->front(), 10);
    List<int>::Iterator c = la->begin();
    la->erase(c);
    ASSERT_EQUAL(la->front(), 1);
    delete la;
}



TEST(test_iterators_2) {
    List<int> *la = new List<int>;
    la->push_back(1);
    ASSERT_EQUAL(la->front(), 1);
    ASSERT_EQUAL(la->back(), 1)
    ASSERT_EQUAL(la->size(), 1);
    la->push_back(9);
    la->push_back(3);
    la->push_front(4);
    la->push_front(21);
    la->push_front(6);
    la->push_back(1);
    la->push_front(6);
    ASSERT_EQUAL(la->front(), 6);
    ASSERT_EQUAL(la->back(), 1)
    ASSERT_EQUAL(la->size(), 8);
    la->pop_back();
    ASSERT_EQUAL(la->front(), 6);
    ASSERT_EQUAL(la->back(), 3)
    ASSERT_EQUAL(la->size(), 7);
    la->pop_front();
    ASSERT_EQUAL(la->front(), 6);
    ASSERT_EQUAL(la->back(), 3)
    ASSERT_EQUAL(la->size(),6);
    List<int>::Iterator a = la->begin();
    ++a;
    ++a;
    --a;
    la->erase(a);
    List<int>::Iterator b = la->begin();
    List<int>::Iterator c = la->end();
    ASSERT_EQUAL(*b, 6);
    ASSERT_TRUE(b!=c);
    la->insert(b,30);
    ASSERT_EQUAL(la->front(),30);
    ++b;
    ++b;
    ++b;
    ++b;
    ++b;
    ASSERT_TRUE(b==c);
    la->pop_front();
    ASSERT_EQUAL(la->front(), 6);
    ASSERT_EQUAL(la->size(), 5);
    delete la;
}

TEST(test_insert_erase) {
    List<int> *la = new List<int>;
    la->push_back(1);
    la->push_back(2);
    la->push_back(3);
    la->push_back(4);
    la->push_back(5);
    la->push_back(6);
    la->push_back(7);
    la->push_back(8);
    List<int>::Iterator b = la->end();
    int i = la->size();
    for (List<int>::Iterator a = la->begin(); a != b; ++a) {
        i = i - 1;
    }
    la->clear();
    ASSERT_EQUAL(i, la->size());
    ASSERT_EQUAL(la->size(), 0);
    la->insert(la->begin(),10);
    ASSERT_EQUAL(la->size(), 1);
    la->insert(la->begin(),6);
    ASSERT_EQUAL(la->size(), 2);
    la->insert(la->begin(),2);
    ASSERT_EQUAL(la->size(), 3);
    ASSERT_EQUAL(la->front(), 2);
    ASSERT_EQUAL(la->back(), 10);
    delete la;
}

TEST(test_insert_erase_1) {
    List<int> *la = new List<int>;
    la->push_back(1);
    la->push_back(2);
    la->push_back(3);
    la->push_back(4);
    la->push_back(5);
    la->push_back(6);
    la->push_back(7);
    la->push_back(8);
    ASSERT_EQUAL(la->size(), 8);
    ASSERT_EQUAL(la->front(), 1);
    ASSERT_EQUAL(la->back(), 8);
    List<int>::Iterator a = la->begin();
    ASSERT_EQUAL(*a, 1);
    la->erase(a);
    ASSERT_EQUAL(la->size(), 7);
    ASSERT_EQUAL(la->front(), 2);
    ASSERT_EQUAL(la->back(), 8);
    List<int>::Iterator b = la->begin();
    ASSERT_EQUAL(*b, 2);
    la->insert(b,30);
    ASSERT_EQUAL(la->size(), 8);
    ASSERT_EQUAL(la->front(), 30);
    ASSERT_EQUAL(la->back(), 8);
    List<int>::Iterator c = la->begin();
    ++c;
    ++c;
    ASSERT_EQUAL(*c, 3);
    --c;
    ASSERT_EQUAL(*c, 2);
    List<int>::Iterator d = la->begin();
    ASSERT_TRUE(c!=d);
    ++d;
    ASSERT_TRUE(c==d);
    delete la;
}
TEST_MAIN()
