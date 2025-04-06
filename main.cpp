#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/loader/SettingNode.hpp>

using namespace geode::prelude;

enum class SoundMode {
    MuteAll,
    MuteBackground,
    MuteMusic
};

SoundMode selectedMode = SoundMode::MuteAll;
int triggerPercent = 70;
bool windowOpen = false;

class $modify(MyPauseLayer, PauseLayer) {
    bool init(bool idk) {
        if (!PauseLayer::init(idk)) return false;

        // Кнопка с зачёркнутой нотой
        auto btn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"),
            this,
            menu_selector(MyPauseLayer::onSoundControl)
        );
        btn->setPosition({ 330, 230 }); // верхний правый угол
        this->m_buttonMenu->addChild(btn);

        return true;
    }

    void onSoundControl(CCObject*) {
        windowOpen = true;

        geode::createQuickPopup(
            "Auto Sound Control",
            "Выбери режим отключения звука и процент прогресса:",
            "OK", "Отмена",
            [=](auto, bool btn2) {
                if (!btn2) {
                    // сохранить настройки
                    Mod::get()->setSavedValue<int>("triggerPercent", triggerPercent);
                    Mod::get()->setSavedValue<int>("mode", static_cast<int>(selectedMode));
                    Notification::create("Настройки сохранены!", 1.f)->show();
                }
            },
            [=](CCNode* popup) {
                // UI элементов нет, только инфа
                auto layer = CCNode::create();

                // Здесь можно было бы добавить кастомное окно, но без UI-файлов — только логику
                // поэтому используем сохранённые настройки

                return layer;
            }
        );
    }
};

class $modify(MyGJGameLevel, GJGameLevel) {
    void setPercentage(float p) {
        GJGameLevel::setPercentage(p);

        std::cout << "Player progress: " << p << "%, trigger percent: " << triggerPercent << "%" << std::endl;  // Debug info

        if (p >= triggerPercent) {
            switch (selectedMode) {
            case SoundMode::MuteAll:
                system("nircmd.exe mutesysvolume 1"); // Windows only
                break;
            case SoundMode::MuteBackground:
                // TODO: оставляем только GD (нужно определить процессы и приостановить их)
                break;
            case SoundMode::MuteMusic:
                // TODO: Отключить музыку через GD API (глобальные громкости?)
                break;
            }
        }
    }
};
