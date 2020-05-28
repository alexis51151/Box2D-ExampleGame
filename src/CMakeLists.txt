
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(src ${SOURCES} )
target_link_libraries(src PUBLIC pugixml sfml-graphics)
target_include_directories(src PUBLIC ./)
