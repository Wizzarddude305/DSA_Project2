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

    void append(Pokemon &p) {
        if (head == nullptr) {
            head = new linkedNode(p);
            tail = head;
        }else{
            tail->next = new linkedNode(p);
            tail = tail->next;
        }
    }

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
