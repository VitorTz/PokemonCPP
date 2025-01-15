#include <cassert>
#include "TexturePool.hpp"
#include "util.hpp"


pk::TexturePool::TexturePool() {
    this->pool.reserve(256);
}


Texture2D pk::TexturePool::get(const char* filepath) {
    const std::size_t h = pk::hash_str(filepath);
    const auto pair = this->pool.find(h);
    if (pair == this->pool.end()) {
        Texture2D t = LoadTexture(filepath);
        assert(t.id > 0);
        this->pool.insert({h, t});
        return t;
    }
    return pair->second;
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