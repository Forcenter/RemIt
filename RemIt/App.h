#ifndef APP_
#define APP_

#include "TaskChooseWindow.h"
#include <queue>
#include "Task.h"

namespace RemIt {
	class App {
	private:
		std::stack<WinEvent> events;

		Window** windows;
		Window* activeWindow;

		sf::Vector2i windowPos;

		Task neededToBeDone[256];
		Task beingDone[256];
		Task done[256];

		sf::Font font;

		int nTBD = 0;
		int bD = 0;
		int d = 0;

		int counter = 0;

		void processEvents() {};
	public:
		App(std::string assetFilePath);
		
		bool update();

	};
}

#endif

