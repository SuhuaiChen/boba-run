#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    void draw(ge211::Sprite_set& set) override;
    void on_frame(double dt) override;
    void on_key(ge211::Key key) override;
private:
    Model model_;
    View view_;
};
