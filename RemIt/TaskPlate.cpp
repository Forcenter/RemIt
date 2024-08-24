#include "TaskPlate.h"

void RemIt::TaskPlate::processFading(){
  if (isFading) {
    if (animationDelay <= animationStateAmount && reverse)
      ++animationDelay;
    else {
      sf::Color color = stateCircle.getFillColor();
      sf::Color faded = sf::Color(color.r, color.g, color.b, fadePhases[fadingState]);
      stateCircle.setFillColor(faded);

      color = stateCircle.getOutlineColor();
      faded = sf::Color(color.r, color.g, color.b, fadePhases[fadingState]);
      stateCircle.setOutlineColor(faded);

      color = rect.getFillColor();
      faded = sf::Color(color.r, color.g, color.b, fadePhases[fadingState]);
      rect.setFillColor(faded);
      leftEnd.setFillColor(faded);
      rightEnd.setFillColor(faded);

      color = namePlate.getFillColor();
      faded = sf::Color(color.r, color.g, color.b, fadePhases[fadingState]);
      namePlate.setFillColor(faded);

      color = leftEnd.getOutlineColor();
      faded = sf::Color(color.r, color.g, color.b, fadePhases[fadingState]);
      leftEnd.setOutlineColor(faded);
      rightEnd.setOutlineColor(faded);
      rect.setOutlineColor(faded);
      if (reverse)
        --fadingState;
      else
        ++fadingState;
      if (fadingState == animationStateAmount || fadingState == -1) {
        if (reverse)
          ++fadingState;
        else
          --fadingState;
        isFading = false;
        if (!reverse) {
          leftEnd.setOutlineThickness(0.6);
          rightEnd.setOutlineThickness(0.6);
        }
      }
    }
  }
}

void RemIt::TaskPlate::processMovement(){
  if (isMoving) {
    if (animationDelay < ANIMATION_DELAY)
      ++animationDelay;
    else {
      setPos(startingPoint + (targetPoint - startingPoint) * animationPhases[animationState]);
      ++animationState;
      if (animationState == animationStateAmount)
        isMoving = false;
    }
  }
}

RemIt::TaskPlate::TaskPlate(const sf::Vector2f& size, Task* task): attachedTask(task), radius(size.y / 2), stateCircleRadius(radius+ UNIVERSAL_MARGIN){
  stateCircle.setRadius(stateCircleRadius);
  stateCircle.setOrigin(sf::Vector2f(stateCircleRadius, stateCircleRadius));
  leftEnd.setRadius(radius - 1);
  leftEnd.setOrigin(sf::Vector2f(radius - 1, radius - 1));
  rightEnd.setRadius(radius - 1);
  rightEnd.setOrigin(sf::Vector2f(radius - 1, radius - 1));
  sf::Vector2f rectSize = size;
  rectSize.x -= rectSize.y * 2;
  rect.setSize(rectSize);

  rightEnd.setRotation(180);

  leftEnd.setFillColor(sf::Color(242, 233, 228));
  rect.setFillColor(sf::Color(242, 233, 228));
  rightEnd.setFillColor(sf::Color(242, 233, 228));

  leftEnd.setOutlineColor(sf::Color(158, 155, 166));
  rightEnd.setOutlineColor(sf::Color(158, 155, 166));

  leftEnd.setOutlineThickness(0.6);
  rightEnd.setOutlineThickness(0.6);

  switch (attachedTask->getState()) {
  case 0:
    stateCircle.setFillColor(sf::Color(242, 124, 124));
    break;
  case 1:
    stateCircle.setFillColor(sf::Color(242, 185, 116));
    break;
  case 2:
    stateCircle.setFillColor(sf::Color(158, 242, 141));
    break;
  }

  sf::Color color = stateCircle.getFillColor();
  sf::Color background(74, 78, 105);
  stateCircle.setOutlineColor(sf::Color((color.r + background.r) / 2, (color.g + background.g) / 2, (color.b + background.b) / 2));
  stateCircle.setOutlineThickness(0.6);

  namePlate.setCharacterSize(25);
  namePlate.setFillColor(sf::Color(107, 105, 126));
  namePlate.setFont(*font);
  namePlate.setString(attachedTask->getName());
}

const sf::Vector2f& RemIt::TaskPlate::getPos() const{
  sf::Vector2f vect = stateCircle.getPosition();
  vect.y -= radius;
  vect.x -= stateCircleRadius;
  return vect;
}

void RemIt::TaskPlate::setPos(const sf::Vector2f& pos) {
  startingPoint = pos;
  sf::Vector2f vect = pos;
  vect.y += radius;
  vect.x += stateCircleRadius;
  stateCircle.setPosition(vect);
  vect.x += stateCircleRadius + UNIVERSAL_MARGIN + radius - 1;
  leftEnd.setPosition(vect);
  vect.x += rect.getSize().x;
  rightEnd.setPosition(vect);
  vect.x -= rect.getSize().x;
  vect.y -= radius;
  rect.setPosition(vect);
  vect.x -= radius / 2;
  vect.y += 4;
  namePlate.setPosition(vect);
}

void RemIt::TaskPlate::display(sf::RenderWindow* window){
  processFading();
  processMovement();
  window->draw(stateCircle);
  window->draw(leftEnd);
  window->draw(rightEnd);
  window->draw(rect);
  window->draw(namePlate);
}

bool RemIt::TaskPlate::isPointInCircle(const sf::Vector2f& point) const{
  sf::Vector2f pos = stateCircle.getPosition();
  return (pos.x - point.x) * (pos.x - point.x) + (pos.y - point.y) * (pos.y - point.y) <= (stateCircleRadius) * (stateCircleRadius);
}

bool RemIt::TaskPlate::isPointInPlate(const sf::Vector2f&) const{
  return false;
}

void RemIt::TaskPlate::startFading() {
  if (isInvisibilityLocked)
    return;
  animationDelay = 0;
  reverse = !reverse;
  if (!reverse)
    fadingState = 0;
  else
    fadingState = animationStateAmount - 1;
  isFading = true;
  leftEnd.setOutlineThickness(0);
  rightEnd.setOutlineThickness(0);
}

void RemIt::TaskPlate::setFont(const sf::Font* font_){
  font = font_;
}

void RemIt::TaskPlate::startMoving(const sf::Vector2f& whereTo){
  animationDelay = 0;
  animationState = 0;
  targetPoint = whereTo;
  startingPoint = stateCircle.getPosition() - sf::Vector2f(stateCircleRadius, radius);
  isMoving = true;
}
