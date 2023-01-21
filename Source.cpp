/* Title:			Sorted Athletes
*  Name:			Gavon Trubee
*  Course:			CSCI 240
*  Instructor:		Professor Gunnett
*  Due Date:		12/09/2022
*
* This program will take input from a file ("players.txt") and sort the player's
* by alphabetical order, and then by win%.
*
* Input (from "players.txt")
* Name   Wins   Losses
*
* Output (to common output)
* Average Percentage:
* Athlete Name      Wins      Losses      Percentage
* ==================================================
*
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_PLAYERS = 500;

struct info {
	string name;
	double wins;
	double losses;
	double winPer;
};

void getData(info athInfo[], int count);
double calcWinPer(info athInfo[], int count);
double averageWinPer(info athInfo[], int count);
void alphOrder(info athInfo[], int count);
void topPercentage(info athInfo[], int count);
void output(info athInfo[], double average, int count);

ifstream inData;

int main() {
	int count = 0;
	double average;
	inData.open("players.txt");
	info athInfo[MAX_PLAYERS];
	while (!inData.eof()) {
		getData(athInfo, count);
		athInfo[count].winPer = calcWinPer(athInfo, count);
		count++;
	}
	average = averageWinPer(athInfo, count);
	alphOrder(athInfo, count);
	output(athInfo, average, count);
	topPercentage(athInfo, count);
	output(athInfo, average, count);
	inData.close();
	return 0;
}

void getData(info athInfo[], int count) {
	inData >> athInfo[count].name;
	inData >> athInfo[count].wins;
	inData >> athInfo[count].losses;
}

// Calculate the win% for each athlete
double calcWinPer(info athInfo[], int count) {
	double winPer = (athInfo[count].wins / (athInfo[count].wins + athInfo[count].losses)) * 100;
	return winPer;
}

// Calculate average win%
double averageWinPer(info athInfo[], int count) {
	double total = 0;
	for (int i = 0; i < count; i++) {
		total += athInfo[i].winPer;
	}
	return total / count;
}

// Sort players by alphabetical order
void alphOrder(info athInfo[], int count) {
	int index;
	int largestIndex;
	int location;
	info temp;

	for (index = 0; index < count; index++) {
		largestIndex = index;
		for (location = index + 1; location < count; location++) {
			if (athInfo[location].name < athInfo[largestIndex].name)
				largestIndex = location;
		}
		temp = athInfo[largestIndex];
		athInfo[largestIndex] = athInfo[index];
		athInfo[index] = temp;
	}
}

// Sort players by win%
void topPercentage(info athInfo[], int count) {
	int index;
	int largestIndex;
	int location;
	info temp;

	for (index = 0; index < count; index++) {
		largestIndex = index;
		for (location = index + 1; location < count; location++) {
			if (athInfo[location].winPer > athInfo[largestIndex].winPer)
				largestIndex = location;
		}
		temp = athInfo[largestIndex];
		athInfo[largestIndex] = athInfo[index];
		athInfo[index] = temp;
	}
}

void output(info athInfo[], double average, int count) {
	cout << "Average Percentage: " << fixed << setprecision(2) << average << "%" << endl;
	cout << "Athlete Name      Win      Loss      Percentage" << endl;
	cout << "===============================================" << endl;
	for (int i = 0; i < count; i++) {
		cout << left << setw(9) << athInfo[i].name << right << setprecision(0) << setw(12) << athInfo[i].wins << setw(8) << athInfo[i].losses << setw(15) << fixed << setprecision(2) << athInfo[i].winPer << "%" << endl;
	}
	cout << endl;
}