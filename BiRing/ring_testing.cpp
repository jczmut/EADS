#include "ring.h"
#include <iostream>
using namespace std;

template class BiRing<int, int>;

int main(){

    BiRing<int, string> ring;
    BiRing<int, string>::iterator it;

    cout << "***************************************************" << endl;
    cout << "TEST CASE 1: EMPTY RING" << endl << endl;
    cout << "------SECTION 1: PRINTING------ " << endl;
    ring.print();
    ring.printFrom(3);

    cout << endl << "------SECTION 2: REMOVING------ " << endl;
    ring.erase(it);
    ring.eraseKey(3);
    ring.clear();
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 2: INSERTING" << endl;
    cout << endl << "------SECTION 1: INSERTING TO AN EMPTY RING------ " << endl;
    ring.insert(BiRing<int, string>::KeyInfoPair(1, "The Smiths"), it);
    ring.print();

    cout << endl << "------SECTION 2: INSERTING TO A NON-EMPTY RING------ " << endl;
    ring.push_back(BiRing<int, string>::KeyInfoPair(2, "Radiohead"));
    ring.push_back(BiRing<int, string>::KeyInfoPair(3, "Muse"));
    ring.push_back(BiRing<int, string>::KeyInfoPair(4, "Red Hot Chilli Peppers"));
    ring.push_back(BiRing<int, string>::KeyInfoPair(5, "Metronomy"));
    ring.push_back(BiRing<int, string>::KeyInfoPair(6, "The Black Keys"));
    ring.push_back(BiRing<int, string>::KeyInfoPair(7, "Coldplay"));
    ring.push_back(BiRing<int, string>::KeyInfoPair(8, "System Of A Down"));
    BiRing<int, string>::iterator it2;
    it2 = ring.find(3);
    ring.insert(BiRing<int, string>::KeyInfoPair(3, "Kazy Lambist"), it2);
    ring.print();
    cout << endl << "***************************************************" << endl;


    cout << "TEST CASE 3: REMOVING" << endl;
    cout << endl << "------SECTION 1: REMOVING FROM A NON-EMPTY RING------ " << endl;
    ring.erase(ring.find(8));
    ring.eraseKey(3);
    ring.erase(ring.find(1));
    ring.print();

    cout << endl << "------SECTION 2: CLEARING THE RING------ " << endl;
    ring.clear();
    ring.print();
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 4: COPY CONSTRUCTOR" << endl;
    cout << endl << "------SECTION 1: CREATING THE ORIGINAL RING AND THE COPIED ONE------ " << endl;
    ring.push_back(BiRing<int, string>::KeyInfoPair(2, "Radiohead"));
    ring.push_back(BiRing<int, string>::KeyInfoPair(3, "Muse"));
    ring.push_back(BiRing<int, string>::KeyInfoPair(4, "Red Hot Chilli Peppers"));
    ring.push_back(BiRing<int, string>::KeyInfoPair(5, "Metronomy"));
    ring.push_back(BiRing<int, string>::KeyInfoPair(6, "The Black Keys"));
    ring.push_back(BiRing<int, string>::KeyInfoPair(7, "Coldplay"));
    ring.push_back(BiRing<int, string>::KeyInfoPair(8, "System Of A Down"));
    BiRing<int, string>::iterator it3;
    it3 = ring.begin();
    ring.insert(BiRing<int, string>::KeyInfoPair(1, "The Smiths"), ++it3);
    ring.print();

    BiRing<int, string> ring2(ring);
    cout <<endl << "COPIED RING" << endl;
    ring2.print();

    cout << endl << "------SECTION 2: COMPARING ORIGINAL AND COPIED RINGS------ " << endl;
    if(ring == ring2) cout << "ring == ring2" << endl;

    cout << endl << "------SECTION 3: TRANSFORMING THE COPIED SEQUENCE------ " << endl;
    ring2.push_back(BiRing<int, string>::KeyInfoPair(9, "Elder Island"));
    ring.push_back(BiRing<int, string>::KeyInfoPair(9, "Cigarettes After Sex"));
    cout << "ring" << endl;
    ring.print();
    cout << endl << "ring2" << endl;
    ring2.print();

    cout << endl << "------SECTION 4: COMPARING ORIGINAL AND COPIED RINGS AGAIN------ " << endl;
    cout << "------THE RINGS ARE DIFFERENT ONLY BY ONE ELEMENT'S INFO------ " << endl;
    if(ring != ring2) cout << "ring != ring2" << endl;
    else cout << "ring == ring2" << endl;

    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 5: ASSIGNMENT OPERATOR" << endl;
    cout << endl << "------SECTION 1: CREATING TWO EMPTY NEW RINGS AND FILLING UP WITH SOME DATA------ " << endl;
    BiRing<int, string> ring3;
    BiRing<int, string> ring4;
    ring3.push_back(BiRing<int, string>::KeyInfoPair(1, "Arctic Monkeys"));
    ring3.push_back(BiRing<int, string>::KeyInfoPair(1, "Pixies"));
    ring4.push_back(BiRing<int, string>::KeyInfoPair(2, "Fisz Emade Tworzywo"));
    ring4.push_back(BiRing<int, string>::KeyInfoPair(5, "The Last Shadow Puppets"));
    ring4.push_back(BiRing<int, string>::KeyInfoPair(7, "Arctic Monkeys"));
    cout << "ring3" << endl;
    ring3.print();
    cout << "ring4" << endl;
    ring4.print();

    cout << endl << "------SECTION 2: ASSIGNING DATA FROM RING 3 TO RING 4 USING ASSIGNMENT OPERATOR------ " << endl;
    ring4 = ring3;

    cout << "ring3" << endl;
    ring3.print();
    cout << "ring4" << endl;
    ring4.print();
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 6: PRINTING RINGS STARTING FROM SPECIFIED KEYS" << endl;
    cout << endl << "------SECTION 1: RING FROM KEY 3------ " << endl;
    ring.printFrom(3);

    cout << endl << "------SECTION 2: RING 3 FROM SECOND KEY 1------ " << endl;
    ring3.printFrom(1, 1);

    cout << endl << "------SECTION 3: TRYING TO PRINT A RING FROM KEY WHICH DOES NOT EXIST------ " << endl;
    ring2.printFrom(111);

    cout << endl << "------SECTION 4: TRYING TO PRINT A RING FROM A NEGATIVE KEY------ " << endl;
    ring2.printFrom(-5);

    cout << "TEST CASE 7: FINDING ELEMENTS" << endl;
    cout << endl << "------SECTION 1: TRYING TO FIND AN ELEMENT WHICH DOES NOT EXIST------ " << endl;
    if(ring.find(100) == ring.end()) cout << "Element not found" << endl;

    cout << endl << "------SECTION 2: TRYING TO FIND AN ELEMENT WHICH EXISTS------ " << endl;
    BiRing<int, string>::iterator foundIt;
    foundIt = ring.find(2);
    cout << "Found element: " << foundIt->key << " " << foundIt->info << endl;
    cout << endl << "------SECTION 3: TRYING TO FIND AN ELEMENT WITH A WRONG NUMBER OF OCCURRENCES------ " << endl;
    foundIt = ring.find(4, -2);
    cout << endl << "***************************************************" << endl;


    // EADS TEST 1

    ring2.eraseBetween(3, 9);
    ring2.print();

}




