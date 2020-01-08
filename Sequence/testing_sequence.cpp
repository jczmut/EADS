#include <iostream>
#include "sequence.h"
using namespace std;

int main(){

    Sequence<int> *sequence = new Sequence<int>;

    cout << "***************************************************" << endl;
    cout << "TEST CASE 1: EMPTY LIST" << endl << endl;
    cout << "------SECTION 1: PRINTING------ " << endl;
    sequence->print();
    sequence->printNode(1);
    sequence->printXNodes(4);

    cout << endl << "------SECTION 2: REMOVING------ " << endl;
    sequence->remove(1);
    sequence->removeAllOccurrences(2);
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 2: INSERTING" << endl << endl;
    cout << endl << "------SECTION 1: ADDING TO THE BEGINNING------ " << endl;
    sequence->insertFirst(2);
    sequence->insertFirst(1);
    sequence->insertFirst(1);
    sequence->print();
    cout << endl << "------SECTION 2: ADDING TO THE END------ " << endl;
    sequence->insertLast(3);
    sequence->insertLast(4);
    sequence->insertLast(3);
    sequence->insertLast(3);
    sequence->print();
    cout << endl << "------SECTION 3: ADDING IN THE MIDDLE------ " << endl;
    sequence->insertAfter(3, 2);
    sequence->insertAfter(1, 1);
    sequence->insertAfter(3, 1, 2);
    sequence->insertAfter(5, 3, 2);
    sequence->insertAfter(6, 3, 3);
    sequence->print();
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 3: REMOVING" << endl << endl;
    cout << endl << "------SECTION 1: REMOVING FROM THE BEGINNING------ " << endl;
    sequence->remove(1);
    sequence->print();
    cout << endl << "------SECTION 2: REMOVING FROM THE END------ " << endl;
    sequence->remove(3, 5);
    sequence->print();
    cout << endl << "------SECTION 3: REMOVING FROM THE MIDDLE------ " << endl;
    sequence->remove(6);
    sequence->print();
    cout << endl << "------SECTION 4: REMOVING SOME OF THE OCCURRENCES------ " << endl;
    sequence->removeFromTo(3, 2, 4);
    sequence->print();
    cout << endl << "------SECTION 5: REMOVING ALL THE OCCURRENCES OF SOME NODE------ " << endl;
    sequence->removeAllOccurrences(1);
    sequence->print();
    cout << endl << "------SECTION 6: CLEARING AN ENTIRE LIST------ " << endl;
    Sequence<int>* sequenceToClear = new Sequence<int>();
    sequenceToClear->insertLast(1);
    sequenceToClear->insertLast(2);
    sequenceToClear->insertLast(3);
    cout << "sequenceToClear:" << endl;
    sequenceToClear->print();
    sequenceToClear->clear();
    sequenceToClear->print();
    delete sequenceToClear;
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 4: COPY CONSTRUCTOR" << endl << endl;

    cout << endl << "------SECTION 1: CREATING THE COPIED SEQUENCE------ " << endl;
    Sequence<int> *copiedSequence = new Sequence<int>(*sequence);
    cout << "copiedSequence (identical to sequence): " << endl;
    copiedSequence->print();
    cout << endl << "------SECTION 2: TRANSFORMING THE COPIED SEQUENCE------ " << endl;
    copiedSequence->insertLast(8);
    copiedSequence->insertFirst(1);
    copiedSequence->remove(2);
    copiedSequence->print();
    cout << endl << "------SECTION 3: COMPARING ORIGINAL AND COPIED SEQUENCES------ " << endl;
    if(copiedSequence == sequence) cout << "copiedSequence == sequence" << endl;
    else if(copiedSequence != sequence) cout << "copiedSequence != sequence" << endl;
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 5: ASSIGNMENT OPERATOR" << endl << endl;
    cout << endl << "------SECTION 1: CREATING TWO EMPTY NEW SEQUENCES AND FILLING ONE UP WITH SOME DATA------ " << endl;
    Sequence<int> *newSequence1 = new Sequence<int>();
    Sequence<int> *newSequence2 = new Sequence<int>();
    newSequence1->print();
    newSequence2->print();
    newSequence1->insertFirst(4);
    newSequence1->insertFirst(7);
    newSequence1->insertFirst(0);
    newSequence1->insertFirst(4);
    cout << "newSequence1:" << endl;
    newSequence1->print();
    cout << endl << "------SECTION 2: ASSIGNING THE EMPTY SEQUENCE TO THE ONE WITH DATA------ " << endl;
    *newSequence2 = *newSequence1;
    cout << "newSequence1:" << endl;
    newSequence1->print();
    cout << "newSequence2:" << endl;
    newSequence2->print();
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 6: NUMBER OF OCCURRENCES" << endl << endl;
    cout << "number of occurrences of 3 in newSequence1 is " << newSequence1->numberOfOccurrences(3) << endl;
    cout << "number of occurrences of 4 in newSequence1 is " << newSequence1->numberOfOccurrences(4) << endl;
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 7: PRINTING X ELEMENTS" << endl << endl;
    cout << endl << "------SECTION 1: TRYING TO PRINT -7 ELEMENTS------ " << endl;
    newSequence1->printXNodes(-7);
    cout << endl << "------SECTION 2: TRYING TO PRINT 5 ELEMENTS WHILE LIST HAS ONLY 4------ " << endl;
    newSequence1->printXNodes(5);
    cout << endl << "------SECTION 1: PRINTING 2 ELEMENTS OUT OF 4------ " << endl;
    newSequence1->printXNodes(2);
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 7: FINDING ELEMENTS" << endl << endl;
    cout << endl << "------SECTION 1: TRYING TO FIND AN ELEMENT WHICH DOES NOT EXIST------ " << endl;
    if(newSequence1->find(10)) cout << "Element found" << endl;
    else cout << "Element not found" << endl;
    cout << endl << "------SECTION 2: TRYING TO FIND AN ELEMENT WHICH EXISTS------ " << endl;
    if(newSequence1->find(0)) cout << "Element found" << endl;
    else cout << "Element not found" << endl;
    cout << endl << "------SECTION 3: TRYING TO FIND AN ELEMENT WITH A WRONG NUMBER OF OCCURRENCES------ " << endl;
    newSequence1->find(4, -2);
    cout << endl << "***************************************************" << endl;

    // REVERSE PRINTING USING RECURSION

    sequence->insertFirst(5);
    sequence->insertFirst(5);

    cout << "REVERSE PRINTING" << endl;
    cout << "sequence:" << endl;
    sequence->print();
    cout << "sequence reversed:" << endl;
    sequence->reversePrint();

    cout << "REVERSE PRINTING FROM LAST KEY" << endl;
    sequence->reversePrintFLK(5);

    cout << "REVERSE PRINTING TO LAST KEY" << endl;
    sequence->reversePrintTLK(5);

    // INSERTING TWO NEW NODES BETWEEN SPECIFIED TWO EXISTING NODES
    Sequence<double>* doubleSeq = new Sequence<double>();
    doubleSeq->insertLast(1);
    doubleSeq->insertLast(2);
    doubleSeq->insertLast(3);
    doubleSeq->insertLast(15);
    doubleSeq->insertLast(13);
    doubleSeq->insertLast(9);
    doubleSeq->insert(2, 3, 4, 4);
    doubleSeq->print();






    delete sequence;
    delete copiedSequence;
    delete newSequence1;
    delete newSequence2;
}