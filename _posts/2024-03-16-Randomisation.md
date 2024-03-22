---
layout: post
title: Randomisation
tags: cpp coding project
categories: demo
---

# Radmomisation
I wanted many aspects of the *drops* be randomised.

## Code

```
void Rain::randomise(int var) {
#if DEBUG
//	std::cout << "Randomise" << std::endl;
#endif

	std::uniform_int_distribution<int> coordXDis(0, maxXCoord), coordYDis(0, maxYCoord), lengthDis(5, 25), charDis(48, 122), intervalDis(50, 200);
	std::random_device rand;

	switch (var) {
	case randomiseType::coord:
		//Radomises the start of the line
		lineCoords[0].insert(lineCoords[0].begin(), coordXDis(rand));
		lineCoords[0].insert(lineCoords[0].begin() + 1, coordYDis(rand));
		for (auto i = 1; i < lineLength; i++) {
			//Sets coordinates to start line
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
```

`std::uniform_int_distribution<int>` creates a unifrom distribution object depending on your min and max distribution.
`std::random_device rand` uses the machine's data to create as a seed for a random data, making it impossible to predict what it returns.

The switch case randomises the different values based on the enum of RandomiseType was given.

```
enum randomiseType {
	coord,
	length,
	chars,
	interval
};
```
