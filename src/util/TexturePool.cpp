#include <cassert>
#include "TexturePool.hpp"
#include "util.hpp"


void pk::TexturePool::init() {
    this->pool.reserve(256);
}


Texture2D pk::TexturePool::get(const char* filepath) {
    const std::size_t hash = pk::hash_str(filepath);
    const auto pair = this->pool.find(hash);
    if (pair == this->pool.end()) {
        const Texture2D new_texture = LoadTexture(filepath);
        assert(new_texture.id > 0);
        this->pool.insert({hash, new_texture});
        return new_texture;
    }
    return pair->second;
}


void pk::TexturePool::register_texture(const char *key, Texture2D texture) {
    this->pool.emplace(pk::hash_str(key), texture);
}


void pk::TexturePool::erase(const char* filepath) {
    const std::size_t h = pk::hash_str(filepath);
    const auto pair = this->pool.find(h);
    if (pair != this->pool.end()) {
        UnloadTexture(pair->second);
        this->pool.erase(h);
    }
}


void pk::TexturePool::clear() {
    for (auto& pair : this->pool) {
        UnloadTexture(pair.second);
    }
    this->pool.clear();
}


std::size_t pk::TexturePool::num_textures() const {
    return this->pool.size();
}