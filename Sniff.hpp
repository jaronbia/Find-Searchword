/*Names: Jaron Bialecki & Evan Perry
* Date:  09-20-2020
*/
#pragma once
#include "FileID.hpp"
#include <sstream>

class Sniff{
private:
    friend class params;
    params* pms;
    vector<string> sniffWords;
    vector<FileID> files;
    vector<FileID> subdirectories;
    string cwd = "./";
    void work(int, char**);
public:
    Sniff(int, char**);
    ~Sniff() = default;
    void oneDir();
    ostream& print(ostream& out);
};
inline ostream& operator << (ostream& out, Sniff& sf) { return sf.print(out); }