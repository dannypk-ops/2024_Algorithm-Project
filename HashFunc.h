//
// Created by 박준규 on 24. 6. 16.
//

#ifndef UNTITLED_HASHFUNC_H
#define UNTITLED_HASHFUNC_H

#include <string>
#include <vector>
#include "Processing_Tree.h"

using namespace std;

const int TABLE_SIZE = 1000;

struct HashEntry {
    string key;
    string path;
    HashEntry* next;

    HashEntry(const string& k, const string& p) : key(k), path(p), next(nullptr) {}
};

class HashFunc {
private:
    HashEntry* table[TABLE_SIZE];
    int hashFunction(const string& key);
    vector<node> Result;

public:
    HashFunc() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;
        }
    }
    ~HashFunc() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashEntry* entry = table[i];
            while (entry != nullptr) {
                HashEntry* prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
    }
    void insert(const string& folderName, const string& path);
    string search(const string& folderName);
    // 주어진 폴더 이름에 해당하는 모든 경로 출력
    void searchAllPaths(const string& folderName);
    void displayAllPaths();
    vector<node> getResult();
};


#endif //UNTITLED_HASHFUNC_H
