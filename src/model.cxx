#include "model.hxx"
#include <iostream>
Model::Model()
        : characters_(),
          game_over(false),
          win_or_lose(false),
          blocks_(),
          keys_(),
          time(0.0),
          last_jump_one(0.0),
          last_jump_two(0.0),
          carrier(0)
{
    std::vector<std::string> boy_files;

        boy_files.push_back("boy.png");
        //std::cout << filename << "\n";


    Player boy(boy_files, {0, 260},
                    ge211::Transform().set_scale(0.1));


    std::vector<std::string> girl_filenames;
    girl_filenames.push_back("girl.png");
    Player girl(girl_filenames, {100, 260},
                        ge211::Transform().set_scale(0.1));

    std::vector<std::string> cat_files;

    cat_files.push_back("tiger.png");

    Monster cat(cat_files,{520,130},ge211::Transform().set_scale(1));

    characters_.push_back(boy);
    characters_.push_back(girl);
    characters_.push_back(cat);

    std::vector<ge211::Posn<double>> bbs{{80,0},{80,160},{80,320},{0,520},
                                        {40,520},{80,520},{160,80},{160,240},
                                        {160,440},{200,440},{240,440},{200,520},
                                        {240,520},{280,520},{320,520},{280,80},
                                        {320,240},{360,240},{400,240},{400,40},
                                        {440,80},{320,400},{360,400},{400,440},{480,480},
                                        {440,520},{480,280},
                                        {520,280},{560,520},{600,520},
                                        {720,520},{760,520},{680,560},{640,440},
                                        {680,440},{720,440},{760,440},{560,360},
                                        {600,360},{640,360},{680,360},{720,360},
                                        {760,360},{640,240},{680,240},{720,240},
                                        {760,240},{600,80},{640,80},{680,80},
                                        {720,80},{760,80},{240,320},{200,360}};

    for(ge211::geometry::Posn<double> pos:bbs){
        ge211::Image_sprite block_pic("block1.jpeg");
        Block block1(block_pic,pos);
        blocks_.push_back(block1);
    }
    for(double i=0; i<11;i++)
    {
        ge211::Image_sprite block_pic("block1.jpeg");
        Block block1(block_pic,{360+i*40,160});
        blocks_.push_back(block1);
    }

    ge211::Image_sprite key_pic("key.png");
    Key key1(key_pic,{600,490});
    keys_.push_back(key1);

}

void
Model:: on_frame(double dt){
   if(!is_game_over()){
       move_player();
       move_monster();
       update_keys();
       time += 0.1;
       evaluate();
   }

}

void Model::update_keys()
{
    for(Key& key: keys_){
        if(key.get_state()){
            key.set_pos(characters_[carrier].get_position().x,
                        characters_[carrier].get_position().y);
        }
        else{
            if((abs(characters_[0].get_position().x - key
            .get_position().x)<35&&abs(characters_[0].get_position()
            .y-key.get_position().y)<35))
            {
                key.flip_state();
                carrier = 0;

            }
            if((abs(characters_[1].get_position().x - key
            .get_position().x)<35&&abs(characters_[1].get_position()
            .y-key.get_position().y)<35))
            {
                key.flip_state();
                carrier = 1;
            }
        }
    }
}
void Model::move_monster()
{
    if(characters_[2].get_face_toward()){
        if(characters_[2].get_position().x < 770){
            characters_[2].set_position(characters_[2].get_position().x+2,
                                        characters_[2].get_position().y);
        }else
        {
            characters_[2].flip_face_toward();
            characters_[2].set_position(characters_[2].get_position().x-2,
                                        characters_[2].get_position().y);
        }
    }
    else{
        if(characters_[2].get_position().x > 360){
            characters_[2].set_position(characters_[2].get_position().x-2,
                                        characters_[2].get_position().y);
        }
        else{
            characters_[2].flip_face_toward();
            characters_[2].set_position(characters_[2].get_position().x+2,
                                        characters_[2].get_position().y);
        }
    }
}
void Model::move_player()
{
    characters_[0].set_next_position_y(characters_[0].get_position().y +
                                       characters_[0].get_vertical_velocity());

    characters_[1].set_next_position_y(characters_[1].get_position()
    .y+characters_[1].get_vertical_velocity());

if(hits_block(characters_[0].get_next_position()))
{
    characters_[0].set_vertical_velocity(0);

      if(fall_on_block(characters_[0]))
    {
          characters_[0].set_next_position_y(characters_[0].get_position().y);

    }
    else
    {

    characters_[0].set_next_position_x(characters_[0].get_position().x);
    characters_[0].set_next_position_y(characters_[0].get_position().y);

    }
}

if(hit_screen_side(characters_[0].get_next_position())||
        hit_screen_top(characters_[0].get_next_position())){

    characters_[0].set_vertical_velocity(0);
    characters_[0].set_next_position_x(characters_[0].get_position().x);
    characters_[0].set_next_position_y(characters_[0].get_position().y);
}

////////

    if(hits_block(characters_[1].get_next_position()))
    {
        characters_[1].set_vertical_velocity(1);

        if(fall_on_block(characters_[1]))
        {
            characters_[1].set_next_position_y(characters_[1].get_position().y);

        }
        else
        {
            characters_[1].set_next_position_x(characters_[1].get_position().x);
            characters_[1].set_next_position_y(characters_[1].get_position().y);

        }
    }

    if(hit_screen_side(characters_[1].get_next_position())||
       hit_screen_top(characters_[1].get_next_position())){

        characters_[1].set_vertical_velocity(0);
        characters_[1].set_next_position_x(characters_[1].get_position().x);
        characters_[1].set_next_position_y(characters_[1].get_position().y);
    }




characters_[0].set_position(characters_[0].get_next_position().x,
                            characters_[0].get_next_position().y);


characters_[0].set_vertical_velocity(characters_[0].get_vertical_velocity()
+0.5);


    characters_[1].set_position(characters_[1].get_next_position().x,
                                characters_[1].get_next_position().y);



    characters_[1].set_vertical_velocity(characters_[1].get_vertical_velocity
    ()+0.5);

}

bool Model::evaluate_win()
{
    for(Key& key: keys_) {
        if (key.get_position().x < 720 || key.get_position().y > 80) {
            return false;
        }
    }
    if(characters_[0].get_position().x<720||characters_[0].get_position().y>80||
    characters_[1].get_position().x<720||characters_[1].get_position().y>80)
    {
    return false;
    }
    win_or_lose = true;
    return true;
}
void Model:: evaluate()
{
    if(hit_monster()||hit_screen_bottom()||evaluate_win()){
        game_over = true;
    }

}

bool Model::hit_monster()
{
return (abs(characters_[0].get_next_position().x - characters_[2]
        .get_position().x)<35&&abs(characters_[0].get_next_position()
        .y-characters_[2].get_position().y)<35)
        ||
        (abs(characters_[1].get_next_position().x - characters_[2]
        .get_position().x)<35&&abs(characters_[1].get_next_position()
        .y-characters_[2].get_position().y)<35);
}

bool Model::hit_screen_bottom()
{
    return characters_[0].get_next_position().y > 560 ||
           characters_[1].get_next_position().y > 560;
}

bool Model::hit_screen_side(ge211::Posn<double>next)
{
    return next.x < 0 || next.x > 760;
}

bool Model::hit_screen_top(ge211::Posn<double>next)
{
    return next.y < 0;
}

bool Model::hits_block(ge211::Posn<double> next)
{
    for (Block& bb : blocks_)
    {
        ge211::Posn<double> bp=bb.get_pos();
        if(abs(bp.x - next.x) < 40 && abs(bp.y - next.y) < 40){

            return true;
        }
    }
return false;
}

bool Model::fall_on_block(Character player)
{

    ge211:: Posn<double>target_pos(0,0);
    for (Block& bb : blocks_)
    {
        ge211::Posn<double> bp=bb.get_pos();
        if(abs(bp.y - player.get_next_position().y) < 40 && abs(bp.x - player
                .get_next_position().x)< 40){
            target_pos.x = bp.x;
            target_pos.y = bp.y;
            if(player.get_position().y+40 > target_pos.y) {
                return false;
            }
            if(!(
                    player.get_position().x == player.get_next_position().x
                    ||
                    (((player.get_position().y - player.get_next_position().y)/(player
                                                                                        .get_position().x-player.get_next_position().x))*(target_pos
                                                                                                                                                  .x+40-player.get_position().x)
                     +player.get_position().y+40 <= target_pos.y
                     && player.get_next_position().x < player.get_position().x)
                    ||
                    (((player.get_position().y - player.get_next_position().y)/(player
                                                                                        .get_position().x-player.get_next_position().x))*(target_pos
                                                                                                                                                  .x-40-player.get_position().x)
                     +player.get_position().y+40 <= target_pos.y
                     && player.get_next_position().x > player.get_position().x))){
                return false;
            }
        }
    }
    return true;
}







