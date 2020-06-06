#include "Rope.h"

Rope::Rope(int x, int y,float length, int nb_links, Box2DEngine* gameController) :
    length(length), nb_links(nb_links), gameController(gameController)
{
    //Rope::ropeEnds = gameController->addBodyRope(x, y,length, nb_links);
    Rope::elements = gameController->addBodyRope(x, y, length, nb_links);
}


void Rope::linkPlayers(Player* player2, Player* player1, b2World* world) {
	float width = length / nb_links;

    b2Body* body_player1 = player1->getBody();
    b2Body* body_player2 = player2->getBody();
    //b2Body* beginBody = Rope::getRopeEnds().first;
   // b2Body* endBody = Rope::getRopeEnds().second;
    b2Body* beginBody = Rope::getElements()[0];
    b2Body* endBody = Rope::getElements()[nb_links-1];

    // Revolution Joint
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.localAnchorA.Set(0.8 * width * UNRATIO, 0);
	revoluteJointDef.localAnchorB.Set(-1.2 * width * UNRATIO, 0);


    // Link player1 to beginBody
    revoluteJointDef.bodyA = body_player1;
    revoluteJointDef.bodyB = beginBody;
	world->CreateJoint(&revoluteJointDef);

    // Link player2 to endBody
	revoluteJointDef.bodyA = endBody;
	revoluteJointDef.bodyB = body_player2;
	world->CreateJoint(&revoluteJointDef);
}
/*
void Rope::draw(sf::Color color, sf::RenderWindow* window) {
	float width;
	float height
    for (auto body : Rope::elements) {
		b2Fixture* fixture = body->GetFixtureList();
		switch (fixture->GetType()) {
		case b2Shape::e_polygon: {
			while (fixture->GetNext() != NULL)
			{
				fixture = fixture->GetNext();
			}
			b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();

			width = sqrt(pow((poly->m_vertices[1].x - poly->m_vertices[0].x), 2) + pow((poly->m_vertices[1].y - poly->m_vertices[0].y), 2));
			height = sqrt(pow((poly->m_vertices[3].x - poly->m_vertices[0].x), 2) + pow((poly->m_vertices[3].y - poly->m_vertices[0].y), 2));
			//printf("width: %f \n", width);
			//printf("heigth: %f \n", height);
			break;
		}
		default:
			printf("No drawing available for this fixture type\n");
			return;
		}
		b2Vec2 position = body->GetPosition();
		std::unique_ptr<sf::CircleShape> shape(new sf::CircleShape(width / 2 * RATIO));
		shape.get()->setFillColor(sf::Color::Cyan);

		// Setting position and drawing with SFML
		shape->setPosition((position.x - width / 2) * RATIO, (position.y - height / 2) * RATIO);
		shape->rotate(body->GetAngle() * DEGTORAD);

		window->draw(*shape);

    }
}
*/