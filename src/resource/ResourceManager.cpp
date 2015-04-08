//
// Created by deniz on 08/04/15.
//

#include "resource/ResourceManager.h"

std::shared_ptr<Texture> ResourceManager::createTexture(std::string& name) {

    return std::make_shared<Texture>();
}

std::shared_ptr<Material> ResourceManager::createMaterial(std::string& name) {

    return std::make_shared<Material>();
}

std::shared_ptr<Mesh> ResourceManager::createMesh(std::string& name) {

    return std::make_shared<Mesh>();
}

std::shared_ptr<ShaderProgram> ResourceManager::createShader(std::string& name) {
    auto it = shaders.find(name);
    if (it == shaders.end()) {
        std::shared_ptr<ShaderProgram> ptr = std::make_shared<ShaderProgram>();
        shaders[name] = ptr;
        return ptr;
    }
    else {
        return it->second;
    }
}
