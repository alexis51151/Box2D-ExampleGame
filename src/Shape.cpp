#include <Shape.h>

Shape::Shape(int x, int y, std::string label) : x(x), y(y), label(label) {
}

Shape::Shape(pugi::xml_node node) {
	x = node.attribute("x").as_int();
	y = node.attribute("y").as_int();
	label = node.attribute("label").value();
}


Shape::Shape() {
	x = 0;
	y = 0;
	label = "";
}

void Shape::translation(int delta_x, int delta_y) {
	x += delta_x;
	y += delta_y;
}