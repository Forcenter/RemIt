#include "CollapseHorWindowField.h"

void RemIt::CollapseHorWindowField::startAnimation() {
  isAnimated = true;
  reverse = !reverse;
  if (!reverse)
    animationState = animationStateAmount - 1;
  else
    animationState = 0;
  animationDelay = 0;
}

void RemIt::CollapseHorWindowField::setStandardSize(sf::Vector2f size){
  standardSize = size;
}

void RemIt::CollapseHorWindowField::processAnimation() {
  if (isAnimated) {
    if (animationDelay < ANIMATION_DELAY)
      ++animationDelay;
    else {
      sf::Vector2f vect = standardSize;
      vect.x *= animationPhases[animationState];
      rect.setSize(vect);
        
      if (!reverse)
        --animationState;
      else
        ++animationState;

      if (animationState == animationStateAmount || animationState == -1) {
        isAnimated = false;
      }
    }
  }
  }
