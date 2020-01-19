#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <stdexcept>
#include <map>
#include "avltree.h"
using namespace std;
using namespace std::chrono;

template class AVLTree<string, int>;

int main()
{
    // AVL TREE

    AVLTree<string, int> counter;
    AVLTree<string, int>::iterator it;

    ifstream file;
    file.open("The bible.txt");

    // getting starting timepoint 
    auto start = high_resolution_clock::now(); 

    // reading the file word by word and update counter
    string word;
    while (file >> word) {
        /*for(auto i=word.begin(); i!=word.end(); ++i){
            if((*i >= 32 && *i < 39) || (*i > 39 && *i <= 64) || (*i >= 91 && *i <= 96) || (*i >= 123 && *i <= 126)) i = word.erase(i);
            if(i == word.end()) break;
        }*/
        if((word[0] >= 32 && word[0] <= 64) || (word[0] >= 91 && word[0] <= 96) || (word[0] >= 123 && word[0] <= 126)) word.erase(0);
        if((word[word.length()-1] >= 32 && word[word.length()-1] <= 64) || (word[word.length()-1] >= 91 && word[word.length()-1] <= 96) || (word[word.length()-1] >= 123 && word[word.length()-1] <= 126)) word.erase(word.length()-1);
        if((word[word.length()-2] >= 32 && word[word.length()-2] <= 64) || (word[word.length()-2] >= 91 && word[word.length()-2] <= 96) || (word[word.length()-2] >= 123 && word[word.length()-2] <= 126)) word.erase(word.length()-2);
       
        it = counter.find(word);

        if (it != counter.end()){
            it->info++;
        } 
        else counter.insert(word, 1);
    }

    file.close();

    // listing the encountered words and their occurrences
    for (it = counter.begin(); it != counter.end(); ++it){
        cout << it->key << " " << it->info << endl;
    }
        
    // printing the number of unique words
    cout << "Total number of unique words: " << counter.size() << endl;

    // getting ending timepoint 
    auto stop = high_resolution_clock::now(); 
  
    auto duration = duration_cast<microseconds>(stop - start);
  
    cout << "Time taken by the AVLTree: " << duration.count() << " microseconds" << endl; 


    //***********************************************************
    // STL MAP
    map<string, int> dictionary;
    map<string, int>::iterator it2;

    file.open("The bible.txt");

    auto start2 = high_resolution_clock::now();

    string word2;
    while (file >> word2) {

        /*for(auto i=word.begin(); i!=word.end(); ++i){
            if((*i >= 32 && *i < 39) || (*i > 39 && *i <= 64) || (*i >= 91 && *i <= 96) || (*i >= 123 && *i <= 126)) i = word.erase(i);
            if(i == word.end()) break;
        }*/
        if((word2[0] >= 32 && word2[0] <= 64) || (word2[0] >= 91 && word2[0] <= 96) || (word2[0] >= 123 && word2[0] <= 126)) word2.erase(0);
        if((word2[word2.length()-1] >= 32 && word2[word2.length()-1] <= 64) || (word2[word2.length()-1] >= 91 && word2[word2.length()-1] <= 96) || (word2[word2.length()-1] >= 123 && word2[word2.length()-1] <= 126)) word2.erase(word2.length()-1);
        if((word2[word2.length()-2] >= 32 && word2[word2.length()-2] <= 64) || (word2[word2.length()-2] >= 91 && word2[word2.length()-2] <= 96) || (word2[word2.length()-2] >= 123 && word2[word2.length()-2] <= 126)) word2.erase(word2.length()-2);

            dictionary[word2]++;
        
    }

    file.close();

    // listing the words and their occurrences
    for(auto it2 = dictionary.cbegin(); it2 != dictionary.cend(); ++it2){
        std::cout << (*it2).first << " " << (*it2).second << " " << "\n";
    }

    // printing the number of unique words
    cout << "Total number of unique words: " << counter.size() << endl;

    auto stop2 = high_resolution_clock::now(); 
  
    auto duration2 = duration_cast<microseconds>(stop2 - start2);

    cout << endl << "Time taken by the AVLTree: " << duration.count() << " microseconds" << endl; 
  
    cout << "Time taken by the map: " << duration2.count() << " microseconds" << endl;

}