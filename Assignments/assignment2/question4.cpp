#include <cstdlib>
#include <iostream>
using namespace std;

template <typename E>  // forward declaration of SLinkedList
class SLinkedList;

template <typename E>
class SNode {  // singly linked list node
 private:
  E elem;                       // linked list element value
  SNode<E>* next;               // next item in the list
  friend class SLinkedList<E>;  // provide SLinkedList access
};

template <typename E>
class SLinkedList {  // a singly linked list
 public:
  SLinkedList();              // empty list constructor
  ~SLinkedList();             // destructor
  bool empty() const;         // is list empty?
  const E& front() const;     // return front element
  void addFront(const E& e);  // add to front of list
  void removeFront();         //  remove front of list
  SNode<E>* getHead();        // gets the head of the list 
  int countNodes();           //  counts the number of nodes 
  void printList() const;     // prints the node elements in order
  void appendList(SLinkedList<E>& other); // appends another singly linked list
  void reverseList(SNode<E>* curr, SNode<E>* prev); // reverses the list 
 private:
  SNode<E>* head;  // head of the list
};

template <typename E>
SLinkedList<E>::SLinkedList()  // constructor
    : head(NULL) {}

template <typename E>
bool SLinkedList<E>::empty() const {  // is list empty?
  return head == NULL;
}

template <typename E>
const E& SLinkedList<E>::front() const {  // return front element
  return head->elem;
}

template <typename E>
SLinkedList<E>::~SLinkedList() {  // destructor
  while (!empty()) removeFront();
}

template <typename E>
void SLinkedList<E>::addFront(const E& e) {  // add to front of list
  SNode<E>* v = new SNode<E>;                // create new node
  v->elem = e;                               // store data
  v->next = head;                            // head now follows v
  head = v;                                  // v is now the head
}

template <typename E>
void SLinkedList<E>::removeFront() {  // remove front item
  if (head == NULL) return;
  SNode<E>* old = head;  // save current head
  head = old->next;      // skip over old head
  delete old;            // delete the old head
}

template <typename E>
SNode<E>* SLinkedList<E>::getHead() {
    return head; // returns head of the list
}

template <typename E>
int SLinkedList<E>::countNodes() {           
    static SNode<E>* curr = head;
    if (curr == NULL) {
        curr = head;
    }
    if (curr == NULL) { // if curr is equal to 0, its the end of the list or the list is empty
        return 0;
    }
    if (curr->next == NULL) { 
        curr = NULL; // if end of node is reached, cur is set to NULL            
        return 1;
    } else { // if end of node is not reached, keep traversing
        curr = curr->next;
        return countNodes() + 1; 
    }
}

template <typename E>
void SLinkedList<E>::printList() const { 
    SNode<E>* curr = head;
    while (curr->next != NULL) { // it gets each number until it reaches null
        cout << curr->elem << "->";
        curr = curr->next;
    }
    cout << curr->elem << endl; //  prints the list 
}

template <typename E>
void SLinkedList<E>::appendList(SLinkedList<E>& list) {
    SNode<E>* curr = head;
    if (curr == NULL) { 
        head = list.head; // sets head to the second list's head if it reaches null
        return;
    }
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = list.head;
    list.head = NULL;  // prevents the appended list from being destroyed
}

template <typename E>
void SLinkedList<E>::reverseList(SNode<E>* curr, SNode<E>* prev) {
    if (curr == NULL) {
        return;
    } else {
        SNode<E>* t = curr->next;
        curr->next = prev; // reverse current node's next
        prev = curr; // advance prev node
        curr = t; // advance current node
        head = prev; // update head to the new start of the list
        reverseList(curr, prev);
    }
}

int main() {
    SLinkedList<std::string> list1;
    list1.addFront("four");
    list1.addFront("three");
    list1.addFront("two");
    list1.addFront("one");

    std::cout << "List 1 has " << list1.countNodes() << " nodes:" << std::endl;
    list1.printList(); 

    SLinkedList<std::string> list2;
    list2.addFront("seven");
    list2.addFront("six");
    list2.addFront("five");

    std::cout << "List 2 has " << list2.countNodes() << " nodes:" << std::endl;
    list2.printList(); 

    list1.appendList(list2);

    std::cout << "After appending list 2 to list 1, list 1 has " << list1.countNodes() << " nodes:" << std::endl;
    list1.printList();

    list1.reverseList(list1.getHead(), NULL);

    std::cout << "After reversing list 1, it looks like this:" << std::endl;
    list1.printList(); 
}
