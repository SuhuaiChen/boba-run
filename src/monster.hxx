//
// Created by Matt Chen on 2022/3/8.
//

#ifndef GAME_MONSTER_HXX
#define GAME_MONSTER_HXX

#endif //GAME_MONSTER_HXX
#include "character.hxx"

class Monster:public Character{

    public:

   // Monster();

    Monster(std::vector<std::string> const& image_filenames,
    ge211::Posn<double> const& initial_position,
            ge211::Transform const& transform);


};