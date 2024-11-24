#include "texture_pool.h"
#include <assert.h>

static avl_tree_t* pool;


static size_t hash_str(const char* s) {
    size_t hash = 5381;
    int c;
    while ((c = *s++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}


void texture_pool_init() {
	pool = avl_tree_create(sizeof(Texture2D), hash_str);
}


Texture2D texture_pool_get(const char* s) {
    void* data = avl_tree_at(pool, s);
    if (data == NULL) {
        Texture2D t = LoadTexture(s);
        assert(t.id > 0);
        avl_tree_insert(pool, s, &t);
        return t;
    }
    return *((Texture*)(data));
}


void texture_pool_erase(const char* s) {
    void* data = avl_tree_at(pool, s);
    if (data != NULL) {
        UnloadTexture(*((Texture2D*)data));
        avl_tree_erase(pool, s);
    }
}


void texture_pool_close() {
    const iterator_t iter = avl_tree_iter(pool);
    for (Texture2D* t = iter.begin; t < iter.end; t++) {
        UnloadTexture(*t);
    }
    avl_tree_destroy(pool);
}