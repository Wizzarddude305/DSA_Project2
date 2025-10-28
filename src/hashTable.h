//
// Created by Frank Ascencio on 10/26/25.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H
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
        arr = new LinkedList[buckets];
        hashNumber = 36;
        loadFactor = 0.0;
        elements = 0;
        maxLoadFactor = .75;
    }

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

    int stringHash(string key) {
        int power = key.size() - 1;
        int hash = 0;
        for (int i = 0; i < key.size(); i++) {
            hash += digitAndAlpha(key[i], power);
            power--;
        }
        return hash;
    }

    void insert(Pokemon& p) {
        int hashNum = stringHash(p.getName());
        int index = abs(hashNum % buckets);
        arr[index].append(p);
        elements++;
        float x = elements;
        float y = buckets;
        loadFactor = x/y;
        if (loadFactor >= maxLoadFactor) {
            resizeArr();
        }
    }

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

    bool search(string name) {
        int hashNum = stringHash(name);
        int index = abs(hashNum % buckets);
        return arr[index].nameSearch(name);;
    }

    Pokemon* get(string name) {
        int hashNum = stringHash(name);
        int index = abs(hashNum % buckets);
        return arr[index].get(name);
    }

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
#endif //HASHTABLE_H
