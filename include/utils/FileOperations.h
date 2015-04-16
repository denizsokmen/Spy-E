//
// Created by Taha Doğan Güneş on 13/04/15.
//

#ifndef SPYE_FILEOPERATIONS_H
#define SPYE_FILEOPERATIONS_H

#include <vector>
#include <string>
#include <dirent.h>

class FileOperations {

public:
    static std::vector<std::string> getAllDirectories(std::string path){
        DIR *dir;
        struct dirent *ent;
        std::vector<std::string> directories;

        auto dirp = opendir(path.c_str());
        if (dirp) {
            while ((ent = readdir(dirp)) != NULL) {
                if (ent->d_name[0] != '.') {
                    directories.push_back(std::string(ent->d_name));
                }
            }
        }
        else {
            printf("[FileOperations] Unable to access to directory: %s \n", path.c_str());
        }



        return directories;
    }

};

#endif //SPYE_FILEOPERATIONS_H
