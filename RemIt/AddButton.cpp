#include "AddButton.h"

void RemIt::AddButton::init(float radius){
  circle.setRadius(radius);
  circle.setOrigin(sf::Vector2f(radius, radius));
}

void RemIt::AddButton::setPosition(const sf::Vector2f& pos){
  circle.setPosition(pos);
}