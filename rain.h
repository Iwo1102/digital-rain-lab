#ifndef RAIN_H
#define RAIN_H

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <windows.h>


#include "Timer.h"

#define DEBUG 0

enum randomiseType {
	coord,
	length,
	chars,
	interval
};

const int maxY = 30,
maxObjects = 1000,
maxXCoord = 80,
maxYCoord = 20;



class Rain {
public:
	void setLineStart(std::vector<unsigned int> n);
	std::vector<std::vector<unsigned int>> getLineCoords() { return lineCoords; }
	void setChars(std::string);
	std::string getChars() { return chars; }
	int getLineLength() { return lineLength; }
	void gotoXY(std::vector<unsigned int>);
	void displayLine(int);
	void randomise(int);
	void fall(int);
	void run();

	Rain();
	Rain(bool*);
	Rain(const Rain&);
	Rain(Rain&&) noexcept;

	Rain& operator=(const Rain&);

	~Rain();


private:

	std::vector<std::vector<unsigned int>> lineCoords;
	std::string chars = "";
	int lineLength = 0;
	int lengthDisplayed = 0;
	static std::mutex mutex;
	std::thread thread;
	int interval = 0;
	bool active;
};

#endif // !RAIN_H
