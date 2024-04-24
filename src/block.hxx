//
// Created by Matt Chen on 2022/3/8.
//

#ifndef GAME_BLOCK_HXX
#define GAME_BLOCK_HXX

#endif //GAME_BLOCK_HXX
#include <ge211.hxx>

class Block{

public:

    Block(ge211::Image_sprite  pic, ge211::Posn<double> pos);

    ge211::Image_sprite const& get_sprite() const{
        return sprite_;
    }

    ge211::Posn<double> const& get_pos () const{
        return position_;
    }

    void set_pos(double x, double y) {
        position_.x = x;
        position_.y = y;
    }

private:

    ge211::Image_sprite sprite_;
    ge211::Posn<double> position_;

};