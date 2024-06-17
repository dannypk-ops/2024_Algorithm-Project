#include "Processing_Tree.h"
#include "Similarity.h"
#include "HashFunc.h"
#include <iostream>
#include <fstream>

int main() {
    std::string path = "file.txt";
    std::string Current_Path = "current.txt";
    std::string line;

    std::ifstream START(Current_Path);
    if (!START) {
        std::cout << "파일을 열 수 없습니다." << std::endl;
        return 1;
    }
    getline(START, start_directory);
    START.close();

    std::cout << start_directory << std::endl;

    std::ifstream inputFile(path);
    if (!inputFile) {
        std::cout << "파일을 열 수 없습니다." << std::endl;
        return 1;
    }

    int index = 0;
    while (getline(inputFile, line)) {
        index++;
        if (index == 1 || index == 2)
            continue;
        ProcessingLine(line);
    }
    inputFile.close();

//    for (auto item : Folder_List) {
//        std::cout << "Name: " << item.Folder_Name << std::endl;
//        std::cout << "Path: " << item.path << std::endl;
//        std::cout << std::endl;
//    }


    // 01. Hash Map
    HashFunc HashMap;

    for (auto item : Folder_List)
        HashMap.insert(item.Folder_Name, item.path);

    //while(true){
        string folderName;
        cout << "폴더 입력: ";
        cin >> folderName;
        HashMap.searchAllPaths(folderName);
    //}

    vector<node> Result = HashMap.getResult();

    // Similarity 구현
    string File_Name = "tartanair_tools";
    Similarity sim(Result, File_Name);
    sim.MakeOrder();
    priority_queue<node> final_result = sim.getResult();

    while(!final_result.empty())
    {
        node target_node = final_result.top();
        cout << "path: " << target_node.path << "   Similarity : " << target_node.Similarity << endl;
        final_result.pop();
    }
    return 0;
}
