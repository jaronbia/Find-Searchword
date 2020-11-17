#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <getopt.h>

using namespace std;

class Params {
    friend class Sniff;
    private:
        constexpr static struct option long_options[] = {
            { "dir",     required_argument, 0, 'd' },
            { "verbose", no_argument,       0,  2  },
            {  0,        0,                 0,  0  }
        };

        char*    pathname = nullptr;              // Path name for file out
        string   dirPath = " ";               // Search Directory path name
        string   commands = " ";              // String of command line args
        //string   searchWords;           // Add search words in vector here
        vector<string> searchWords;     // Add search words in vector here
        ofstream fileout;               // File to output
        bool recursive = false;                 // Is Recursive?
        bool verbose = false;                   // Is Verbose?
        bool caseSens = false;                  // Is Case Insensitive?
        bool output = false;                    // Is Recursive?

        void usage(const int err);
        void processCL(int argc, char* argv[]);   // Process command line arguments
        void searchDir();

        void setFileName() {
            if(invalidOpt()) usage(2);
            output = true;
            pathname = optarg;
        }

        void writeToFile() { 
            fileout.open(pathname);
            fileout << this << '\n';
            fileout.close();
        }

        // File non existent or filename starts w/ '-' then no valid file name given
        bool invalidOpt() { return !optarg || optarg[0] == '-'; }

    public:
        Params(int argc, char* argv[]);
        ~Params() = default;

        bool isVerbose()   { return verbose; }
        const char* getdirPath() { return dirPath.c_str(); }

        ostream& print(ostream& out);
};

inline ostream& operator << (ostream& out, Params& p) { return p.print(out); }
inline ostream& operator << (ostream& out, Params* p) { return p->print(out); }