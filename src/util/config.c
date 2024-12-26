#include "config.h"

static int should_clear_bg = 1;


void poke_config_set_should_clear_background(const int status) {
	should_clear_bg = status;
}

int poke_config_should_clear_background() {
	return should_clear_bg;
}
