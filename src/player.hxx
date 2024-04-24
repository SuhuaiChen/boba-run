//
// Created by Matt Chen on 2022/3/7.
//
#include "character.hxx"


#ifndef GAME_PLAYER_HXX
#define GAME_PLAYER_HXX

#endif //GAME_PLAYER_HXX


class Player:public Character{
public:
    Player(std::vector<std::string> const& image_filenames,
            ge211::Posn<double> const& initial_position,
            ge211::Transform const& transform
            );






};