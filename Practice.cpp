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


int main() {
    string path = "file.txt";
    string Current_Path = "current.txt";
    string line;

    ifstream START(Current_Path);
    if (!START) {
        cout << "파일을 열 수 없습니다." << endl;
        return 1;
    }
    getline(START, start_directory);
    START.close();

    cout << start_directory << endl;

    ifstream inputFile(path);
    if (!inputFile) {
        cout << "파일을 열 수 없습니다." << endl;
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

//    for (auto item : Folder_List)
//    {
//        cout << " Name: " << item.Folder_Name << endl;
//        cout << " Path: " << item.path << endl;
//        cout << endl;
//    }
    for( char c : Only_Directory)
        cout << c;
}

void ProcessingLine(string line)
{
    int pos = string::npos;
    if ((pos = line.find("+---")) != string::npos || (pos = line.find("\\---")) != string::npos )
    {
        Only_Directory += line + "\n";
        ExtractingLine(line);
    }
    else if(((line.find("|") == string::npos) && (line.find(" ") == string::npos)))
    {
        Only_Directory += line + "\n";
        ExtractingLine(line);
    }
    else
    {
        return;
    }

}
int calculateDepth(string line) {
    int totalDepth = 0;
    int flag = 0;
    size_t pos = 0;
    size_t prev_pos = 0;

    // 반복문을 통해 모든 '|' 문자의 위치를 찾습니다.
    while ((pos = line.find('|', pos)) != std::string::npos) {
        int spaceLength = pos - prev_pos - 1;

        // 첫 번째 '|'는 고려하지 않으므로 continue
        if (flag == 0) {
            prev_pos = pos;
            pos++;
            totalDepth++;
            flag = 1;
            continue;
        }

        if ((spaceLength - 3) % 4 == 0) {
            int depth = (spaceLength - 3) / 4;
            totalDepth += (depth + 1);
        } else {
            std::cerr << "Invalid space length between '|' characters: " << spaceLength << std::endl;
            return -1;
        }

        prev_pos = pos;
        pos++;
    }

    // 마지막에 +--- 또는 \--- 패턴이 있는지 확인하고 그 사이의 공백 길이를 계산합니다.
    size_t lastPatternPos = line.find("+---", prev_pos);
    if (lastPatternPos == std::string::npos) {
        lastPatternPos = line.find("\\---", prev_pos);
    }

    if(lastPatternPos == 0)
    {
        totalDepth = 1;
    }
    else if (lastPatternPos != std::string::npos) {
        int spaceLength = lastPatternPos - prev_pos - 1;

        if ((spaceLength - 3) % 4 == 0) {
            int depth = (spaceLength - 3) / 4;
            totalDepth += (depth + 1);
        } else {
            return 0;
        }
    }

    return totalDepth;
}
void ExtractingLine(string line)
{
    int depth = calculateDepth(line);

    // Extracting Directory (Folder) Name
    size_t pos = line.find_last_of("-") + 1;
    string folderName = line.substr(pos);

    cout << folderName << ", " << depth << endl;
    if(Hierarchy.size() > depth)
    {
        while ( Hierarchy.size() > depth)
            Hierarchy.pop_back();
    }

    // Extracting Directory (Folder) Path
    string fullPath = "";
    for(auto folderName : Hierarchy)
    {
        if(folderName != "C:.")
            fullPath.append("\\" + folderName);
        else
            fullPath.append(start_directory);
    }

    if(folderName == "C:.")
        fullPath.append(start_directory);
    else
        fullPath.append("\\"+folderName);

    Hierarchy.push_back(folderName);

//    cout << "Name : " << folderName << endl;
//    cout << "Path : " << fullPath << endl;
//    cout << "Depth : " << depth  << "\n" << endl;

    node folderNode;
    folderNode.Folder_Name = folderName;
    folderNode.path = fullPath;
    Folder_List.push_back(folderNode);
}

