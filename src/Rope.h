#include "Global.h"
#include <memory>
#include "Box2DEngine.h"


class Rope
{
public:
	Rope(int x, int y, float length, int nb_links, Box2DEngine* gameController);
	float getLength() const { return length; }
	int	getNb_links() const { return nb_links; }
private:
	float length;
	int nb_links;
	Box2DEngine* gameController;
	b2Body* body;
};
