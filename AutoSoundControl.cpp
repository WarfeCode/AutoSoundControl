#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Структура для хранения настроек мода
struct ModSettings {
    int soundMode;
    float progressThreshold;
    std::string modName;
    std::string version;
};

// Функция для загрузки настроек из JSON
ModSettings LoadModSettings(const std::string& filename) {
    std::ifstream inputFile(filename);  // Открываем файл для чтения
    json config;

    // Чтение из файла
    if (inputFile.is_open()) {
        inputFile >> config;
    }
    else {
        std::cerr << "Failed to load mod settings from " << filename << std::endl;
    }

    ModSettings settings;
    settings.soundMode = config.value("soundMode", 1);  // По умолчанию 1 (Mute Background Tasks)
    settings.progressThreshold = config.value("progressThreshold", 50.0f);  // По умолчанию 50%
    settings.modName = config.value("modName", "AutoSoundControl");
    settings.version = config.value("version", "1.0");

    return settings;
}

// Функция для сохранения настроек в JSON
void SaveModSettings(const std::string& filename, const ModSettings& settings) {
    json config;
    config["soundMode"] = settings.soundMode;
    config["progressThreshold"] = settings.progressThreshold;
    config["modName"] = settings.modName;
    config["version"] = settings.version;

    std::ofstream outputFile(filename);  // Открываем файл для записи
    if (outputFile.is_open()) {
        outputFile << config.dump(4);  // Записываем с отступами для читаемости
    }
    else {
        std::cerr << "Failed to save mod settings to " << filename << std::endl;
    }
}

// Применение настроек
void ApplySoundSettings(int soundMode) {
    switch (soundMode) {
    case 0:
        std::cout << "Mute All Sounds" << std::endl;
        // Здесь добавь код для полного отключения звуков
        break;
    case 1:
        std::cout << "Mute Background Tasks" << std::endl;
        // Здесь добавь код для отключения только фоновых звуков
        break;
    case 2:
        std::cout << "Mute Music Only" << std::endl;
        // Здесь добавь код для отключения только музыки
        break;
    default:
        std::cerr << "Invalid sound mode!" << std::endl;
        break;
    }
}

// Пример функции для отслеживания прогресса
void CheckProgress(float playerProgress, float progressThreshold, int soundMode) {
    if (playerProgress >= progressThreshold) {
        ApplySoundSettings(soundMode);
    }
}

// Пример функции для изменения настроек
void OnSettingsChanged(int newSoundMode, float newProgressThreshold) {
    ModSettings newSettings = { newSoundMode, newProgressThreshold, "AutoSoundControl", "1.0" };
    SaveModSettings("mod.json", newSettings);
}

int main() {
    // Загружаем настройки
    ModSettings settings = LoadModSettings("mod.json");

    // Применяем настройки
    ApplySoundSettings(settings.soundMode);

    // Пример проверки прогресса
    float playerProgress = 60.0;  // Пример прогресса (можно заменить на динамическое значение)
    CheckProgress(playerProgress, settings.progressThreshold, settings.soundMode);

    // Изменение настроек (пример)
    OnSettingsChanged(2, 70.0f);  // Новый режим звука и порог прогресса

    return 0;
}
