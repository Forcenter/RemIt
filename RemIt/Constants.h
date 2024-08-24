#ifndef CONSTANTS_
#define CONSTANTS_

#define _UNICODE

#include <iostream>

namespace RemIt {
	const int winAmount = 3;
	enum class winNames {
		none = 4,
		passiveIconWindow = 0,
		smallTaskWindow = 1,
		taskListWindow = 2,
		infoTaskWindow = 3
	};

	enum class winWhatToDo {
		none = 0,
		show = 1,
		hide = 2
	};

	struct WinEvent {
		winNames window;
		winWhatToDo deed;
	};
	
	const int animationStateAmount = 12;
	const float animationPhases[animationStateAmount] = {
		0.f,
		0.075f,
		0.15f,
		0.25f,
		0.35f,
		0.5f,
		0.65f,
		0.75f,
		0.85f,
		0.925f,
		0.975f,
		1
	};
	const int fadePhases[animationStateAmount] = {
		255,
		223,
		191,
		159,
		128,
		96,
		64,
		32,
		0,
		0,
		0,
		0
	};

	enum class fieldTypes {
		normal,
		collapseHor
	};

	const float SPACING_BETWEEN_TASKPLATES = 1.4f;
	const int TIMER_MAX_VALUE = 500;
	const int FRAMERATE = 60;
	const int UNIVERSAL_MARGIN = 5;
	const int ANIMATION_DELAY = 10;
}

#endif