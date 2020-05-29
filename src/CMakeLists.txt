
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(src ${SOURCES} )
target_link_libraries(src PUBLIC box2d pugixml sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
target_include_directories(src PUBLIC ./)
