project(life)

add_subdirectory(Tests)

add_executable(life
            main.cpp)

target_link_libraries(life PRIVATE
            tests)