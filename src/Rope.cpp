#include "Rope.h"

Rope::Rope(int x, int y,float length, int nb_links, Box2DEngine* gameController) :
    length(length), nb_links(nb_links), gameController(gameController)
{
    Rope::elements = gameController->addBodyRope(x, y, length, nb_links);
    Rope::shape = std::unique_ptr<Circle>(new Circle());
}

void Rope::linkPlayers(Player* player2, Player* player1, b2World* world) {
	float width = length / nb_links;

    b2Body* body_player1 = player1->getBody();
    b2Body* body_player2 = player2->getBody();
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

void Rope::draw(sf::Color color, sf::RenderWindow* window) {
    for (auto body : elements) {
        Rope::shape->draw(body, color, window);
    }
}
