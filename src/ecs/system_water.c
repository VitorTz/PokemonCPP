#include "system_manager.h"
#include "ecs_manager.h"
#include "../util/texture_pool.h"


const static uint8_t max_index = 4;
const static uint8_t max_frame = SPRITE_ANIMATION_SPEED_NORMAL;
static uint8_t index = 0;
static uint8_t frame = 0;

static Texture2D water_texture;
static char water_texture_path[] = GRAPHICS_PATH "tilesets/water/0.png";


void system_water_update(const float dt, const iterator_t iter) {
	frame++;
	if (frame > max_frame) {
		frame = 0;
		index = (index + 1) % max_index;
		water_texture_path[36] = '0' + index;
		water_texture = texture_pool_get(water_texture_path);
	}
} 


void system_water_draw(const entity_t e) {
	ecs_t* ecs = ecs_manager_get_instance();
	const transform_t* transform = ecs_get_transform(ecs, e);	
	const int rows = transform->size.y / TILE_SIZE;
	const int cols = transform->size.x / TILE_SIZE;	
	Vector2 pos = transform->pos;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			DrawTextureV(water_texture, pos, WHITE);
			pos.x += TILE_SIZE;
		}
		pos.x = transform->pos.x;
		pos.y += TILE_SIZE;
	}
}