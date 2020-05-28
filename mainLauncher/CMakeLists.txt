
add_executable(mainLauncher mainLauncher.cpp)

target_link_libraries(mainLauncher PUBLIC src pugixml sfml-graphics)

add_custom_command(TARGET mainLauncher POST_BUILD
		   COMMAND ${CMAKE_COMMAND} -E copy
			   ${CMAKE_SOURCE_DIR}/resources/visage.xml
			   ${CMAKE_CURRENT_BINARY_DIR})