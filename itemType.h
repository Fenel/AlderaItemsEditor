#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <vector>
#include <SFML/Graphics.hpp>
#include "enums.h"

class ItemType
{
public:
	friend class BaseItems;

	ItemType();
	~ItemType(){}

	sf::Texture texture;
    sf::Sprite sprite;

	int32_t		   miniMapColor; //16
    int32_t		   height; //8
	int32_t		   animcount; //8
	int32_t		   numsprites; //8
	int32_t        spriteID; //16
	int32_t        id; //16
    int32_t        group; /*ItemGroup*/
	std::string    name;
	std::string    pluralName;
	std::string    description;
	int32_t        maxItems; //16
	int32_t        weight; //16
	bool           showCount;
	int32_t        weaponType; /*WeaponType*/
	int32_t        ammoType; /*AmmoType*/
	int32_t        shootType; /*ShootType*/
	int32_t        magicEffect; /*MagicEffect*/
	int32_t	       attack; //16
	int32_t        defence; //16
	int32_t        armor; //16
	int32_t	       slotPosition; //16
	bool           isVertical;
	bool           isHorizontal;
	bool           allowDistRead;
	bool           clientCharges;
	int32_t        speed; //16
	int32_t        decayTo; //16
	int32_t        decayTime;
	bool		   stopTime;

	bool           canReadText;
	bool           canWriteText;
	int32_t        maxTextLen; //16

	bool           stackable;
	bool           useable;
	bool           moveable;
	bool           alwaysOnTop;
	int32_t        alwaysOnTopOrder; //8
	bool           pickupable;
	bool		   hasHeight;
	bool           rotable;
	int32_t        rotateTo;

	int32_t        runeIntelligence;

	int32_t       wieldInfo;
	int32_t       vocation; /*Vocation*/
	int32_t       minReqDex;
	int32_t       minReqStr;
	int32_t       minReqInt;
	int32_t       minReqMPW;

	int32_t lightLevel;
	int32_t lightColor;

	bool floorChangeDown;
	bool floorChangeNorth;
	bool floorChangeSouth;
	bool floorChangeEast;
	bool floorChangeWest;

	bool blockSolid;
	bool blockProjectile;
	bool blockPathFind;

	int32_t transformEquipTo;
	int32_t transformDeEquipTo;
	bool showCharges;
	int32_t charges;
	int32_t shootRange; //16
	int32_t ammoAction; /*AmmoAction*/
	int32_t combatType; /*CombatType*/

	bool isAlwaysOnTop() const {return alwaysOnTop;}

	bool isGroundTile() const {return (group == ITEM_GROUP_GROUND);}
	bool isContainer() const {return (group == ITEM_GROUP_CONTAINER);}
	bool isSplash() const {return (group == ITEM_GROUP_SPLASH);}
	bool isFluidContainer() const {return (group == ITEM_GROUP_FLUID);}

	bool isDoor() const {return( group == ITEM_GROUP_DOOR);}
	bool isMagicField() const {return ( group == ITEM_GROUP_MAGICFIELD);}
	bool isTeleport() const {return ( group == ITEM_GROUP_TELEPORT);}
	bool isKey() const {return ( group == ITEM_GROUP_KEY);}
	bool hasSubType() const {return ( stackable || charges != 0);}
	bool isRune() const {return (group == ITEM_GROUP_RUNE);}
};


#endif
