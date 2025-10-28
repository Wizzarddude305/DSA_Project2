#pragma once
#include "pokemon.h"
#include "linkedLists.h"

int exp(int base, int power) {

    if (power ==0  || base == 0) {
        return 1;
    }else {
        int total = exp(base, power/2);
        if (total % 2 == 1) {
            return total * total * base;
        }else {
            return total * total;
        }
    }

}


class HashTable {
private:
    int buckets;
    LinkedList* arr;
    int hashNumber;
    float loadFactor;
    int elements;
    float maxLoadFactor;

public:
    HashTable() {
        buckets = 5;
        //Store points via seperate chaining
        arr = new LinkedList[buckets];
        //This hasnumber is determined by the amount of characters you're including
        hashNumber = 36;
        loadFactor = 0.0;
        elements = 0;
        maxLoadFactor = .75;
    }

    //The two different hash functions for either only alphabet or both alphabet and digits
    int alphabetHash(char k, int power) {
        return (tolower(k) - 'a') * exp(hashNumber, power);
    }

    int digitAndAlpha(char k, int power) {
        if (isalpha(k)) {
            return (tolower(k) - 'a') * exp(hashNumber, power);
        } else {
            return (26 + (k - '0')) * exp(hashNumber, power);
        }
    }

    //Converts a string to deseried hash
    int stringHash(string key) {
        int power = key.size() - 1;
        int hash = 0;
        for (int i = 0; i < key.size(); i++) {
            hash += digitAndAlpha(key[i], power);
            power--;
        }
        return hash;
    }

    //This is the insertion for a Pokemon object
    void insert(Pokemon& p) {
        int hashNum = stringHash(p.getName());
        //Must do absolute value due to integer overflow
        int index = abs(hashNum % buckets);
        //Append new pokemon in to the linked list in said index
        arr[index].append(p);
        elements++;
        float x = elements;
        float y = buckets;
        loadFactor = x/y;
        if (loadFactor >= maxLoadFactor) {
            resizeArr();
        }
    }

    //Resize if maximum load factor is reached
    void resizeArr() {
        buckets *=  2;
        LinkedList* newArr = new LinkedList[buckets];
        for (int i = 0; i < buckets/2; i++) {
            linkedNode* current = arr[i].getHead();
            while (current != nullptr) {
                Pokemon p = current->pokemon;
                int hashNum = stringHash(p.getName());
                int index = abs(hashNum % buckets);
                newArr[index].append(p);
                current = current->next;
            }
        }
        delete[] arr;
        float x = elements;
        float y = buckets;
        loadFactor = x/y;
        arr = newArr;
    }

    //Search if a pokemon exists via name or Pokemon object
    bool search(string name) {
        int hashNum = stringHash(name);
        int index = abs(hashNum % buckets);
        return arr[index].nameSearch(name);;
    }

    bool search(Pokemon p) {
        int hashNum = stringHash(p.getName());
        int index = abs(hashNum % buckets);
        return arr[index].nameSearch(p.getName());;
    }

    //Get Pokemon object via name
    Pokemon get(string name) {
        int hashNum = stringHash(name);
        int index = abs(hashNum % buckets);
        return *arr[index].get(name);
    }

    //All basic getters for private variables
    float getLoadFactor() {
        return loadFactor;
    }

    int getElements() {
        return elements;
    }

    int getHashSize() {
        return buckets;
    }

    float getMaxLoadFactor() {
        return maxLoadFactor;
    }

};

