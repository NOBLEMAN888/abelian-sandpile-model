add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE arguments_parsing)
target_link_libraries(${PROJECT_NAME} PRIVATE file_reading)
target_link_libraries(${PROJECT_NAME} PRIVATE picture_processing)
target_link_libraries(${PROJECT_NAME} PRIVATE sandpile_processing)

#target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})