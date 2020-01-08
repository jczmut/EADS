#include <iostream>
#include "counter.h"
using namespace std;

int main(){

    Counter<int> *counter = new Counter<int>;

    cout << "***************************************************" << endl;
    cout << "TEST CASE 1: EMPTY LIST" << endl << endl;
    cout << "------SECTION 1: PRINTING------ " << endl;
    counter->printCounter();
    counter->printNode(1);
    counter->printXCountedNodes(3);
    counter->printXCountedNodes(-10);
    cout << endl << "------SECTION 2: REMOVING------ " << endl;
    counter->removeKey(2);
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 2: INSERTING" << endl << endl;
    cout << endl << "------SECTION 1: ADDING UNIQUE KEYS------ " << endl;
    counter->addKey(1);
    counter->addKey(6);
    counter->addKey(4);
    counter->addKey(2);
    counter->addKey(-1);
    counter->printCounter();
    cout << endl << "------SECTION 2: ADDING KEYS WHICH ALREADY EXIST------ " << endl;
    counter->addKey(4);
    counter->addKey(4);
    counter->addKey(1);
    counter->addKey(4);
    counter->addKey(6);
    counter->addKey(6);
    counter->addKey(6);
    counter->printCounter();
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 3: REMOVING" << endl << endl;
    cout << endl << "------SECTION 1: REMOVING KEYS WHICH APPEARED MORE THAN ONCE------ " << endl;
    counter->removeKey(4);
    counter->removeKey(1);
    counter->printCounter();
    cout << endl << "------SECTION 2: REMOVING KEYS WHICH APPEARED ONCE------ " << endl;
    counter->removeKey(2);
    counter->printCounter();
    cout << endl << "------SECTION 3: REMOVING A WHOLE NODE------ " << endl;
    counter->removeNode(6);
    counter->printCounter();
    cout << endl << "------SECTION 4: CLEARING AN ENTIRE LIST------ " << endl;
    Counter<int> *counterToClear = new Counter<int>();
    counterToClear->addKey(1);
    counterToClear->addKey(1);
    counterToClear->addKey(2);
    counterToClear->addKey(3);
    counterToClear->printCounter();
    counterToClear->clear();
    counterToClear->printCounter();
    delete counterToClear;

    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 4: COPY CONSTRUCTOR" << endl << endl;

    cout << endl << "------SECTION 1: CREATING THE COPIED COUNTER------ " << endl;
    Counter<int> *copiedCounter = new Counter<int>(*counter);
    cout << "copiedCounter (identical to counter): " << endl;
    copiedCounter->printCounter();
    cout << endl << "------SECTION 2: TRANSFORMING THE COPIED counter------ " << endl;
    copiedCounter->addKey(5);
    copiedCounter->addKey(4);
    copiedCounter->printCounter();
    cout << endl << "------SECTION 3: COMPARING ORIGINAL AND COPIED COUNTERS------ " << endl;
    if(copiedCounter == counter) cout << "copiedCounter == counter" << endl;
    else if(copiedCounter != counter) cout << "copiedCounter != counter" << endl;
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 5: ASSIGNMENT OPERATOR" << endl << endl;
    cout << endl << "------SECTION 1: CREATING TWO EMPTY NEW COUNTERS AND FILLING ONE UP WITH SOME DATA------ " << endl;
    Counter<int> *newCounter1 = new Counter<int>();
    Counter<int> *newCounter2 = new Counter<int>();
    newCounter1->printCounter();
    newCounter2->printCounter();
    newCounter1->addKey(4);
    newCounter1->addKey(7);
    newCounter1->addKey(0);
    newCounter1->addKey(4);
    cout << "newCounter1:" << endl;
    newCounter1->printCounter();
    cout << endl << "------SECTION 2: ASSIGNING THE EMPTY COUNTER TO THE ONE WITH DATA------ " << endl;
    *newCounter2 = *newCounter1;
    cout << "newCounter1:" << endl;
    newCounter1->printCounter();
    cout << "newCounter2:" << endl;
    newCounter2->printCounter();
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 6: PRINTING X ELEMENTS" << endl << endl;
    cout << endl << "------SECTION 1: TRYING TO PRINT -1 ELEMENTS------ " << endl;
    newCounter1->printXCountedNodes(-1);
    cout << endl << "------SECTION 2: TRYING TO PRINT 7 ELEMENTS WHILE LIST HAS ONLY 4------ " << endl;
    newCounter1->printXCountedNodes(7);
    cout << endl << "------SECTION 3: PRINTING THE FIRST 3 ELEMENTS OUT OF 4------ " << endl;
    newCounter1->printXCountedNodes(3);
    cout << endl << "------SECTION 4: PRINTING THE FIRST 3 ELEMENTS FROM COUNTER'S SEQUENCE------ " << endl;
    newCounter1->printXNotCountedNodes(3);
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 7: FINDING ELEMENTS" << endl << endl;
    cout << endl << "------SECTION 1: TRYING TO FIND AN ELEMENT WHICH DOES NOT EXIST------ " << endl;
    if(newCounter1->find(10)) cout << "Element found" << endl;
    else cout << "Element not found" << endl;
    cout << endl << "------SECTION 2: TRYING TO FIND AN ELEMENT WHICH EXISTS------ " << endl;
    if(newCounter1->find(0)) cout << "Element found" << endl;
    else cout << "Element not found" << endl;
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 8: PRINTING CONTENTS OF COUNTER'S INSIDE SEQUENCE OBJECT" << endl << endl;
    newCounter1->printSequence();
    cout << endl << "***************************************************" << endl;
    
    delete counter;
    delete copiedCounter;
    delete newCounter1;
    delete newCounter2;
}