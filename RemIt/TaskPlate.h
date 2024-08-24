#ifndef TASK_PLATE_
#define TASK_PLATE_

#include "SFML/Graphics.hpp"
#include "SemiCircleShape.h"
#include "Constants.h"
#include "Task.h"

namespace RemIt {
  class TaskPlate {
  private:
    Task* attachedTask;

    sf::RectangleShape rect;
    sf::SemiCircleShape leftEnd;
    sf::SemiCircleShape rightEnd;
    sf::CircleShape stateCircle;

    static const sf::Font* font;
    sf::Text namePlate;

    int radius;
    const int stateCircleRadius;

    bool isInvisibilityLocked = false;
    bool isFading = false;
    int fadingState = 0;
    bool reverse = true;
    int fadingDelay = 0;

    bool isMoving = false;
    int animationState = 0;
    int animationDelay = 0;
    sf::Vector2f startingPoint = {};
    sf::Vector2f targetPoint = {};

    void processMovement();

    void processFading();

  public:
    TaskPlate(const sf::Vector2f& size, Task* task);

    const sf::Vector2f& getPos() const;

    void setPos(const sf::Vector2f&);

    inline void incState() { attachedTask->incState(); };

    inline int getState() { return attachedTask->getState(); }

    void display(sf::RenderWindow* window);

    bool isPointInCircle(const sf::Vector2f&) const;

    bool isPointInPlate(const sf::Vector2f&) const;

    inline void lockFadeStatus() { isInvisibilityLocked = true; };
    inline void unlockFadeStatus() { isInvisibilityLocked = false; };

    void startFading();

    void startMoving(const sf::Vector2f& whereTo);

    static void setFont(const sf::Font* font);

    inline bool operator==(const TaskPlate& other) { return *attachedTask == *other.attachedTask; };
    inline bool operator<(const TaskPlate& other) { return *attachedTask < *other.attachedTask; };
    inline bool operator>(const TaskPlate& other) { return *attachedTask > *other.attachedTask; };
  };
}

#endif