#include "Sniff.hpp"

Sniff:: 
Sniff(int argc, char* argv[]) : prm(argc, argv) {
    string curr = " ";
    string prev = " ";
    istringstream swrd(prm.commands);
  
    // process sniff words
    for(;;) {
        swrd >> curr;
        if(swrd.eof()) break;
        if(prev[0] != '-' && curr[0] != '-')
            sniffWords.push_back(curr);
        prev = curr;
    }

    oneDir();
}

//-------------------------------------------------------------
void Sniff:: 
oneDir() {
    char    wcwd[PATH_MAX];
    char*   npwd = getcwd(wcwd, sizeof(wcwd));
    DIR*    dir;
    Dirent* fidir;
    string  path;
    Stats   fistat;
    FileID  fid;

    currDirPath = string(npwd) + string(prm.getdirPath());

    dir = opendir(currDirPath.c_str());
    if(!dir) throw BadFile();
  
    for(;;) {
        fidir = (Dirent*) readdir(dir);

        if(fidir == nullptr) 
            break;
        if(!validFile(fidir) || fidir->name()[0] == '.') 
            continue;

        setPath(path, fidir->name());
        lstat(path.c_str(), (Stats*) &fistat);
     
        if(prm.isVerbose()) cout << fidir->name() << '\n';

        fid = oneFile(fidir, fistat, path);   // Process regular file 
        if(!fid.swrdEmpty()) files.push_back(fid);
    }

    closedir(dir);
}

//-------------------------------------------------------------
FileID Sniff:: 
oneFile(Dirent* dnt, Stats sts, string path) {
    string   word;
    FileID   fid(dnt, sts, path);
    ifstream in(path);

    for(;;) {
        in >> word;
        if(in.eof()) break;

        // Compare each sniffword to the word found in the file
        for(string s : sniffWords) {    
            if(s == word) fid.insertSniff(s);
        }
    }

    return fid;
}

//-------------------------------------------------------------
ostream& Sniff:: 
print(ostream& out) {
    out << prm << '\n';

    for(FileID fi : files)
        out << fi << '\n';

    return out;
}
