/**
 *    Welcome to my 3D Open GL game development project.
 *    My goal is to make a 3D adventure survival game, where
 *    the goal of the game will be to explore, craft, and survive.
 *
 *    I might make my own game engine for my own use, for the learning
 *    experiance and also just for the fun of having my own engine.
 *
 *
 *    Can you discover all the ruins?
 *    Can you fight your way to survival?
 *
 *    You will be able to craft items, fight monsters, and build
 *    your base to protect yourself from the creatures of the night.
 *
 *    Features that will be part of the core game idea;
 *    - adventure
 *    - survival
 *    - battle
 *    - crafting
 *    - building
 *    - animals
 *
 *
 */


#include "../include/helper.hpp"
// #include "../include/mywindowmanager.hpp"
#include "../include/mycore.hpp"

#include <iostream>
#include <sstream>
// #include <memory> // For smart pointers

// #include "examplewindow.hpp"

// Global initialization for Helper variables can be placed in a dedicated source file,
// but here we leave them as-is for simplicity.
int Helper::progLogLevel = 3;    // Default log level
int Helper::skippedLogCount = 0; // Initialize skipped log count

MyCore* myCore;
// MyWindowManager windowManager;

// Anonymous namespace to limit the scope of internal helper functions.
namespace {

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
        if (helper.isValidInt(argv[1], logLevel)) {
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


// Function to initialize the core, and 
// start game manager after window has succesfully been created. 
void start() {
    // Use a smart pointer for automatic memory management.
    // myCore = std::make_unique<MyCore>();

    // program core
    // Core should consist of only core program stuff, such as program config for window size.
    // The core should not contain any game logic.
    // The core is the base of the program, and should be used to initialize the program.
    // The flow should be: main -> core -> window manager -> game manager
    // Main is the entry point of the program, which will start the Core.
    // Core will initialize the WindowManager using values from the config file.
    // The window manager will initialize a window, and then start the game manager.
    // The game manager will initialize the game, and then start the game loop.
    // The game loop will handle events, update the game, and render the game.

    myCore = new MyCore("./config.text"); 
    // game manager
    // gameManager = new GameManager();
    // helper.log(3, "Initializing compleated.");
    // helper.log(3, "Generating world... ");
    // WorldGenerator_A generator;
    // GameManager gameManager(generator);
    // gameManager.init();
}

} // end of anonymous namespace

int main(int argc, char *argv[]) {
    UsefulFunctions::StdOutput stdOut;
    // stdOut.print("Testing standard output");

    // Log the command line arguments.
    printCommandLineArguments(argc, argv);

    // Set the log level based on user input or use the default.
    Helper::progLogLevel = parseLogLevel(argc, argv);

    // Log some startup messages.
    helper.log(3, "Hello World!!");
    helper.log(3, "Main Function");

    //ExampleWindow* exampleWindow = new ExampleWindow();
    //exampleWindow->show();

    // Start the core application.
    start();

    helper.log(3, "Program end----");
    return 0;
}
