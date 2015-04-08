//
// Created by deniz on 08/04/15.
//

#ifndef SPYE_RESOURCEMANAGER_H
#define SPYE_RESOURCEMANAGER_H
#include <map>
#include <memory>

class Texture;
class Material;
class Mesh;
class ShaderProgram;


class ResourceManager {

    std::map<std::string, std::shared_ptr<Texture>> textures;
    std::map<std::string, std::shared_ptr<Material>> materials;
    std::map<std::string, std::shared_ptr<Mesh>> meshes;
    std::map<std::string, std::shared_ptr<ShaderProgram>> shaders;


public:
    std::shared_ptr<Texture> createTexture(std::string name);
    std::shared_ptr<Material> createMaterial(std::string name);
    std::shared_ptr<Mesh> createMesh(std::string name);
    std::shared_ptr<ShaderProgram> createShader(std::string name);


};

#endif //SPYE_RESOURCEMANAGER_H
