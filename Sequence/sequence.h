#ifndef SEQUENCE
#define SEQUENCE

#include <iostream>
using namespace std;

// DECLARATION OF THE CLASS SEQUENCE   

template <typename valType>
class Sequence{

    private:

    struct Node{
        valType key;
        Node *next;
    };
    Node *head;
    int size;
    Node* findNode(const valType& x, int occurrence = 1);
    Node* findPreviousNode(const valType& x, int occurrence = 1);

    // EADS TEST 1
    void reversePrint(Node* node);
    bool reversePrintFLK(const valType&, Node*);
    bool reversePrintTLK(const valType&, Node*);


    public:
    Sequence();
    ~Sequence();
    Sequence(const Sequence<valType>& );
    void insertFirst(const valType& x);
    void insertLast(const valType& x);
    void insertAfter(const valType& x, const valType& where, int occurrence = 1);
    bool remove(const valType& x, int occurrence = 1);
    bool removeAllOccurrences(const valType& x);    // removes all occurrences of a given key in the sequence
    bool removeFromTo(const valType& x, int start = 1, int end = 0);
            // removes occurrences of a key starting from occurrence number specified by 'start' and ending 
            // on the occurrence number specified by 'end' 
    bool find(const valType& x, int occurrence = 1);
    int numberOfOccurrences(const valType& x);
    void print();
    void printNode(const valType& x);   // prints the key of a given Node
    void printXNodes(int num);  // prints the first X Nodes' keys
    int getSize();
    void clear();
    bool isEmpty();
    bool operator==(const Sequence<valType> &otherSequence);
    bool operator!=(const Sequence<valType> &otherSequence);
    Sequence<valType> &operator=(const Sequence<valType> &otherSequence);

    // EADS TEST 1 PREPARATION
    void reversePrint();
    void reversePrintFLK(const valType& x);
    void reversePrintTLK(const valType& x);
    int insert(double first, double second, double inside1, double inside2);  // return number of inserted pairs
   

};

// DEFINITIONS OF FUNCTIONS

template <typename valType>
Sequence<valType>::Sequence(){
    head = NULL;
    size = 0;
    cout << "Sequence created." << endl;
}

template <typename valType>
Sequence<valType>::~Sequence(){
    clear();
}

template <typename valType>
Sequence<valType>::Sequence(const Sequence<valType>& otherSequence){
    head = NULL;
    Node* current = otherSequence.head;
    while(current != NULL){
        this->insertLast(current->key);
        current = current->next;
    }
}

template <typename valType>
void Sequence<valType>::clear(){
    Node *current = head;
    while(head != NULL){
        current = head->next;
        delete head;
        head = current;
    }
}

template <typename valType>
typename Sequence<valType>::Node* Sequence<valType>::findNode(const valType& x, int occurrence){
    if(occurrence >= 1){
        Node* current = head;
        int count = 0;
    
        while(current != NULL){
            if(current->key == x){
                count++;
                if(count == occurrence){
                return current;
                }
            }
            current = current->next;
        }
        if(current == NULL) return NULL;
    }
    else return NULL;
}
    
template <typename valType>
typename Sequence<valType>::Node* Sequence<valType>::findPreviousNode(const valType& x, int occurrence){
    if(occurrence >= 1){
        if(isEmpty()) return NULL;
        Node* current = head;
        Node* prev = NULL;
        int count = 0;

        while(current != NULL){
            if(current->key == x){
                count++;
                if(count == occurrence){
                    return prev;
                }
            }
            prev = current;
            current = current->next;
        }
        if(current == NULL) return NULL;
    }
    else return NULL;
}

template <typename valType>
void Sequence<valType>::print(){
    Node *current = head;
    if(isEmpty()){
        cout << "print: The list is empty." << endl;
        return;
    }
    cout << "Sequence contents: " << endl;
    while(current != NULL){
        cout << "Key: " << current->key << endl;
        current = current->next; 
    }
}

template <typename valType>
void Sequence<valType>::printNode(const valType& x){
    Node* foundNode = findNode(x);
    if(foundNode != NULL){
        cout << "Key: " << foundNode->key << endl;
    }
    else cout << "printNode: There is no such element." << endl;
}

template <typename valType>
void Sequence<valType>::printXNodes(int num){
    if(num <= size && num >= 0){
        cout << "First " << num << " elements in the sequence:" << endl;
        Node* current = head;
        int count = 0;
        while(current != NULL){
            printNode(current->key);
            count++;
            current = current->next;
            if(count == num) break;
        }
    }
    else if(num <= 0) cout << "printXNodes: Wrong number at the input." << endl;
    else cout << "printXNodes: Not enough elements on the list." << endl;
}

template <typename valType>
void Sequence<valType>::insertFirst(const valType& x){

    Node *current = head;
    if(isEmpty()){
        Node *newHead = new Node();
        newHead->key = x;
        newHead->next = NULL;
        head = newHead;
        size++;
    }
    else{
    Node *newObject = new Node();
    newObject->key = x;
    newObject->next = head;
    head = newObject;
    size++;
    }
    
}

template<typename valType>
void Sequence<valType>::insertLast(const valType& x){
    Node *current = head;
    Node *prev = NULL;

    if(isEmpty()){
        Node *newHead = new Node();
        newHead->key = x;
        newHead->next = NULL;
        head = newHead;
        size++;
    }
    else{
        Node *newObject = new Node();
        while(current != NULL){
            prev = current;
            current = current->next;
        }
        newObject->key = x;
        prev->next = newObject;
        newObject->next = NULL;
        size++;
    }
}

template<typename valType>
void Sequence<valType>::insertAfter(const valType& x, const valType& where, int occurrence){
    if(occurrence >= 1){
        if(head == NULL){
            Node *newHead = new Node();
            newHead->key = x;
            newHead->next = NULL;
            head = newHead;
            size++;
        }
        else{
            if(findNode(where, occurrence) != NULL){
                Node *newObject = new Node();
                Node *foundNode = findNode(where, occurrence);
                newObject->key = x;
                newObject->next = foundNode->next;
                foundNode->next = newObject;
                size++; 
            }
        }
    }
    else cout << "insertAfter: Wrong number of occurrence, must be >= 1." << endl;
}

template<typename valType>
bool Sequence<valType>::remove(const valType& x, int occurrence){
    if(occurrence >= 1){
        if(isEmpty()){
            cout << "remove: The list is empty." << endl;
            return false;
        }
        else if(find(x, occurrence)){
            Node* current = head;

            // removing from the beginning of the list
            if(head->key == x){
                head = head->next;
                delete current;
                size--;
                return true;
            }

            Node *foundNode = findNode(x, occurrence);
            Node *previousNode = findPreviousNode(x, occurrence);

            // removing from the end
            if(foundNode->next == NULL){
                previousNode->next = NULL;
                delete foundNode;
                size--;
                return true;
            } 
        
            // removing from the middle
            previousNode->next = foundNode->next;
            delete foundNode;
            size--;
            return true;
        }
        else{
            cout << "remove: There is no such element." << endl;
            return false;
        }
    }
    else{
        cout << "remove: Wrong number of occurrence, must be >= 1." << endl;
        return false;
    }    
}

template <typename valType>
bool Sequence<valType>::removeAllOccurrences(const valType& x){
    if(isEmpty()){
        cout << "removeAllOccurrences: The list is empty." << endl;
        return false;
    }
    if(!find(x)){
        cout << "removeAllOccurrences: There is no such element." << endl;
        return false;
    }
    while(find(x)){
        
        Node *foundNode = findNode(x);

        // removing from the beginning
        if(foundNode == head){
            head = head->next;
            delete foundNode;
            size--;
            continue;
        }
        Node *previousNode = findPreviousNode(x);

        // removing from the end
        if(foundNode->next == NULL){
            previousNode->next = NULL;
            delete foundNode;
            size--;
            continue;
        }

        // removing from the middle
        previousNode->next = foundNode->next;
        delete foundNode;
        size--;
        continue;
    }
    return true;
}

template <typename valType>
bool Sequence<valType>::removeFromTo(const valType& x, int start, int end){
    if(!find(x, start) || !find(x, end)){
        cout << "removeFromTo: This element does not exist or occurs at another number of times" << endl;
        return false;
    }
    int count = start;
    int howMany = end - start;
    while(find(x, count)){
        remove(x, count);
        if(howMany == 0) break;
        howMany--;
    }
    return true;
}


template<typename valType>
bool Sequence<valType>::find(const valType& x, int occurrence){
    if(occurrence >= 1){
        Node *current = head;
        int count = 0;
        if(head == NULL) return false;
    
        if(findNode(x, occurrence) != NULL) return true;
        else return false;
    }
    else{
        cout << "find: Wrong number of occurrences, must be >= 1." << endl;
        return false;
    }
}

template <typename valType>
int Sequence<valType>::numberOfOccurrences(const valType& x){
    if(!find(x)) return 0;
    int count = 1;
    while(find(x, count)){
        count++;
    }
    return count-1;
}

template <typename valType>
int Sequence<valType>::getSize(){
    return size;
}

template <typename valType>
bool Sequence<valType>::isEmpty(){
    if(head == NULL) return true;
    else return false;
}

// operators overloading

template <typename valType>
Sequence<valType> &Sequence<valType>::operator=(const Sequence<valType> &otherSequence){
    clear();
    Node* current = otherSequence.head;
    while(current != NULL){
        insertLast(current->key);
        current = current->next;
    }
    return *this;
}

template <typename valType>
bool Sequence<valType>::operator==(const Sequence<valType>& otherSequence){
    if(this.size != otherSequence.size){
        return false;
    }
    Node *current = head;
    Node *currentOther = otherSequence.head;
    while(current != NULL){
        if(current->key != currentOther->key){
            return false;
        }
        current = current->next;
        currentOther = currentOther->next;
    }
    return true;
}

template <typename valType>
bool Sequence<valType>::operator!=(const Sequence<valType>& otherSequence){
   return !operator==(otherSequence); 
}

// EADS TEST 1
template <typename valType>
void Sequence<valType>::reversePrint(Node* node) {
    if(node == NULL) return;    // anchor
    reversePrint(node->next);
    cout << node->key << endl;
}

template <typename valType>
void Sequence<valType>::reversePrint() {
    reversePrint(head);
}

template <typename valType>
bool Sequence<valType>::reversePrintFLK(const valType& x, Node* node) {
    if(!node) return false;

    bool start = reversePrintFLK(x, node->next);

    if(node->key == x)
        start = true;
    if(start == true){
        cout << node->key << endl;
        return true;
    }
    return false;
}

template <typename valType>
void Sequence<valType>::reversePrintFLK(const valType& x) {
    reversePrintFLK(x, head);
}

template <typename valType>
bool Sequence<valType>::reversePrintTLK(const valType& x, Node* node) {
    if(!node) return false;

    bool finish = reversePrintTLK(x, node->next);
    
    if(node->key == x){
        finish = true;
    } 
    if(finish == true){
        return true;
    }
    if(finish == false){
        cout << node->key << endl;
        return false;
    }
    return false;
}

template <typename valType>
void Sequence<valType>::reversePrintTLK(const valType& x) {
    reversePrintTLK(x, head);
}

template <typename valType>
int Sequence<valType>::insert(double first, double second, double inside1, double inside2) {
    Node* temp = head;
    int count = 0;

    while(temp) {
        if(temp->key == first && temp->next->key == second){
            Node* new1 = new Node();
            new1->key = inside1;
            Node* new2 = new Node();
            new2->key = inside2;
            new1->next = new2;
            new2->next = temp->next;
            temp->next = new1;
            count++;
        }
        temp = temp->next;
    }
    return count;
}


#endif