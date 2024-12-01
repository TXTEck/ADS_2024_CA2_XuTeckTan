#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>
#include "TreeMap.h" 
#include "BinaryTree.h" 

using namespace std;

void populateTreeMap(TreeMap<char, BinaryTree<string>>& treeMap, const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string word;
    while (file >> word) {
        
		//Remove punctuation from the word: https://stackoverflow.com/questions/19138983/c-remove-punctuation-from-string
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());

		// Convert the word to lowercase: https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (!word.empty()) {
            char firstLetter = word[0];

            if (!treeMap.containsKey(firstLetter)) {
                treeMap.put(firstLetter, BinaryTree<string>()); 
            }

            treeMap[firstLetter].add(word);
        }
    }

    file.close();
}


void displayLetters(TreeMap<char, BinaryTree<string>>& treeMap) {
    cout << "Letters found in the file:" << endl;

    char* letters = treeMap.keySet().toArray(); 
    for (int i = 0; i < treeMap.size(); i++) {
        cout << letters[i] << " ";
    }

    cout << endl;
    delete[] letters; 
}

void displayWordsForLetter(TreeMap<char, BinaryTree<string>>& treeMap, char letter) {
    letter = tolower(letter); 

    if (!treeMap.containsKey(letter)) {
        cout << "No words found for the letter '" << letter << "'" << endl;
        return;
    }

    string* words = treeMap[letter].toArray(); 
    cout << "Words for the letter '" << letter << "':" << endl;

    for (int i = 0; i < treeMap[letter].count(); i++) {
        cout << words[i] << endl;
    }

    delete[] words; 
}

int main() {
    TreeMap<char, BinaryTree<string>> treeMap;


    string filename = "../part2.txt";


    populateTreeMap(treeMap, filename);


    displayLetters(treeMap);


    char letter;
    cout << "Enter a letter to view words, or '0' to exit: ";
    while (cin >> letter && letter != '0') {
        displayWordsForLetter(treeMap, letter);
        cout << "Enter another letter, or '0' to exit: ";
    }

    cout << "Goodbye!" << endl;
    return 0;
}

