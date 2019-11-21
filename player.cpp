#include "player.h"

Player::Player()
{

}

Player* PlayerFactory::createCpu() {
    Player* p = new Player();
    return p;
}


Player* PlayerFactory::createHuman() {
    Player* p = new Player();
    return p;
}
