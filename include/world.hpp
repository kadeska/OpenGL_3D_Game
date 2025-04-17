#pragma once

#include <vector>
#include "../include/cube.hpp"

class World {
public:
    /**
     * @brief World constructor
     * @param size
     * The size of the world. The world is a 3D array of cubes. Actual generated
     * size is (size x size x size).
     * I may change this so the world size hieght is capped at 50, but for now
     * just use the raw size given.
     * 
     * @note This constructor initializes the world with the given size.
     * this does not generate the world, it just initializes this 
     * world with the given size. World generation happens in the
     * WorldGenerator class. This world class is inteded to be uses
     * only by the WorldGenerator class. (I may change this later to add
     * more functionality to the world class, such as being able to choose
     * what generator to use, or to load a world from a file.)
     */
    explicit World(int size);


    /**
     * @brief update
     * This function updates the world. This is called every frame.
     * I may add more functionality to this later, such as updating
     * the world based on player input, or updating the world based
     * on time.
     */
    void update();

    /**
     * @brief getCube
     * @param x
     * @param y
     * @param z
     * @return
     * This function returns a reference to the cube at the given coordinates.
     * The coordinates are in the range of 0 to size-1.
     */
    Cube getCube(int x, int y, int z);

    /**
     * @brief save
     * @param filename
     * This function saves the world to a file.
     * The file is saved in binary format.
     * I may add the ability to save the world in a human readable format
     * to allow for easier debugging and testing, or even modding.
     * The file is saved in the same directory as the executable.
     */
    void save(const std::string& filename);

    /**
     * @brief getSize
     * @return
     * This function returns the size of the world.
     */
    int getSize();

    /**
     * @brief getWorld
     * @return
     * This function returns a reference to the vector of cubes in the world.
     * This is used for easy access to the cubes in the world.
     */
    std::vector<Cube>& getWorld();

private:
    /**
     * @brief size
     * The size of the world. The world is a 3D array of cubes. Actual generated
     * size is (size x size x size).
     */
    int size;

    /**
     * @brief cubes
     * The cubes in the world. This is a 3D array of cubes.
     * The cubes are stored in a vector for easy access and manipulation.
     */
    std::vector<Cube> cubes;
};
