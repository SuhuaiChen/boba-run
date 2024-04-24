//
// Created by Matt Chen on 2022/3/8.
//

#include "monster.hxx"
Monster::Monster(
        const std::vector<std::string>& image_filenames,
        const ge211::Posn<double>& initial_position,
        const ge211::Transform& transform)
        :Character(image_filenames,initial_position,transform)
{}

