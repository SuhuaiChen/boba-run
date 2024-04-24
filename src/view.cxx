#include "view.hxx"

View::View(Model const& model)
        : model_(model),
        result(),
        boba("boba.png")
{ }

void
View::draw(ge211::Sprite_set& set)
{
    for(auto& block: model_.get_blocks()){
        set.add_sprite(block.get_sprite(),
                       block.get_pos().into<int>(),
                               0),ge211::Transform().set_scale(0.1)
    ;}
    for (auto& character: model_.get_characters()) {
        set.add_sprite(character.get_sprite(),
                       character.get_position().into<int>(),
                       1,
                       character.get_transform());
    }
    for(auto& key: model_.get_keys()){
        if(!key.get_state()){
            set.add_sprite(key.get_sprite(),
                           key.get_position().into<int>(),
                           0),ge211::Transform().set_scale(0.1);
        }

    }
    set.add_sprite(boba,{740,20});


    if(model_.is_game_over()){
        if(model_.game_win()){
            ge211::Text_sprite::Builder result_builder(sans30_);
            result_builder << "YOU WIN!";
            result.reconfigure(result_builder);
            set.add_sprite(result,{350,250},1);
        }
        else{
            ge211::Text_sprite::Builder result_builder(sans30_);
            result_builder << "YOU LOSE!";
            result.reconfigure(result_builder);
            set.add_sprite(result,{350,250},1);

        }
    }
}
