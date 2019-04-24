#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Animation : public Sprite
{
public:
    Animation() = default;
    Animation(const Texture &texture) : Sprite(texture) 
    {
       // Initialize the view of the animation so that it shows the 1st frame
        mCurView.left = 0;
        mCurView.top = 0;
        mCurView.height = 16;
        mCurView.width = 16;
        this->setTextureRect(mCurView);

        mCurFrame = 0;
    };

    void changeFrame(void);
    int getCurFrame(void);
    void resetFrame();

private:
    sf::IntRect mCurView;
    int mCurFrame;
};