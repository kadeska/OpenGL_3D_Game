#include "../include/filemanager.hpp"

#include "../include/helper.hpp"


FileManager::FileManager(){
    helper.log(3, "FileManager constructor");
    filename = "";

    std::vector<GameEntity>* array = new std::vector<GameEntity>;
    saveAsBinary(array, "save");
    saveAsText("Hello world!", "save.text");
}

void FileManager::saveAsBinary(const std::vector<GameEntity>* entities, const std::string& file_name)
{
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
}

// Load a list of game entities from a binary file.
std::vector<GameEntity> FileManager::loadBinaryData(const std::string& file_name) {
    std::ifstream in(file_name, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Could not open file for reading");
    }
    uint32_t count;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    std::vector<GameEntity> entities(count);
    in.read(reinterpret_cast<char*>(entities.data()), count * sizeof(GameEntity));
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
    filename = file_name;

    // Save game data as a text string.
    std::ofstream outFile(filename, std::ios::out | std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Could not open file for writing");
    }
    outFile.write(data.c_str(), data.size());

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
std::string loadGameData(const std::string& file_name) {
std::ifstream inFile(file_name, std::ios::in | std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Could not open file for reading");
    }
    std::string data((std::istreambuf_iterator<char>(inFile)),
                     std::istreambuf_iterator<char>());
    return data;
}
