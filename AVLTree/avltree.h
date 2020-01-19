#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include <stdexcept>
using namespace std;

template <typename Key, typename Info>
class AVLTree {
    public:
        struct KeyInfoPair {
            const Key key;
            Info info;
            KeyInfoPair(Key, Info);
        };
        class iterator;
        class const_iterator;



    private:
        struct Node {
            KeyInfoPair keyAndInfo;
            Node* left;
            Node* right;
            Node* parent;
            int height;

            Node(KeyInfoPair);
            ~Node();
            Node(const Node&);
            Node(Node&&);
            Node& operator=(const Node&);
            Node& operator=(Node&&);
        };

        Node* root;
        int numberOfNodes;
        iterator beginIt;
        iterator endIt;

        // struct for printing the structure
        struct Connection {
            string link;
            Connection* prev;
            Connection(Connection* p, string link){
                this->link = link;
                this->prev = p;
            }
        };

    public:
        AVLTree();
        ~AVLTree();
        AVLTree(const AVLTree&);
        AVLTree(AVLTree&&);
        void clear();
        AVLTree<Key, Info>& operator=(const AVLTree<Key, Info>&);
        AVLTree<Key, Info>& operator=(AVLTree<Key, Info>&&);
        iterator begin();   // returns iterator to the node with lowest key
        iterator end();     // returns iterator to one past the node with the biggest key
        const_iterator cbegin() const;
        const_iterator cend() const;
        bool operator==(const AVLTree<Key, Info>&) const;
        bool operator!=(const AVLTree<Key, Info>&) const;
        KeyInfoPair& at(int);   // returns the element at specified position
        KeyInfoPair& front();   // returns the first element
        KeyInfoPair& back();    // returns the last element
        const KeyInfoPair& at(int) const;
        const KeyInfoPair& front() const;
        const KeyInfoPair& back() const;
        iterator insert(const KeyInfoPair&);
        iterator insert(const Key&, const Info&);
        iterator erase(const iterator&);    // returns iterator to the next node
        iterator find(const Key&);
        const_iterator find(const Key&) const;
        bool empty() const;
        int size() const;
        void printStructure();
        void printPreorder();

    private:
        void setBeginAndEnd();  // sets beginIt and endIt
        Node* insertLeaf(Node*, bool, const KeyInfoPair&);
        int getBalanceFactor(Node*);
        void updateHeight(Node*);
        Node* rotateLeft(Node*);
        Node* rotateRight(Node*);
        void updateRelations(Node*, Node*, Node*);
        void updateParent(Node*, Node*);
        const KeyInfoPair& internalAt(int) const;
        const_iterator internalFind(const Key&) const;
        // for printing
        void showConnection(Connection*);
        void printStructure(Node*, Connection*, bool);
        void printPreorder(Node*);

};

#include "iterators.h"

template <typename Key, typename Info>
AVLTree<Key, Info>::AVLTree::KeyInfoPair::KeyInfoPair(Key newKey, Info newInfo): key(newKey), info(newInfo) {
    
}

template <typename Key, typename Info>
AVLTree<Key, Info>::AVLTree() {
    this->root = nullptr;
    this->beginIt = iterator(nullptr);
    this->endIt = iterator(nullptr);
    this->numberOfNodes = 0;
}

template <typename Key, typename Info>
AVLTree<Key, Info>::~AVLTree() {
    clear();
}

template <typename Key, typename Info>
AVLTree<Key, Info>::AVLTree(const AVLTree<Key, Info>& other) {
    this->root = new Node(*other.root);
    this->numberOfNodes = other.numberOfNodes;
    setBeginAndEnd();
}

template <typename Key, typename Info>
AVLTree<Key, Info>::AVLTree(AVLTree<Key, Info>&& other) {
    // taking over other tree's contents
    this->root = other.root;
    this->beginIt = other.beginIt;
    this->endIt = other.endIt;
    this->numberOfNodes = other.numberOfNodes;
    other.root = nullptr;
}

template <typename Key, typename Info>
AVLTree<Key, Info>& AVLTree<Key, Info>::operator=(const AVLTree<Key, Info>& other) {
    // to prevent self-assignment
    if (&other == this){
        return *this;
    }
    
    delete this->root;
    this->root = new Node(*other.root);
    this->numberOfNodes = other.numberOfNodes;
    setBeginAndEnd();
    return *this;
}

template <typename Key, typename Info>
AVLTree<Key, Info>& AVLTree<Key, Info>::operator=(AVLTree<Key, Info>&& other) {
    // taking other tree's contents
    delete this->root;
    this->root = other.root;
    this->beginIt = other.beginIt;
    this->endIt = other.endIt;
    this->numberOfNodes = other.numberOfNodes;
    other.root = nullptr;
    return *this;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::begin() {
    return beginIt;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::end() {
    return endIt;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::cbegin() const {
    return const_iterator(beginIt);
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::cend() const {
    return const_iterator(endIt);
}

template <typename Key, typename Info>
bool AVLTree<Key, Info>::operator==(const AVLTree<Key, Info>& other) const {
    if (numberOfNodes != other.numberOfNodes){
        return false;
    }
        
    // checking each node
    const_iterator it1 = cbegin();
    const_iterator it2 = other.cbegin();
    while (it1 != cend()) {
        if (it1->key != it2->key || it1->info != it2->info){
            return false;
        } 
        ++it1;
        ++it2;
    }
    return true;
}

template <typename Key, typename Info>
bool AVLTree<Key, Info>::operator!=(const AVLTree<Key, Info>& other) const {
    return !(*this == other);
}

template <typename Key, typename Info>
const typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::internalAt(int x) const {
    if (empty()) throw std::out_of_range("internalAl: empty tree, so no elements");

    if (x < 0 || x >= numberOfNodes) throw std::out_of_range("internalAt: wrong parameter");

    // iterating to access the x-th element
    const_iterator it = cbegin();
    for (int i = 0; i < x; i++){
        ++it;
    } 
    return *it;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::at(int index) {
    return (KeyInfoPair&)internalAt(index);
}

template <typename Key, typename Info>
const typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::at(int index) const {
    return internalAt(index);
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::front() {
    return (KeyInfoPair&)internalAt(0);
}

template <typename Key, typename Info>
const typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::front() const {
    return internalAt(0);
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::back() {
    return (KeyInfoPair&)internalAt(numberOfNodes - 1);
}

template <typename Key, typename Info>
const typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::back() const {
    return internalAt(numberOfNodes - 1);
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::insert(const KeyInfoPair& newKeyAndInfo) {
    // if the tree is empty, new element becomes the root
    if (empty()) {
        root = new Node(newKeyAndInfo);
        numberOfNodes++;
        setBeginAndEnd();
        return iterator(root);
    }

    Node* parent = root;
    Node* newNode;

    // BST insertion
    while (true) {
        // case 1: if there's already a node with such key, update its info
        if (parent->keyAndInfo.key == newKeyAndInfo.key) {
            parent->keyAndInfo.info = newKeyAndInfo.info;
            return iterator(parent);
        }
        // case 2: checking if there's space on the parent's left
        if (newKeyAndInfo.key < parent->keyAndInfo.key) {
            if (parent->left == nullptr){
                newNode = insertLeaf(parent, false, newKeyAndInfo); // false means it will be inserted on the left
                break;
            }
            else parent = parent->left;
        }
        // case 3: if there's space on the parent's right
        else { 
            if (parent->right == nullptr){
                newNode = insertLeaf(parent, true, newKeyAndInfo);  // true means on the right
                break;
                }
            else parent = parent->right;
        }
    }

    // now that newNode is inserted, we need to balance the tree
    for (Node* ancestor = parent; ancestor; ancestor = ancestor->parent) {
        int balance = getBalanceFactor(ancestor);

        // left left case
        if (balance > 1 && newKeyAndInfo.key < ancestor->left->keyAndInfo.key) {
            ancestor = rotateRight(ancestor);
            continue;
        }
        // right right case
        if (balance < -1 && newKeyAndInfo.key > ancestor->right->keyAndInfo.key) {
            ancestor = rotateLeft(ancestor);
            continue;
        }
        // left right case
        if (balance > 1 && newKeyAndInfo.key > ancestor->left->keyAndInfo.key) {
            ancestor->left = rotateLeft(ancestor->left);
            ancestor = rotateRight(ancestor);
            continue;
        }
        // right left case
        if (balance < -1 && newKeyAndInfo.key < ancestor->right->keyAndInfo.key) {
            ancestor->right = rotateRight(ancestor->right);
            ancestor = rotateLeft(ancestor);
            continue;
        }
    }
    return iterator(newNode);
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::insert(const Key& key, const Info& info) {
    return insert(KeyInfoPair(key, info));
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::erase(const iterator& toErase) {
    if (toErase.node == nullptr) throw std::out_of_range("erase: cannot erase end()");

    //obtain reference to next node sans the iterator as well as the current parent
    Node* nextNode = (++iterator(toErase)).node;
    Node* originalParent = toErase.node->parent;

    // BST removal
    // case 1: node toErase has no children (is a leaf)
    if (toErase.node->left == nullptr && toErase.node->right == nullptr) {
        updateParent(toErase.node, nullptr);
        updateHeight(toErase.node->parent);

        if (toErase.node == root){
            root = nullptr;
        }
        delete toErase.node;
    }
    // case 2: node toErase has one child, so we replace it with the child
    else if (toErase.node->left == nullptr || toErase.node->right == nullptr) {

        Node*& child = toErase.node->left ? toErase.node->left : toErase.node->right;
        updateParent(toErase.node, child);
        child->parent = toErase.node->parent;
        updateHeight(child->parent);

        if (toErase.node == root){
            root = child;
        }
        child = nullptr;
        delete toErase.node;
    }
    // case 3: node toErase has two children, so we replace it with its successor
    else {

        // successor will be the lowest node in the right subtree
        Node* successor = toErase.node->right;
        while (successor->left != nullptr){
            successor = successor->left;
        }
        updateParent(successor, nullptr);
        updateHeight(successor->parent);
        updateParent(toErase.node, successor);
        successor->left = toErase.node->left;
        successor->right = toErase.node->right;
        successor->parent = toErase.node->parent;

        if (toErase.node == root){
            root = successor;
        }
        toErase.node->left = nullptr;
        toErase.node->right = nullptr;
        delete toErase.node;
    }

    // now that the node is deleted, we need to balance the tree
    for (Node* ancestor = originalParent; ancestor; ancestor = ancestor->parent) {
        int balance = getBalanceFactor(ancestor);

        // left left case
        if (balance > 1 && getBalanceFactor(ancestor->left) >= 0) {
            ancestor = rotateRight(ancestor);
            continue;
        }
        // right right case
        if (balance < -1 && getBalanceFactor(ancestor->right) <= 0) {
            ancestor = rotateLeft(ancestor);
            continue;
        }
        // left right case
        if (balance > 1 && getBalanceFactor(ancestor->left) < 0) {
            ancestor->left = rotateLeft(ancestor->left);
            ancestor = rotateRight(ancestor);
            continue;
        }
        // right left case
        if (balance < -1 && getBalanceFactor(ancestor->left) > 0) {
            ancestor->right = rotateRight(ancestor->right);
            ancestor = rotateLeft(ancestor);
            continue;
        }
    }

    numberOfNodes--;
    setBeginAndEnd();
    return iterator(nextNode);
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::clear() {
    delete root;
    // each further node will call its destructor, so it is enough to destroy the root
    root = nullptr;
    numberOfNodes = 0;
    beginIt = iterator(nullptr);
    endIt = iterator(nullptr);
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::internalFind(const Key& keyToFind) const {
    // traversal
    Node* node = root;
    while (node != nullptr) {
        // if the key matches
        if (keyToFind == node->keyAndInfo.key)
            return const_iterator(node);

        // if the keyToFind is even smaller, go further left
        if (keyToFind < node->keyAndInfo.key)
            node = node->left;
        // if the keyToFind is bigger, go right
        else
            node = node->right;
    }
    //if nothing was found
    return cend();
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::find(const Key& keyToFind) {
    const_iterator it = internalFind(keyToFind);
    iterator output;
    output.node = it.node;
    output.prev = it.prev;
    return output;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::find(const Key& keyToFind) const {
    return internalFind(keyToFind);
}

template <typename Key, typename Info>
bool AVLTree<Key, Info>::empty() const {
    return numberOfNodes == 0;
}

template <typename Key, typename Info>
int AVLTree<Key, Info>::size() const {
    return numberOfNodes;
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::setBeginAndEnd() {
    if (empty()) {
        beginIt = iterator(nullptr);
        endIt = iterator(nullptr);
    }

    // go as left as possible, to get to the smallest key
    Node* node = root;
    while (node->left){
        node = node->left;
    }
    beginIt = iterator(node);    // points to node with smallest key

    // go as right as possible, to get to the biggest key
    node = root;
    while (node->right != nullptr){
        node = node->right;
    }
    endIt = ++iterator(node);     // points to one past the node with the biggest key
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::insertLeaf(Node* parent, bool rightSide, const KeyInfoPair& newKeyAndInfo) {
    // checking if there's space on right or left
    if (rightSide == false && parent->left) throw std::invalid_argument("insertLeaf: there's no space on parent's left");
    if (rightSide == true && parent->right) throw std::invalid_argument("insertLeaf: there's no space on parent's right");

    // if rightSide, assign on parent's right, if !rightSide, assign on parent's left
    Node*& newLeaf = rightSide ? parent->right : parent->left;
    newLeaf = new Node(newKeyAndInfo);
    newLeaf->parent = parent;

    numberOfNodes++;
    setBeginAndEnd();
    updateHeight(parent);
    return newLeaf;
}

template <typename Key, typename Info>
int AVLTree<Key, Info>::getBalanceFactor(Node* node) {
    if (node == nullptr) return 0;

    int leftHeight = node->left ? node->left->height : -1;
    int rightHeight = node->right ? node->right->height : -1;

    return leftHeight - rightHeight;
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::updateHeight(Node* node) {
    while (node != nullptr){
        int newHeight = 0;

        if (node->left != nullptr){
            if (node->left->height >= newHeight){
                newHeight = node->left->height + 1;
            }
        }  
        if (node->right != nullptr){
            if (node->right->height >= newHeight){
                newHeight = node->right->height + 1;
            }
        }
        node->height = newHeight;
        node = node->parent;
    }
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::rotateLeft(Node* pivot) {
	Node* newAtTheTop = pivot->right;
	Node* adoptedChild = newAtTheTop->left;

	// rotating
	newAtTheTop->left = pivot;
	pivot->right = adoptedChild;

	updateRelations(pivot, newAtTheTop, adoptedChild);
	return newAtTheTop;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::rotateRight(Node* pivot) {
	Node* newAtTheTop = pivot->left;
	Node* adoptedChild = newAtTheTop->right;

	// rotating
	newAtTheTop->right = pivot;
	pivot->left = adoptedChild;

	updateRelations(pivot, newAtTheTop, adoptedChild);
	return newAtTheTop;
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::updateRelations(Node* pivot, Node* newAtTheTop, Node* adoptedChild) {
    // pivot's parent's new child is newAtTheTop
	updateParent(pivot, newAtTheTop);

	// updating parents
	newAtTheTop->parent = pivot->parent;
	pivot->parent = newAtTheTop;
	if (adoptedChild != nullptr) adoptedChild->parent = pivot;

	if (pivot == root){
        root = newAtTheTop;
    }

	updateHeight(pivot);
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::updateParent(Node* oldChild, Node* newChild) {
	if (oldChild->parent == nullptr) return;

    if (oldChild->parent->left == oldChild){
        oldChild->parent->left = newChild;
    } 
    else{
        oldChild->parent->right = newChild;
    } 
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::showConnection(Connection* c) {
    if(c == nullptr) return;
    showConnection(c->prev);
    cout << c->link;
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::printStructure() {
    printStructure(root, nullptr, false);
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::printStructure(Node* node, Connection* prevConnection, bool isLeft) {
    if(node == nullptr) return;
    string indent = "    ";
    Connection* connection = new Connection(prevConnection, indent);

    printStructure(node->left, connection, true);

    if(!prevConnection) connection->link = "---";
    else if(isLeft){
        connection->link = ".---";
        indent = "   |";
    }
    else{
        connection->link = "`---";
        prevConnection->link = indent;
    }
    showConnection(connection);
    cout << node->keyAndInfo.key << endl;

    if(prevConnection){
        prevConnection->link = indent;
    }
    connection->link = "   |";

    printStructure(node->right, connection, false);
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::printPreorder() {
    printPreorder(root);
    cout << endl;
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::printPreorder(Node* node) {
    if(node){
        cout << node->keyAndInfo.key << " ";
        printPreorder(node->left);
        printPreorder(node->right);
    }
}

//..........................................................................................
// NODE

template <typename Key, typename Info>
AVLTree<Key, Info>::Node::Node(KeyInfoPair newKeyAndInfo) : keyAndInfo(newKeyAndInfo) {
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->height = 0;
}

template <typename Key, typename Info>
AVLTree<Key, Info>::Node::~Node() {
    if(this->left != nullptr) delete this->left;
    if(this->right != nullptr) delete this->right;
}

template <typename Key, typename Info>
AVLTree<Key, Info>::Node::Node(const Node& other) : keyAndInfo(other.keyAndInfo) {
    this->left = nullptr;
    this->right = nullptr;

    if(other.left != nullptr){
        this->left = new Node(*other.left);
        this->left->parent = this;
    }
    if(other.right != nullptr){
        this->right = new Node(*other.right);
        this->right->parent = this;
    }
    this->parent = other.parent;
    this->height = other.height;
}

template <typename Key, typename Info>
AVLTree<Key, Info>::Node::Node(Node&& other) : keyAndInfo(other.keyAndInfo) {
    this->left = other.left;
    this->right = other.right;
    this->parent = other.parent;
    this->height = other.height;
    other.left = nullptr;
    other.right = nullptr;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node& AVLTree<Key, Info>::Node::operator=(const Node& other) {
    // to prevent self-assignment
    if (&other == this){
          return *this;
    }
    // deleting own nodes and copying other's nodes
    if(this->left != nullptr) delete this->left;
    if(this->right != nullptr) delete this->right;
    this->left = nullptr;
    this->right = nullptr;

    if(other.left != nullptr) {
        this->left = new Node(*other.left);
        this->left->parent = this;
    }
    if(other.right != nullptr) {
        this->right = new Node(*other.right);
        this->right->parent = this;
    }

    this->parent = other.parent;
    this->height = other.height;
    return *this;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node& AVLTree<Key, Info>::Node::operator=(Node&& other) {
    // to prevent self-assignment
    if (&other == this){
        return *this; 
    }
    
    // deleting own nodes and taking over other's nodes
    if(this->left != nullptr) delete this->left;
    if(this->right != nullptr) delete this->right;
    this->left = other.left;
    this->right = other.right;
    this->height = other.height;

    other.left = nullptr;
    other.right = nullptr;

    return *this;
}

#endif