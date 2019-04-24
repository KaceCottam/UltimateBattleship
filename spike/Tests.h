#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


using std::cout;
using std::endl;

class Tests
{
public:
    void testAnimationChangeFrame(void);
    void testUpdateFleetStatus(void);
    void testIsWinner(void);
    void testAnimationResetFrame(void);
    void testAnimationDisplay(void);
    void testShipPlacement(void);
};