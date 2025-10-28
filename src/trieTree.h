//
// Created by Frank Ascencio on 10/26/25.
//

#ifndef TIRETREE_H
#define TIRETREE_H
#include <array>
#include <string>
#include <cctype>
#include "pokemon.h"
using namespace std;
#endif //TIRETREE_H

struct trieNode {
    array<trieNode*, 36> children;
    bool isWord;
    Pokemon pokemon;
    trieNode() {
        isWord = false;
        children.fill(nullptr);
    }
};

class TrieTree {
    public:
    trieNode* root;
    TrieTree() {
        root =  new trieNode();
    }

    //Conversion of either alphabets into
    int alphabet(char k) {
        return (tolower(k) - 'a');
    }

    int digitAndAlpha(char k) {
        if (isalpha(k)) {
            return (tolower(k) - 'a');
        } else {
            return (26 + (k - '0'));
        }
    }

    void insert(Pokemon pokemon) {
        trieNode* current = root;
        string target = pokemon.getName();
        for (int i = 0; i < target.length(); i++) {
            char c = tolower(target[i]);
            int index = digitAndAlpha(c);
            if (!current->children[index]) {
                current->children[index] = new trieNode();
            }
            current = current->children[index];
        }
        current->isWord = true;
        current->pokemon = pokemon;
    }

    bool exists(Pokemon pokemon) {
        trieNode* current = root;
        string target = pokemon.getName();
        for (int i = 0; i < target.length(); i++) {
            char c = tolower(target[i]);
            int index = digitAndAlpha(c);
            if (!current->children[index]) {
                current->children[index] = new trieNode();
            }
            current = current->children[index];
        }
        return current->isWord;
    }

    bool exists(string target) {
        trieNode* current = root;
        for (int i = 0; i < target.length(); i++) {
            char c = tolower(target[i]);
            int index = digitAndAlpha(c);
            if (!current->children[index]) {
                current->children[index] = new trieNode();
            }
            current = current->children[index];
        }
        return current->isWord;
    }

    Pokemon get(Pokemon pokemon) {
        trieNode* current = root;
        string target = pokemon.getName();
        for (int i = 0; i < target.length(); i++) {
            char c = tolower(target[i]);
            int index = digitAndAlpha(c);
            if (!current->children[index]) {
                current->children[index] = new trieNode();
            }
            current = current->children[index];
        }
        return current->pokemon;
    }

    Pokemon get(string target) {
        trieNode* current = root;
        for (int i = 0; i < target.length(); i++) {
            char c = tolower(target[i]);
            int index = digitAndAlpha(c);
            if (!current->children[index]) {
                current->children[index] = new trieNode();
            }
            current = current->children[index];
        }
        return current->pokemon;
    }

    void deleteAllNodes(trieNode* node) {
        if (node) {
           for (int i = 0; i < 26; i++) {
               if (node->children[i]) {
                   deleteAllNodes(node->children[i]);
               }
               delete node->children[i];
           }
        }
    }
    ~TrieTree() {
        deleteAllNodes(root);
    }

};
