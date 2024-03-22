#include "rain.h"

std::mutex Rain::mutex;

void ShowConsoleCursor(bool showFlag)
{
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.dwSize = 10;
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
#if DEBUG
	std::cout << "cursor is visible: " << cursorInfo.bVisible << std::endl;
#endif
}

int main() {
	ShowConsoleCursor(false);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	std::vector<Rain> pour;
	bool rainMask[maxObjects] = {false};
	pour.reserve(maxObjects);
	int count = 0;

#if DEBUG
	std::cout << "main thread: " << std::this_thread::get_id() << std::endl;
#endif

	while (1) {
		int emptySlot = -1;
		for (int i = 0; i < maxObjects; i++) {

			if (!rainMask[i]) {
				emptySlot = i;
				count++;
				break;
			}
		}

		if (emptySlot != -1) {
#if DEBUG
			std::cout << "Mask1[" << emptySlot << "]: " << rainMask[emptySlot] << std::endl;
#endif // DEBUG
			if (count > 35) 
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			Rain r(rainMask + emptySlot);
			pour.push_back(r);
#if DEBUG
			std::cout << "Mask2[" << emptySlot << "]: " << rainMask[emptySlot] << std::endl;
#endif // DEBUG
		}

	}

	return 0;
}