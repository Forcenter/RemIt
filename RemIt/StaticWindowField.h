#pragma once
#include "WindowField.h"
namespace RemIt {
  class StaticWindowField : public WindowField {
    void processAnimation() override {};

    void setStandardSize(sf::Vector2f) override {};

    void startAnimation() override {};
  };
}

