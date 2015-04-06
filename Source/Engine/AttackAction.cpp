#include "AttackAction.h"
#include <iostream>

#include <iostream>

using namespace Marx;

AttackAction::AttackAction(float _TTL, float _damage) :
Action(_TTL), damage(_damage)
{

}

void AttackAction::onUpdate(Entity * me, float time)
{
	std::cout << "AttackAction onUpdate start" << std::endl;
	(static_cast<Projectile*>(me))->setTTL((static_cast<Projectile*>(me))->getTTL() - time);
	std::cout << "AttackAction onUpdate TTL set" << std::endl;
	MoveEvent * m = new MoveEvent(me->left, me->top, (static_cast<Projectile*>(me))->getVector().x,
													 (static_cast<Projectile*>(me))->getVector().y, true);

	std::cout << "AttackAction onUpdate after MoveEvent" << std::endl;
	if (me->getController() != NULL)
		me->getController()->addEvent(m);
	else		
		std::cout << "AttackAction Controller null" << std::endl;

	std::cout << "AttackAction onUpdate end" << std::endl;
}

void AttackAction::onHit(Entity * me, Entity *e)
{
    ServerNetworkController *cont = (ServerNetworkController*)((Projectile*)me)->getShooter()->getController();
    /*           Set Health            */
    SetHealthEvent event(cont->getId(), damage);
    cont->addEvent(&event);
    /*           Set Points            */

}
