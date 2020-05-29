
add_executable(mainLauncher mainLauncher.cpp)

target_link_libraries(mainLauncher PUBLIC src box2d pugixml sfml-system sfml-window sfml-graphics sfml-audio sfml-network)


