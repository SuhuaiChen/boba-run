//
// Created by Matt Chen on 2022/3/7.
//

#include "player.hxx"

Player::Player(
        const std::vector<std::string>& image_filenames,
        const ge211::Posn<double>& initial_position,
        const ge211::Transform& transform)

        :
        Character(image_filenames,initial_position,transform)

{}

