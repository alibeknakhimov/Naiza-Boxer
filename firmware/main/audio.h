#ifndef AUDIO_H
#define AUDIO_H

#include "config.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Объявление внешних переменных
extern DFRobotDFPlayerMini player;
extern SoftwareSerial softwareSerial;

// Функции для работы со звуком
void initAudio();
void playSound(int folder, int track);
void stopSound();
void setVolume(int volume);

#endif
