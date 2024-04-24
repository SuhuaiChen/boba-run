#pragma once

#include <ge211.hxx>
#include "character.hxx"
#include "player.hxx"
#include "block.hxx"
#include "monster.hxx"
#include "key.hxx"

class Model
{
public:
    // Constructor(s)
    Model();

    // Getters/Setters
    // Implemented in place if they're really simple (one liners)
    std::vector<Character> const& get_characters()const
    { return characters_; }

    std::vector<Block> const& get_blocks()const
    { return blocks_; }

    std::vector<Key> const& get_keys()const
    {return keys_;}

    bool const& is_game_over() const
    { return game_over; }

    bool const& game_win() const
    {return win_or_lose;}

    void move_left_one(){
        characters_[0].move_left();
    }

    void move_right_one(){
        characters_[0].move_right();
    }

    void move_left_two(){
        characters_[1].move_left();
    }

    void move_right_two(){
        characters_[1].move_right();
    }
    void jump_one(){
        if(time-last_jump_one>5){
            characters_[0].jump();
            last_jump_one = time;

        }

    }
    void jump_two(){
        if(time-last_jump_two>5){
            characters_[1].jump();
            last_jump_two = time;

        }
    }
    void set_game_over(bool const& state)
    { game_over = state; }

    Character& character_one (){
        return characters_[0];
    }
    Character& character_two (){
        return characters_[1];
    }

    Key& key(){
        return keys_[0];
    }
    Character& monster(){
        return characters_[2];
    };

    // Public interface
    void on_frame(double dt);



private:
    // Data members

    std::vector<Character> characters_;

    bool game_over;
    bool win_or_lose;
    std::vector<Block> blocks_;
    std::vector<Key>keys_;
    double time;
    double last_jump_one;
    double last_jump_two;
    int carrier;
    //helpers
    bool hits_block(ge211::Posn<double> next);
    bool fall_on_block(Character player);
    void evaluate();
    void move_player();
    void move_monster();
    bool hit_screen_side(ge211::Posn<double>next);
    bool hit_screen_top(ge211::Posn<double> next);
    bool hit_screen_bottom();
    bool hit_monster();
    void update_keys();
    bool evaluate_win();

};