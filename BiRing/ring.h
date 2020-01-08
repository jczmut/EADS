#ifndef RING_H
#define RING_H

template <typename Key, typename Info>
class BiRing {
    public:
        struct KeyInfoPair {
            Key key;
            Info info;

            KeyInfoPair() = default;
            KeyInfoPair(Key newKey, Info newInfo);
        };

    private:
        struct Node {
            
            KeyInfoPair keyAndInfo;
            Node* next;
            Node* prev;
            Node();
            Node(Key newKey, Info newInfo, Node* node, Node* prevNode);
        };
        Node* anchor;
        int nodeCount;
        void copyNodes(const BiRing&);

    public:

    BiRing();
    ~BiRing();
    BiRing(const BiRing&);
    BiRing(BiRing&&);
    
    BiRing<Key, Info>& operator=(const BiRing<Key, Info>&);
    BiRing<Key, Info>& operator=(BiRing<Key, Info>&&);
    bool operator==(const BiRing<Key, Info>&) const;
    bool operator!=(const BiRing<Key, Info>&) const;

    class iterator;
    class const_iterator;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
    
    iterator insert(const KeyInfoPair&, iterator& beforeThis);
    void push_back(const KeyInfoPair&);  // inserts the node at the abstract "end", so simply before the anchor
    iterator erase(const iterator&);    // returns the next iterator
    iterator find(const Key&, int which = 0);
    const_iterator find(const Key&, int which = 0) const;
    void advance(const Key&, const_iterator&) const;
    void clear();
    void eraseKey(const Key&);
    bool empty() const;
    bool doesExist(const Key&) const;
    int size() const;
    int howMany(const Key&) const;
    void print();
    void printFrom(const Key&, int which = 0);

    // EADS TEST 1
    bool eraseBetween(const Key&, const Key&);

    private:
    const_iterator internalFind(const Key&, int) const;
};

#include "ring.hpp"
#include "iterators.h"

#endif