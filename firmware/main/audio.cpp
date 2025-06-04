#include "audio.h"
#include "config.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Создаем объекты для работы с MP3 плеером
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
DFRobotDFPlayerMini player;

// Инициализация аудиосистемы
void initAudio() {
  softwareSerial.begin(9600);
  
  if (player.begin(softwareSerial)) {
    // Настройка громкости (от 0 до 30)
    player.volume(30);
  }
}

// Воспроизведение звука из конкретной папки и трека
void playSound(int folder, int track) {
  player.playFolder(folder, track);
}

// Остановка воспроизведения
void stopSound() {
  player.stop();
}

// Установка громкости
void setVolume(int volume) {
  if (volume >= 0 && volume <= 30) {
    player.volume(volume);
  }
}
