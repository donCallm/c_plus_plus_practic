project(red_belt)

add_library(lred_belt
                rtest.cpp)

add_executable(red_belt
                    main.cpp)
                    
target_link_libraries(red_belt PRIVATE
                        lred_belt)   