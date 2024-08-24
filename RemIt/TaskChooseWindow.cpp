#include "TaskChooseWindow.h"

void RemIt::TaskChooseWindow::processInputs() {
	sf::Event winEvent;
	bool justPressed = false;
	while (window.pollEvent(winEvent)) {
		switch (winEvent.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonPressed:
			switch (winEvent.mouseButton.button) {
			case sf::Mouse::Left:
				if (miniWindowAddTask.isInButton(sf::Vector2f(winEvent.mouseButton.x, winEvent.mouseButton.y))) {
					miniWindowAddTask.pressButton();
					miniWindowAddTask.close();
					continue;
				}

				if (addButton.isPointInCircle(sf::Vector2f(winEvent.mouseButton.x, winEvent.mouseButton.y))) {
					miniWindowAddTask.open();
					miniWindowAddTask.setPosition(addButton.getPosition());
				}

				justPressed = true;
				if (buttons[3]->press()) {
					filterButton->startFading();
					for (int i = 0; i < neededToBeDonePlates.size(); ++i)
						neededToBeDonePlates[i].startFading();
					for (int i = 0; i < beingDonePlates.size(); ++i)
						beingDonePlates[i].startFading();
					for (int i = 0; i < donePlates.size(); ++i)
						donePlates[i].startFading();
					break;
				}

				if (filterButton->isPointInButton(sf::Vector2i(winEvent.mouseButton.x, winEvent.mouseButton.y))) {
					filterButton->incState();
					sf::Vector2f pos = taskPlateStartPos;
					int state = filterButton->getState();
					switch (state) {
					case 0:
						for (auto& x : beingDonePlates) {
							x.unlockFadeStatus();
							x.setPos(pos);
							x.startFading();
							pos.y += SPACING_BETWEEN_TASKPLATES * taskPlateSize.y;
						}
						for (auto& x : neededToBeDonePlates) {
							x.unlockFadeStatus();
							x.setPos(pos);
							x.startFading();
							pos.y += SPACING_BETWEEN_TASKPLATES * taskPlateSize.y;
						}
						for (auto& x : donePlates) {
							x.startMoving(pos);
							pos.y += SPACING_BETWEEN_TASKPLATES * taskPlateSize.y;
						}
						break;
					case 1:
						for (auto& x : neededToBeDonePlates) {
							x.startFading();
							x.lockFadeStatus();
						}
						for (auto& x : beingDonePlates) {
							x.startMoving(pos);
							pos.y += SPACING_BETWEEN_TASKPLATES * taskPlateSize.y;
						}
						for (auto& x : donePlates) {
							x.startFading();
							x.lockFadeStatus();
						}
						break;
					case 2:
						for (auto& x : neededToBeDonePlates) {
							x.unlockFadeStatus();
							x.startFading();
							x.setPos(pos);
							pos.y += SPACING_BETWEEN_TASKPLATES * taskPlateSize.y;
						}
						for (auto& x : beingDonePlates) {
							x.startFading();
							x.lockFadeStatus();
						}
						break;
					case 3:
						for (auto& x : neededToBeDonePlates) {
							x.startFading();
							x.lockFadeStatus();
						}
						for (auto& x : donePlates) {
							x.unlockFadeStatus();
							x.startFading();
							x.setPos(pos);
							pos.y += SPACING_BETWEEN_TASKPLATES * taskPlateSize.y;
						}
						break;
					}
				}

				sf::Vector2f pos = field[fieldPurposes::topBorder]->rect.getPosition();
				sf::Vector2f size = field[fieldPurposes::topBorder]->rect.getSize();
				if (winEvent.mouseButton.x >= pos.x && winEvent.mouseButton.x <= pos.x + size.x && winEvent.mouseButton.y >= pos.y && winEvent.mouseButton.y <= pos.y + size.y) {
					lockedOnMouse = true;
					lastMousePosition = sf::Mouse::getPosition();
					break;
				}
				break;
			}
			break;
		case sf::Event::MouseButtonReleased:
			switch (winEvent.mouseButton.button) {
			case sf::Mouse::Left:
				lockedOnMouse = false;
				if (!justPressed)
					buttons[3]->unPress();
				break;
			}
			break;
		case sf::Event::KeyPressed:
			miniWindowAddTask.pressedKey(winEvent.key.code);
			break;
		}
	}
}

void RemIt::TaskChooseWindow::display() {
	window.clear(sf::Color::Black);
	for (int i = 0; i < fieldAmount; ++i)
		window.draw(field[i]->rect);
	//for (int i = 0; i < buttonAmount; ++i)
	//	window.draw(buttons[i]->display());
	window.draw(buttons[3]->display());

	window.draw(filterButton->display());

	int filter = filterButton->getState();
	for (auto& x : neededToBeDonePlates) {
		x.display(&window);
	}
	for (auto& x : beingDonePlates) {
		x.display(&window);
	}
	for (auto& x : donePlates) {
		x.display(&window);
	}

	if (lockedOnMouse) {
		window.setPosition(window.getPosition() - lastMousePosition + sf::Mouse::getPosition());
		lastMousePosition = sf::Mouse::getPosition();
	}

	if (miniWindowAddTask.isOpen())
		miniWindowAddTask.display(window);

	window.display();
}

void RemIt::TaskChooseWindow::processAnimations() {
	for (int i = 0; i < fieldAmount; ++i)
		field[i]->processAnimation();
}

const RemIt::WinEvent& RemIt::TaskChooseWindow::processEvents(){
	WinEvent result;
	/*for (int i = 0; i < buttonAmount; ++i) {
		result = buttons[i]->update(sf::Mouse::getPosition() - window.getPosition());
		if (result.window != winNames::none && result.deed != winWhatToDo::none)
			return result;
	}*/
	result = buttons[3]->update(sf::Mouse::getPosition() - window.getPosition());
	return result;
}

bool RemIt::TaskChooseWindow::update(std::stack<WinEvent>&) {
	processAnimations();
	processInputs();
	processEvents();
	display();
	return window.isOpen();
}

void RemIt::TaskChooseWindow::loadAsset(std::string assetFilePath) {
	std::wifstream fin;
	buttons = new Button*[buttonAmount];
	fin.open(assetFilePath);
	loadWindowAsset(fin);
	
	for (int i = 0; i < fieldAmount; ++i) {
		int k;
		fieldTypes type;
		int x, y, width, height;
		int r, g, b;

		fin >> k;
		type = static_cast<fieldTypes>(k);
		switch (type) {
		case fieldTypes::normal:
			field[i] = new StaticWindowField();
			break;
		case fieldTypes::collapseHor:
			field[i] = new CollapseHorWindowField();
			break;
		}
		fin >> x >> y >> width >> height >> r >> g >> b;
		field[i]->rect.setFillColor(sf::Color(r, g, b));
		field[i]->rect.setPosition(sf::Vector2f(x, y));
		field[i]->rect.setSize(sf::Vector2f(width, height));
		switch (type) {
		case fieldTypes::collapseHor:
			field[i]->setStandardSize(sf::Vector2f(width, height));
			break;
		}
	}

	/*for (int i = 0; i < buttonAmount; ++i) {
		int k;
		char textureFile[256];

		fin >> k;
		fin.ignore(1);
		fin.getline(textureFile, 256);

		buttons[i] = new Button(textureFile, field[k]);
	}*/
	int k;
	wchar_t textureFile[256];

	int radius;

	fin >> k >> radius;
	fin.ignore(1);
	fin.getline(textureFile, 256);
	buttons[3] = new Button(textureFile, field[k], field[fieldPurposes::taskBar]->getPosition() + sf::Vector2f(field[fieldPurposes::taskBar]->getSize().x - radius, -((field[fieldPurposes::topBorder]->getSize().y - radius * 2) / 2 + radius)), radius);

	fin >> radius;
	filterButton = new FilterButton(field[fieldPurposes::taskBar]->getPosition() - sf::Vector2f(-radius, (field[fieldPurposes::topBorder]->getSize().y - radius * 2) / 2 + radius), radius);

	taskPlateSize.y = field[fieldPurposes::topBorder]->getSize().y * 4 / 5;
	taskPlateSize.x = field[fieldPurposes::taskBar]->getSize().x - taskPlateSize.y - UNIVERSAL_MARGIN;

	miniWindowAddTask.init(sf::Vector2f(400, 200));
}

void RemIt::TaskChooseWindow::createTaskPlates(Task* nTBD_, Task* bD_, Task* d_, int nTBDNum_, int bDNum_, int dNum_){
	neededToBeDonePlates.reserve(nTBDNum_);
	beingDonePlates.reserve(bDNum_);
	donePlates.reserve(dNum_);
	for (int i = 0; i < nTBDNum_; ++i) {
		neededToBeDonePlates.push_back(TaskPlate(taskPlateSize, &nTBD_[i]));
	}
	for (int i = 0; i < bDNum_; ++i) {
		beingDonePlates.push_back(TaskPlate(taskPlateSize, &bD_[i]));
	}
	for (int i = 0; i < dNum_; ++i) {
		donePlates.push_back(TaskPlate(taskPlateSize, &d_[i]));
	}
	sf::Vector2f pos = taskPlateStartPos;
	for (auto& x : beingDonePlates) {
		x.setPos(pos);
		pos.y += taskPlateSize.y * SPACING_BETWEEN_TASKPLATES;
	}
	for (auto& x : neededToBeDonePlates) {
		x.setPos(pos);
		pos.y += taskPlateSize.y * SPACING_BETWEEN_TASKPLATES;
	}
	for (auto& x : donePlates) {
		x.setPos(pos);
		pos.y += taskPlateSize.y * SPACING_BETWEEN_TASKPLATES;
	}
}

bool RemIt::TaskChooseWindow::isTaskCreated(){
	return miniWindowAddTask.isTaskCreated();
}

const RemIt::Task& RemIt::TaskChooseWindow::getCreatedTask(){
	return miniWindowAddTask.getcreatedTask();
}
