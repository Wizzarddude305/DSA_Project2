//
// Created by Frank Ascencio on 10/26/25.
//

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
    tree.insert(&pokemon1);
    REQUIRE(tree.exists(pokemon1) == true);
    REQUIRE(tree.exists("bruh") == true);
    Pokemon* pokemon3 = tree.get(pokemon1);
    REQUIRE(pokemon3  == &pokemon1);
    Pokemon pokemon2 =  Pokemon("nah");
    REQUIRE(tree.exists(pokemon2) == false);
    tree.insert(&pokemon2);
    REQUIRE(tree.exists(pokemon2) == true);
    pokemon3 = tree.get(pokemon2);
    REQUIRE(pokemon3== &pokemon2);
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
        bool exists = table.search(arr[i]);
        REQUIRE(exists == true);
    }

    pokemon = Pokemon(arr[3]);
    table.insert(pokemon);

    REQUIRE(table.getElements() == 4);
    REQUIRE(table.getHashSize() == 10);
    REQUIRE(table.getMaxLoadFactor() == 0.75f);
    REQUIRE(table.getLoadFactor() == 0.4f);

    for (int i = 0; i < 4; i++) {
        bool exists = table.search(arr[i]);
        REQUIRE(exists == true);
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
        REQUIRE(table.search(names[i]) == true);
    }

    for (int i = 0; i < pokemons.size(); i++) {
        REQUIRE(*table.get(names[i]) == pokemons[i]);
    }
    Pokemon unique =  pokemons[990];
    REQUIRE(*table.get(names[990]) == unique);
    Pokemon uniqueTable = *table.get(names[990]);

    REQUIRE(uniqueTable == unique);

}

TEST_CASE("Trie insertion 100,000 points test", "[flag]") {
    TrieTree tree;
    vector<string> names;
    vector<Pokemon> pokemons;
    string regular_name = "pokemon";
    for (int i = 0; i < 100000; i++) {
        string name = regular_name + to_string(i);
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
        tree.insert(&pokemon);
    }

    for (int i = 0; i < 100000; i++) {
        REQUIRE(tree.exists(names[i]) == true);
    }


}