#include "tiled_map.h"
#include <assert.h>


#define BUFFER_LENGHT 256
static char buffer[BUFFER_LENGHT];


typedef struct tile {
	float x;
	float y;
	float width;
	float height;
	int objid;
	zindex_t zindex;
	int terrain;
	int n;
	char direction;	
} tile_t;


static void findnum(FILE* file) {
	while (!feof(file)) {
		const char c = fgetc(file);
		if (c >= '0' && c <= '9') {
			fseek(file, -sizeof(char), SEEK_CUR);
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
			buffer[i++] = c;
		} else {
			fseek(file, -sizeof(char), SEEK_CUR);
			break;
		}
	}
	buffer[i] = '\0';
	return atoi(buffer);
}

static char readchar(FILE* file) {
	while (!feof(file)) {
		const char c = fgetc(file);
		if (c != '\n' && c != ' ') {
			return c;
		}
	}
}


static readfloat(FILE* file) {
	findnum(file);
	int i = 0;

	while (!feof(file) && i < BUFFER_LENGHT) {
		char c = fgetc(file);
		if (c >= '0' && c <= '9' || c == '.') {
			buffer[i++] = c;
		} else {
			fseek(file, -sizeof(char), SEEK_CUR);
			break;
		}
	}
	buffer[i] = '\0';

	return atof(buffer);
}


static void readstr(FILE* file) {
	int i = 0;
	while (!feof(file)) {
		const c = fgetc(file);
		if (c == '\n') {
			break;
		}
		else if (c != ' ') {
			buffer[i++] = c;
		}
	}
	buffer[i] = '\0';
}



static void load_tile(ecs_t* ecs, tile_t* tile) {
	
}


void load_tiledmap(ecs_t* ecs, const char* filepath) {
	FILE* file;
	file = fopen(filepath, "r");
	assert(file != NULL);

	int groupid, numobjs;
	tile_t tile;

	while (!feof(file)) {
		groupid = readint(file);
		numobjs = readint(file);		
		for (int i = 0; i < numobjs; i++) {
			tile.x = readfloat(file);
			tile.y = readfloat(file);
			tile.width = readfloat(file);
			tile.height = readfloat(file);
			tile.objid = readint(file);
			tile.zindex = readint(file);
			tile.terrain = readint(file);
			tile.n = readint(file);
			tile.direction = readchar(file);
			readstr(file);			
			load_tile(ecs, &tile);
		}
	}

}