/*
 * Settings.h
 *
 *  Created on: 2013-12-3
 *      Author: zp
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

class Settings {
public:

	static bool isCasualMode;
	static bool soundEnabled;
	static bool musicEnabled;
	static bool showConflictedDigit;
	static bool showTimer;
	static bool preventSleeping;
	static bool autoHighLight;
	static bool autoRemoveNotes;
	static bool removeCompleteDigits;
	static bool isFirstPlay;
	static bool hasRated;
};

class Stats {
public:

	static long bestTime[4];
	static int bestRun[4];
	static int run[4];
	static int finished[4];
	static int hintNum;
	static long totalLastTime;
	static long anHourTime;
	static long startTime;
};


#endif /* SETTINGS_H_ */
