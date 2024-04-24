#include "controller.hxx"

Controller::Controller()
        : view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}
void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
}

void
Controller::on_key(ge211::Key key)
{
    if(!model_.is_game_over()){
        if(key.code() == 'a'){
            model_.move_left_two();
        }
        if(key.code() == 'd'){
            model_.move_right_two();
        }
        if(key == ge211::events::Key::left()){
            model_.move_left_one();
        }
        if(key == ge211::events::Key::right()){
            model_.move_right_one();
        }
        if(key.code() == 'w'){
        model_.jump_two();
        }
        if(key == ge211::events::Key::up()){
        model_.jump_one();
        }
    }

}