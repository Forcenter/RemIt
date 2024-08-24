#pragma once
#include "SFML/Graphics.hpp"

namespace RemIt {
  class AddButton {
  private:
    sf::CircleShape circle;

  public:
    AddButton() = default;

    bool isPointInCircle(const sf::Vector2f& point) {
      float radius = circle.getRadius();
      sf::Vector2f pos = circle.getPosition();
      return (pos.x - point.x) * (pos.x - point.x) + (pos.y - point.y) * (pos.y - point.y) <= radius * radius;
    }

    void init(float radius);

    inline const sf::CircleShape& getSprite() { return circle; };

    void setPosition(const sf::Vector2f& pos);

    inline const sf::Vector2f& getPosition() { return circle.getPosition(); }
  };
}
