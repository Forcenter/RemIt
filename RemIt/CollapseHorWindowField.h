#pragma once
#include "windowField.h"
namespace RemIt {
  class CollapseHorWindowField : public WindowField {
  private:
    bool reverse = true;
    int animationDelay = 0;

  public:
    sf::Vector2f standardSize;

    void startAnimation() override;

    void setStandardSize(sf::Vector2f) override;

    void processAnimation() override;
  };
}

