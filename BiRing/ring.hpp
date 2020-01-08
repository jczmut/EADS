using namespace std;
#include <iostream>

template <typename Key, typename Info>
BiRing<Key, Info>::BiRing::Node::Node(Key newKey, Info newInfo, Node* node, Node* prevNode) {
    keyAndInfo = KeyInfoPair(newKey, newInfo);
    next = node;
    prev = prevNode;
}

template <typename Key, typename Info>
BiRing<Key, Info>::BiRing::Node::Node() {
    next = nullptr;
    prev = nullptr;
}

template <typename Key, typename Info>
BiRing<Key, Info>::BiRing::KeyInfoPair::KeyInfoPair(Key newKey, Info newInfo) {
    key = newKey;
    info = newInfo;
}

template <typename Key, typename Info>
BiRing<Key, Info>::BiRing() {
    anchor = nullptr;
    nodeCount = 0;
}

template  <typename Key, typename Info>
BiRing<Key, Info>::~BiRing() {
    clear();
}

template  <typename Key, typename Info>
void BiRing<Key, Info>::copyNodes(const BiRing<Key, Info>& other) {
    Node* temp = other.anchor;
    while(true){
        push_back(temp->keyAndInfo);
        temp = temp->next;
        if(temp == other.anchor) break;
    }
}

template  <typename Key, typename Info>
BiRing<Key, Info>::BiRing(const BiRing<Key, Info>& other) {
    if (&other == this) return;
    anchor = nullptr;
    nodeCount = 0;
    copyNodes(other);
}

template  <typename Key, typename Info>
BiRing<Key, Info>::BiRing(BiRing<Key, Info>&& other) {
    anchor = other.anchor;
    nodeCount = other.nodeCount;
    other.anchor = nullptr;
    other.nodeCount = 0;
}

template  <typename Key, typename Info>
BiRing<Key, Info>& BiRing<Key, Info>::operator=(const BiRing<Key, Info>& other) {
    if(&other == this) return *this;

    clear();
    copyNodes(other);
    
    return *this;
}

template  <typename Key, typename Info>
BiRing<Key, Info>& BiRing<Key, Info>::operator=(BiRing<Key, Info>&& other) {
    clear();
    anchor = other.anchor;
    nodeCount = other.nodeCount;

    other.anchor = nullptr;
    other.nodeCount = 0;

    return *this;
}

template  <typename Key, typename Info>
typename BiRing<Key, Info>::iterator BiRing<Key, Info>::begin() {
    iterator it;
    it.node = anchor;
    return it;
}

template  <typename Key, typename Info>
typename BiRing<Key, Info>::iterator BiRing<Key, Info>::end() {
    iterator it;
    it.node = nullptr;
    return it;
}

template  <typename Key, typename Info>
typename BiRing<Key, Info>::const_iterator BiRing<Key, Info>::cbegin() const {
    const_iterator it;
    it.node = anchor;
    return it;
}

template  <typename Key, typename Info>
typename BiRing<Key, Info>::const_iterator BiRing<Key, Info>::cend() const {
    const_iterator it;
    it.node = nullptr;
    return it;
}

template  <typename Key, typename Info>
void BiRing<Key, Info>::clear() {
    if (!anchor) return;
    Node* temp = anchor;
    for(int i = 0; i < nodeCount; i++) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
    anchor = nullptr;
    nodeCount = 0;
}

template  <typename Key, typename Info>
bool BiRing<Key, Info>::empty() const {
    return nodeCount == 0;
}

template  <typename Key, typename Info>
int BiRing<Key, Info>::size() const {
    return nodeCount;
}

template  <typename Key, typename Info>
void BiRing<Key, Info>::advance(const Key& seekedKey, const_iterator& start) const {
    
    const_iterator it = start;
    ++it;
    while(true){
        if(it->key == seekedKey){    // (*it).key
            start = it;
            return;
        }
        if(it == start) break;
        ++it;
    }
    
    if(start->key == seekedKey) return;
    start.node = nullptr; //set output iterator to end()
}

template  <typename Key, typename Info>
void BiRing<Key, Info>::push_back(const KeyInfoPair& keyInfo) {
    if(!anchor){
        Node* newNode = new Node(keyInfo.key, keyInfo.info, nullptr, nullptr);
        newNode->next = newNode;
        newNode->prev = newNode;
        anchor = newNode;
        nodeCount++;
        return;
    }
    Node* newNode = new Node(keyInfo.key, keyInfo.info, anchor, anchor->prev);
    anchor->prev->next = newNode;
    anchor->prev = newNode;
    nodeCount++;
}

template  <typename Key, typename Info>
typename BiRing<Key, Info>::iterator BiRing<Key, Info>::insert(const KeyInfoPair& keyInfo, iterator& beforeThis) {
    if(empty()){
        push_back(keyInfo);
        beforeThis.node = anchor;
        return begin();
    }

    Node* newNode = new Node(keyInfo.key, keyInfo.info, beforeThis.node, beforeThis.node->prev);
    beforeThis.node->prev->next = newNode;
    beforeThis.node->prev = newNode;
    nodeCount++;

    iterator it;
    it.node = newNode;
    return it;
}

template  <typename Key, typename Info>
typename BiRing<Key, Info>::iterator BiRing<Key, Info>::erase(const iterator& toDelete) {
    if(toDelete.node == nullptr){
        cout << "erase: Undefined iterator" << endl;
        return end();
    }

    if(nodeCount == 1){
        clear();
        return end();
    }

    toDelete.node->prev->next = toDelete.node->next;
    toDelete.node->next->prev = toDelete.node->prev;

    if(toDelete.node == anchor) {
        anchor = toDelete.node->next;
    }

    iterator nextIt;
    nextIt.node = toDelete.node->next;

    delete toDelete.node;
    nodeCount--;

    return nextIt;
}

template  <typename Key, typename Info>
typename BiRing<Key, Info>::iterator BiRing<Key, Info>::find(const Key& seekedKey, int which) {
    if(which >= 0){
        return const_iterator(internalFind(seekedKey, which));
    }
    std::cout << "find: Wrong number of occurrence at the input" << std::endl;
    return end();
}

template  <typename Key, typename Info>
typename BiRing<Key, Info>::const_iterator BiRing<Key, Info>::find(const Key& seekedKey, int which) const {
    if(which >= 0){
        return internalFind(seekedKey, which);
    }
    std::cout << "find: Wrong number of occurrence at the input" << std::endl;
    return cend();
}

template  <typename Key, typename Info>
typename BiRing<Key, Info>::const_iterator BiRing<Key, Info>::internalFind(const Key& seekedKey, int which) const {
    if(which >= 0){
        if(empty()) return cend();

        const_iterator it = cbegin();
        if (it->key != seekedKey){
            advance(seekedKey, it);
        }
            
        if(it == cend()) return cend();

        if(howMany(seekedKey) == 1) return it;

        for(int i=0; i<which; i++) advance(seekedKey, it);

        return it;
    }
    return cend();
}

template  <typename Key, typename Info>
int BiRing<Key, Info>::howMany(const Key& key) const {
    if(empty()) return 0;

    const_iterator it = cbegin();
    int howMany = 0;

    while(true){
        if(it->key == key) howMany++;
        ++it;
        if(it == cbegin()) break;
    }
    
    return howMany;
}

template  <typename Key, typename Info>
bool BiRing<Key, Info>::operator==(const BiRing<Key, Info>& other) const {
    if (nodeCount != other.nodeCount)
        return false;

    Node* otherAnchor = other.anchor;
    do {
        Node* thisNode = anchor;
        Node* otherNode = otherAnchor;

        bool mismatch = false;
        do {
            if (thisNode->keyAndInfo.key != otherNode->keyAndInfo.key || thisNode->keyAndInfo.info != otherNode->keyAndInfo.info) {
                mismatch = true;
                break;
            }

            thisNode = thisNode->next;
            otherNode = otherNode->next;
        } while (thisNode != anchor);

        if (!mismatch) return true;
        otherAnchor = otherAnchor->next;
    } while(otherAnchor != other.anchor);

    return false;
}

template  <typename Key, typename Info>
bool BiRing<Key, Info>::operator!=(const BiRing<Key, Info>& other) const {
    return !(*this == other);
}

template  <typename Key, typename Info>
void BiRing<Key, Info>::eraseKey(const Key& key) {
    if(empty()){
        cout << "eraseKey: Empty ring" << endl;
        return;
    }
    iterator it = begin();
    for(int i = 0; i < nodeCount; i++){
        if(it->key == key){
            it = erase(it);
            i--;
        }
        if(it->key == key) continue;
        ++it;
    }
}

template  <typename Key, typename Info>
bool BiRing<Key, Info>::doesExist(const Key& key) const {
    const_iterator it = find(key, 0);
    return it != cend();
}

template <typename Key, typename Info>
void BiRing<Key, Info>::print() {
    if(empty()){
        cout << "print: Empty ring" << endl;
        return;
    }
    const_iterator it = cbegin();
    for(int i = 0; i < size(); i++){
        cout << it->key << " " << it->info << endl;
        ++it;
    }
}

template <typename Key, typename Info>
void BiRing<Key, Info>::printFrom(const Key& key, int which) {
    if(which >= 0){
        if(empty()){
            cout << "printFrom: Empty ring" << endl;
            return;
            }
            const_iterator it;
            it = internalFind(key, which);

            if(it != cend()){
                for(int i = 0; i < size(); i++){
                cout << it->key << " " << it->info << endl;
                ++it;
                }
                return;
            }
            cout << "printFrom: Key or its given occurrence does not exist" << endl;
            return;  
    }
    cout << "printFrom: Wrong number of occurrence at the input" << endl;
}

// EADS TEST 1

template <typename Key, typename Info>
bool BiRing<Key, Info>::eraseBetween(const Key& first, const Key& second) {
    Node* temp = anchor;
    //if(find(first) && find(second)){
        while(temp->keyAndInfo.key != first){
            temp = temp->next;
        }
        temp = temp->next;
        do{
            if(temp->keyAndInfo.key == second) break;
            
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;

            if(temp == anchor){
                anchor = temp->next;
            }

            delete temp;
            nodeCount--;
            
            temp = temp->next;

        } while(temp != anchor);
    //}
}
/*

    toDelete.node->prev->next = toDelete.node->next;
    toDelete.node->next->prev = toDelete.node->prev;

    if(toDelete.node == anchor) {
        anchor = toDelete.node->next;
    }

    iterator nextIt;
    nextIt.node = toDelete.node->next;

    delete toDelete.node;
    nodeCount--;
*/