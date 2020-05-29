
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_executable(hello_world
  ${SOURCES}
  )

target_link_libraries(hello_world PUBLIC box2d)
