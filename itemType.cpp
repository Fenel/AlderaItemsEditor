#include <string>
#include "itemType.h"
#include "enums.h"


ItemType::ItemType()
{
	miniMapColor		  = 0;
    height				  = 0;
	animcount			  = 0;
	numsprites			  = 0;
	spriteID			  = 0;
	id                    = 0;
	group                 = 0;//ITEM_GROUP_NONE;
	name                  = "Unnamed Item";
	pluralName            = "";
	description           = "";
	maxItems              = 0;
	weight                = 0;
	showCount             = false;
	weaponType            = 0;//WEAPON_NONE;
	ammoType              = 0;//AMMO_NONE;
	shootType             = 0;//NM_SHOOT_NONE;
	magicEffect           = 0;//NM_ME_NONE;
	attack                = 0;
	defence               = 0;
	armor                 = 0;
	slotPosition          = 0;
	isVertical            = false;
	isHorizontal          = false;
	allowDistRead         = false;
	clientCharges         = false;
	speed                 = 0;
	decayTo               = -1;
	decayTime             = 0;
	stopTime              = false;

	canReadText           = false;
	canWriteText          = false;
	maxTextLen            = 0;

	stackable             = false;
	useable               = false;
	moveable              = false;
	alwaysOnTop           = false;
	alwaysOnTopOrder      = 0;
	pickupable            = false;
	hasHeight             = false;
	rotable               = false;
	rotateTo              = 0;

	runeIntelligence      = 0;

	wieldInfo             = 0;//WIELDINFO_NONE;
	vocation              = 0;//VOCATION_NONE;
	minReqDex             = 0;
	minReqStr             = 0;
	minReqInt             = 0;
	minReqMPW             = 0;

	lightLevel    = 0;
	lightColor    = 0;

	floorChangeDown  = false;
	floorChangeNorth = false;
	floorChangeSouth = false;
	floorChangeEast  = false;
	floorChangeWest  = false;

	blockSolid       = false;
	blockProjectile  = false;
	blockPathFind    = false;

	transformEquipTo = 0;
	transformDeEquipTo = 0;
	showCharges      = false;
	charges      = 0;
	shootRange   = 0;
	ammoAction = 0;//AMMOACTION_NONE;
	combatType = 0;//COMBAT_NONE;
}
