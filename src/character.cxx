//
// Created by Matt Chen on 2022/3/7.
//
#include "character.hxx"

#include <string>


Character::Character(std::vector<std::string> const& image_filenames,
                     ge211::Posn<double> const& initial_position,
                     ge211::Transform const& transform)
        : sprite_(image_filenames[0]),
          transform_(transform),
          position_(initial_position),
          vertical_velocity_(0.0),
          image_index_(0),
          images_(),
          next_position_(initial_position),
          facetoward(true)
{
    // actually save all the images
    for (std::string filename : image_filenames) {
        images_.push_back(ge211::sprites::Image_sprite(filename));
    }
}




