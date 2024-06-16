//
// Created by 박준규 on 24. 6. 16.
//

#include "HashFunc.h"
#include <iostream>
using namespace std;

int HashFunc::hashFunction(const string& key) {
    int hashValue = 0;
    for (char ch : key) {
        hashValue += ch;
    }
    return hashValue % TABLE_SIZE;
}

void HashFunc::insert(const string& folderName, const string& path) {
    int hashValue = hashFunction(folderName);
    HashEntry* newEntry = new HashEntry(folderName, path);

    if (table[hashValue] == nullptr) {
        table[hashValue] = newEntry;
    }
    else {
        HashEntry* current = table[hashValue];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newEntry;
    }
}

string HashFunc::search(const string& folderName) {
    int hashValue = hashFunction(folderName);

    HashEntry* current = table[hashValue];
    while (current != nullptr) {
        if (current->key == folderName) {
            return current->path;
        }
        current = current->next;
    }
    return "";
}

void HashFunc::searchAllPaths(const string& folderName) {
    int hashValue = hashFunction(folderName);

    HashEntry* current = table[hashValue];
    while (current != nullptr) {
        if (current->key == folderName) {
            node new_node;
            new_node.Folder_Name = current->key;
            new_node.path = current->path;
            Result.push_back(new_node);
//          cout << "Folder Name: " << current->key << ", Path: " << current->path << endl;

        }
        current = current->next;
    }
}

void HashFunc::displayAllPaths() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashEntry* current = table[i];
        while (current != nullptr) {
            cout << "Path: " << current->path << endl;
            current = current->next;
        }
    }
}

vector<node> HashFunc::getResult(){
    return Result;
}