

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "trieTree.h"
#include "pokemon.h"
#include <set>
#include <string>

#include "hashTable.h"
#define CATCH_CONFIG_MAIN


TEST_CASE("Trie insertion and search", "[flag]") {
    TrieTree tree;
    Pokemon pokemon1 =  Pokemon("bruh");
    tree.insert(pokemon1);
    REQUIRE(tree.search(pokemon1) == true);
    REQUIRE(tree.search("bruh") == true);
    Pokemon pokemon3 = tree.get(pokemon1);
    REQUIRE(pokemon3  == pokemon1);
    Pokemon pokemon2 =  Pokemon("nah");
    REQUIRE(tree.search(pokemon2) == false);
    tree.insert(pokemon2);
    REQUIRE(tree.search(pokemon2) == true);
    pokemon3 = tree.get(pokemon2);
    REQUIRE(pokemon3==  pokemon2);
}


TEST_CASE("Hash table resizing", "[flag]") {
    HashTable table;
    string arr[4]= {"bruh", "yes", "lol", "nah"};
    Pokemon pokemon;
    for (int i = 0; i < 3; i++) {
        pokemon = Pokemon(arr[i]);
        table.insert(pokemon);
    }

    for (int i = 0; i < 3; i++) {
        bool search = table.search(arr[i]);
        REQUIRE(search == true);
    }

    pokemon = Pokemon(arr[3]);
    table.insert(pokemon);

    REQUIRE(table.getElements() == 4);
    REQUIRE(table.getHashSize() == 10);
    REQUIRE(table.getMaxLoadFactor() == 0.75f);
    REQUIRE(table.getLoadFactor() == 0.4f);

    for (int i = 0; i < 4; i++) {
        bool search = table.search(arr[i]);
        REQUIRE(search == true);
    }

}


TEST_CASE("Hash table alpha and digit (100,000 data points)", "[flag]") {
    HashTable table;
    vector<string> names;
    vector<Pokemon> pokemons;

    string regular_name = "pokemon";
    string name;
    for (int i = 0; i < 100000; i++) {
        name = regular_name + to_string(i);
        names.push_back(name);
        map<string, float> mapping;
        for (int j = 0; j < 20; j++) {
            string teamName = "teammatePokemon" + to_string(j);
            int raw = rand() % 10000 + 1;
            float random_percent = raw/100.0f;
            mapping[teamName] = random_percent;
        }

        Pokemon pokemon = Pokemon(name);
        pokemons.push_back(pokemon);
        table.insert(pokemon);
    }

    for (int i = 0; i < 100000; i++) {
        name = regular_name + to_string(i);
        REQUIRE(table.search(name) == true);
        Pokemon pokemon = table.get(name);
        REQUIRE(pokemon == pokemons[i]);
        REQUIRE(pokemon.getTeamStats() == pokemons[i].getTeamStats());
        map<string, float> mapping;
        mapping = pokemon.getTeamStats();
        for (auto it = mapping.begin(); it != mapping.end(); it++) {
            REQUIRE(it->second == pokemons[i].getTeamStats()[it->first]);
        }
    }
}

TEST_CASE("Trie insertion 100,000 points test", "[flag]") {
    TrieTree tree;
    vector<string> names;
    vector<Pokemon> pokemons;
    for (int i = 0; i < 100000; i++) {
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

    for (int i = 0; i < 100000; i++) {
        REQUIRE(tree.search(names[i]) == true);
        Pokemon other = tree.get(names[i]);
        Pokemon pokemon = pokemons[i];
        REQUIRE(other == pokemon);
    }


}