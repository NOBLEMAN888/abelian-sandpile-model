add_library(
        arguments_parsing
        src/arguments_parsing/arguments_parsing.cpp
        src/arguments_parsing/arguments_parsing.h
)
add_library(
        file_reading
        src/file_reading/file_reading.cpp
        src/file_reading/file_reading.h
)
add_library(
        picture_processing
        src/picture_processing/picture_processing.cpp
        src/picture_processing/picture_processing.h
)
add_library(
        sandpile_processing
        src/sandpile_processing/sandpile_processing.cpp
        src/sandpile_processing/sandpile_processing.h
)
target_include_directories(arguments_parsing PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(file_reading PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(picture_processing PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(sandpile_processing PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")