//
// Created by 박준규 on 2024. 6. 11..
//

#ifndef UNTITLED_PROCESSING_TREE_H
#define UNTITLED_PROCESSING_TREE_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <deque>
#include <vector>

using namespace std;

void ProcessingLine(string line); // Deleting hidden directory and Preprocessing text File
void ExtractingLine(string line); // Creating Folder_List
int calculateDepth(string line);  // Calculating Directory Depth

struct node{
    string Folder_Name;
    string path;
};
typedef struct node node;
typedef node* node_ptr;

string str_01 = "+---";
string str_02 = "\\---";
string Only_Directory;
string start_directory;

vector<node> Folder_List;
deque<string> Hierarchy;

#endif //UNTITLED_PROCESSING_TREE_H
