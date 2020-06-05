#include "Monster.h"


Monster::Monster()
{
}

Monster::Monster(Box2DEngine* gameController, int x, int y, float height, float whidth)
{
	body=gameController->addBodyMonster(x * RATIO, y * RATIO, height * RATIO, whidth * RATIO );
}
