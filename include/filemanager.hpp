#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <cstdint>
#include <string>
#include <unordered_map>

#include "cube.hpp"

//#include "../include/helper.hpp"
#include <cstdio>
#include <algorithm>


//#include "helper.hpp"




struct GameEntity {
    int id;
    float x, y;
};

/**
 * @brief The FileManager class
 * This class is for managing files such as config files.
 */
class FileManager 
{
public:
    std::string filename;
    std::unordered_map<std::string, std::string> config;

    FileManager();
    void saveAsBinary(const std::vector<GameEntity>* entities, const std::string& file_name);
    void saveAsBinary(std::vector<Cube> world, std::string file_name);
    void saveAsText(const std::string& data, const std::string& file_name);
    std::vector<GameEntity> loadBinaryData(const std::string& file_name);
    std::string loadGameData(const std::string& file_name);

    std::string trim(const std::string &str);
    bool keyCheck(std::string key, std::string value);
    bool loadConfig(std::string file_path);
    int countLines(const std::string &filename);
};

inline FileManager fileManager;

#endif
