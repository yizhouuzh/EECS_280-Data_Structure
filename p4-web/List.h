#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    return (first == nullptr);
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const {
    return len;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front() {
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back() {
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) {
    if (empty()) {
      Node *p = new Node;
      p->datum = datum;
      first = p;
      last = p;
      first->next = nullptr;
      first->prev = nullptr;
      len++;
    } else {
      Node *p = new Node;
      p->datum = datum;
      p->next = first;
      first->prev = p;
      p->prev = nullptr;
      first = p;
      len++;
    }
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
    if (empty()) {
      Node* p = new Node;
      p->datum = datum;
      first = p;
      last = p;
      first->next = nullptr;
      first->prev = nullptr;
      len++;
    } else {
      Node *p = new Node;
      p->datum = datum;
      p->prev = last;
      p->next = nullptr;
      len++;
      last = p;
      last->prev->next = p;
    }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {
    assert(!empty());
    Node *victim = first;
    if (size()==1) {
      first = nullptr;
      last = nullptr;
    } else {
      first = first->next;
      first->prev = nullptr;
    }
    len = len - 1;
    delete victim;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
    assert(!empty());
    Node *victim = last;
    if (size()==1) {
      first = nullptr;
      last = nullptr;
    } else {
      last = last->prev;
      last->next = nullptr;
    }
    len = len - 1;
    delete victim;
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear() {
    while (!empty()) {
      pop_front();
    }
  }
  ~List() {
    clear();
  }

  List() 
    : len(0), first(nullptr), last(nullptr) {
  }
  List(const List<T> &other)
    : len(0), first(nullptr), last(nullptr) {
      copy_all(other);
  }

  List & operator=(const List<T> &rhs) {
    if (this == &rhs) {
      return *this;
    }
    clear();
    copy_all(rhs);
    return *this;
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) {
    assert(empty());
    for (Node *np = other.first;np;np = np->next) {
      push_back(np->datum);
    }
    len = other.len;
  }
  int len = 0;
  Node *first = nullptr;   // points to first Node in list, or nullptr if list is empty
  Node *last = nullptr;    // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List
    
    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    T& operator *() const {
      return node_ptr->datum;
    }

    Iterator& operator++() {
      node_ptr = node_ptr->next;
      return *this;
    }

    bool operator==(const Iterator other) const {
      return (node_ptr == other.node_ptr);
    }

    bool operator!=(const Iterator other) const {
      return (node_ptr != other.node_ptr);
    }
    Iterator() : node_ptr(nullptr) {}
  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here
    friend class List;
    // add any friend declarations here
    // construct an Iterator at a specific position
    Iterator(Node *p) : node_ptr(p) {}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {
    if (i == begin()) {
      pop_front();
    } else if (i == end()) {
      pop_back();
    } else {
      i.node_ptr->next->prev = i.node_ptr->prev;
      i.node_ptr->prev->next = i.node_ptr->next;
      len--;
      delete i.node_ptr;
    }
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum) {
    if (i == begin()) {
      push_front(datum);
    } else if (i == end()) {
      push_back(datum);
    } else {
      Node* p = new Node;
      p->datum = datum;
      p->next = i.node_ptr->next;
      p->prev = i.node_ptr;
      p->next->prev = p;
      p->prev->next = p;
      len++;
    }
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
