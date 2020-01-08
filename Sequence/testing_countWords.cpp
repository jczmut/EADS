#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "counter.h"
using namespace std;


int countWords(Counter<string>& counter, istream& source){

    string key;
    stringstream ss;

    while(source){
        ss.put(source.get());
    }

    for(int i=0; i<ss.str().size(); i++){
        if((ss.str()[i] >= 'A' && ss.str()[i] <= 'Z') || ss.str()[i] >= 'a' && ss.str()[i] <= 'z'){
            key += ss.str()[i];
            continue;
        }
        if(char(ss.str()[i]) == 39){
            if((ss.str()[i-1] >= 'A' && ss.str()[i] <= 'Z') || ss.str()[i] >= 'a' && ss.str()[i] <= 'z'){
                key += ss.str()[i];
                continue;
            }

        }
        else{
            if(key.size() > 0){
                for(int i=0; i<key.size(); i++){  // switching uppercase letters to lowercase
                    if(key[i] >= 'A' && key[i] <= 'Z'){
                    key[i] = key[i] + 32;
                    }
                }
                counter.addKey(key); 
                key.clear(); 
            }  
            else continue;
        }  
    }
    counter.printCounter();
    return counter.getSize();
}

int main(){

    Counter<string> counter;

    cout << "How would you like to test the countWords function?" << endl;
    cout << "Input 'f' for file or 'c' for console. " << endl;
    string decision;
    while(getline(cin, decision)){
        if(decision == "f"){
            cout << "Input from the file:" << endl;
            ifstream f;
            f.open("text.txt");
            istream& s = f;
            countWords(counter, s);
            f.close();
            break;
        }
        else if(decision == "c"){
            cout << "Input from the console:" << endl;
            string properSource;
            string source;
            while(getline(cin, source)){
        
                properSource += '\n';
                properSource += source;
                string answer;
                cout << "Do you want to continue? 'y'/'n' ";
                getline(cin, answer);
                if(answer == "y") continue;
                else if(answer == "n") break;
                else{
                    cout << "Wrong input. Remember? 'y' for yes, 'n' for no." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
            }
        }
        stringstream ss(properSource);
        countWords(counter, ss);
        break;
    }
    else{
        cout << "Wrong input. Remember? 'f' for file, 'c' for console." << endl;
        cin.clear();
        //cin.ignore(10000, '\n');
    }
    }
    
    


}
    