#ifndef SEMI_CIRCLE_SHAPE
#define SEMI_CIRCLE_SHAPE

#include "SFML/Graphics.hpp"

namespace sf {
  class SemiCircleShape : public sf::Shape {
  public:
    explicit SemiCircleShape(float radius = 0):
      m_radius(radius) {
      update();
    }

    void setRadius(float radius)
    {
      m_radius = radius;
      update();
    }

    float getRadius() const
    {
      return m_radius;
    }

    virtual unsigned int getPointCount() const
    {
      return 30;
    }

    virtual sf::Vector2f getPoint(unsigned int index) const
    {
      static const float pi = 3.141592654f;

      float angle = index * 2 * pi / getPointCount() - pi / 2;
      float x;
      if (angle >= pi / 2 && angle <= 3 * pi / 2)
        x = std::cos(angle) * m_radius;
      else
        x = 0;
      float y = std::sin(angle) * m_radius;

      return sf::Vector2f(m_radius + x, m_radius + y);
    }

  private:
    float m_radius;
  };
}

#endif