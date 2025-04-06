#pragma once

#include <imgui.h>

class SoundControlPopup {
public:
    SoundControlPopup();  // Конструктор
    ~SoundControlPopup(); // Деструктор

    // Метод для отображения окна
    void ShowPopup(bool* open);

    // Устанавливаем порог прогресса
    void SetProgressThreshold(float threshold);

    // Устанавливаем режим
    void SetMode(int mode);

private:
    float progressThreshold; // Порог прогресса
    int currentMode;         // Режим (0 - все звуки, 1 - фоновые задачи, 2 - музыка)

    // Вспомогательные методы для UI
    void DrawModeSelector();
    void DrawProgressSlider();
};
