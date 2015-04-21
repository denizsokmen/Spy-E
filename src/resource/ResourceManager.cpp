//
// Created by deniz on 08/04/15.
//

#include "resource/ResourceManager.h"
#include <graphics/Texture.h>
#include <graphics/Material.h>
#include <graphics/Mesh.h>
#include <graphics/Shader.h>
#include "resource/ObjLoader.h"
#include <SDL_image.h>

/* TODO: FILE DOESN'T EXIST HANDLING*/


ResourceManager* ResourceManager::manager = NULL;

std::shared_ptr<Texture> ResourceManager::createTexture(std::string name) {
	auto it = textures.find(name);
	if (it == textures.end()) {
		std::shared_ptr<Texture> ptr = std::make_shared<Texture>();
		SDL_Surface *surface = IMG_Load(name.c_str());
		if (surface == NULL)  {
            printf("Failed to load tex : %s\n", name.c_str());
			ptr = NULL;
			return NULL;
		}

		ptr->createFromSDL(surface);
		textures[name] = ptr;
		return ptr;
	}
	else {
		return it->second;
	}
}

std::shared_ptr<Material> ResourceManager::createMaterial(std::string name) {
    auto it = materials.find(name);
    if (it == materials.end()) {
        std::shared_ptr<Material> ptr = std::make_shared<Material>();
		ptr->program = createShader("./shaders/generic").get();
        materials[name] = ptr;
        return ptr;
    }
    else {
        return it->second;
    }
}

std::shared_ptr<Mesh> ResourceManager::createMesh(std::string name) {

    auto it = meshes.find(name);
    if (it == meshes.end()) {
        std::shared_ptr<Mesh> ptr = std::shared_ptr<Mesh>(objLoader->loadOBJ(name.c_str()));

        meshes[name] = ptr;
        return ptr;
    }
    else {
        return it->second;
    }

}


/* Exception for shaders, shaders programs consist of a vertex and a fragment program
 * you shouldn't specify an extension while invoking this function. It will look for
 * .vp and .fp files.
 */
std::shared_ptr<ShaderProgram> ResourceManager::createShader(std::string name) {
    auto it = shaders.find(name);
    if (it == shaders.end()) {
        std::shared_ptr<ShaderProgram> ptr = std::make_shared<ShaderProgram>();
        ptr->load(std::string(name+".vp").c_str(), std::string(name+".fp").c_str());
        shaders[name] = ptr;
        return ptr;
    }
    else {
        return it->second;
    }
}

ResourceManager::ResourceManager() {

}

ResourceManager::~ResourceManager() {

}
