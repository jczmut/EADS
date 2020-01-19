#ifndef ITERATORS_H
#define ITERATORS_H

template <typename Key, typename Info>
class AVLTree<Key, Info>::iterator {

    friend class AVLTree;

    private:
        Node* prev;
        Node* node;

    public:
        iterator();
        KeyInfoPair& operator*() const;
        KeyInfoPair* operator->() const;
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;

    private:
        iterator(Node*);
        Node* lnr(Node*, Node*);    // traverses "inorder": left-node-right
        Node* rnl(Node*, Node*);    // traverses "inorder": right-node-left
};

template <typename Key, typename Info>
class AVLTree<Key, Info>::const_iterator {
    friend class AVLTree;

    private:
        Node* prev;
        Node* node;

    public:
        const_iterator();
        const_iterator(const iterator&);
        const KeyInfoPair& operator*() const;
        const KeyInfoPair* operator->() const;
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;

    private:
        const_iterator(Node*);
};

template <typename Key, typename Info>
AVLTree<Key, Info>::iterator::iterator() {
    prev = nullptr;
    node = nullptr;
}

template <typename Key, typename Info>
AVLTree<Key, Info>::iterator::iterator(Node* start) {
    prev = start ? rnl(start, start) : nullptr;
    node = start;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::iterator::operator*() const {
    if(!node) throw std::logic_error("operator*: cannot dereference end iterator");

    return node->keyAndInfo;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::KeyInfoPair* AVLTree<Key, Info>::iterator::operator->() const {
    if(!node) throw std::logic_error("operator->: cannot dereference end iterator");

    return &node->keyAndInfo;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator& AVLTree<Key, Info>::iterator::operator++() {
    if(!node) throw std::logic_error("operator++: cannot increment end iterator");

    prev = node;
    if (node) node = lnr(node, node);
    return *this;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::iterator::operator++(int) {
    if(!node) throw std::logic_error("operator++: cannot increment end iterator");

    iterator old = *this;
    ++(*this);
    return old;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator& AVLTree<Key, Info>::iterator::operator--() {
    if(!prev) throw std::logic_error("operator--: can't decrement begin iterator");

    node = prev;
    if (prev) prev = rnl(prev, prev);
    return *this;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::iterator::operator--(int) {
    if(!prev) throw std::logic_error("operator--: can't decrement begin iterator");

    iterator old = *this;
    --(*this);
    return old;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::iterator::lnr(Node* start, Node* current) {
    bool leftExists = current->left != nullptr;
    bool rightExists = current->right != nullptr;
    bool parentExists = current->parent != nullptr;

    // checking left
    if(leftExists){
        if(current->left->keyAndInfo.key > start->keyAndInfo.key){
            return lnr(start, current->left);
        }
    }

    // checking node
    if(current->keyAndInfo.key > start->keyAndInfo.key){
        return current;
    } 

    // checking right
    if(rightExists){
        if(current->right->keyAndInfo.key > start->keyAndInfo.key){
            return lnr(start, current->right);
        }
    } 

    // checking parent
    if (parentExists){
        return lnr(start, current->parent);
    }
    
    // if there's no parent
    return nullptr;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::iterator::rnl(Node* start, Node* current) {
    bool leftExists = current->left != nullptr;
    bool rightExists = current->right != nullptr;
    bool parentExists = current->parent != nullptr;

    // checking right
    if(rightExists){
        if(current->right->keyAndInfo.key < start->keyAndInfo.key){
            return rnl(start, current->right);
        }
    } 

    // checking node
    if(current->keyAndInfo.key < start->keyAndInfo.key){
        return current;
    }
    
    // checking left
    if(leftExists){
        if (current->left->keyAndInfo.key < start->keyAndInfo.key){
            return rnl(start, current->left);
        }
    } 

    // checking parent
    if (parentExists){
        return rnl(start, current->parent);
    } 

    // if there's no parent
    return nullptr;
}

template <typename Key, typename Info>
bool AVLTree<Key, Info>::iterator::operator==(const iterator& other) const {
    return other.node == node;
}

template <typename Key, typename Info>
bool AVLTree<Key, Info>::iterator::operator!=(const iterator& other) const {
    return other.node != node;
}

//..................................................................................
// CONST_ITERATOR

template <typename Key, typename Info>
AVLTree<Key, Info>::const_iterator::const_iterator() {
    prev = nullptr;
    node = nullptr;
}

template <typename Key, typename Info>
AVLTree<Key, Info>::const_iterator::const_iterator(Node* start) {
    iterator it(start);
    prev = it.prev;
    node = it.node;
}

template <typename Key, typename Info>
AVLTree<Key, Info>::const_iterator::const_iterator(const iterator& other) {
    prev = other.prev;
    node = other.node;
}

template <typename Key, typename Info>
const typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::const_iterator::operator*() const {
    if(!node) throw std::logic_error("operator*: cannot dereference end iterator");

    return node->keyAndInfo;
}

template <typename Key, typename Info>
const typename AVLTree<Key, Info>::KeyInfoPair* AVLTree<Key, Info>::const_iterator::operator->() const {
    if(!node) throw std::logic_error("operator->: cannot dereference end iterator");

    return &node->keyAndInfo;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator& AVLTree<Key, Info>::const_iterator::operator++() {
    // iterator's code will be used
    iterator it;
    it.prev = prev;
    it.node = node;
    ++it;
    prev = it.prev;
    node = it.node;
    return *this;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::const_iterator::operator++(int) {
    const_iterator old = *this;
    ++(*this);
    return old;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator& AVLTree<Key, Info>::const_iterator::operator--() {
    // iterator's code will be used
    iterator it;
    it.prev = prev;
    it.node = node;
    --it;
    prev = it.prev;
    node = it.node;
    return *this;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::const_iterator::operator--(int) {
    const_iterator old = *this;
    --(*this);
    return old;
}

template <typename Key, typename Info>
bool AVLTree<Key, Info>::const_iterator::operator==(const const_iterator& other) const {
    return other.node == node;
}

template <typename Key, typename Info>
bool AVLTree<Key, Info>::const_iterator::operator!=(const const_iterator& other) const {
    return other.node != node;
}

#endif