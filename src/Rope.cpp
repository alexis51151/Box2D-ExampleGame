#include "Rope.h"

Rope::Rope(int x, int y,float length, int nb_links, Box2DEngine* gameController) :
    length(length), nb_links(nb_links), gameController(gameController)
{
    body = gameController->addBodyRope(x, y,length, nb_links);
}
