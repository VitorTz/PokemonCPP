#include "ShaderPool.h"
#include "../util/util.hpp"
#include "../constants.hpp"


void pk::ShaderPool::init() {
    this->register_shader(
        SHADERS_PATH "wave.fs",
        LoadShader(nullptr, SHADERS_PATH "wave.fs")
    );
}


void pk::ShaderPool::register_shader(const char *key, const Shader &shader) {
    this->pool.emplace(pk::hash_str(key), shader);
}

Shader pk::ShaderPool::get_shader(const char *key) const {
    return this->pool.at(pk::hash_str(key));
}


void pk::ShaderPool::unload_shader(const char *key) {
    const std::size_t h = pk::hash_str(key);
    if (const auto pair = this->pool.find(h); pair != this->pool.end()) {
        UnloadShader(pair->second);
        this->pool.erase(h);
    }
}


void pk::ShaderPool::clear() {
    for (auto& pair : this->pool) {
        UnloadShader(pair.second);
    }
    this->pool.clear();
}
