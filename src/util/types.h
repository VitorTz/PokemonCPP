#ifndef POKE_TYPES_H
#define POKE_TYPES_H
#include <stddef.h>
#include <stdint.h>


typedef uint32_t entity_id;
typedef uint8_t component_id;
typedef int8_t zindex_t;


typedef struct _iter {
	char* begin;
	char* end;
	size_t step;
} iter_t;

typedef struct _entity_pair {
	entity_id entity;
	float centery;
} entity_pair;


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


typedef enum _character_id {
	PlayerCharacterID,
	NurseCharacterID,
	NumCharactersIDs
} CharacterID;


#endif // !POKE_TYPES_H