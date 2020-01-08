#include "ring.h"
#include "iterators.h"
#include <iostream>

using namespace std;

template <typename Key, typename Info>
BiRing<Key, Info> shuffle(const BiRing<Key, Info>& first, const BiRing<Key, Info>& second, int fromFirst, int fromSecond, int reps) {
    BiRing<Key, Info> shuffledRing;
    if(first.empty() || second.empty()) return shuffledRing;
    if(fromFirst < 0 || fromSecond < 0 || reps < 1) return shuffledRing;
    if(fromFirst + fromSecond == 0) return shuffledRing;

    typename BiRing<Key, Info>::const_iterator firstIt;
    firstIt = first.cbegin();
    typename BiRing<Key, Info>::const_iterator secondIt;
    secondIt = second.cbegin();
    

    for(int r = 0; r < reps; r++){
        for(int f = 0; f < fromFirst; f++){
            Key key = firstIt->key;
            Info info = firstIt->info;
            shuffledRing.push_back(typename BiRing<Key, Info>::KeyInfoPair(key, info));
            ++firstIt;
        }
        for(int s = 0; s < fromSecond; s++){
            Key key2 = secondIt->key;
            Info info2 = secondIt->info;
            shuffledRing.push_back(typename BiRing<Key, Info>::KeyInfoPair(key2, info2));
            ++secondIt;
        }
    }
    return shuffledRing;

}

int main(){

    BiRing<int, string> first;
    first.push_back(BiRing<int, string>::KeyInfoPair(1, "Radiohead"));
    first.push_back(BiRing<int, string>::KeyInfoPair(2, "Radiohead"));
    first.push_back(BiRing<int, string>::KeyInfoPair(3, "Muse"));
    first.push_back(BiRing<int, string>::KeyInfoPair(4, "Red Hot Chilli Peppers"));
    first.push_back(BiRing<int, string>::KeyInfoPair(5, "Metronomy"));
    first.push_back(BiRing<int, string>::KeyInfoPair(6, "The Black Keys"));
    first.push_back(BiRing<int, string>::KeyInfoPair(7, "Coldplay"));
    first.push_back(BiRing<int, string>::KeyInfoPair(8, "System Of A Down"));

    BiRing<int, string> second;
    second.push_back(BiRing<int, string>::BiRing::KeyInfoPair(10, "Rhye"));
    second.push_back(BiRing<int, string>::BiRing::KeyInfoPair(11, "Editors"));

    cout << "FIRST RING" << endl;
    first.print();
    cout << endl << "SECOND RING" << endl;
    second.print();
    cout << endl;
    cout << endl << "***************************************************" << endl;

    BiRing<int, string> shuffledRing;
    shuffledRing = shuffle(first, second, 3, 1, 5);
    cout << "SHUFFLED RING" << endl;
    shuffledRing.print();

    BiRing<int, string> shuffledRing2;
    shuffledRing2 = shuffle(first, second, 3, 1, -8);
    cout << endl << "SHUFFLED RING (with reps < 0)" << endl;
    shuffledRing2.print();
}