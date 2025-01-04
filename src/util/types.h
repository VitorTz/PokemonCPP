#ifndef POKE_TYPES_H
#define POKE_TYPES_H
#include <stddef.h>
#include <stdint.h>


typedef uint32_t entity_t;
typedef uint8_t component_t;
typedef int8_t zindex_t;


typedef struct _iter {
	char* begin;
	char* end;
	size_t step;
} Iterator;

typedef struct _entity_pair {
	entity_t entity;
	float centery;
} EntityPair;


typedef enum _scene_id {
	TitleScreenID,
	WorldSceneID,
	FireArenaSceneID,
	PlantArenaSceneID,
	WaterArenaSceneID,
	HospitalSceneID,
	HouseSceneID,
	TestScene1ID,
	TestScene2ID,
	TestScene3ID,
	NumScenes
} SceneID;

typedef enum _obj_id {
	SmallGreenHouseObjID,
	LargeGreenHouseObjID,
	SmallPurpleHouseObjID,
	HospitalObjID,
	PlantArenaObjID,
	WaterArenaObjID,
	FireArenaObjID,
	TreeObjID,
	SmallTreeObjID,
	WinterTreeObjID,
	SmallWinterTreeObjID,
	RockObjID,
	PalmObjID,
	SmallPalmObjID,
	PillarObjID,
	PillarTopObjID
} ObjID;

typedef enum _character_id {
	PlayerCharacterID,
	NurseCharacterID,
	NumCharactersIDs
} CharacterID;

typedef enum _tile_obj_group_id {
	EntitiesGroupID,
	CoastGroupID,
	MonstersGroupID,
	GameObjsGroupID,
	TransitionGroupID,
	CollisionGroupID,
	WaterGroupID
} TiledObjectGroupID;


#endif // !POKE_TYPES_H