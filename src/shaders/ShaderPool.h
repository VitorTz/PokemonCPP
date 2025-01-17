#pragma once
#include <raylib.h>
#include <map>


namespace pk {

    class ShaderPool {

    private:
        std::map<std::size_t, Shader> pool{};

    private:
        void register_shader(const char* key, const Shader& shader);

    public:
        void init();
        Shader get_shader(const char* key) const;
        void unload_shader(const char* key);
        void clear();

    };

    inline pk::ShaderPool gShaderPool{};

}