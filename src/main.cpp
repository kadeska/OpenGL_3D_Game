#include "../include/helper.hpp"
#include "../include/mywindowmanager.hpp"
#include "mycore.hpp"

#include <iostream>
#include <sstream>
// #include <memory> // For smart pointers

// Global static initialization for Helper variables can be placed in a dedicated source file,
// but here we leave them as-is for simplicity.
int Helper::progLogLevel = 3;    // Default log level
int Helper::skippedLogCount = 0; // Initialize skipped log count

MyCore* myCore;

// Anonymous namespace to limit the scope of internal helper functions.
namespace {

// Validate if the given string represents a valid integer.
bool isValidInt(const std::string &str, int &result) {
    try {
        size_t pos;
        result = std::stoi(str, &pos);
        return pos == str.length();
    } catch (const std::exception &) {
        return false;
    }
}

// Print command line arguments in a formatted string.
void printCommandLineArguments(int argc, char *argv[]) {
    std::ostringstream out;
    out << "main(argc: " << argc << ", argv: [";
    for (int i = 0; i < argc; ++i) {
        out << "\"" << argv[i] << "\"";
        if (i < argc - 1)
            out << ", ";
    }
    out << "])";
    helper.log(2, out.str());
}

// Parse the optional user-defined log level from command line arguments.
// Exits the program if the argument is invalid.
int parseLogLevel(int argc, char *argv[]) {
    if (argc > 1) {
        int logLevel;
        if (isValidInt(argv[1], logLevel)) {
            helper.log(2, "Valid argument: " + std::to_string(logLevel));
            helper.log(3, "Setting 'user_defined_log_level' as: " + std::to_string(logLevel));
            return logLevel;
        } else {
            helper.log(2, "Invalid argument: " + std::string(argv[1]));
            helper.log(2, "Usage: <arg1> must be of type 'int' for 'user_defined_log_level'");
            std::exit(EXIT_FAILURE);
        }
    }
    return Helper::progLogLevel; // Use default if not provided.
}

// Function to encapsulate core initialization and the main loop.
void start() {
    // Use a smart pointer for automatic memory management.
    //auto myCore = std::make_unique<MyCore>();
    MyCore* myCore = new MyCore();
    //myCore->fileManager->loadBinaryData("save");

    // Load the entities back from file.
    // std::vector<GameEntity> loadedEntities = myCore->fileManager->loadBinaryData("save");
    // for (const auto& entity : loadedEntities) {
    //     std::cout << "Entity " << entity.id << ": (" << entity.x << ", " << entity.y << ")\n";
    // }

    if (!myCore->fileManager->loadConfig("save.text")) {
        helper.log(1, "oops... something went wrong, shutting down!!");
        return;
    }

    MyWindowManager windowManager;
    if (!windowManager.createWindow("My OpenGL App", 1280, 720)) {
        return;
    }

    while (!windowManager.shouldClose()) {
        windowManager.pollEvents();
        windowManager.swapBuffers();
    }
}

} // end of anonymous namespace

int main(int argc, char *argv[]) {
    // Log some startup messages.
    helper.log(3, "Hello World!!");
    helper.log(3, "Main Function");

    UsefulFunctions::StdOutput stdOut;
    stdOut.print("Testing standard output");

    // Log the command line arguments.
    printCommandLineArguments(argc, argv);

    // Set the log level based on user input or use the default.
    Helper::progLogLevel = parseLogLevel(argc, argv);

    // Start the core application.
    start();

    return 0;
}
