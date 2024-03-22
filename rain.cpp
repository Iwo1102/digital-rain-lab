#include "rain.h"

void Rain::setLineStart(std::vector<unsigned int> n) {
#if DEBUG
	//std::cout << "SetLineStart" << std::endl;
#endif
	lineCoords[0][0] = n[0];
	lineCoords[0][1] = n[1];
}

void Rain::setChars(std::string c) {
#if DEBUG
	//std::cout << "setChars" << std::endl;
#endif
	c = chars;
}

void Rain::gotoXY(std::vector<unsigned int> n) {
#if DEBUG
	//std::cout << "gotoXY" << std::endl;
#endif
	COORD coord;
	coord.X = n[0];
	coord.Y = n[1];

#if DEBUG
//	std::cout << "x" << n[0] << std::endl;
//	std::cout << "y" << n[1] << std::endl;
#else 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#endif

}

void Rain::displayLine(int n) {
#if DEBUG
	//std::cout << "displayLine" << std::endl;
#endif
	std::lock_guard<std::mutex> lock(mutex);
	if (n < lineLength)
		for (auto i = 0; i < n; i++) {
			gotoXY(lineCoords[i]);
			if (lineCoords[i][1] == maxY)
				chars[i] = ' ';
#if DEBUG
#else
			std::cout << chars[i];
#endif // DEBUG
		}
	else {
		for (auto i = 0; i < lineLength; i++) {
			gotoXY(lineCoords[i]);
			if (lineCoords[i][1] == maxY)
				chars[i] = ' ';
#if DEBUG
#else
			std::cout << chars[i];
#endif // DEBUG
		}
	}
}

void Rain::randomise(int var) {
#if DEBUG
//	std::cout << "Randomise" << std::endl;
#endif

	std::uniform_int_distribution<int> coordXDis(0, maxXCoord), coordYDis(0, maxYCoord), lengthDis(5, 25), charDis(48, 122), intervalDis(50, 200);
	std::random_device rand;

	switch (var) {
	case randomiseType::coord:
		lineCoords[0].insert(lineCoords[0].begin(), coordXDis(rand));
		lineCoords[0].insert(lineCoords[0].begin() + 1, coordYDis(rand));
		for (auto i = 1; i < lineLength; i++) {
			lineCoords[i].insert(lineCoords[i].begin(), lineCoords[0][0]);
			lineCoords[i].insert(lineCoords[i].begin() + 1, lineCoords[0][1]);
		}
		break;
	case randomiseType::length:
		lineLength = lengthDis(rand);
		break;
	case randomiseType::chars:
		for (auto i = 0; i < lineLength; i++) {
			chars[i] = charDis(rand);
		}
		chars[lineLength - 1] = ' ';
		break;
	case randomiseType::interval:
		interval = intervalDis(rand);
		break;
	default:
		std::cout << "rand failed" << std::endl;
		break;
	}

}

void Rain::fall(int n) {
#if DEBUG
//	std::cout << "falling" << std::endl;
#endif
	if (n < lineLength)
		for (auto i = 0; i < n; i++)
			lineCoords[i][1]++;
	else
		for (auto i = 0; i < lineLength; i++)
			lineCoords[i][1]++;

#if DEBUG
	//	std::cout << "linecoords[n]: " << n << ": " << lineCoords[n][0] << ", " << lineCoords[n][1] << std::endl;
#endif
}

void Rain::run() {
#if DEBUG
		std::cout << "running on thread: " << std::this_thread::get_id() << std::endl;
#endif
	auto i = 0;
	while (1) {
		fall(i);
		displayLine(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(interval));
		if (lineCoords[lineLength - 1][1] == maxY)
			break;
		i++;
	}
	active = false;
#if DEBUG
	std::cout << "run ended " << std::this_thread::get_id() << std::endl;
#endif
	
}

Rain::Rain() {
	active = 1;
	randomise(randomiseType::length);
	lineCoords.resize(lineLength);
	for (auto i = lineCoords.begin(); i != lineCoords.end(); i++)
		i->resize(2);

	chars.resize(lineLength);
	randomise(randomiseType::chars);
	randomise(randomiseType::coord);
	randomise(randomiseType::interval);
}

Rain::Rain(bool* n) {
	*n = true;
	active = *n;
	randomise(randomiseType::length);
	lineCoords.resize(lineLength);
	for (auto i = lineCoords.begin(); i != lineCoords.end(); i++)
		i->resize(2);

	chars.resize(lineLength);
	randomise(randomiseType::chars);
	randomise(randomiseType::coord);
	randomise(randomiseType::interval);
#if DEBUG
	std::cout << "n: " << *n << std::endl;
#endif
}

Rain::Rain(const Rain& r) {
#if DEBUG
	std::cout << "Copy Constructor on thread: " << std::this_thread::get_id() << std::endl;
#endif
	lineCoords = r.lineCoords;
	chars = r.chars;
	lineLength = r.lineLength;
	lengthDisplayed = r.lengthDisplayed;
	interval = r.interval;
	active = r.active;
	thread = std::thread(&Rain::run, this);
	
}

Rain::Rain(Rain&& r) noexcept : lineCoords(r.lineCoords),
						chars(r.chars),
						lineLength(r.lineLength),
						lengthDisplayed(r.lengthDisplayed),
						interval(r.interval),
						active(r.active) {
#if DEBUG
	std::cout << "Assignment Constructor on thread: " << std::this_thread::get_id() << std::endl;
#endif
	r.lineCoords.clear();
	r.chars.clear();
	r.lineLength = 0;
	r.lengthDisplayed = 0;
	r.interval = 0;
	r.active = 0;
}

Rain& Rain::operator=(const Rain& r) {
	if (this != &r) {
		lineCoords = r.lineCoords;
		chars = r.chars;
		lineLength = r.lineLength;
		lengthDisplayed = r.lengthDisplayed;
		interval = r.interval;
		active = r.active;
	}
	return *this;
}

Rain::~Rain() {
#if DEBUG
	std::cout << "Destructor called on thread: " << std::this_thread::get_id() << std::endl;
#endif

	if (thread.joinable())
		thread.join();

	for (auto& innerVector : lineCoords) {
		innerVector.clear();
	}	

	lineCoords.clear();
	chars.clear();
	lineLength = 0;
	lengthDisplayed = 0;
	interval = 0;

	
#if DEBUG
	std::cout << "destructed " << std::this_thread::get_id() << std::endl;
#endif

}