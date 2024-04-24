//
// Created by Matt Chen on 2022/3/8.
//

#ifndef GAME_KEY_HXX
#define GAME_KEY_HXX

#endif //GAME_KEY_HXX
#include <ge211.hxx>

class Key{

public:

    Key();
    Key(ge211::Image_sprite pic, ge211::Posn<double> pos);

    ge211::Image_sprite const& get_sprite() const{
        return sprite_;
    }

    ge211::Posn<double> const& get_position () const{
        return position_;
    }

    void set_pos(double x, double y) {
        position_.x = x;
        position_.y = y;
    }

    bool const& get_state()const{
        return is_carried;
    }

    void flip_state(){
        is_carried = !is_carried;
    }

    private:

    ge211::Image_sprite sprite_;
    ge211::Posn<double> position_;
    bool is_carried;

};