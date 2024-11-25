#include "system_manager.h"
#include "ecs_manager.h"
#include "../util/texture_pool.h"


static uint8_t index = 0;
const static uint8_t max_index = 4;

static uint8_t frame = 0;
const static uint8_t max_frame = SPRITE_ANIMATION_SPEED_NORMAL;

static Texture2D textures[2][8];


void system_coast_init() {
	textures[0][0] = texture_pool_get(GRAPHICS_PATH "tilesets/coast/forest-0.png");
	textures[0][1] = texture_pool_get(GRAPHICS_PATH "tilesets/coast/forest-1.png");
	textures[0][2] = texture_pool_get(GRAPHICS_PATH "tilesets/coast/forest-2.png");
	textures[0][3] = texture_pool_get(GRAPHICS_PATH "tilesets/coast/forest-3.png");
	textures[0][4] = texture_pool_get(GRAPHICS_PATH "tilesets/coast/forest-4.png");
	textures[0][5] = texture_pool_get(GRAPHICS_PATH "tilesets/coast/forest-5.png");
	textures[0][6] = texture_pool_get(GRAPHICS_PATH "tilesets/coast/forest-6.png");
	textures[0][7] = texture_pool_get(GRAPHICS_PATH "tilesets/coast/forest-7.png");

	textures[1][0] = texture_pool_get(GRAPHICS_PATH "tilesets/coast/sand-0.png");
	textures[1][1] = texture_pool_get(GRAPHICS_PATH "tilesets/coast/sand-1.png");
	textures[1][2] = texture_pool_get(GRAPHICS_PATH "tilesets/coast/sand-2.png");
	textures[1][3] = texture_pool_get(GRAPHICS_PATH "tilesets/coast/sand-3.png");
	textures[1][4] = texture_pool_get(GRAPHICS_PATH "tilesets/coast/sand-4.png");
	textures[1][5] = texture_pool_get(GRAPHICS_PATH "tilesets/coast/sand-5.png");
	textures[1][6] = texture_pool_get(GRAPHICS_PATH "tilesets/coast/sand-6.png");
	textures[1][7] = texture_pool_get(GRAPHICS_PATH "tilesets/coast/sand-7.png");
}


void system_coast_update(const float dt, const iterator_t iter) {
	frame++;
	if (frame > max_frame) {
		frame = 0;
		index = (index + 1) % max_index;
	}
}


void system_coast_draw(const entity_t e) {
	ecs_t* ecs = ecs_manager_get_instance();
	const transform_t* transform = ecs_get_transform(ecs, e);
	const coast_t* coast = (coast_t*) ecs_component_at(ecs, e, COAST_ID);
	const Rectangle rect = { coast->n % 3 * TILE_SIZE, coast->n / 3 * TILE_SIZE, TILE_SIZE, TILE_SIZE };
	switch (coast->terrain) {
		case 0:
			DrawTextureRec(textures[0][index], rect, transform->pos, WHITE);
			break;
		case 1:
			DrawTextureRec(textures[0][index + 4], rect, transform->pos, WHITE);
			break;
		case 2:
			DrawTextureRec(textures[1][index], rect, transform->pos, WHITE);
			break;
		case 3:
			DrawTextureRec(textures[1][index + 4], rect, transform->pos, WHITE);
			break;
		default:
			break;
	}	
}