#include "player.h"

Player::Player(int id)
{

}

Player* PlayerFactory::createCpu(int id) {
    Player* p = new Player(id);
    return p;
}


Player* PlayerFactory::createHuman(int id) {
    Player* p = new Player(id);
    return p;
}
