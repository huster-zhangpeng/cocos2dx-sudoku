/*
 * Settings.cpp
 *
 *  Created on: 2013-12-3
 *      Author: zp
 */
#include "Settings.h"

bool Settings::isCasualMode = true;
bool Settings::soundEnabled = true;
bool Settings::musicEnabled = true;
bool Settings::showConflictedDigit = true;
bool Settings::showTimer = true;
bool Settings::preventSleeping = true;
bool Settings::autoHighLight = true;
bool Settings::autoRemoveNotes = true;
bool Settings::removeCompleteDigits = true;
bool Settings::isFirstPlay = true;
bool Settings::hasRated = false;

long Stats::bestTime[4] = { 0 };
int Stats::bestRun[4] = { 0 };
int Stats::run[4] = { 0 };
int Stats::finished[4] = { 0 };
int Stats::hintNum = 5;
long Stats::totalLastTime;
long Stats::anHourTime;
long Stats::startTime;

