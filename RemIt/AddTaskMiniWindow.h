#pragma once
#include "SFML/Graphics.hpp"
#include "Task.h"

namespace RemIt {
  class AddTaskMiniWindow {
  private:
    sf::RectangleShape background;
    sf::RectangleShape textFieldBackground;
    sf::Text textField;

    static const sf::Font* font;

    bool opened = false;

    sf::CircleShape button;
    bool isPressed = false;

    bool wasTaskCreated = false;
    Task created;
  public:
    AddTaskMiniWindow() = default;

    static void setFont(const sf::Font*);

    void init(const sf::Vector2f& size);

    void setPosition(const sf::Vector2f& vect);

    void pressedKey(const sf::Keyboard::Key& key);

    bool isInMiniWindow(const sf::Vector2f& pos);
    bool isInButton(const sf::Vector2f& pos);

    void pressButton();

    inline bool isTaskCreated() { return wasTaskCreated; };
    inline const Task& getcreatedTask() {
      wasTaskCreated = false;
      return created;
    };

    void open();
    inline void close() { opened = false; };

    inline bool isOpen() { return opened; };

    void display(sf::RenderWindow& window);
  };
}
