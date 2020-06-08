#include "Global.h"
#include <memory>
#include "Box2DEngine.h"
#include "Player.h"
#include "Shape.h"
#include "box2d/box2d.h"


class Rope
{
public:
	Rope(int x, int y, float length, int nb_links, Box2DEngine* gameController);
	float getLength() const { return length; }
	int	getNb_links() const { return nb_links; }
	std::vector<b2Body*> getElements() const { return elements; }
	void linkPlayers(Player* player1, Player* player2, b2World* world);
	void Rope::draw(sf::Color color, sf::RenderWindow* window);
	std::vector<b2Body*>addBodyRope(Box2DEngine* gameController, int x, int y, float length, int nb_links);
private:
	float length;
	int nb_links;
	std::vector<b2Body*> elements;
	std::unique_ptr<Shape> shape; // Same shape for all the elements
};
