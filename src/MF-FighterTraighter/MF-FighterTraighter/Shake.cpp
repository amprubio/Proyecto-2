#include "Shake.h"

void Shake::update()
{
    if (shaking)
    {
        updateShake();
    }
   
}

void Shake::updateShake()
{
    if (delta==0)
    {
        SDL_HapticRumblePlay(app_->getInputManager()->getHaptic(0), 0.75, SHAKE_TIME_MS);
        
    }
    //Add passed milliseconds to timer... If timer exceeds configuration, shaking ends
    delta = SDL_GetTicks() - timeStart_;
   // shakeTimer += delta;
    if (delta > SHAKE_TIME_MS)
    {
       //Shaking ends 
        timeStart_ = SDL_GetTicks();
        delta = 0;
        shaking = false;
        xOffset = 0;
        yOffset = 0;
    }
    else
    {
        applyScreenShake();
    }
}

void Shake::applyScreenShake()
{
    //Depending on shake direction, the screen is moved either to the top left, or the bottom right
    if (shakeDirection)
    {
        xOffset -= 1.5f * delta;
        if (xOffset < -SHAKE_OFFSET)
        {
            //SWITCH DIRECTION
            xOffset = -SHAKE_OFFSET;
            shakeDirection = !shakeDirection;
        }
        yOffset = xOffset;
    }
    else
    {
        xOffset += 1.5f * delta;
        if (xOffset > SHAKE_OFFSET)
        {
            //SWITCH DIRECTION
            xOffset = SHAKE_OFFSET;
            shakeDirection = !shakeDirection;
        }
        yOffset = xOffset;
    }
    cam->setPosition(xOffset, yOffset);
}
