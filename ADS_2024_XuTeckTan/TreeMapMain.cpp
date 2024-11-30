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





