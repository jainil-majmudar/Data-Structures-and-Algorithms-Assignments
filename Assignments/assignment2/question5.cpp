#include <cstdlib>
#include <iostream>

typedef std::string Elem;

class DNode {  // doubly linked list node
 private:
  Elem name;                 // node name value
  int score;
  DNode* prev;               // previous node in list
  DNode* next;               // next node in list
  friend class DLinkedList;  // allow DLinkedList access
};

class DLinkedList {  // doubly linked list
 public:
  DLinkedList();                 // constructor
  ~DLinkedList();                // destructor
  bool empty() const;            // is list empty?
  const Elem& front() const;     // get front element
  const Elem& back() const;      // get back element
  void addFront(const Elem& e);  // add to front of list
  void addBack(const Elem& e);   // add to back of list
  void removeFront();            // remove from front
  void removeBack();             // remove from back
  int Size(); // counts the nodes in the list
  void AddScoreInOrder(const Elem& name, const int& score); // adds a new game score entry to the front of list
  void RemoveScore(int index); //removes the node at an index
  bool UpdateScore(std::string name, int score); // updates score with the given name
  void Print(); // prints the list
  DLinkedList(const DLinkedList &copy); // copies the list
  void operator = (const DLinkedList &copy1); // overloads the assignment (=) operator
 private:                        // local type definitions
  DNode* header;                 // list sentinels
  DNode* trailer;

 protected:                           // local utilities
  void add(DNode* v, const Elem& e);  // insert new node before v
  void remove(DNode* v);              // remove node v
};

DLinkedList::DLinkedList() {  // constructor
  header = new DNode;         // create sentinels
  trailer = new DNode;
  header->next = trailer;  // have them point to each other
  trailer->prev = header;
  header->prev = NULL;
  trailer->next = NULL;
}

DLinkedList::~DLinkedList() {  // destructor
  while (!empty()) {
    removeFront();  //  remove all but sentinels
  }
  delete header;  //  remove the sentinels
  delete trailer;
}

bool DLinkedList::empty() const {  // is list empty?
  return (header->next == trailer);
}

const Elem& DLinkedList::front() const {  // get front element
  return header->next->name;
}

const Elem& DLinkedList::back() const {  // get back element
  return trailer->prev->name;
}

void DLinkedList::add(DNode* x, const Elem& value) {
  DNode* newNode = new DNode;
  newNode->name = value;
  newNode->next = x->next;
  newNode->prev = x;
  x->next->prev = newNode;
  x->next = newNode;
}

void DLinkedList::addFront(const Elem& e) {  // add to front of list
  add(header, e);
}

void DLinkedList::addBack(const Elem& e) {  // add to back of list
  add(trailer->prev, e);
}

void DLinkedList::remove(DNode* v) {  // remove node v
  DNode* u = v->prev;                 // predecessor
  DNode* w = v->next;                 // successor
  u->next = w;                        // unlink v from list
  w->prev = u;
  delete v;
}

void DLinkedList::removeFront() {  // remove from font
  remove(header->next);
}

void DLinkedList::removeBack() {  // remove from back
  remove(trailer->prev);
}

void listReverse(DLinkedList& L) {  // reverse a list
  DLinkedList T;                    // temporary list
  while (!L.empty()) {              // reverse L into T
    Elem s = L.front();
    L.removeFront();
    T.addFront(s);
  }
  while (!T.empty()) {  // copy T back to L
    Elem s = T.front();
    T.removeFront();
    L.addBack(s);
  }
}

int DLinkedList::Size() {
  static DNode* curr = header->next;
  if (curr == NULL) { 
    curr = header->next;
  }
  if (curr == NULL) { // if curr is equal to 0, its the end of the list or the list is empty
        return 0;
    }
  if (curr->next == trailer) {
    curr = NULL; // if end of node is reached, cur is set to NULL
    return 1;
  } else { // if end of node is not reached, keep traversing
    curr = curr->next;
    return Size() + 1;
  }
}

void DLinkedList::AddScoreInOrder(const Elem& name, const int& score) {
  DNode* newNode = new DNode;
  newNode->name = name;
  newNode->score = score;
  DNode* currFront = header->next;
  DNode* currBack = trailer->prev;

  while (currFront != trailer && currBack != header) { // compares the score from head and tail
    if (score >= currFront->score) { // if the score is greater than then front node, then it inserts node before it
      newNode->next = currFront;
      newNode->prev = currFront->prev;
      currFront->prev->next = newNode;
      currFront->prev = newNode;
      return;
    } else if (score <= currBack->score) { // if the score is lower than the last node, then it inserts node after it
      newNode->next = currBack->next;
      newNode->prev = currBack;
      currBack->next->prev = newNode;
      currBack->next = newNode;
      return;
    }
    currFront = currFront->next;
    currBack = currBack->prev;
  }
  header->next = newNode; // this is for the first node
  newNode->next = trailer;
  trailer->prev = newNode;
  newNode->prev = header;
}

void DLinkedList::RemoveScore(int index) {
  int size = Size();
  int currIndex;
  DNode* curr;
  
  if (index >= size/2) { // if the index is located in second half of the list, traverse and search through that half
    curr = trailer->prev;         
    currIndex = size - 1;
      while (currIndex != index) { // traverse the list until curr matches the node we want to delete
        curr = curr->prev;
        currIndex--;
      }
      (curr->prev)->next = curr->next;
      (curr->next)->prev = curr->prev;
  } else { // if the index is located in first half of list, traverse and search through that half
    curr = header->next; // set curr to first node
    currIndex = 0;
    while (currIndex != index) { // traverse the list until curr matches the node we want to delete
      curr = curr->next;
      currIndex++;
    }
    (curr->prev)->next = curr->next;
    (curr->next)->prev = curr->prev;
  }
  delete curr; // delete old node
}

bool DLinkedList::UpdateScore(std::string name, int score) {
  DNode* currFront = header->next;
  DNode* currBack = trailer->prev;  
  
  while (currFront != trailer || currBack != header) { // traverse through the front and back of the list until the correct node is found, then changes value
    if (currFront->name == name) {
      currFront->score = score;
      return true;
    } else if (currBack->name == name) {
      currBack->score = score;
      return true;
    }
    currFront = currFront->next;
    currBack = currBack->prev;
  }
  return false;
}

void DLinkedList::Print() {
  static DNode* curr = header; 
  if (curr == NULL) { 
    curr = header;
  }
  curr = curr->next;

  if (curr->next == trailer) { // if end of list is reached, it prints  the last node and exits
    std::cout << "{" << curr->name << "," << curr->score << "}" << std::endl;
    curr = NULL;  
  } else { // if end is not reached, then prints node, and keeps traversing by calling itself 
    std::cout << "{" << curr->name << "," << curr->score << "}->"; 
    Print();
  }
}

DLinkedList::DLinkedList(const DLinkedList &copy) {
  header = new DNode;
  trailer = new DNode;
  header->prev = NULL;
  trailer->next = NULL;
  DNode* currPass = copy.header->next;
  DNode* currNew = header;

  while (currPass->next != NULL) { // traverses and copies until it hits the end of the list
    currNew->next = new DNode; // allocates new memory, and sets pointers to the new node 
    currNew->next->prev = currNew; 
    currNew = currNew->next;
    currNew->name = currPass->name; // copies the values
    currNew->score = currPass->score;
    currPass = currPass->next; // goes to the next node and repeats
  }
  currNew->next = trailer;
  trailer->prev = currNew;
}

void DLinkedList::operator = (const DLinkedList &copy1) {
  DLinkedList copy(copy1); // calls the copy constructor
}

int main() {
  DLinkedList scores;
  scores.AddScoreInOrder("Jeff", 7);
  scores.AddScoreInOrder("Jen", 9);
  scores.AddScoreInOrder("Ilya", 3);
  scores.AddScoreInOrder("Sara", 10);
  scores.AddScoreInOrder("Sam", 11);
  // Test size function
  std::cout << "Number of scores is " << scores.Size() << std::endl;
  scores.Print();
  // Test remove function
  scores.RemoveScore(3);
  std::cout << "Number of scores is now " << scores.Size() << std::endl;
  scores.Print();
  // Test update function
  if (scores.UpdateScore("Jeff",6))
  scores.Print();
  // Test copy construcor
  DLinkedList scores_copy_1(scores);
  scores.UpdateScore("Jen",5);
  scores.Print();
  scores_copy_1.Print();
  // Test assignment operator overload
  DLinkedList scores_copy_2 = scores_copy_1;
  scores_copy_1.UpdateScore("Jen",5);
  scores_copy_1.Print();
  scores_copy_2.Print();
}
