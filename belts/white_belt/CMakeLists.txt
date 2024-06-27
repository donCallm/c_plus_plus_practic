project(white_belt)

add_library(lwhite_belt test.cpp)

add_executable(white_belt
            main.cpp)

target_link_libraries(white_belt PRIVATE
                    lwhite_belt)