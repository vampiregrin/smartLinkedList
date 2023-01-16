#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>

template <typename T> class Node {
public:
  Node<T>(const T &value) : value(value) {
    std::cout << "Konstruktor Node'a\n";
  }
  ~Node<T>() { std::cout << "Destruktor Node'a\n"; }
  T value;
  std::shared_ptr<Node> next;
  std::shared_ptr<Node> prev;
};

template <typename T> class List {
private:
  std::shared_ptr<Node<T>> head;
  std::shared_ptr<Node<T>> tail;

public:
  List();
  ~List();
  std::shared_ptr<Node<T>> getHead();
  std::shared_ptr<Node<T>> getTail();
  T &getNthValue(int index);
  void addAtEnd(T newVal);
  void addAfterTail(T newVal);
  void addAtBeginning(T newVal);
  int listSize();
  bool insertAtGivenPosition(int x, T newVal);
  void printList();
  void printListBackwards();
  bool deleteNode(int x);
};

class Example {
public:
  Example(int x) : x(x) {
    std::cout << "Konstruktor" << x << "             this:   " << this
              << std::endl;
  }
  Example(const Example &e) {
    x = e.x;
    std::cout << "Konstruktor kopiujacy     this:   " << this << std::endl;
  }
  ~Example() {
    std::cout << "Destruktor" << x << "              this:   " << this
              << std::endl;
  }
  int x;
  void print() {
    std::cout << "printing  pointer: " << x << "   " << this << std::endl;
  }
};

template <typename T> List<T>::List() {
  head = NULL;
  tail = NULL;
}

template <typename T> List<T>::~List() {
  if (head->next != NULL) {
    head->next->prev = NULL;
    head = NULL;
  }

  // if (listSize() == 0) {
  //   std::cout << "List is empty" << std::endl;
  // } else {
  //   tail = getTail();
  //   std::shared_ptr<Node<T>> current = head;
  //   int count = 0;
  //   while (current->next != NULL) {
  //     count++;
  //     current = current->next;
  //     // delete current->prev;
  //     current->prev = NULL;
  //   }
  //   // delete tail;
  // }
}

template <typename T> std::shared_ptr<Node<T>> List<T>::getTail() {
  if (head == NULL) {
    return NULL;
  } else {
    std::shared_ptr<Node<T>> current = head;
    if (current->next == NULL) {
      tail = current;
    } else {
      while (current->next != NULL) {
        current = current->next;
        tail = current;
      }
    }
    return tail;
  }
}

template <typename T> std::shared_ptr<Node<T>> List<T>::getHead() {
  return head;
}

template <typename T> void List<T>::addAtEnd(T newVal) {

  // Node<T> *newNode = new Node<T>(newVal);
  std::shared_ptr<Node<T>> newNode(new Node<T>(newVal));

  // newNode->value = newVal;
  newNode->next = NULL;

  if (head == NULL) {
    newNode->prev = NULL;
    head = newNode;
  } else {
    tail = getTail();
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  }
}
template <typename T> void List<T>::addAtBeginning(T newVal) {

  // Node<T> *newNode = new Node<T>(newVal);
  std::shared_ptr<Node<T>> newNode(new Node<T>(newVal));

  newNode->value = newVal;
  std::shared_ptr<Node<T>> current = head;
  head = newNode;
  head->next = current;
}
template <typename T> void List<T>::addAfterTail(T newVal) {

  // Node<T> *newNode = new Node<T>(newVal);
  std::shared_ptr<Node<T>> newNode(new Node<T>(newVal));

  // newNode->value = newVal;
  newNode->next = NULL;

  if (head == NULL) {
    newNode->prev = NULL;
    head = newNode;
  } else {
    tail = getTail();
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  }
}
template <typename T> T &List<T>::getNthValue(int index) {

  std::shared_ptr<Node<T>> current = head;

  int count = 0;
  while (current != NULL) {
    if (count == index)
      return (current->value);
    count++;
    current = current->next;
  }
  return current->value;
}
template <typename T> int List<T>::listSize() {
  std::shared_ptr<Node<T>> current = head;

  int count = 0;
  while (current != NULL) {
    count++;
    current = current->next;
  }
  return count;
}
template <typename T> bool List<T>::insertAtGivenPosition(int x, T newVal) {

  int size = listSize();

  // Node<T> *newNode = new Node<T>(newVal);
  std::shared_ptr<Node<T>> newNode(new Node<T>(newVal));

  newNode->value = newVal;
  std::shared_ptr<Node<T>> current = head;
  std::shared_ptr<Node<T>> prevNode;

  if (x == 0) {
    head = newNode;
    head->next = current;
    return true;
  } else if (x == size + 1) {
    addAtEnd(newVal);
    return true;
  } else if (x > size + 1) {
    return false;
  } else {
    int count = 0;
    while (current != NULL) {

      if (count == x) {
        prevNode = current->prev;
        break;
      }
      count++;
      current = current->next;
    }
    prevNode->next = newNode;
    newNode->next = current;
    return true;
  }
}
template <typename T> void List<T>::printList() {
  if (listSize() == 0) {
    std::cout << "List is empty" << std::endl;
  } else {
    Node<T> *current = head;
    int count = 0;
    while (current != NULL) {
      std::cout << count << ".";
      std::cout << current->value << std::endl;
      count++;
      current = current->next;
    }
  }
}

template <typename T> void List<T>::printListBackwards() {
  if (listSize() == 0) {
    std::cout << "List is empty" << std::endl;
  } else {
    tail = getTail();
    Node<T> *current = tail;
    int count = listSize() - 1;
    while (current != head) {
      std::cout << count << ".";
      std::cout << current->value << std::endl;
      count--;
      current = current->prev;
    }
    std::cout << "0." << head->value << std::endl;
  }
}

template <typename T> bool List<T>::deleteNode(int x) {

  int size = listSize();
  std::shared_ptr<Node<T>> current = head;
  std::shared_ptr<Node<T>> prevNode;
  std::shared_ptr<Node<T>> nextNode;

  if (x == 0 && size == 1) {
    head = NULL;
    return true;
  } else if (x == 0) {
    head->next = head;
    std::cout << head->value << std::endl;
    return true;
  } else if (x > size + 1) {
    return false;
  } else if (size == 0) {
    return false;
  } else if (x == size) {
    tail->prev = tail;
    tail->next = NULL;
    return true;
  } else {
    int count = 0;
    while (current != NULL) {
      if (count == x) {
        prevNode = current->prev;
        nextNode = current->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        break;
      }
      count++;
      current = current->next;
    }

    // delete current;
    return true;
  }
}

List<std::string> createSampleListOfStrings() {
  List<std::string> l = List<std::string>();
  l.addAtEnd("first");
  l.addAtEnd("second");
  l.addAtEnd("third");
  l.addAtEnd("fourth");
  return l;
}

List<int> createSampleListOfInts() {
  List<int> l = List<int>();
  l.addAtEnd(1);
  l.addAtEnd(2);
  l.addAtEnd(3);
  l.addAtEnd(4);
  return l;
}

void createSampleListOfExamples() {
  List<Example> l = List<Example>();

  // std::cout << l.getHead() << std::endl;
  // std::cout << l.getTail() << std::endl;

  // Example e = Example(50);
  // std::cout << e.x << std::endl;

  for (int i = 0; i < 3; i++) {
    Example e = Example(i);
    // Example f = e;
    // std::cout << e.x << std::endl;
    l.addAtEnd(e);
  }
  // // return l;
}

void test_addAtEndOfEmptyString() {
  List<std::string> l = List<std::string>();

  l.addAtEnd("Hello");
  assert(l.getHead()->value == "Hello");
  assert(l.getTail()->value == "Hello");
}

void test_addAtEndOfEmptyInt() {
  List<int> l = List<int>();
  l.addAtEnd(100);
  assert(l.getHead()->value == 100);
  assert(l.getTail()->value == 100);
}

void test_addAtEndOfNotEmptyInt() {
  List<std::string> l = createSampleListOfStrings();
  l.addAtEnd("fifth");
  assert(l.getHead()->value == "first");
  assert(l.getTail()->value == "fifth");
  bool deleteNode(int x);
};

void test_emptyListInt() {
  List<int> l = List<int>();
  assert(l.getHead() == NULL);
  assert(l.getTail() == NULL);
}
void test_getTailOfNonEmpty() {
  List<std::string> l = createSampleListOfStrings();
  assert(l.getTail()->value == "fourth");
}

void test_getNthValue() {
  List<std::string> l = createSampleListOfStrings();
  assert(l.getNthValue(0) == "first");
  assert(l.getNthValue(2) == "third");
}

void test_insertAtGivenPosition() {
  List<int> l = createSampleListOfInts();
  l.insertAtGivenPosition(0, 0);
  assert(l.getNthValue(0) == 0);
  assert(l.getNthValue(1) == 1);
  l.insertAtGivenPosition(l.listSize() + 1, 5);
  assert(l.getNthValue(5) == 5);
  assert(l.insertAtGivenPosition(10, 10) == false);
}

void test_listSize() {
  List<int> l = createSampleListOfInts();
  assert(l.listSize() == 4);
}
void test_addAfterTail() {
  List<std::string> l = createSampleListOfStrings();
  l.addAfterTail("last");
  assert(l.getTail()->value == "last");
}
void test_addAtBeginning() {
  List<std::string> l = createSampleListOfStrings();
  l.addAtBeginning("zero");
  assert(l.getHead()->value == "zero");
}

void test_deleteNodeString() {
  List<std::string> l = createSampleListOfStrings();
  l.deleteNode(2);
  assert(l.getNthValue(2) == "fourth");
  assert(l.listSize() == 3);
  assert(l.deleteNode(5) == false);
}

void test_getHead() {
  List<int> l = List<int>();
  assert(l.getHead() == NULL);
}

// void test_shared() {
//   std::shared_ptr<Node<Example>> p1(new Node<Example>(1));
//   std::shared_ptr<Node<Example>> p2(new Node<Example>(2));
//   std::shared_ptr<Node<Example>> p3(new Node<Example>(3));

//   std::cout << "p1 use count: " << p1.use_count() << std::endl;
//   std::cout << "p2 use count: " << p2.use_count() << std::endl;
//   std::cout << "p3 use count: " << p3.use_count() << std::endl;

//   std::cout << __LINE__ << std::endl;
//   p1->next = std::shared_ptr<Node<Example>>(p2);
//   p2->prev = std::shared_ptr<Node<Example>>(p1);
//   p3->prev = std::shared_ptr<Node<Example>>(p2);
//   p2->next = std::shared_ptr<Node<Example>>(p3);

//   std::cout << __LINE__ << std::endl;
//   std::cout << "p1 use count: " << p1.use_count() << std::endl;
//   std::cout << "p2 use count: " << p2.use_count() << std::endl;
//   std::cout << "p3 use count: " << p3.use_count() << std::endl;

//   p1->next = p3;
//   std::cout << "p1 use count: " << p1.use_count() << std::endl;
//   std::cout << "p2 use count: " << p2.use_count() << std::endl;
//   std::cout << "p3 use count: " << p3.use_count() << std::endl;

//   p3->prev = p1;
//   std::cout << "p1 use count: " << p1.use_count() << std::endl;
//   std::cout << "p2 use count: " << p2.use_count() << std::endl;
//   std::cout << "p3 use count: " << p3.use_count() << std::endl;

// }

void test_shared2() { new Node<Example>(2); }
int main() {

  test_getTailOfNonEmpty();
  test_getNthValue();
  test_insertAtGivenPosition();
  test_addAfterTail();
  test_addAtBeginning();
  test_listSize();
  test_addAtEndOfEmptyInt();
  test_getTailOfNonEmpty();
  test_emptyListInt();
  test_addAtEndOfNotEmptyInt();
  createSampleListOfExamples();
  //     while (true) {
  test_deleteNodeString();
  //    }
  // test_shared();
  return 0;
}
