#pragma once
#include "pokemon.h"

//Structure for a singly linked Node
struct linkedNode{
    Pokemon pokemon;
    linkedNode* next;
    linkedNode(Pokemon &p) {
        next = nullptr;
        pokemon = p;
    }

};

//Basic linked list structure consisting of head and tail pointers
class LinkedList {
private:
    linkedNode* head;
    linkedNode* tail;
public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }
    //This is simply implemented to quickly add an item to the end of the linked list for hash table chaining
    void append(Pokemon &p) {
        if (head == nullptr) {
            head = new linkedNode(p);
            tail = head;
        }else{
            tail->next = new linkedNode(p);
            tail = tail->next;
        }
    }

    //A simple O(n) function to se if an item is in the seperate chain for a pokemon object
    bool exists(const Pokemon &p) {
        linkedNode* current = head;
        while (current != nullptr) {
            if (current->pokemon == p) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    //This is the same as the previous function just for the name
    bool nameSearch(string name) {
        linkedNode* current = head;
        while (current != nullptr) {
            if (current->pokemon.getName() == name) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    //A getter for a specific linked Node O(n) time
    Pokemon* get(string name) {
        linkedNode* current = head;
        while (current != nullptr) {
            if (current->pokemon.getName() == name) {
                return &(current->pokemon);
            }
            current = current->next;
        }
        return nullptr;
    }

    //This is for the hashtable to identify if there is an established list or not
    bool isHead() {
        if (head) {
            return true;
        }else {
            return false;
        }
    }

    linkedNode* getHead() {
        return head;
    }
};
