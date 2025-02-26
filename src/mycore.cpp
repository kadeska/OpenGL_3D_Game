#include "mycore.hpp"
#include "../include/helper.hpp"

MyCore::MyCore() {
    helper.log(3, "MyCore constructor");
    fileManager = new FileManager();
}
