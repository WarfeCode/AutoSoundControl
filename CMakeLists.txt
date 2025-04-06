cmake_minimum_required(VERSION 3.10)

project(AutoSoundControl)

set(CMAKE_CXX_STANDARD 17)

# Указываем папку с исходными файлами
include_directories(include)

# Указываем исходные файлы
set(SOURCES
    src/AutoSoundControl.cpp
    # Добавь другие исходники, если они есть
)

# Генерация исполняемого файла
add_executable(AutoSoundControl ${SOURCES})
# Подключаем внешнюю зависимость
include_directories(${CMAKE_SOURCE_DIR}/path/to/dependency/include)
link_directories(${CMAKE_SOURCE_DIR}/path/to/dependency/lib)

# Подключаем исходные файлы из этой библиотеки
add_subdirectory(path/to/dependency)
