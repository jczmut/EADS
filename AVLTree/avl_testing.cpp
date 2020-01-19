#include <iostream>
#include <stdexcept>
#include "avltree.h"
using namespace std;

template class AVLTree<string, int>;

int main(){

    AVLTree<int, int> tree1;
    AVLTree<int, int>::iterator it;

    cout << "***************************************************" << endl;
    cout << "TEST CASE 1: EMPTY TREE" << endl << endl;
    cout << "------SECTION 1: PRINTING------ " << endl;
    tree1.printStructure();
    tree1.printStructure();
    cout << endl << "------SECTION 2: ACCESSING ELEMENTS------ " << endl;
    try{
        tree1.at(3);
    }
    catch(out_of_range& o){
        cerr << o.what() << endl;
    }
    cout << endl << "------SECTION 3: DELETING ELEMENTS------ " << endl;
    try{
        tree1.erase(it);    // 'it' does not point to anything
    }
    catch(out_of_range& f){
        cerr << f.what() << endl;
    }
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 2: AVL TREE INSERTION" << endl;
    cout << endl << "------SECTION 1: INSERTING SOME ELEMENTS------ " << endl;
    tree1.insert(1, 2);
    tree1.insert(5, 3);
    tree1.insert(3, 6);
    tree1.insert(5, 6);
    tree1.insert(8, 2);
    tree1.insert(14, 6);
    tree1.insert(4, 0);
    tree1.insert(0, 0);
    tree1.insert(9, 6);
    tree1.printStructure();
    cout << endl;
    cout << "PRINTING IN PREORDER:" << endl;
    tree1.printPreorder();
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 3: AVL TREE DELETION" << endl;
    cout << endl << "------SECTION 1: DELETING------ " << endl;
    AVLTree<int, int>::iterator it2;
    AVLTree<int, int>::iterator it3;
    it2 = tree1.find(5);
    tree1.erase(it2);
    cout << "After deleting key 5 (current root):" << endl;
    tree1.printStructure();

    cout << endl << "------SECTION 2: CLEARING ENTIRE TREE------ " << endl;
    tree1.clear();
    cout << endl << "PRINTING THE STRUCTURE:" << endl;
    tree1.printStructure();
    cout << "PRINTING IN PREORDER:" << endl;
    tree1.printPreorder();
    cout << endl;
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 4: COPY CONSTRUCTOR" << endl;
    cout << endl << "------SECTION 1: CREATING THE ORIGINAL TREE AND THE COPIED ONE------ " << endl;
    tree1.insert(7, 2);
    tree1.insert(5, 3);
    tree1.insert(3, 6);
    tree1.insert(20, 6);
    tree1.insert(8, 2);
    tree1.insert(14, 6);
    tree1.insert(4, 0);
    tree1.insert(0, 9);
    tree1.insert(9, 6);
    AVLTree<int, int> tree2(tree1);
    tree2.printStructure();

    cout << endl << "------SECTION 2: DELETING SOME ELEMENTS FROM THE ORIGINAL TREE AND THE COPIED ONE------ " << endl;
    tree2.erase(tree2.find(14));
    cout << endl << "Tree2 after deleting key 14:" << endl;
    tree2.printStructure();
    tree1.erase(tree1.find(5));
    cout << "Tree1 after deleting key 5:" << endl;
    tree1.printStructure();
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 5: ASSIGNMENT OPERATOR" << endl;
    cout << endl << "------SECTION 1: CREATING TWO EMPTY NEW TREES AND FILLING UP WITH SOME DATA------ " << endl;
    AVLTree<int, int> tree3;
    AVLTree<int, int> tree4;
    tree3.insert(6, 0);
    tree3.insert(2, 2);
    tree3.insert(8, 11);
    tree3.insert(3, 6);

    tree4.insert(7, -100);
    tree4.insert(9, 3);
    tree4.insert(9, 6);
    cout << endl << "Tree3:" << endl;
    tree3.printStructure();
    cout << "preorder:  ";
    tree3.printPreorder();
    cout << endl << "Tree4:" << endl;
    tree4.printStructure();
    cout << "preorder:  ";
    tree4.printPreorder();

    cout << endl << "------SECTION 2: OVERWRITING tree4 WITH DATA FROM tree3 USING ASSIGNMENT OPERATOR------ " << endl;
    tree4 = tree3;
    cout << endl << "Tree3:" << endl;
    tree3.printStructure();
    cout << "preorder:  ";
    tree3.printPreorder();
    cout << endl << "Tree4:" << endl;
    tree4.printStructure();
    cout << "preorder:  ";
    tree4.printPreorder();
    cout << endl << "***************************************************" << endl;

    cout << "TEST CASE 5: RANDOM TESTS" << endl;
    cout << endl << "------SECTION 1: FUNCTION AT------ " << endl;
    cout << "---negative index---" << endl;
    try{
        tree4.at(-5);
    }
    catch(out_of_range& e){
        cerr << e.what() << endl;
    }
    cout << "---index bigger than number of nodes---" << endl;
    try{
        tree4.at(50);
    }
    catch(out_of_range& a){
        cerr << a.what() << endl;
    }
    cout << endl << "------SECTION 2: ITERATORS------ " << endl;
    AVLTree<int, int>::iterator it4;
    cout << "---incrementing empty iterator---" << endl;
    try{
        it4++;
    }
    catch(logic_error& l){
        cerr << l.what() << endl;
    }
    cout << "---decrementing empty iterator---" << endl;
    try{
        --it4;
    }
    catch(logic_error& k){
        cerr << k.what() << endl;
    }

    cout << endl << "------SECTION 4: COMPARING TREES------ " << endl;
    if(tree3 == tree4) cout << "tree3 == tree4" << endl;
    else cout << "tree3 != tree4" << endl;



}