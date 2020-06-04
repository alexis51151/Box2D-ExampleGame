#include "Rope.h"

Rope::Rope(int x, int y,float length, int nb_links, Box2DEngine* gameController) :
    length(length), nb_links(nb_links), gameController(gameController)
{
    Rope::ropeEnds = gameController->addBodyRope(x, y,length, nb_links);
}


void Rope::linkPlayers(Player* player1, Player* player2, b2World* world) {
	float width = length / nb_links;

    b2Body* body_player1 = player1->getBody();
    b2Body* body_player2 = player2->getBody();
    b2Body* beginBody = Rope::getRopeEnds().first;
    b2Body* endBody = Rope::getRopeEnds().second;

    // Revolution Joint
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.localAnchorA.Set(0.8 * width * UNRATIO, 0);
	revoluteJointDef.localAnchorB.Set(-1.2 * width * UNRATIO, 0);


    // Link player1 to beginBody
    revoluteJointDef.bodyA = body_player1;
    revoluteJointDef.bodyB = beginBody;
	world->CreateJoint(&revoluteJointDef);

    // Link player2 to endBody
	revoluteJointDef.bodyA = body_player2;
	revoluteJointDef.bodyB = endBody;
	world->CreateJoint(&revoluteJointDef);
}