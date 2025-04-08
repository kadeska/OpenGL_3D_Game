#include "player.hpp"

Player::Player(Cube player_model, std::string player_name, glm::vec3 pos)
    : playerModel(player_model), playerName(player_name), playerPosition(pos)
{}

std::string Player::getPlayerName()
{
    return playerName;
}

void Player::setPlayerName(std::string newPlayerName)
{
    playerName = newPlayerName;
}

bool Player::move(glm::vec3 direction)
{
    playerPosition += direction;
    return true;
}

Cube Player::getPlayerModel()
{
    return playerModel;
}

void Player::setPlayerModel(Cube newPlayerModel)
{
    playerModel.setCube_model(newPlayerModel.cube_model);
}
