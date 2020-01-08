#ifndef COUNTER
#define COUNTER

#include <iostream>
#include "sequence.h"
using namespace std;

// DECLARATION OF CLASS COUNTER

template<typename Key>
class Counter{

    private:
    struct Node{
        Key key;
        int numberOfOccurrences = 0;
        Node* next;
    };
    Node* head;
    Sequence<Key> *sequence = new Sequence<Key>();
    int size;
    Node* findKey(const Key& x);
    Node* findPreviousKey(const Key& x);
    void addNode(Node* nodeToAdd);

    public:
    Counter();
    ~Counter();
    Counter(const Counter<Key>& );
    void addKey(const Key& x);  // adds at the end if key is unique, otherwise increments numberOfOccurrences
    bool removeKey(const Key& x);   // removes the node if it occurs only one, otherwise decrements numberOfOccurrences
    bool removeNode(const Key& x);  // removes the node and does not care about the numberOfOccurrences
    void printCounter();
    void printSequence();   // prints the sequence object
    void printNode(const Key& x);   // prints the key and numberOfOccurrences of the given node
    void printXCountedNodes(int num);   // prints the first X nodes from Counter
    void printXNotCountedNodes(int num);    // prints the first X nodes from Sequence object
    int getSize();
    void clear();
    bool find(const Key& x);
    bool operator==(const Counter<Key> &otherCounter);
    bool operator!=(const Counter<Key> &otherCounter);
    Counter<Key> &operator=(const Counter<Key> &otherCounter);

};

// DEFINITION OF FUNCTIONS

template <typename Key>
Counter<Key>::Counter(){
    size = 0;
    head = NULL;
    cout << "Counter created" << endl;
}

template <typename Key>
Counter<Key>::~Counter(){
    sequence->clear();
    clear();
}

template <typename Key>
Counter<Key>::Counter(const Counter<Key>& otherCounter){
    head = NULL;
    Node* current = otherCounter.head;
    while(current != NULL){
        this->addNode(current);
        current = current->next;
    }
}

template <typename Key>
void Counter<Key>::clear(){
    Node *current = head;
    while(head != NULL){
        current = head->next;
        delete head;
        head = current;
    }
}

template <typename Key>
typename Counter<Key>::Node* Counter<Key>::findKey(const Key& x){
    Node* current = head;
    if(head == NULL) return NULL;
    while(current != NULL){
        if(current->key == x){
            return current;
        }
        current = current->next;
    }
    if(current == NULL) return NULL;
}

template <typename Key>
typename Counter<Key>::Node* Counter<Key>::findPreviousKey(const Key& x){
    Node* current = head;
    Node* prev = NULL;

    if(head == NULL) return NULL;

    while(current != NULL){
        if(current->key == x){
            return prev;
        }
        prev = current;
        current = current->next;
    }
    if(current == NULL) return NULL;
}

template <typename Key>
void Counter<Key>::addNode(Node* nodeToAdd){    // adds to the end of the list, only for copy constructor and =
    if(head == NULL){
        sequence->insertLast(nodeToAdd->key);
        Node* newNode = new Node();
        newNode->key = nodeToAdd->key;
        newNode->numberOfOccurrences = nodeToAdd->numberOfOccurrences;
        newNode->next = NULL;
        head = newNode;
        size++;
        return;
    }
    sequence->insertLast(nodeToAdd->key);
    Node* current = head;
    Node* prev = NULL;
    while(current != NULL){
        prev = current;
        current = current->next;
    }
    Node* newNode = new Node();
    newNode->key = nodeToAdd->key;
    newNode->numberOfOccurrences = nodeToAdd->numberOfOccurrences;
    prev->next = newNode;
    newNode->next = NULL;
    size++;
        
}


template <typename Key>
void Counter<Key>::printCounter(){
    if(sequence->isEmpty()){
        cout << "printCounter: The list is empty." << endl;
        return;
    }
    Node* current = head;
    cout << "Counter contents:" << endl;
    while(current != NULL){
        cout << "Key: " << current->key << " occurrences: " << current->numberOfOccurrences << endl;
        current = current->next;
    }
}


template <typename Key>
void Counter<Key>::printSequence(){
    sequence->print();
}

template <typename Key>
void Counter<Key>::printNode(const Key& x){
    if(sequence->isEmpty()){
        cout << "printNode: The list is empty." << endl;
        return;
    }
    Node* foundNode = findKey(x);
    if(foundNode != NULL){
        cout << "Key: " << foundNode->key << " occurrances: " << foundNode->numberOfOccurrences << endl;
    }
    else cout << "printNode: There is no such element." << endl;
}

template <typename Key>
void Counter<Key>::printXCountedNodes(int num){
    if(num <= size && num >= 0){
        cout << "First " << num << " nodes in the counter:" << endl;
        Node* current = head;
        int count = 0;
        while(current != NULL){
            printNode(current->key);
            count++;
            current = current->next;
            if(count == num) break;
        }
    }
    else if(num <= 0) cout << "printXCountedNodes: Wrong number at the input" << endl;
    else cout << "printXCountedNodes: Not enough elements on this list." << endl;

}

template <typename Key>
void Counter<Key>::printXNotCountedNodes(int num){
    sequence->printXNodes(num);
}

template <typename Key>
bool Counter<Key>::find(const Key& x){
    Node* current = head;
    if(head == NULL) return false;
    while(current != NULL){
        if(current->key == x){
            return true;
        }
        current = current->next;
    }
    if(current == NULL) return false;
}

template <typename Key>
void Counter<Key>::addKey(const Key& x){
    if(head == NULL){
        sequence->insertLast(x);
        Node* newNode = new Node();
        newNode->key = x;
        newNode->numberOfOccurrences++;
        newNode->next = NULL;
        head = newNode;
        size++;
        return;
    }
    sequence->insertLast(x);
    Node* foundNode = findKey(x);
    if(foundNode != NULL){
        foundNode->numberOfOccurrences++;
    }
    else{
        Node* current = head;
        Node* prev = NULL;
        while(current != NULL){
            prev = current;
            current = current->next;
        }
        Node* newNode = new Node();
        newNode->key = x;
        newNode->numberOfOccurrences++;
        prev->next = newNode;
        newNode->next = NULL;
        size++;
    }
}

template <typename Key>
bool Counter<Key>::removeKey(const Key& x){
    if(sequence->isEmpty()){
        cout << "removeKey: The list is empty." << endl;
        return false;
    }
    if(find(x)){
        sequence->remove(x);
        Node* foundKey = findKey(x);
        if(foundKey->numberOfOccurrences > 1){
            foundKey->numberOfOccurrences--;
            return true;
        }
        else if(foundKey->numberOfOccurrences == 1){
            Node* keyToRemove = findKey(x);
            // if beginning of the list
            if(keyToRemove == head){
                head = head->next;
                delete keyToRemove;
                size--;
                return true;
            }
            Node* previousKey = findPreviousKey(x);
            // if end of the list
            if(keyToRemove->next == NULL){
                previousKey->next = NULL;
                delete keyToRemove;
                size--;
                return true;
            }
            // if middle of the list
            previousKey->next = keyToRemove->next;
            delete keyToRemove;
            size--;
            return true;
        }
    } 
    else{
        cout << "removeKey: There is no such element" << endl;
    }  

}

template <typename Key>
bool Counter<Key>::removeNode(const Key& x){
    if(sequence->isEmpty()){
        cout << "removeNode: The list is empty." << endl;
        return false;
    }
    if(!find(x)){
        cout << "removeNode: There is no such element." << endl;
        return false;
    }
    while(find(x)){
        removeKey(x);
    }
    return true;
}

template <typename Key>
int Counter<Key>::getSize(){
    return size;
}

// operators overloading

template <typename Key>
bool Counter<Key>::operator==(const Counter<Key> &otherCounter){
    if(this.size != otherCounter.size){
        return false;
    }
    Node *current = head;
    Node *currentOther = otherCounter.head;
    while(current != NULL){
        if(current->key != currentOther->key){
            return false;
        }
        current = current->next;
        currentOther = currentOther->next;
    }
    return true;
}

template <typename Key>
bool Counter<Key>::operator!=(const Counter<Key> &otherCounter){
    return !operator==(otherCounter); 
}

template <typename Key>
Counter<Key> &Counter<Key>::operator=(const Counter<Key> &otherCounter){
    clear();
    Node* current = otherCounter.head;
    while(current != NULL){
        addNode(current);
        current = current->next;
    }
    return *this;
}

#endif

