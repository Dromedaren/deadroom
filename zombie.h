
 /* zombie.h
 *
 *  Created on: 5 dec 2013
 *      Author: harvog, elili
*/

#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "sprite.h"
#include "player.h"
#include <time.h>

using randomSpawnPositions = std::map<std::string, std::pair<int, int> >;

class Zombie: public Sprite {
public:
	Zombie(Game* gamePointer, Level* level, std::string zombiename, Player* player);
	Zombie(const Zombie&) = delete;
	Zombie& operator=(const Zombie&) = delete;
	~Zombie() = default;

	int attack();
	int getHealth() const;
	void move();
	void events();
    void takeDamage(int damage);
    void randomSpawn();
	bool collision();

private:
	Player* player;
	Level* level;
    int health{0};
    int speed{0};
    std::map<std::string, std::pair<int, int>>::iterator randomEntryPoints_it = randomEntryPoints.begin();
    int damage{0};

    randomSpawnPositions randomEntryPoints
    									{
											{"top", std::make_pair(400, 50)},
											{"right", std::make_pair(750, 400)},
											{"down", std::make_pair(400, 750)},
											{"left", std::make_pair(50, 400)},
    									};
};
#endif // ZOMBIE_H
