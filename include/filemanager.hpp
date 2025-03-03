#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <cstdint>
#include <string>


struct GameEntity {
    int id;
    float x, y;
};

class FileManager 
{
public:
    std::string filename;

    FileManager();
    void saveAsBinary(const std::vector<GameEntity>* entities, const std::string& file_name);
    void saveAsText(const std::string& data, const std::string& file_name);
    std::vector<GameEntity> loadBinaryData(const std::string& file_name);
    std::string loadGameData(const std::string& file_name);

    bool loadConfig(std::string file_path);
    int countLines(const std::string &filename);
};

#endif
