//
// Created by Matt Chen on 2022/3/7.
//

#pragma once

#include <ge211.hxx>


class Character
{
public:
    // Constructor(s)
    Character();

    Character(std::vector<std::string> const& image_filenames,
              ge211::Posn<double> const& initial_position,
              ge211::Transform const& transform);

    // Getters/Setters
    // Implemented in place if they're really simple (one liners)
    //void set_position(ge211::Posn<float> position) {
    //    position_ = position;
    //}
    ge211::Posn<double> const& get_position() const {
        return position_;
    }
    ge211::Image_sprite const& get_sprite() const {
        return sprite_;
    }
    ge211::Transform const& get_transform() const {
        return transform_;
    }

    void set_position(double x, double y){
        position_.x = x;
        position_.y = y;
    }

    void move_left(){
        next_position_.x -= 10;
    }
    void move_right(){
        next_position_.x += 10;
    }
    void jump(){
        if(vertical_velocity_>=0){
            vertical_velocity_ -= 12;
        }

    }

    ge211::Posn<double> const& get_next_position() const{
        return next_position_;
    }

    void set_next_position_x(double x){
        next_position_.x = x;
    }
    void set_next_position_y(double y){
        next_position_.y = y;
    }

    float const get_vertical_velocity() const{
        return vertical_velocity_;
    }
    void set_vertical_velocity(double y){
        vertical_velocity_ = y;
    }

    bool const& get_face_toward()const{
        return facetoward;
    }
    void flip_face_toward(){
        facetoward = !facetoward;
    }
protected:

    // Data members
    ge211::Image_sprite sprite_;
    ge211::Transform transform_;

    ge211::Posn<double> position_;
    double vertical_velocity_;

    unsigned int image_index_;
    std::vector<ge211::Image_sprite> images_;
    ge211::Posn<double> next_position_;
    bool facetoward;

};
