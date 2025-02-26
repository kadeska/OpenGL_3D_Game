#include "../include/helper.hpp"
#include "../include/mywindowmanager.hpp"

#include "mycore.hpp"

// using namespace std;

// Defines
bool isValidInt(const std::string &str, int &result);
void start();

UsefulFunctions::StdOutput stdOut;
MyCore* myCore;

int Helper::progLogLevel = 3;    // Default log level
int Helper::skippedLogCount = 0; // Initialize skipped log count

/**
 * @brief main 
 * This program is compatable with both Windows and Linux systems. You can pass a custom log level if desired.
 * @param argc 
 * @param argv 
 * Arguments prefixed with '*' are optional
 * <*arg1> must be of type 'int' for 'user_defined_log_level'
 * @return 
 */
int main(int argc, char *argv[])
{
    // initialize
    helper.log(3, "Hello World!!");
    helper.log(3, "Main Function");
    stdOut.print("Testing standard output");
    std::string out = "main(argc: " + std::to_string(argc) + ", argv: [";
    // build a string containing all given arguments.
    for (int i = 0; i < argc; ++i) {
        out += "\"" + std::string(argv[i]) + "\"";
        if (i < argc - 1)
            out += ", "; // Add a comma between arguments
    }
    out += "])";
    // print the prebuilt string defining all arguments passed to program.
    helper.log(2, out);

    // gather user defind log level if any.
    int user_defined_log_level;
    if (argc > 1) {
        if (isValidInt(argv[1], user_defined_log_level)) {
            helper.log(2, "Valid argument: " + std::to_string(user_defined_log_level));
            helper.log(3,
                       "Setting 'user_defined_log_level' as: "
                           + std::to_string(user_defined_log_level));
            helper.progLogLevel = user_defined_log_level;
            // Do Stuff using user_defined_log_level.
            start();
        } else {
            helper.log(2, "Invalid argument: " + std::string(argv[1]));
            helper.log(2, "Usage: <arg1> must be of type 'int' for 'user_defined_log_level' ");
            // Try Again
            return 1;
        }
    } else {
        helper.log(1, "Usage: <*arg1>");
        helper.log(1, "Arguments prefixed with '*' are optional");
        // Do stuff using default log level.
        start();
    }

    return 0;
}

bool isValidInt(const std::string &str, int &result)
{
    try {
        size_t pos;
        result = std::stoi(str, &pos);

        // Ensure the entire string was consumed (no extra characters)
        return pos == str.length();
    } catch (const std::invalid_argument &e) {
        return false; // Not a valid integer
    } catch (const std::out_of_range &e) {
        return false; // Integer out of range
    }
}

void start()
{
    // do core set up first

    myCore = new MyCore();

    // then render the window

    MyWindowManager windowManager;

    if (!windowManager.createWindow("My OpenGL App", 1280, 720)) {
        return; // -1; // Exit if window creation fails
    }

    while (!windowManager.shouldClose()) {
        windowManager.pollEvents();
        windowManager.swapBuffers(); // Render (add OpenGL code here)
    }
}
