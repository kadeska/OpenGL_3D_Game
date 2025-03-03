#include "../include/filemanager.hpp"

#include "../include/helper.hpp"


FileManager::FileManager(){
    helper.log(3, "FileManager constructor");
    filename = "";

    // std::vector<GameEntity>* array = new std::vector<GameEntity>;
    // saveAsBinary(array, "save");
    // saveAsText("Hello world!", "save.text");
}

void FileManager::saveAsBinary(const std::vector<GameEntity>* entities, const std::string& file_name)
{
    helper.log(3, std::string("Saving as Binary: " + file_name));
    filename = file_name;

    // Save a list of game entities to a binary file.
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Could not open file for writing");
    }
    // Write the number of entities first.
    uint32_t count = static_cast<uint32_t>(entities->size());
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));
    // Write the actual entity data.
    out.write(reinterpret_cast<const char*>(entities->data()), count * sizeof(GameEntity));
    helper.log(3, std::string("File saved: " + file_name));
}

// Load a list of game entities from a binary file.
std::vector<GameEntity> FileManager::loadBinaryData(const std::string& file_name) {
    helper.log(3, std::string("Loading file: " + file_name));

    std::ifstream in(file_name, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Could not open file for reading");
    }
    uint32_t count;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    std::vector<GameEntity> entities(count);
    in.read(reinterpret_cast<char*>(entities.data()), count * sizeof(GameEntity));
    helper.log(3, std::string("File loaded succesfuly: " + file_name));
    return entities;
}

    // int main() {
    //     try {
    //         GameDataManager manager("entities.dat");
    //         std::vector<GameEntity> entities = {
    //             {1, 100.0f, 200.0f},
    //             {2, 150.0f, 250.0f}
    //         };

    //         // Save the entities to file.
    //         manager.saveEntities(entities);

    //         // Load the entities back from file.
    //         std::vector<GameEntity> loadedEntities = manager.loadEntities();
    //         for (const auto& entity : loadedEntities) {
    //             std::cout << "Entity " << entity.id
    //                       << ": (" << entity.x << ", " << entity.y << ")\n";
    //         }
    //     } catch (const std::exception& ex) {
    //         std::cerr << "Error: " << ex.what() << '\n';
    //     }
    //     return 0;
    // }

void FileManager::saveAsText(const std::string& data, const std::string& file_name)
{
    helper.log(3, std::string("Saving as Text: " + file_name));
    filename = file_name;

    // Save game data as a text string.
    std::ofstream outFile(filename, std::ios::out | std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Could not open file for writing");
    }
    outFile.write(data.c_str(), data.size());
    helper.log(3, std::string("File saved: " + file_name));

    // int main() {
    //     try {
    //         GameDataFileManager fileManager("game_data.bin");
    //         std::string gameData = "PlayerScore: 100\nPlayerName: John\n";

    //         // Save game data to file.
    //         fileManager.saveGameData(gameData);

    //         // Load game data from file.
    //         std::string loadedData = fileManager.loadGameData();
    //         std::cout << "Loaded game data:\n" << loadedData;
    //     } catch (const std::exception& ex) {
    //         std::cerr << "Error: " << ex.what() << '\n';
    //     }
    //     return 0;
    // }


}

// Load game data from file.
std::string FileManager::loadGameData(const std::string &file_name)
{
    std::ifstream inFile(file_name, std::ios::in | std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Could not open file for reading");
    }
    std::string data((std::istreambuf_iterator<char>(inFile)),
                     std::istreambuf_iterator<char>());
    return data;
}

bool FileManager::loadConfig(std::string file_path)
{
    std::ifstream inFile(file_path, std::ios::in);
    if (!inFile.is_open()) {
        // error
        helper.log(1, std::string("Error opening file: " + file_path));
        return false;
    }
    helper.log(3, std::string("Config file line count: " + std::to_string(countLines(file_path))));
    std::string line;
    while (std::getline(inFile, line)) {
        if (line[0] == '#') {
            continue;
        }
        std::cout << line << std::endl;
    }
    // close then re-open the file to refresh the stream. For some reason if I dont do this,
    // then the folowing while loop doesnt get excecuted.
    inFile.clear();
    inFile.close();
    inFile.open(file_path, std::ios::in);

    std::string key;
    std::string value;
    int numLines = countLines(file_path);
    int currentLineNumber = 0;

    // Read the file and output the config values.
    // while (!inFile.eof()) { // this is the way
    while (std::getline(inFile, line)) { // this doesnt work right
        // while (inFile.is_open() & (currentLineNumber < numLines)) {

        if ((currentLineNumber < numLines)) {
            if (line[0] == '#') {
                continue;
            }
            currentLineNumber++;
            inFile >> key;
            inFile >> value;

            /**
            * @brief loglevel
            * local scope usage
            * for debug set this to 3 or lower if initial LogLevel is set to 3
            */
            int loglevel = 4;
            // key check
            switch (helper.hashit(key)) {
            case helper.config_key_code::eHeight:
                helper.log(loglevel, std::string("Key: " + key));
                helper.log(loglevel, std::string("Value: " + value));
                // set screen height

                break;

            case helper.config_key_code::eWidth:
                helper.log(loglevel, std::string("Key: " + key));
                helper.log(loglevel, std::string("Value: " + value));
                // set screen width

                break;

            case helper.config_key_code::eNull:
                helper.log(loglevel, std::string("Key: Null"));
                helper.log(loglevel, std::string("Value: Null"));
                //helper.log(3, value);
                // error out with 'invalid hash'

                break;

            default:
                helper.log(1, std::string("Invalid key")); // would this ever run?

                break;
            }
        }
    }
    inFile.close();
    return true;
}

int FileManager::countLines(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return -1;
    }

    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        ++count;
    }
    return count;
}
