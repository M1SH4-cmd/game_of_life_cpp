cmake_minimum_required(VERSION 3.30)
project(gameoflife)

set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.10)
project(MySDLProject)

# Поиск SDL2
set(SDL2_DIR "C:/SDL2-devel-2.32.4-VC/SDL2-2.32.4/cmake")
set(SDL2_PATH "C:/SDL2-devel-2.32.4-VC/SDL2-2.32.4")
include_directories(${SDL2_PATH}/include)
find_package(SDL2 REQUIRED)

# Создание исполняемого файла
add_executable(gameoflife
        src/main.cpp
        src/gameoflife.cpp
        include/gameoflife.h
        include/constants.h)

# Подключение SDL2
target_link_libraries(gameoflife PRIVATE
        ${SDL2_PATH}/lib/x64/SDL2.lib
        ${SDL2_PATH}/lib/x64/SDL2main.lib
)
target_include_directories(gameoflife PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
