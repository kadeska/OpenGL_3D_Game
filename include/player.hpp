#pragma once

#include "../include/cube.hpp" // placeholder until I make a player model
#include "../include/helper.hpp"

#include <glm/glm.hpp>

class Player
{
public:
    Player(Cube player_model, std::string player_name, glm::vec3 pos);

    Cube getPlayerModel();
    void setPlayerModel(Cube newPlayerModel);
    std::string getPlayerName();
    void setPlayerName(std::string newPlayerName);
    bool move(glm::vec3 direction);


    Cube playerModel;
    std::string playerName;
    glm::vec3 playerPosition;// = glm::vec3(0,0,0);
};
