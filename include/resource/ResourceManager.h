//
// Created by deniz on 08/04/15.
//

#ifndef SPYE_RESOURCEMANAGER_H
#define SPYE_RESOURCEMANAGER_H
#include <map>
#include <memory>
#include <string>
#include "MD5Loader.h"
#include "MD5AnimLoader.h"

class Texture;
class Material;
class Mesh;
class ShaderProgram;
class ObjLoader;
class ModelOBJ;
class AnimationState;

class ResourceManager {

    std::map<std::string, std::shared_ptr<Texture>> textures;
    std::map<std::string, std::shared_ptr<Material>> materials;
    std::map<std::string, std::shared_ptr<Mesh>> meshes;
	std::map<std::string, std::shared_ptr<ShaderProgram>> shaders;
	std::map<std::string, std::shared_ptr<AnimationState>> animations;
	ResourceManager();


public:
	static ResourceManager* instance() {
		if (manager == NULL) {
			manager = new ResourceManager();
		}

		return manager;
	}

	static ResourceManager* manager;
    ~ResourceManager();
    std::shared_ptr<Texture> createTexture(std::string name);
    std::shared_ptr<Material> createMaterial(std::string name);
    std::shared_ptr<Mesh> createMesh(std::string name);
	std::shared_ptr<ShaderProgram> createShader(std::string name);
	std::shared_ptr<AnimationState> createAnimation(std::string name);


    ObjLoader* objLoader;
    ModelOBJ* objLoader2;
    MD5Loader* md5Loader;
	MD5Anim* md5AnimLoader;

    std::shared_ptr<Mesh> createSkeletalMesh(std::string name);
};


#endif //SPYE_RESOURCEMANAGER_H
