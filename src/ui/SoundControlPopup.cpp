#include "SoundControlPopup.hpp"

SoundControlPopup::SoundControlPopup() : progressThreshold(50.0f), currentMode(1) {
    // Инициализация значений
}

SoundControlPopup::~SoundControlPopup() {
    // Очистка, если нужно
}

void SoundControlPopup::ShowPopup(bool* open) {
    if (*open) {
        ImGui::Begin("Sound Control Settings", open);  // Окно ImGui

        // Выбор режима звука
        DrawModeSelector();

        // Слайдер для порога прогресса
        DrawProgressSlider();

        ImGui::End();
    }
}

void SoundControlPopup::SetProgressThreshold(float threshold) {
    progressThreshold = threshold;
    std::cout << "New progress threshold: " << progressThreshold << std::endl;  // Добавлено для отладки
}

void SoundControlPopup::SetMode(int mode) {
    currentMode = mode;
    std::cout << "New sound mode: " << currentMode << std::endl;  // Добавлено для отладки
}

void SoundControlPopup::DrawModeSelector() {
    ImGui::Text("Select Sound Control Mode");

    const char* modes[] = { "Mute All", "Mute Background Tasks", "Mute Music Only" };
    if (ImGui::Combo("Mode", &currentMode, modes, IM_ARRAYSIZE(modes))) {
        SetMode(currentMode);
    }
}

void SoundControlPopup::DrawProgressSlider() {
    ImGui::Text("Set Progress Threshold");
    if (ImGui::SliderFloat("Progress (%)", &progressThreshold, 0.0f, 100.0f)) {
        SetProgressThreshold(progressThreshold);
    }
}
