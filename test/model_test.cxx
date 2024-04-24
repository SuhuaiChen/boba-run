#include "model.hxx"
#include <catch.hxx>

TEST_CASE("player not on a block")
{
Model m;
    CHECK(!m.is_game_over());
    //going up, then falling down, due to acceleration
    m.character_one().set_position(120,10);
    m.character_one().set_next_position_x(120);
    m.character_one().set_next_position_y(0);
    m.character_one().set_vertical_velocity(-1);
    CHECK(m.character_one().get_position() == ge211::geometry::Posn<double>(120,10));
    m.on_frame(1);
    CHECK(m.character_one().get_position() == ge211::geometry::Posn<double>
            (120,9));
    m.on_frame(1);
    CHECK(m.character_one().get_position() == ge211::geometry::Posn<double>
            (120,8.5));
    m.on_frame(1);
    CHECK(m.character_one().get_position() == ge211::geometry::Posn<double>
            (120,8.5));
    m.on_frame(1);
    CHECK(m.character_one().get_position() == ge211::geometry::Posn<double>
            (120,9));
    m.on_frame(1);
    CHECK(m.character_one().get_position() == ge211::geometry::Posn<double>
            (120,10));
    m.on_frame(1);
    CHECK(m.character_one().get_position() == ge211::geometry::Posn<double>
            (120,11.5));
    m.on_frame(1);
    CHECK(m.character_one().get_position() == ge211::geometry::Posn<double>
            (120,13.5));

    //falling down
    m.character_two().set_position(240,0);
    m.character_two().set_next_position_x(240);
    m.character_two().set_next_position_y(0);
    m.character_two().set_vertical_velocity(0.5);
    m.on_frame(1);
    CHECK(m.character_two().get_position() == ge211::geometry::Posn<double>
            (240,0.5));
    m.on_frame(1);
    CHECK(m.character_two().get_position() == ge211::geometry::Posn<double>
            (240,1.5));
    m.on_frame(1);
    CHECK(m.character_two().get_position() == ge211::geometry::Posn<double>
            (240,3));
    m.on_frame(1);
    CHECK(m.character_two().get_position() == ge211::geometry::Posn<double>
            (240,5));
    m.on_frame(1);
    CHECK(m.character_two().get_position() == ge211::geometry::Posn<double>
            (240,7.5));

}

TEST_CASE("land on a block"){
    Model m;
    //initialize
    m.character_one().set_position(30,480);
    m.character_one().set_next_position_x(30);
    m.character_one().set_next_position_y(480);
    m.on_frame(1);
    CHECK(m.character_one().get_position()==
          ge211::geometry::Posn<double>(30,480));
    //jump and then land on a block
    m.character_one().set_vertical_velocity(-12);
    for(int i = 1; i< 50;i++){
        m.on_frame(1);
        CHECK(m.character_one().get_position().y == 480-12*i+0.25*i*(i-1));
    }
    m.on_frame(1);
    CHECK(!(m.character_one().get_position().y == 480-12*50+0.25*50*(50-1)));
    CHECK(m.character_one().get_position().y == 480);
    m.on_frame(1);
    CHECK(m.character_one().get_position().y == 480);
    m.on_frame(1);
    CHECK(m.character_one().get_position().y == 480);

}

TEST_CASE("walk on the rocks till fall"){
    //Here I use the mutation of next x-coordinate to simulate left and right
    // keys
    Model m;
    //initialize
    m.character_one().set_position(0,480);
    m.character_one().set_next_position_x(0);
    m.character_one().set_next_position_y(480);
    m.on_frame(1);
    CHECK(m.character_one().get_position()==
    ge211::geometry::Posn<double>(0,480));
    //moves rightward, falls when it is not on a block anymore
    for(int i =1;i<12;i++){
        m.character_one().set_next_position_x(i*10);
        m.on_frame(1);
        CHECK(m.character_one().get_position()==
              ge211::geometry::Posn<double>(i*10,480));
    }
    m.character_one().set_next_position_x(120);
    m.on_frame(1);
    CHECK(m.character_one().get_position()==
          ge211::geometry::Posn<double>(120,480.5));
    m.character_one().set_next_position_x(130);
    m.on_frame(1);
    CHECK(m.character_one().get_position()==
          ge211::geometry::Posn<double>(130,481.5));

    //initialize
    m.character_one().set_position(0,480);
    m.character_one().set_next_position_x(0);
    m.character_one().set_next_position_y(480);
    m.character_two().set_position(760,320);
    m.character_two().set_next_position_x(760);
    m.character_two().set_next_position_y(320);
    m.on_frame(1);
    CHECK(m.character_two().get_position()==
          ge211::geometry::Posn<double>(760,320));
    //moves leftward, falls when it is not on a block anymore
    for(int i =1;i<24;i++){
        m.character_two().set_next_position_x(760-i*10);
        m.on_frame(1);
        CHECK(m.character_two().get_position()==
              ge211::geometry::Posn<double>(760-i*10,320));
    }
    m.character_two().set_next_position_x(520);
    m.on_frame(1);
    CHECK(m.character_two().get_position()==
          ge211::geometry::Posn<double>(520,321.5));
    m.character_two().set_next_position_x(510);
    m.on_frame(1);
    CHECK(m.character_two().get_position()==
          ge211::geometry::Posn<double>(510,323.5));
}


TEST_CASE("A player carries the key"){
    Model m;
    //initialize
    m.character_one().set_position(0,480);
    m.character_one().set_next_position_y(480);
    m.character_one().set_next_position_x(40);
    m.character_one().set_vertical_velocity(0);
    m.key().set_pos(80,490);

    CHECK(!m.key().get_state());
    CHECK(!m.key().get_state());
    m.character_one().set_next_position_x(50);
    m.on_frame(1);
    CHECK(m.character_one().get_position() == ge211::geometry::Posn<double>
            (50,480));
    //get key
    CHECK(m.key().get_state());
    CHECK(m.key().get_position() == ge211::geometry::Posn<double>(80,490));
    m.on_frame(1);
    for(int i = 0; i<= 5;i++){
        m.character_one().set_next_position_x(50-i*10);
        m.on_frame(1);
        CHECK(m.character_one().get_position() == m.key().get_position());
    }

    Model n;
    //initialize
    n.key().set_pos(0,490);
    n.character_two().set_position(40,480);
    n.character_two().set_next_position_x(30);
    n.character_two().set_next_position_y(480);
    n.on_frame(1);
    //jump after getting key
    CHECK(n.key().get_state());
    n.character_two().set_vertical_velocity(12);
    for (int i = 0; i <20; i++)
    {
        n.on_frame(1);
        CHECK(n.character_two().get_position() == n.key().get_position());
    }

}

TEST_CASE("movement of monster"){
Model m;


for(int i = 0; i <400; i++){
    int x = m.monster().get_position().x;
    int y = m.monster().get_position().y;
    m.on_frame(1);
    //constant speed
    CHECK(abs(x-m.monster().get_position().x) == 2);
    CHECK(y == m.monster().get_position().y);
    //within boundary
    CHECK(m.monster().get_position().x>=360);
    CHECK(m.monster().get_position().x<=770);
}
}

TEST_CASE("U Lose"){
    //fall off the block, then hit the bottom
    Model m;
    m.character_one().set_position(110,480);
    m.character_one().set_next_position_x(110);
    m.character_one().set_next_position_y(480);
    m.character_one().set_vertical_velocity(0);
    m.on_frame(1);
    m.character_one().set_next_position_x(120);
    for(int i = 0; i<17;i++){
        m.on_frame(1);
        CHECK(m.character_one().get_position().y<=560);
        CHECK(!m.is_game_over());

    }
    m.on_frame(1);
    CHECK(m.character_one().get_position().y > 560);
    CHECK(m.is_game_over());
    CHECK(!m.game_win());

    //hit the monster
    Model n;
    n.character_two().set_position(600,120);
    n.character_two().set_next_position_x(600);
    n.character_two().set_next_position_y(120);
    n.character_two().set_vertical_velocity(0);
    for(int i = 0; i<22;i++){
        n.on_frame(1);
        CHECK(!n.is_game_over());
        CHECK(n.character_two().get_position() ==
        ge211::geometry::Posn<double>(600,120));
        CHECK(n.character_two().get_position().x - n.monster().get_position()
        .x >35);
    }
    n.on_frame(1);
    CHECK(n.character_two().get_position().x - n.monster().get_position().x <
            35);
    CHECK(n.is_game_over());
    CHECK(!n.game_win());

}

TEST_CASE("Yayyy"){

    //two players with a key
    Model a;
    CHECK(!a.is_game_over());
    a.character_one().set_position(740,40);
    a.character_one().set_next_position_x(740);
    a.character_one().set_next_position_y(40);
    a.character_one().set_vertical_velocity(0);
    a.character_two().set_position(740,40);
    a.character_two().set_next_position_x(740);
    a.character_two().set_next_position_y(40);
    a.character_two().set_vertical_velocity(0);
    a.key().set_pos(740,40);
    a.on_frame(1);
    CHECK(a.is_game_over());
    CHECK(a.game_win());

    //one player with a key
    Model c;
    CHECK(!c.is_game_over());
    c.character_one().set_position(0,0);
    c.character_one().set_next_position_x(0);
    c.character_one().set_next_position_y(0);
    c.character_one().set_vertical_velocity(0);
    c.character_two().set_position(740,40);
    c.character_two().set_next_position_x(740);
    c.character_two().set_next_position_y(40);
    c.character_two().set_vertical_velocity(0);
    c.key().set_pos(740,40);
    c.on_frame(1);
    CHECK(!c.is_game_over());


    //two players without a key
    Model b;
    CHECK(!b.is_game_over());
    b.character_one().set_position(740,40);
    b.character_one().set_next_position_x(740);
    b.character_one().set_next_position_y(40);
    b.character_one().set_vertical_velocity(0);
    b.character_two().set_position(740,40);
    b.character_two().set_next_position_x(740);
    b.character_two().set_next_position_y(40);
    b.character_two().set_vertical_velocity(0);
    b.key().set_pos(0,0);
    b.on_frame(1);
    CHECK(!b.is_game_over());

}
//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate your functional requirements.
//
