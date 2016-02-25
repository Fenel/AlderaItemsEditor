#ifndef ITEM_H
#define ITEM_H

#include "thing.h"

//class Container;
//class Teleport;
class ItemType;

//class Abilities
//{
//};

class Item : public Thing
{
 public:
  unsigned int mID;
  unsigned char count;
  ItemType *baseItem;
  //Abilities abilities;

  //virtual Item* getItem() {return this;};
  //virtual const Item* getItem() const {return this;};
  //virtual Container* getContainer() {return 0;};
  //virtual const Container* getContainer() const {return 0;};
  //virtual Teleport* getTeleport() {return 0;};
  //virtual const Teleport* getTeleport() const {return 0;};

  bool isGroundTile();
  bool isSplash();
  bool isStackable();
  bool isRune();
  bool isFluidContainer();
  bool hasHeight();
  bool isCollision();
  
  Item(unsigned int id, unsigned char _count = 1);
  ~Item();
};




#endif
