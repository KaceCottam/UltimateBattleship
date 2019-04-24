#include "Tests.h"
#include <iostream>

int main()
{
  Tests t;
  t.testAnimationChangeFrame();
  t.testUpdateFleetStatus();
  t.testIsWinner();
  t.testAnimationResetFrame();
  t.testShipPlacement();
  
  
  t.testAnimationDisplay();

  std::cin.get();

  return 0;
}