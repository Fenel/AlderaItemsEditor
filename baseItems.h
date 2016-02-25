#ifndef __BASEITEMS_H__
#define __BASEITEMS_H__

#include <deque>
#include "itemType.h"
#include "enums.h"


class BaseItems
{
public:
	BaseItems();
	~BaseItems()
    {
    }
	bool addNewItem();
	bool deleteLastItem();
	void load();
	void save();
	void loadSprite(ItemType *item);
	void parseSpriteList();
	unsigned int getItemsCount(){return items.size();};
	ItemType* getItemType(unsigned int mID);

	std::deque<SpriteProperties> spritesProperties;
private:
    int itemsCount;
	std::deque<ItemType> items;
};
    
#endif
