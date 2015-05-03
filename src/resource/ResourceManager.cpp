//
// Created by deniz on 08/04/15.
//

#include "resource/ResourceManager.h"
#include <graphics/Texture.h>
#include <graphics/Material.h>
#include <graphics/Mesh.h>
#include <graphics/Shader.h>
#include "resource/ObjLoader.h"
#include "resource/ObjLoader2.h"
#include <SDL_image.h>

/* TODO: FILE DOESN'T EXIST HANDLING*/


ResourceManager* ResourceManager::manager = NULL;

std::shared_ptr<Texture> ResourceManager::createTexture(std::string name) {
    printf("Loading texture: %s\n", name.c_str());
	auto it = textures.find(name);
	if (it == textures.end()) {
		std::shared_ptr<Texture> ptr = std::make_shared<Texture>();
		SDL_Surface *surface = IMG_Load(name.c_str());
		if (surface == NULL)  {
            printf("Failed to load texture in path: : %s\n", name.c_str());
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
        std::shared_ptr<Mesh> ptr = std::shared_ptr<Mesh>(objLoader2->import(name.c_str()));

        meshes[name] = ptr;
        objLoader2->destroy();
        return ptr;
    }
    else {
        return it->second;
    }

}

std::shared_ptr<Mesh> ResourceManager::createSkeletalMesh(std::string name) {

    auto it = meshes.find(name);
    if (it == meshes.end()) {
		glm::quat ro1 = glm::angleAxis(glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f)) * glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 0.0f,-1.0f));
		//glm::quat ro2 = glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        std::shared_ptr<Mesh> ptr = std::shared_ptr<Mesh>(md5Loader->load(name.c_str(), glm::vec3(0.08f, 0.08f, 0.08f), std::move(ro1) ));

        meshes[name] = ptr;
        return ptr;
    }
    else {
        return it->second;
    }

}

std::shared_ptr<AnimationState> ResourceManager::createAnimation(std::string name) {

	auto it = animations.find(name);
	if (it == animations.end()) {
		glm::quat ro1 = glm::angleAxis(glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f)) * glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, -1.0f));
		std::shared_ptr<AnimationState> ptr = std::shared_ptr<AnimationState>(md5AnimLoader->loadAnim(name.c_str(), glm::vec3(0.08f, 0.08f, 0.08f), std::move(ro1)));

		animations[name] = ptr;
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
    objLoader2 = new ModelOBJ();
    md5Loader = new MD5Loader();
	md5AnimLoader = new MD5Anim();
}

ResourceManager::~ResourceManager() {

}
