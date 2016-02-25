#include "item.h"
#include "baseItems.h"

extern BaseItems BaseItems;

Item::Item(unsigned int id, unsigned char _count)
{
    mID = id;
    baseItem = BaseItems.getItemType(id);
    count = _count;
}

Item::~Item()
{

}

bool Item::isGroundTile()
{
    return (baseItem && baseItem->group == ITEM_GROUP_GROUND);
}

bool Item::isSplash()
{
    return (baseItem && baseItem->group == ITEM_GROUP_SPLASH);
}

bool Item::hasHeight()
{
    return (baseItem && baseItem->hasHeight);
}

bool Item::isStackable()
{
    return (baseItem && baseItem->stackable);
}

bool Item::isRune()
{
    return (baseItem && baseItem->group == ITEM_GROUP_RUNE);
}

bool Item::isFluidContainer()
{
    return (baseItem && baseItem->group == ITEM_GROUP_FLUID);
}

bool Item::isCollision()
{
     return (baseItem && baseItem->blockSolid);
}