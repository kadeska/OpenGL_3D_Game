#ifndef HELPER_HPP
#define HELPER_HPP

#include <iostream>
#include <string>

/**
 * @brief The Helper class
 * This class contains shared data and other functions that I may need.
 */
class Helper
{
public:
    Helper() = default;

    // This string is for contructing a compound string, used anywhere that helper.hpp is included.
    std::string string;
    // This bool is a flag to determin if we should use QT framework
    bool enable_QT;
    // screen width and height
    int screen_width;
    int screen_height;
    const char* vertex_shader_path = "../include/shaders/vertex.shader";
    const char* fragment_shader_path = "../include/shaders/fragment.shader";

    // logLevel is used to set the programs log level.
    // 0 = no logging

    /**
     * @brief logLevel
     * Used as program log level
     *
     * logLevel = 0, 1, 2, 3, 4
     * 0 = Critical errors only.
     * 1 = Default, log all errors.
     * 2 = All info, warnings and errors.
     * 3 = Debug, everything is logged to output.
     * 4 = Extensive logging, including tick updates, mouse movements, keyboard input, and anything/everything else.
     */
    static int progLogLevel;
    static int skippedLogCount;

    // Example utility function: clamps a value between a minimum and maximum
    static float clamp(float value, float min, float max)
    {
        return (value < min) ? min : (value > max) ? max : value;
    }

    // Example utility function: log messages
    /**
     * @brief log
     * @param logLevel
     * logLevel = 0, 1, 2, 3, 4
     * 0 = Critical errors only.
     * 1 = Default, log all errors.
     * 2 = All info, warnings and errors.
     * 3 = Debug, everything is logged to output.
     * 4 = Extensive logging, including tick updates, mouse movements, keyboard input, and anything/everything else.
     * @param message
     */
    static void log(int logLevel, const std::string &message)
    {
        if (logLevel <= progLogLevel) {
            std::cout << "[" << logLevel << "]" << "[LOG]: " << message << std::endl;
        } else {
            skippedLogCount++;
        }
    }

    enum config_key_code {
        eNull,  // invalid hash
        eWidth, // screen width
        eHeight // screen height
    };
    config_key_code hashit(std::string const &inString)
    {
        //log(3, inString);
        if (inString == "WIDTH") {
            return config_key_code::eWidth;
        }
        if (inString == "HEIGHT") {
            return config_key_code::eHeight;
        }

        return config_key_code::eNull;
    }
    int getScreen_width();
    void setScreen_width(int newScreen_width);
    int getScreen_height();
    void setScreen_height(int newScreen_height);
};

inline int Helper::getScreen_width() {return screen_width;}

inline void Helper::setScreen_width(int newScreen_width){screen_width=newScreen_width;}

inline int Helper::getScreen_height() {return screen_height;}

inline void Helper::setScreen_height(int newScreen_height){screen_height=newScreen_height;}

// int Helper::progLogLevel = 1; // Default log level
// int Helper::skippedLogCount = 0; // Initialize skipped log count

// Declare the global helper instance
// extern Helper helper;
inline Helper helper;

/**
 * @brief The foobar struct template
 */
template<typename T>
struct foobar
{
    T value;

    foobar() {}

    foobar(std::string str) {}

    foobar(T val, std::string str)
        : value(val)
    {
        helper.log(3, "FooBar created: " + str + " | Value: " + std::to_string(value));
    }

    void display()
    {
        // std::cout << "Stored value: " << value << std::endl;
        helper.log(3, std::string("Stored value: " + std::to_string(value)));
    }
};

/**
 * @brief findMax function template
 * @param a
 * @param b
 * @return
 */
template<typename T>
T findMax(T a, T b)
{
    return (a > b) ? a : b;
}

// Class template

template<typename T>
class Box
{
private:
    T value;

public:
    Box(T val)
        : value(val)
    {} // constructor
    void show() { helper.log(3, std::string("Value: " + std::to_string(value))); }
};

// printer to print custom values or for an easier print function.

template<typename T>
class Printer
{
public:
    void print(T value, int loglevel) { helper.log(loglevel, std::to_string(value)); }
};

// specialization for char* c-style strings.
#include <cstring>
template<>
class Printer<char *>
{
public:
    void print(char *value, int loglevel)
    {
        helper.log(loglevel,
                   std::string("String: ") + std::string(value)
                       + " (length: " + std::to_string(strlen(value)) + ")");
    }
};

// Namespace for managing background color
namespace BackgroundColor {
// Encapsulate RGBA values and provide getters/setters
inline float R = 0.0f;
inline float G = 0.0f;
inline float B = 0.0f;
inline float A = 1.0f;

void setColor(float red, float green, float blue, float alpha);
void getColor(float &red, float &green, float &blue, float &alpha);

} // namespace BackgroundColor

// Namespace for organizing various utilities
namespace UsefulFunctions {

class StdOutput
{
public:
    StdOutput() = default;

    // Example function: print a message
    static void print(const std::string &message) { std::cout << message << std::endl; }
};

class QtOutput
{
public:
    QtOutput() = default;

    // Placeholder: Example for Qt-specific output functionality
    void qtSpecificOutput(const std::string &message)
    {
        // Add Qt-specific output logic here
    }
};

class Calculation
{
public:
    Calculation() = default;

    // Example function: compute a square
    static float square(float value) { return value * value; }
};

class Misc
{
public:
    Misc() = default;

    // Example function: generate a random number
    static int randomInt(int min, int max);
    static bool IsValid() { return false; }
};

} // namespace UsefulFunctions



#endif // HELPER_HPP
