#include "Animation.h"

void Animation::changeFrame(void)
{
    if (mCurView.left < 32) // Needs to go right
    {
        mCurView.left += 16;
    }
    
    else // Needs to go to next row
    {
        if (mCurView.top < 32) // Needs to loop back to the top
        {
            mCurView.top += 16;
        }
        else // Needs to go to second or thrid row
        {
            mCurView.top = 0;
        }
        mCurView.left = 0;
    }
    this->setTextureRect(mCurView); // set the new view
}