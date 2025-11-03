#include <iostream>
#include "trieTree.h"
#include "pokemon.h"
#include "hashTable.h"
#include <set>
#include <string>
#include <fstream>

using namespace std;


HashTable createHashTable(int nodeNumber) {
    HashTable table;
    vector<string> names;
    vector<Pokemon> pokemons;

    string regular_name = "pokemon";
    string name;
    for (int i = 0; i < nodeNumber; i++) {
        name = regular_name + to_string(i);
        names.push_back(name);
        map<string, float> mapping;
        for (int j = 0; j < 10; j++) {
            string teamName = "teammatePokemon" + to_string(j);
            int raw = rand() % 10000 + 1;
            float random_percent = raw/100.0f;
            mapping[teamName] = random_percent;
        }

        Pokemon pokemon = Pokemon(name, mapping);
        pokemons.push_back(pokemon);
        table.insert(pokemon);
    }
    return table;
}

void hashTable() {
    cout << "Creating hash table" << endl;
    HashTable table = createHashTable(100000);
    int exit = 0;
    cout << "Would you like to search for a pokemon? (y: 1/n: 0) ";
    cin >> exit;
    while (exit == 1) {
        cout << "What pokemon do you want to search: ";
        string searchedName;
        cin >> searchedName;

        if (table.search(searchedName) == true) {
            Pokemon pokemon = table.get(searchedName);
            cout << pokemon.getName() << endl;
            map<string, float> mapping;
            mapping = pokemon.getTeamStats();
            for (auto it = mapping.begin(); it != mapping.end(); it++) {
                cout << it->first << "-> " << it->second << endl;
            }
        }else {
            cout << "No such pokemon exists" << endl;
        }

        cout << "Would you like to search for a pokemon again? (y: 1/n: 0) ";
        cin >> exit;
    }
}

TrieTree createTrieTree(int nodeNumber) {
    TrieTree tree;
    vector<string> names;
    vector<Pokemon> pokemons;
    for (int i = 0; i < nodeNumber; i++) {
        string name = "pokemon" + to_string(i);
        names.push_back(name);
        map<string, float> mapping;
        for (int j = 0; j < 20; j++) {
            string teamName = "teammatePokemon" + to_string(j);
            int raw = rand() % 10000 + 1;
            float random_percent = raw/100.0f;
            mapping[teamName] = random_percent;
        }

        Pokemon pokemon = Pokemon(name, mapping);
        pokemons.push_back(pokemon);
        tree.insert(pokemon);
    }
    return tree;
}

void trieTree() {
    cout << "Creating trieTree" << endl;
    TrieTree tree = createTrieTree(100000);
    int exit = 0;
    cout << "Would you like to search for a pokemon? (y: 1/n: 0) ";
    cin >> exit;
    while (exit == 1) {
        cout << "What pokemon do you want to search: ";
        string searchedName;
        cin >> searchedName;

        if (tree.search(searchedName) == true) {
            Pokemon pokemon = tree.get(searchedName);
            cout << pokemon.getName() << endl;
            map<string, float> mapping;
            mapping = pokemon.getTeamStats();
            for (auto it = mapping.begin(); it != mapping.end(); it++) {
                cout << it->first << "-> " << it->second << endl;
            }
        }else {
            cout << "No such pokemon exists" << endl;
        }

        cout << "Would you like to search for a pokemon again? (y: 1/n: 0) ";
        cin >> exit;
    }
}


void searchAndMaking() {
    int decision;
    cout << "0 for Hash and 1 for tree: ";
    cin >> decision;
    if (decision == 0) {
        hashTable();
    }else if (decision == 1) {
        trieTree();
    }
}

int main() {
    int genNum = 1;
    int indexRank = 0;
    int ranks[5] = {0, 2, 3, 4, 5};
    string uses[2] = {"ou", "uu"};
    int indexUse = 0;
    string dataPath = "data/cppOrganized/";
    string fileName = dataPath + "AllPokemon-organized.txt";

    cout << fileName << endl;
    ifstream infile(fileName); // open file for reading

    if (!infile) { // check if file opened successfully
        cerr << "Error: Could not open file " << fileName << endl;
        return 1;
    }

    cout << "File opened successfully!" << endl;

    string line;
    while (getline(infile, line)) {
        cout << line << endl; // process the file line by line
    }

    infile.close();
    return 0;
}
