#include <iostream>
#include <cstdlib>
#include <Windows.h>
using namespace std;
int main() {
	string guesses;
	bool state = false;
	int input;
	bool playThing;

menulable:
	system("cls");
	cout << "/////ASCIING FOR DIRECTION/////\n";
	cout << "play (1).\nsetting (2).\nexit(3).\n";
	cin >> input;
	switch (input) {
	case 1:
		goto playlable;
	case 2:
		goto settinglable;
	case 3:
		return 0;
	default:
		goto menulable;
	}

playlable:
	playThing = true;
	state = 1;
	system("cls");
	cout << "you awake in a dungeon.\n";
	cout << "exiting, you find yourself in a meadow.\n";
	while (playThing) {
		cout << "'where am i?' you ask yourself.\n";
		cin >> guesses;
		cout << "'maybe " << guesses << "?' you thought.\n";
		cout << "continue (1).\nsetting (2).\nexit(3).\n";
		cin >> input;
		switch (input) {
		case 2:
		case 3:
			playThing = false;
		default:
			break;
		}
		system("cls");
	}
	switch (input) {
	case 2:
		goto settinglable;
	case 3:
		return 0;
	}

settinglable:
	system("cls");
	cout << "back (1).\nexit(3).\n";
	cin >> input;
	switch (input) {
		case 1: {
			if (state)
				goto playlable;
			else
				goto menulable;
		}
		case 3:
			return 0;
		}
}