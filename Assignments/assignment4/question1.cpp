#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <cmath>
using namespace std;

typedef string Elem; // base element type 
class LinkedBinaryTree {
    protected:
        struct Node { // a node of the tree
            Elem elt; // element value
            Node* par; // parent
            Node* left; // left child
            Node* right; // right child
            Node() : elt(), par(NULL), left(NULL), right(NULL) { } // constructor
        };
    
    public:
        class Position { // position in the tree
            private:
                Node* v; // pointer to the node

            public:
                Position(Node* v = NULL) : v( v) { } // constructor
                Elem& operator*() // get element
                { return v->elt; }
                Position left() const // get left child
                { return Position(v->left); }
                Position right() const // get right child
                { return Position(v->right); }
                Position parent() const // get parent
                { return Position(v->par); }
                bool isRoot() const // root of the tree?
                { return v->par == NULL; }
                bool isExternal() const // an external node?
                { return v->left == NULL && v->right == NULL; }
                friend class LinkedBinaryTree; // give tree access
            };
            typedef std::list<Position> PositionList; // list of positions
    
    public:
        LinkedBinaryTree(); // constructor
        ~LinkedBinaryTree(); // destructor 
        void destructorHelper(Node* node); // helper function for the destructor 
        int size() const; // number of nodes
        bool empty() const; // is tree empty?
        Position root() const; // get the root
        PositionList positions() const; // list of nodes
        void addRoot(); // add root to empty tree
        void expandExternal(const Position& p); // expand external node
        Position removeAboveExternal(const Position& p); // remove p and parent
        // housekeeping functions omitted. . .
        friend LinkedBinaryTree createExpressionTree(string postfix); // helper function which builds and returns a binary expression tree
        void printExpression(); // recursively prints an expression tree
        void printExpressionHelper(Node* curr); // helper function for the printExpression function 
        double evaluateExpression(double a, double b); // recursively evaluates an expression for given values of a and b
        double evaluateExpressionHelper(double a, double b, Node* curr); // helper function for the evaluateExpression function 
        double getScore(); // returns the score 
        void setScore(double s); // sets the tree's score 
        bool operator<(const LinkedBinaryTree& b); // used to compare tree scores 

    protected: // local utilities
        void preorder(Node* v, PositionList& pl) const; // preorder utility

    private:
        Node* _root; // pointer to the root
        int n; // number of nodes 
        double score; // average score
};

LinkedBinaryTree::LinkedBinaryTree() // constructor
    : _root(NULL), n(0) { }
int LinkedBinaryTree::size() const // number of nodes
    { return n; }
bool LinkedBinaryTree::empty() const // is tree empty?
    { return size() == 0; }
LinkedBinaryTree::Position LinkedBinaryTree::root() const // get the root
    { return Position(_root); }
void LinkedBinaryTree::addRoot() // add root to empty tree
    { _root = new Node; n = 1; }

LinkedBinaryTree::~LinkedBinaryTree() { // destructor
    destructorHelper(_root);
}

void LinkedBinaryTree::destructorHelper(LinkedBinaryTree::Node* node) { // recursively traverses through the tree and deletes from end to the start
    if (node == NULL) { // if node is null, returns to parent node
        return;
    }
    destructorHelper(node->left); // checks if left node exists
    destructorHelper(node->right); // checks if right node exists
    node = NULL; // after traversal is done, sets node to null and deletes it 
    delete node;
}

void LinkedBinaryTree::expandExternal(const Position& p) { // expand external node
    Node* v = p.v; // p’s node
    v->left = new Node; // add a new left child
    v->left->par = v; // v is its parent
    v->right = new Node; // and a new right child
    v->right->par = v; // v is its parent
    n += 2; // two more nodes
}

LinkedBinaryTree::Position // remove p and parent
LinkedBinaryTree::removeAboveExternal(const Position& p) {
    Node* w = p.v; Node* v = w->par; // get p’s node and parent
    Node* sib = (w == v->left ? v->right : v->left);
    if (v == _root) { // child of root?
        _root = sib; // . . .make sibling root
        sib->par = NULL;
    } 
    else {
        Node* gpar = v->par; // w’s grandparent
        if (v == gpar->left) gpar->left = sib; // replace parent by sib
        else gpar->right = sib;
        sib->par = gpar;
    }
    delete w; delete v; // delete removed nodes
    n -= 2; // two fewer nodes
    return Position(sib);
}

LinkedBinaryTree::PositionList LinkedBinaryTree::positions() const { // list of all nodes
    PositionList pl;
    preorder(_root, pl); // preorder traversal
    return PositionList(pl); // return resulting list
}
// preorder traversal
void LinkedBinaryTree::preorder(Node* v, PositionList& pl) const {
    pl.push_back(Position(v)); // add this node
    if (v->left != NULL) // traverse left subtree
        preorder(v->left, pl);
    if (v->right != NULL) // traverse right subtree
        preorder(v->right, pl);
}

LinkedBinaryTree createExpressionTree(string postfix) {
    stack<LinkedBinaryTree::Node*> stack;
    stringstream ss(postfix);
    string token;
    LinkedBinaryTree *temp;
    int count = 0;

    while (getline(ss, token, ' ')) { // tokenizes the string for every space 
        temp = new LinkedBinaryTree(); // creates a new tree and initializes it to root
        temp->addRoot();
        temp->_root->elt = token;
        temp->_root->left = NULL;
        temp->_root->right = NULL;
        count++;

        if ((isdigit(token[0]) || isdigit(token[1])) || (isalpha(token[0]) && token != "abs")) { } // if token is a number or a/b, does nothing and pushes it to stack 
        else if (token == "abs") { // if token is abs, it makes the right node hold the other node in the stack
            temp->_root->right = stack.top();
            temp->_root->right->par = temp->_root;
            stack.pop();
        } else { // if it is an operator, it will take the latest two stack elements and make them the children of the root
            temp->_root->right = stack.top();
            temp->_root->right->par = temp->_root;
            stack.pop();
            temp->_root->left = stack.top();
            temp->_root->left->par = temp->_root;
            stack.pop();
        } 
        stack.push(temp->_root); // pushes root of the tree to the stack 
    }
    LinkedBinaryTree answer;
    answer._root = stack.top(); // creates a new tree, sets the stack element to the root of the tree, returns the tree
    answer.n = count;
    return answer;
}

void LinkedBinaryTree::printExpression() {
    printExpressionHelper(_root);
}

void LinkedBinaryTree::printExpressionHelper(Node* curr) {
    if (curr->elt == "abs") { // if element is absolute, write everything by abs(), and then traverse right node
        cout << "abs(";
        printExpressionHelper(curr->right); // recursively calls to the next node
        cout << ")";
    } else if(curr->left == NULL && curr->right == NULL) { // if node is external, print the value of the node
        cout << curr->elt;
    } else { // if element is operator, then prints bracket, left element, operator, right element, and bracket 
        cout << "(";
        printExpressionHelper(curr->left); // recursively calls the left element
        cout << " " << curr->elt << " ";
        printExpressionHelper(curr->right); // recursively calls the right element
        cout << ")";
    }
}

double LinkedBinaryTree::evaluateExpression(double a, double b) {
    return evaluateExpressionHelper(a,b, _root);
}

double LinkedBinaryTree::evaluateExpressionHelper(double a, double b, Node* curr) {
    if (curr->elt == "+") { // if element is a specific operator, return the value of left and right elements using that operator 
        return evaluateExpressionHelper(a,b,curr->left) + evaluateExpressionHelper(a,b,curr->right); 
    } else if (curr->elt == "-") {
        return evaluateExpressionHelper(a,b,curr->left) - evaluateExpressionHelper(a,b,curr->right);
    } else if (curr->elt == "*") {
        return evaluateExpressionHelper(a,b,curr->left) * evaluateExpressionHelper(a,b,curr->right);
    } else if (curr->elt == "/") {
        float denominator = evaluateExpressionHelper(a,b,curr->right); 
        if (denominator == 0.0) return 0; // checks for division by 0 error
        else return evaluateExpressionHelper(a,b,curr->left) / denominator;
    } else if (curr->elt == "abs") { // applies absolute value on its argument 
        return fabs(evaluateExpressionHelper(a,b,curr->right));
    } else if (curr->elt == ">") { // returns 1 if left is greater than right
        if (evaluateExpressionHelper(a,b,curr->left) > evaluateExpressionHelper(a,b,curr->right)) return 1;
        else return -1;
    } else if (curr->elt == "a") { // if element is a, returns the value a
        return a;
    } else if (curr->elt == "b") { // if element is b, returns the value b
        return b;
    } else { // if element is a regular number, converts to double and returns it
        return stod(curr->elt);
    }
}

double LinkedBinaryTree::getScore() {
    return score; // gets the score
}

void LinkedBinaryTree::setScore(double s) {
    score = s; // sets the score 
}

bool LinkedBinaryTree::operator<(const LinkedBinaryTree& copy1) { // checks if first input score is lower than other input score
    if (this->score < copy1.score) {
        return true;
    } else {
        return false;
    }
}

int main() {
    // Read postfix expressions into vector
    vector<LinkedBinaryTree> trees;
    ifstream exp_file("expressions.txt");
    string line;
    while (getline(exp_file, line)) {
        trees.push_back(createExpressionTree(line));
    }
    // Read input data into 2D vector
    vector<vector<double>> inputs;
    ifstream input_file("input.txt");
    while (getline(input_file, line)) {
        vector<double> ab_input;
        stringstream ss(line);
        string str;
        while (getline(ss, str, ' ')) {
            ab_input.push_back(stod(str));
        }
        inputs.push_back(ab_input);
    }
    // Evaluate expressions on input data
    for (auto& t : trees) {
        double sum = 0;
        for (auto& i : inputs) {
            sum += t.evaluateExpression(i[0], i[1]);
        }
    t.setScore(sum/inputs.size());
    }
    // Sort trees by their score
    sort(trees.begin(), trees.end());
    for (auto& t : trees) {
        cout << "Exp ";
        t.printExpression();
        cout << " Score " << t.getScore() << endl;
    }
}
