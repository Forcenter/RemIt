#include "App.h"

RemIt::App::App(std::string assetFilePath){
	std::ifstream fin;
	fin.open(assetFilePath);

	std::string str;
	fin >> str;

	font.loadFromFile(str);
	TaskPlate::setFont(&font);

	AddTaskMiniWindow::setFont(&font);

	windows = new Window*[winAmount];
	windows[static_cast<int>(winNames::passiveIconWindow)];
	windows[static_cast<int>(winNames::smallTaskWindow)];
	windows[static_cast<int>(winNames::taskListWindow)] = new TaskChooseWindow;
	/*for (int i = 0; i < winAmount; ++i) {
		fin >> assetForWin;
		windows[i]->loadAsset(assetForWin);
	}*/
	windows[2]->loadAsset("taskChooseWindowAsset.txt");

	beingDone[0].setName(L"abobus");
	beingDone[0].incState();
	++bD;
	beingDone[1].setName(L"Lopuh");
	beingDone[1].incState();
	++bD;

	neededToBeDone[0].setName(L"abibus");
	++nTBD;
	neededToBeDone[1].setName(L"Lopuhus");
	++nTBD;

	done[0].setName(L"Chuckcha съел жижу");
	done[0].incState();
	done[0].incState();
	++d;
	done[1].setName(L"Жижа съела Chukchu");
	done[1].incState();
	done[1].incState();
	++d;

	windows[2]->makeActive(sf::Vector2i(200, 100));
	activeWindow = windows[2];

	activeWindow->createTaskPlates(neededToBeDone, beingDone, done, nTBD, bD, d);
	fin.close();
}

bool RemIt::App::update() {
	windowPos = activeWindow->getPosition();
	return activeWindow->update(events);
}

const sf::Font* RemIt::TaskPlate::font = nullptr;
const sf::Font* RemIt::AddTaskMiniWindow::font = nullptr;