#include <iostream>
#include "trieTree.h"
#include "pokemon.h"
#include "hashTable.h"
#include <set>
#include <string>
#include <fstream>

using namespace std;

template <typename T>
void searching(T ds) {
    int exit = 0;
    cout << "Would you like to search for a pokemon? (y: 1/n: 0) ";
    cin >> exit;
    while (exit == 1) {
        cout << "What pokemon do you want to search: ";
        string searchedName;
        cin >> searchedName;

        if (ds.search(searchedName) == true) {
            Pokemon pokemon = ds.get(searchedName);
            cout <<"Name: " << pokemon.getName()  << " " << "Elo: " << pokemon.getRank() << " " << "Generation: " << pokemon.getGen()  << endl;
            map<string, float> mapping;
            cout << "Common Teammates" << endl;
            mapping = pokemon.getTeamStats();
            for (auto it = mapping.begin(); it != mapping.end(); it++) {
                cout << it->first << "-> " << it->second << endl;
            }

            cout << "Common Moves" << endl;
            mapping = pokemon.getMoveStats();
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


Pokemon randomPokemon(int i) {
    string name = "pokemon" + to_string(i);
    map<string, float> mapping;
    for (int j = 0; j < 20; j++) {
        string teamName = "teammatePokemon" + to_string(j);
        int raw = rand() % 10000 + 1;
        float random_percent = raw/100.0f;
        mapping[teamName] = random_percent;
    }

    Pokemon pokemon = Pokemon(name, mapping);
    return pokemon;
}


HashTable createHashTable(vector<Pokemon> pokemons, int nodeNumber) {
    HashTable table;
    string name;
    int realPokemon = pokemons.size();
    for (int i = 0; i < nodeNumber; i++) {
        if (realPokemon == 0) {
            Pokemon pokemon = randomPokemon(i - pokemons.size());
            pokemons.push_back(pokemon);
            table.insert(pokemon);
        }else {
            table.insert(pokemons[i]);
            realPokemon--;
        }
    }

    return table;
}

void hashTable(vector<Pokemon> pokemons, int nodeNumber = 100000) {
    cout << "Creating hash table" << endl;
    HashTable table = createHashTable(pokemons, nodeNumber);
    searching(table);
}

TrieTree createTrieTree(int nodeNumber) {
    TrieTree tree;
    vector<Pokemon> pokemons;
    for (int i = 0; i < nodeNumber; i++) {
        Pokemon pokemon = randomPokemon(i);
        pokemons.push_back(pokemon);
        tree.insert(pokemon);
    }
    return tree;
}

void trieTree(vector<string> names, int nodeNumber = 100000) {
    cout << "Creating trieTree" << endl;
    TrieTree tree = createTrieTree(nodeNumber);
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

vector<Pokemon> loadPokemonsFromFile(string fileName) {
    cout << fileName << endl;
    ifstream infile(fileName); // open file for reading

    if (!infile) { // check if file opened successfully
        cerr << "Error: Could not open file " << fileName << endl;
    }

    string line;
    vector<Pokemon> pokemons;
    int lineNumber = 0;
    Pokemon pokemon;
    while (getline(infile, line)) {
        size_t start = 0;
        size_t end= 0;
        vector<string> data;
        if (lineNumber % 3 == 0 ) {
            //If pokemon pokemon is already established then add it to the list of pokemons
            //(the only pokemon not established would be the very first)
            if (lineNumber != 0) {
                pokemons.push_back(pokemon);
                pokemon.empty();
            }

            //Getting the first line of information
            while ((end = line.find(',', start)) != string::npos){
                data.push_back(line.substr(start, end - start));
                start = end + 1;
            }
            data.push_back(line.substr(start, end - start));
            //Get generation number from data
            string genNum = data[1];
            end = genNum.find(':');
            int genNumI = stoi(genNum.substr(end + 1));
            //Get rank number
            string rank = data[2];
            end = rank.find(':');
            int rankI = stoi(rank.substr(end + 1));

            string name = data[0] + to_string(rankI) + to_string(genNumI);
            pokemon.setName(name);
            pokemon.setRank(rankI);
            pokemon.setGen(genNumI);

        }else if (lineNumber % 3 == 1){
            //Gets the second line of information
            map<string, float> moveStats;
            while ((end = line.find(',', start)) != string::npos){
                string moveStat = (line.substr(start, end - start));
                size_t colon = moveStat.find(':');
                string moveName = moveStat.substr(0, colon);
                float stat = stof(moveStat.substr(colon + 1));
                moveStats[moveName] = stat;
                start = end + 1;
            }
            pokemon.setMoveStats(moveStats);

        }else if (lineNumber % 3 == 2) {
            //Gets the third line of information
            map<string, float> teamStats;
            while ((end = line.find(',', start)) != string::npos){
                string teamStat = (line.substr(start, end - start));
                size_t colon = teamStat.find(':');
                string teamName = teamStat.substr(0, colon);
                float stat = stof(teamStat.substr(colon + 1));
                teamStats[teamName] = stat;
                start = end + 1;
            }
            pokemon.setTeamStats(teamStats);
        }
        lineNumber++;


    }
    infile.close();
    return pokemons;
}

int main() {
    int genNum = 1;
    int indexRank = 0;
    int ranks[5] = {0, 2, 3, 4, 5};
    string uses[2] = {"ou", "uu"};
    int indexUse = 0;

    vector<Pokemon> pokemons = loadPokemonsFromFile("data/cppOrganized/AllPokemon-organized.txt");

    int decision;
    cout << "0 for Hash and 1 for tree: ";
    cin >> decision;
    if (decision == 0) {
        hashTable(pokemons);
    }else if (decision == 1) {
        //Replace all of this
        vector<string> names;
        trieTree(names);
    }
    return 0;
}
