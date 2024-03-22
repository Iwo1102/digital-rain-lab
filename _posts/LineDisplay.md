---
layout: post
title: Displaying the Lines
tags: cpp coding project
categories: demo
---

# Line Display 

To display the lines i used `GotoXY()` function given that uses `SetConsoleCursorPosition()` go set where each character should go, which then I printed.

```
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
	//Blocks this thread until the shared mutex is not used
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
```
The charactwer will be printed as whitespace if they go below a set set line maxY. After all characters have been printed the cursor will only print whitespace after.

The mutex ensures that `SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord)` has ample time to print without getting overwritten in the middle of the execution.

