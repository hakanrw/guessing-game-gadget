cmake_minimum_required(VERSION 3.13)

# initialize the SDK directly
set(PICO_BOARD pico_w)
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

project(guessing_game C CXX ASM)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# localized question files
file(GLOB QUESTION_FILES "${CMAKE_CURRENT_SOURCE_DIR}/questions_*.txt")
if (LOCALE)
    add_definitions(-DLOCALE=${LOCALE})
endif()

# question.c depends on text file
set_source_files_properties(question.c 
    PROPERTIES OBJECT_DEPENDS "${QUESTION_FILES}"
)

# rest of your project
add_executable(guessing_game
    guess.c
    lcd.c
    question.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(guessing_game pico_stdlib pico_stdio pico_rand hardware_i2c)
target_include_directories(guessing_game PUBLIC .)

pico_add_extra_outputs(guessing_game)
pico_enable_stdio_usb(guessing_game 1)
