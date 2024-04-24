#pragma once

#include "model.hxx"

class View
{
public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

private:
    Model const& model_;
    ge211::sprites::Text_sprite result;
    ge211::Font sans30_{"sans.ttf", 30};
    ge211::sprites::Image_sprite boba;
};
