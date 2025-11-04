#include <iostream>
#include "trieTree.h"
#include "pokemon.h"
#include "hashTable.h"
#include <set>
#include <string>
#include <fstream>
#include <regex>
#include <cctype>

using namespace std;



static map<string, float> parsePercentLine(const string &line, const string &separator) {
    map<string, float> mapping;
    if (line.rfind(separator, 0) != 0) return mapping;
    string values = line.substr(separator.size());

    static const regex kv(R"(\s*([^:,]+)\s*:\s*([0-9]*\.?[0-9]+)\s*%?)");

    auto begin = sregex_iterator(values.begin(), values.end(), kv);
    auto end = sregex_iterator();
    for (auto it = begin; it != end; it++) {
        string key = (*it)[1].str();
        float pct = stof((*it)[2].str());
        mapping[key] = pct;
    }
    return mapping;
}

template <typename T>
static void loadFromTxt(T &structure, const string &fileName, int genFilter, int floorFilter) {
    ifstream in(fileName);
    if (!in.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return;
    }
    string line, name;
    int genNum = 0, minRank = 0;
    map<string, float> moves, teammates, items, spreads, tera, abilities;

    auto flushPokemon = [&]() {
        if (name.empty()) return;

        auto trim = [](string s) -> string { //gets rid of spaces
            while (!s.empty() && isspace((unsigned char)s.back())) s.pop_back();
            while (!s.empty() && isspace((unsigned char)s.front())) s.erase(s.begin());
            return s;
        };

        //gets rid of trailing commas
        if (!name.empty() && name.back()==',') name.pop_back();
        name = trim(name);

        if ((genFilter == -1 || genNum == genFilter) &&
            (minRank == floorFilter)) {
            Pokemon mon(name, teammates, genNum, minRank);
            mon.setTopMoves(moves);
            mon.setTopItems(items);
            mon.setTopSpreads(spreads);
            mon.setTopTera(tera);
            mon.setAbilities((abilities));
            mon.setGenNum(genNum);
            mon.setMinRank(minRank);

            structure.insert(mon);
            cout << "Loaded: " << name << " (" << genNum << ")" << endl;
        }

        name.clear(); genNum = 0; minRank = 0;
        moves.clear(); teammates.clear(); items.clear(); spreads.clear(); tera.clear(); abilities.clear();

    };

    static const regex header(R"(^\s*([^,]+)\s*,\s*Generation:\s*(\d+)\s*,\s*lowestRank:\s*(\d+))"); //parses
    //first pokemon line

    while (getline(in, line)) {
        smatch match;
        if (regex_search(line, match, header)) {
            flushPokemon();
            name = match[1].str();
            genNum = stoi(match[2].str());
            minRank = stoi(match[3].str());
            continue;
        }
        if (line.rfind("Moves:", 0) == 0) {moves = parsePercentLine(line, "Moves:"); continue;}
        if (line.rfind("Teammates:", 0) == 0) {teammates = parsePercentLine(line, "Teammates:"); continue;}
        if (line.rfind("Top Items:", 0) == 0) {items = parsePercentLine(line, "Top Items:"); continue;}
        if (line.rfind("Top Spreads:", 0) == 0) {spreads = parsePercentLine(line, "Top Spreads:"); continue;}
        if (line.rfind("Top Tera:", 0) == 0) {tera = parsePercentLine(line, "Top Tera:"); continue;}
        if (line.rfind("Abilities:", 0) == 0) {abilities = parsePercentLine(line, "Abilities:");}
    }
    flushPokemon();
}

static string trim(string extra) {
    auto isSpace = [](unsigned char space){return isspace(space); };
    extra.erase(extra.begin(), find_if(extra.begin(), extra.end(),
        [&](unsigned char space) {return !isSpace(space); }));
    extra.erase(find_if(extra.rbegin(), extra.rend(), [&](unsigned char space)
        {return !isSpace(space); }).base(), extra.end());
    return extra;
}


void hashTable(int gen, int floor) {
    cout << "Creating hash table" << endl;
    HashTable table;
    const string fileName = "data/cppOrganized/AllPokemon-organized.txt";
    loadFromTxt(table, fileName, gen, floor);
    cin.ignore(10000, '\n');

    auto decideYN = [&](const string &line) ->bool {
        cout << line;
        string s;
        if (!getline(cin, s)) return false;
        s = trim(s);
        return !s.empty() && (s[0]=='1' || s[0]=='y' || s[0]=='Y');
    };

    if (!decideYN("Would you like to search for a pokemon? (y: 1/n: 0) ")) return;

    for (;;) {
        cout << "What pokemon do you want to search: ";
        string searchedName;
        if (!getline(cin, searchedName)) break;
        searchedName = trim(searchedName);
        if (searchedName.empty()) {
            cout << "Enter a name" << endl;
            continue;
        }
        if (table.search(searchedName) == true) {
            Pokemon pokemon = table.get(searchedName);
            cout << pokemon.getName() << endl;
            cout << "Generation " << pokemon.getGenNum() << endl;
            cout << "Skill Floor " << pokemon.getMinRank() << endl;
            map<string, float> teams;
            teams = pokemon.getTeamStats();
            for (auto it = teams.begin(); it != teams.end(); it++) {
                cout << it->first << "-> " << it->second << endl;
            }
            map<string, float> ability;
            ability = pokemon.getAbilities();
            for (auto it = ability.begin(); it != ability.end(); it++) {
                cout << it->first << "-> " << it->second << endl;
            }
            map<string, float> moves;
            moves = pokemon.getTopMoves();
            for (auto it = moves.begin(); it != moves.end(); it++) {
                cout << it->first << "-> " << it->second << endl;
            }
            map<string, float> items;
            items = pokemon.getTopItems();
            for (auto it = items.begin(); it != items.end(); it++) {
                cout << it->first << "-> " << it->second << endl;
            }
            map<string, float> spreads;
            spreads = pokemon.getTopSpreads();
            for (auto it = spreads.begin(); it != spreads.end(); it++) {
                cout << it->first << "-> " << it->second << endl;
            }
            map<string, float> tera;
            tera = pokemon.getTopTera();
            for (auto it = tera.begin(); it != tera.end(); it++) {
                cout << it->first << "-> " << it->second << endl;
            }
        }else {
            cout << "No such pokemon exists" << endl;
        }
        if (!decideYN("Search again with the same constraints? (y:1/n: 0) ")) break;
    }
}


void trieTree(int gen, int floor) {
    cout << "Creating trie tree" << endl;
    TrieTree tree;
    const string fileName = "data/cppOrganized/AllPokemon-organized.txt";
    loadFromTxt(tree, fileName, gen, floor);
    cin.ignore(10000, '\n');

    auto decideYN = [&](const string &line) ->bool {
        cout << line;
        string s;
        if (!getline(cin, s)) return false;
        s = trim(s);
        return !s.empty() && (s[0]=='1' || s[0]=='y' || s[0]=='Y');
    };

    if (!decideYN("Would you like to search for a pokemon? (y: 1/n: 0) ")) return;

    for (;;) {
        cout << "What pokemon do you want to search: ";
        string searchedName;
        if (!getline(cin, searchedName)) break;
        searchedName = trim(searchedName);
        if (searchedName.empty()) {
            cout << "Enter a name" << endl;
            continue;
        }
        if (tree.search(searchedName) == true) {
            Pokemon pokemon = tree.get(searchedName);
            cout << pokemon.getName() << endl;
            cout << "Generation " << pokemon.getGenNum() << endl;
            cout << "Skill Floor " << pokemon.getMinRank() << endl;
            map<string, float> teams;
            teams = pokemon.getTeamStats();
            for (auto it = teams.begin(); it != teams.end(); it++) {
                cout << it->first << "-> " << it->second << endl;
            }
            map<string, float> ability;
            ability = pokemon.getAbilities();
            for (auto it = ability.begin(); it != ability.end(); it++) {
                cout << it->first << "-> " << it->second << endl;
            }
            map<string, float> moves;
            moves = pokemon.getTopMoves();
            for (auto it = moves.begin(); it != moves.end(); it++) {
                cout << it->first << "-> " << it->second << endl;
            }
            map<string, float> items;
            items = pokemon.getTopItems();
            for (auto it = items.begin(); it != items.end(); it++) {
                cout << it->first << "-> " << it->second << endl;
            }
            map<string, float> spreads;
            spreads = pokemon.getTopSpreads();
            for (auto it = spreads.begin(); it != spreads.end(); it++) {
                cout << it->first << "-> " << it->second << endl;
            }
            map<string, float> tera;
            tera = pokemon.getTopTera();
            for (auto it = tera.begin(); it != tera.end(); it++) {
                cout << it->first << "-> " << it->second << endl;
            }
        }else {
            cout << "No such pokemon exists" << endl;
        }
        if (!decideYN("Search again with the same constraints? (y:1/n: 0) ")) break;
    }
}


void searchAndMaking() {
    int dataStructure;
    int genFilter;
    int floorFilter;
    int back = 1;

    while (back == 1) {
        cout << "\nChoose data structure (0 = Hash, 1 = Trie): ";
        cin >> dataStructure;
        cout << "Enter Generation 1 to 9 (-1 for all): ";
        cin >> genFilter;
        cout << "Enter Skill Floor 0, 1500, 1630, or 1760: ";
        cin >> floorFilter;

        if (dataStructure == 0) {
            hashTable(genFilter, floorFilter);
        } else if (dataStructure == 1) {
            trieTree(genFilter, floorFilter);
        } else {
            cout << "Invalid choice." << endl;
        }

        cout << "\nWould you like to go back and choose again? (y: 1/n: 0) ";
        cin >> back;
    }
}


int main() {
    searchAndMaking();
    return 0;
};
