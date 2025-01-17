#pragma once
#include <raylib.h>
#include <unordered_map>


namespace pk {

    class TexturePool {

    private:
        std::unordered_map<std::size_t, Texture2D> pool{};
    
    public:
        void init();
        Texture2D get(const char* filepath);
        void register_texture(const char* key, Texture2D texture);
        void erase(const char* filepath);
        void clear();
        std::size_t num_textures() const;

    };

    inline pk::TexturePool gTexturePool{};
    
} // namespace pk
