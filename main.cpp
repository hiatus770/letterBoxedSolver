#include <iostream> 
#include <string> 
#include <vector> 
#include <set>
#include <fstream> 
#include <cmath> 
#include <map> 

char letters[] = {'h', 'l', 'u', 'a', 'c', 'o', 'y', 'r', 'n', 'd', 'p', 'g'}; 

#include <chrono> 



int getLetterIndex(char letter){
    for (int i = 0; i < sizeof(letters)/sizeof(char); i++){
        if (letter == letters[i]){
            return i; 
        }
    }
    return -1; 
}

/**
 * @brief Checks if two letters are in the same tiple for validity, if this is false then you pooped up 
 * 
 * @param letter1 
 * @param letter1 
 * @return true 
 * @return false 
 */
bool isSameTriplet(char letter1, char letter2){
    if (floor(getLetterIndex(letter1)/3) == floor(getLetterIndex(letter2)/3)){
        return true; 
    }
    return false; 
}

bool isValidString(std::string s){
    for(int i = 0; i < s.length()-1; i++){
        if (isSameTriplet(s[i], s[i+1])){
            return false; 
        }
    }
    return true; 
}

bool checkSequence(std::string s){
    int check[] = {0,0,0,0,0,0,0,0,0,0,0,0}; 
    for (int i = 0; i < s.length(); i++){
        if (check[getLetterIndex(s[i])] == 0){
            check[getLetterIndex(s[i])] = 1; 
        }
    }
    for (int i = 0; i < 12; i++){
        if (check[i] == 0){
            return false; 
        }
    }
    return true; 
}

bool isValidLetter(char letter){ 
    for (char l : letters){
        if (l == letter){
            return true; 
        } 
    }
    return false; 
}

int main(){

    
    
    std::map<char, std::vector<std::string>> firstLetterLists; 

    std::ifstream wordFile("words.txt");

    std::set<std::string> wordSetFile; 
    std::set<std::string> wordSet; 

    auto start = std::chrono::high_resolution_clock::now(); 

    if (wordFile.is_open()){
        while (wordFile.good()){
            std::string iptString; 
            wordFile >> iptString; 
            wordSetFile.insert(iptString); 
        }
    } 

    // First Filter, remove all words that aren't made up solely of the special letters of the dayt
    for (std::string element : wordSetFile){
        bool toAdd = true; ; 
        for (char l : element){
            if (!isValidLetter(l)){
                toAdd = false; 
            }
        }
        if (toAdd){
            wordSet.insert(element); 
        }   
    }

    wordSetFile = wordSet; 

    wordSet.clear(); 

    // Second filter only generates valid words 
    for (std::string element : wordSetFile){
        if (isValidString(element)){
            wordSet.insert(element); 
            firstLetterLists[element[0]].push_back(element); 
        }
    }

    // Now start generating the pairs 
    for (auto element1 : wordSet){
        for (auto element2 : firstLetterLists[element1[element1.length()-1]]){
            if (checkSequence(element1 + element2)){
                std::cout << element1 << " " << element2 << std::endl; 
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);


    std::cout << "GENERATED " << wordSet.size() << " WORDS IN " << duration.count()/1000 << "MS\n"; 
    std::cout << getLetterIndex('h'); 

    // Filter out words that aren't possible 


}