#pragma once
#include "Constants.h"
#include "SFML/Graphics.hpp"

namespace RemIt {
  class WindowField {
  protected:
    bool isAnimated = false;

  public:
    sf::RectangleShape rect;
    int animationState = -1;

    WindowField() = default;

    virtual void startAnimation() = 0;

    virtual void setStandardSize(sf::Vector2f) = 0;

    virtual void processAnimation() = 0;

    inline const sf::Vector2f& getPosition() { return rect.getPosition(); }

    inline const sf::Vector2f& getSize() { return rect.getSize(); }
  };
}

