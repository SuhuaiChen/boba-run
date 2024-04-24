//
// Created by Matt Chen on 2022/3/8.
//

#include "key.hxx"


Key::Key(ge211::Image_sprite pic, ge211::Posn<double> pos)
        :
        sprite_(pic),
        position_(pos),
        is_carried(false)
{}