// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <sstream>
using namespace std;
TEST(bst_public_test) {
  BinarySearchTree<int> tree;

  tree.insert(5);

  ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);

  ASSERT_TRUE(tree.find(5) != tree.end());

  tree.insert(7);
  tree.insert(3);

  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*tree.max_element() == 7);
  ASSERT_TRUE(*tree.min_element() == 3);
  ASSERT_TRUE(*tree.min_greater_than(5) == 7);

  cout << "cout << tree.to_string()" << endl;
  cout << tree.to_string() << endl << endl;

  cout << "cout << tree" << endl << "(uses iterators)" << endl;
  cout << tree << endl << endl;

  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "5 3 7 ");

  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "3 5 7 ");
}

TEST(bst_test_1) {
  BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.empty());
  tree.insert(5);
  tree.insert(12);
  tree.insert(1);
  tree.insert(2);
  tree.insert(8);
  tree.insert(10);
  ASSERT_TRUE(tree.size() == 6);
  ASSERT_TRUE(tree.height() == 4);

  ASSERT_TRUE(tree.find(5) != tree.end());
  ASSERT_TRUE(tree.find(1) != tree.end());
  ASSERT_TRUE(tree.find(2) != tree.end());
  ASSERT_TRUE(tree.find(12) != tree.end());
  ASSERT_TRUE(tree.find(8) != tree.end());
  ASSERT_TRUE(tree.find(10) != tree.end());
  tree.insert(7);
  tree.insert(3);

  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*tree.max_element() == 12);
  ASSERT_TRUE(*tree.min_element() == 1);
  ASSERT_TRUE(*tree.min_greater_than(5) == 7);
  ASSERT_TRUE(*tree.min_greater_than(7) == 8);
  ASSERT_TRUE(*tree.min_greater_than(1) == 2);
  ASSERT_TRUE(*tree.min_greater_than(0) == 1);
  cout << "cout << tree.to_string()" << endl;
  cout << tree.to_string() << endl << endl;

  cout << "cout << tree" << endl << "(uses iterators)" << endl;
  cout << tree << endl << endl;

  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_EQUAL(oss_preorder.str(),"5 1 2 3 7 8 10 12 ");

  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "1 2 3 5 7 8 10 12 ");

  
  BinarySearchTree<int> new_treee = tree;
  ASSERT_TRUE(new_treee.size() == 8);
  ASSERT_TRUE(new_treee.height() == 4);
  ASSERT_TRUE(*new_treee.max_element() == 12);
  ASSERT_TRUE(*new_treee.min_element() == 1);
  ASSERT_TRUE(*new_treee.min_greater_than(5) == 7);
 ASSERT_FALSE(new_treee.empty());
}

TEST(test_copy_tree) {

    BinarySearchTree <int> tree2;
    tree2.insert(1);	
    tree2.insert(2);	
    tree2.insert(3);	
    tree2.insert(4);
    tree2.insert(5);
    tree2.insert(6);
    tree2.insert(7);

    BinarySearchTree <int> tree_copy2(tree2);
    BinarySearchTree<int>::Iterator it2 = tree2.begin();
    BinarySearchTree<int>::Iterator it2_copy = tree_copy2.begin();
    for (int i = 2; i <= 8; ++i, ++it2, ++it2_copy) {
	    ASSERT_EQUAL(*it2, *it2_copy);	
	    ASSERT_NOT_EQUAL(&(*it2), &(*it2_copy));
	    ASSERT_NOT_EQUAL(it2, it2_copy);
    }
}

TEST(size_height) {
  BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.empty());
  tree.insert(5);
  ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);
  ASSERT_TRUE(tree.check_sorting_invariant());
  tree.insert(12);
  ASSERT_TRUE(tree.size() == 2);
  ASSERT_TRUE(tree.height() == 2);
  tree.insert(1);
  ASSERT_TRUE(tree.size() == 3);
  ASSERT_TRUE(tree.height() == 2);
  tree.insert(2);
  ASSERT_TRUE(tree.size() == 4);
  ASSERT_TRUE(tree.height() == 3);
  tree.insert(8);
  ASSERT_TRUE(tree.size() == 5);
  ASSERT_TRUE(tree.height() == 3);
  ASSERT_TRUE(tree.check_sorting_invariant());
  tree.insert(10);
  ASSERT_TRUE(tree.size() == 6);
  ASSERT_TRUE(tree.height() == 4);
  ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(find) {
  BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.empty());
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  tree.insert(4);
  tree.insert(5);
  tree.insert(6);
  tree.insert(7);
  BinarySearchTree<int>::Iterator iter = tree.begin();
  for (int i = 1; i < 10; i++) {
    if (i > 7) {
      ASSERT_EQUAL(tree.find(i), tree.end());
    } else {
      ASSERT_EQUAL(tree.find(i), iter);
      iter++;
    }
  }
}

TEST(max_min) {
  BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.empty());
  tree.insert(1);
  ASSERT_TRUE(*tree.max_element() == 1);
  ASSERT_EQUAL(tree.max_element(),tree.find(1));
  ASSERT_EQUAL(tree.min_element(),tree.find(1));
  ASSERT_TRUE(*tree.min_element() == 1);
  tree.insert(3);
  ASSERT_TRUE(*tree.max_element() == 3);
  ASSERT_TRUE(*tree.min_element() == 1);
  ASSERT_EQUAL(tree.max_element(),tree.find(3));
  ASSERT_EQUAL(tree.min_element(),tree.find(1));
  tree.insert(5);
  ASSERT_TRUE(*tree.max_element() == 5);
  ASSERT_TRUE(*tree.min_element() == 1);
  ASSERT_EQUAL(tree.max_element(),tree.find(5));
  ASSERT_EQUAL(tree.min_element(),tree.find(1));
  tree.insert(0);
  ASSERT_TRUE(*tree.max_element() == 5);
  ASSERT_TRUE(*tree.min_element() == 0);
  ASSERT_EQUAL(tree.max_element(),tree.find(5));
  ASSERT_EQUAL(tree.min_element(),tree.find(0));
  ASSERT_EQUAL(++(tree.min_element()),tree.find(1));
}

TEST(bad_sort) {
  BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.empty());
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  tree.insert(4);
  tree.insert(5);
  tree.insert(6);
  tree.insert(7);
  *tree.max_element()=0;
  ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(bad_sort_2) {
  BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.empty());
  tree.insert(4);
  tree.insert(1);
  tree.insert(2);
  tree.insert(7);
  tree.insert(9);
  tree.insert(5);
  tree.insert(6);
  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "1 2 4 5 6 7 9 ");
  *tree.max_element()=0;
  BinarySearchTree<int>::Iterator iter= tree.min_element();
  iter++;
  iter++;
  iter++;
  *iter=3;
  ASSERT_FALSE(tree.check_sorting_invariant());
  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_EQUAL(oss_preorder.str(),"4 1 2 3 6 7 0 ");
}

TEST_MAIN()
