#include "tiled_map.h"
#define BUFFER_LENGHT 256


static char image_path[BUFFER_LENGHT];


const static map_info_t MAP_INFO[NumScenes] = {
	{"Title Screen", SCREEN_W, SCREEN_H},
	{"World", 5504.0f, 5504.0f},
	{"Fire Arena", 5504.0f, 5504.0f},
	{"Plant Arena", 5504.0f, 5504.0f},
	{"Water Arena", 5504.0f, 5504.0f},
	{"Hospital", 5504.0f, 5504.0f},
	{"House", 5504.0f, 5504.0f},
	{"Test Scene", SCREEN_W, SCREEN_H}
};


const map_info_t* get_map_info(const enum SceneID scene_id) {
	return &MAP_INFO[scene_id];
}

 
static void findnum(FILE* file) {
	while (!feof(file)) {
		const char c = fgetc(file);
		if (c >= '0' && c <= '9') {
			fseek(file, -1, SEEK_CUR);
			break;
		}
	}
}


static int readint(FILE* file) {
	findnum(file);
	int i = 0;
	while (!feof(file)) {
		char c = fgetc(file);
		if (c >= '0' && c <= '9') {
			image_path[i++] = c;
		} else {			
			fseek(file, -1, SEEK_CUR);
			break;
		}
	}
	image_path[i] = '\0';
	return atoi(image_path);
}


static char readchar(FILE* file) {
	char c = '\0';
	while (!feof(file)) {
		c = fgetc(file);
		if (c != '\n' && c != ' ')
			break;
	}
	return c;
}


static float readfloat(FILE* file) {
	findnum(file);
	int i = 0;

	while (!feof(file) && i < BUFFER_LENGHT) {
		char c = fgetc(file);
		if (c >= '0' && c <= '9' || c == '.') {
			image_path[i++] = c;
		} else {
			fseek(file, -1, SEEK_CUR);
			break;
		}
	}
	image_path[i] = '\0';

	return (float) atof(image_path);
}


static void readstr(FILE* file) {
	int i = 0;
	while (!feof(file)) {
		const c = fgetc(file);
		if (c == '\n')
			break;
		else if (c != ' ')
			image_path[i++] = c;
	}
	image_path[i] = '\0';
}


static void read_tile(tile_t* tile, FILE* file) {
	tile->x = readfloat(file);
	tile->y = readfloat(file);
	tile->width = readfloat(file);
	tile->height = readfloat(file);
	tile->objid = readint(file);
	tile->zindex = readint(file);
	tile->terrain = readint(file);
	tile->n = readint(file);
	tile->direction = readchar(file);
	readstr(file); // read image path 
}


static void load_gameobj(ecs_t* ecs, const tile_t* tile) {
	ecs_create_sprite_with_tile(ecs, tile, image_path);
	switch (tile->objid) {
		case Building:
			ecs_add_collisions(
				ecs,
				tile->x + tile->width / 2.0f - tile->width * 0.45f,
				tile->y + tile->height - tile->height * 0.7f,
				tile->width * 0.9f,
				tile->height * 0.7f
			);
			break;
		case CollisionSprite:
			ecs_add_collisions(
				ecs,
				tile->x + tile->width / 2.0f - TILE_SIZE * 0.4f,
				tile->y + tile->height - TILE_SIZE * 0.8f,
				TILE_SIZE * 0.8f,
				TILE_SIZE * 0.8f
			);
			break;		
		default:
			break;
	}
}


static void load_entity(ecs_t* ecs, const tile_t* tile) {
	if (tile->objid < 0 || tile->objid >= NumScenes) {
		return;
	}
	
	// Create entity
	const entity_t e = ecs_create_entity_with_tile(ecs, tile, 1);
	
	// Add components 
	character_t* character = (character_t*)ecs_component_insert(ecs, e, CHARACTER_ID);
	character_init(character, (enum CharacterID)tile->objid);	

	sprite_animation_t* s = (sprite_animation_t*) ecs_component_insert(ecs, e, SPRITE_ANIMATION_ID);

	switch (tile->objid) {
		case PlayerID:
			sprite_animation_init_character(s, CHARACTERS_PATH "player.png");
			movement_init(
				(movement_t*) ecs_component_insert(ecs, e, MOVEMENT_ID), 
				PLAYER_SPEED,
				TILE_SIZE * 0.6f,
				TILE_SIZE * 0.6f
			);
			player_init(
				(player_t*) ecs_component_insert(ecs, e, PLAYER_ID), 
				ecs_create_sprite(ecs, tile->zindex - 1, GRAPHICS_PATH "other/shadow.png", 0.0f, 0.0f)
			);
			break;
		case NurseID:
			sprite_animation_init_character(s, CHARACTERS_PATH "hat_girl.png");
			break;
		default:
			break;
	}
}


static void load_water(ecs_t* ecs, const tile_t* tile) {
	const entity_t e = ecs_create_entity_with_pos(ecs, tile->zindex, 1, tile->x, tile->y);
	ecs_component_insert(ecs, e, WATER_ID);
	ecs_get_transform(ecs, e)->size = (Vector2){ tile->width, tile->height };
}

static void load_coast(ecs_t* ecs, const tile_t* tile) {
	const entity_t e = ecs_create_entity_with_pos(ecs, tile->zindex, 1, tile->x, tile->y);
	coast_t* coast = (coast_t*) ecs_component_insert(ecs, e, COAST_ID);
	coast_init(coast, tile->terrain, tile->n);	
}


static void load_transition(ecs_t* ecs, const tile_t* tile) {
	const entity_t e = ecs_create_entity_with_tile(ecs, tile, 1);
	transition_t* transition = (transition_t*)ecs_component_insert(ecs, e, TRANSITION_ID);
	transition_init(transition, (enum SceneID) tile->objid);
}


static void load_tile(ecs_t* ecs, const tile_t* tile, const enum ObjectGroupID group_id) {
	switch (group_id) {
		case EntitiesGroupID:
			load_entity(ecs, tile);
			break;
		case CoastGroupID:		
			load_coast(ecs, tile);
			break;
		case MonsterGroupID:
			break;
		case GameObjsGroupID:
			load_gameobj(ecs, tile);
			break;
		case TransitionGroupID:
			load_transition(ecs, tile);
			break;
		case CollisionGroupID:
			ecs_add_collisions(ecs, tile->x, tile->y, tile->width, tile->height);
			break;
		case WaterGroupID:
			load_water(ecs, tile);
			break;
		default:
			break;
	}
}


void load_tiledmap(ecs_t* ecs, const char* filepath) {
	FILE* file = fopen(filepath, "r");
	assert(file != NULL);

	int n;
	enum ObjectGroupID groupid;
	tile_t tile = { 0 };

	while (!feof(file)) {
		groupid = (enum ObjectGroupID) readint(file);
		n = readint(file);		
		for (int i = 0; i < n; i++) {
			read_tile(&tile, file);
			load_tile(ecs, &tile, groupid);
		}
	}

}