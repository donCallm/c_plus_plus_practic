project(yello_belt)

add_library(lyello_belt  ytest.cpp
                        bus_manager.cpp
                        query.cpp
                        responses.cpp)

add_executable(yello_belt
            main.cpp)

target_link_libraries(yello_belt PRIVATE
                    lyello_belt)