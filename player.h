#ifndef PLAYER_H
#define PLAYER_H
#include "square.h"

class Player
{
public:
    Player(int id);

    Square* get_location() { return location_; };

    void set_location(Square* loc) { location_ = loc; };

    int get_wins() { return wins_; };

    void IncrementWins() { wins_++; };

    Powerup get_powerup() { return powerup_; };

    void set_powerup(Powerup powerup) { powerup_ = powerup; };

    void UsePowerup() { powerup_ = None;};

    void drawCard();

    void Move();




private:
    Square* location_;

    int wins_;

    Powerup powerup_;

    int id_;


};



class PlayerFactory {
public:


    static Player* createHuman(int id);

    static Player* createCpu(int id);

};


#endif // PLAYER_H
