#include <SFML/Graphics.hpp>

using namespace sf;

class Animation : public Sprite
{
public:

    Animation(const Texture &texture) : Sprite(texture) 
    {
       // Initialize the view of the animation so that it shows the 1st frame
        mCurView.left = 0;
        mCurView.top = 0;
        mCurView.height = 16;
        mCurView.width = 16;
        this->setTextureRect(mCurView);
    };

    void changeFrame(void);

private:
    sf::IntRect mCurView;
};