#pragma once

#include "SFML/Graphics.hpp"
#include "Constants.h"

namespace RemIt {
  class FilterButton {
  private:
    sf::CircleShape sprite;

    int state = 0;
    static const int maxState = 3;

    int fadingState = -1;
    bool reverse = true;
    int radius;
  
  public:
    FilterButton(const sf::Vector2f& pos, int radius);

    void incState();

    bool isPointInButton(const sf::Vector2i&);

    void startFading();

    inline int getState() { return state; };

    sf::CircleShape& display();
  };
}