//
// Created by deniz on 21/03/15.
//


#include <graphics/Drawable.h>
#include <world/Camera.h>
#include <GL/glew.h>
#include <SDL_image.h>
#include "graphics/Drawer.h"
#include "logic/Game.h"
#include "world/Scene.h"
#include "graphics/Shader.h"
#include "graphics/VertexBuffer.h"
#include "graphics/Texture.h"



Drawable* Drawer::createDrawable(std::string name) {

    Texture *tex = new Texture();
    tex->createFromSDL(IMG_Load(name.c_str()));
    return new Drawable(tex);

}

void Drawer::draw(Drawable *drawable, glm::vec2 position, glm::vec2 size) {
    DrawObj obj;
    obj.drawable = drawable;
    obj.position = position;
    obj.size = size;
    drawList.push_back(obj);
}


void Drawer::drawAll() {
    Camera *cam = game->scene->camera;
    cam->ortho(0, game->width, 0, game->height);
	glUseProgram(quadShader->id);

    glDisable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    DrawObj *obj = NULL;
    for(auto it = drawList.begin(); it != drawList.end(); it++) {
        obj = &(*it);
        glm::mat4 MVP = cam->projection  * glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(obj->position.x, obj->position.y, 0.0f)),glm::vec3(obj->size.x, obj->size.y, 0.0f));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, obj->drawable->getTexture()->getId());
        glUniformMatrix4fv(glGetUniformLocation(quadShader->id, "MVP"), 1, GL_FALSE, &MVP[0][0]);
		glUniform1i(glGetUniformLocation(quadShader->id, "tex"), 0);
		quadBuffer->bind();
		quadBuffer->draw();
		quadBuffer->unbind();

    }

	glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    drawList.clear();
}

void Drawer::update(float dt) {
}

void Drawer::draw() {
}

void Drawer::draw2D() {
    drawAll();
}

Drawer::Drawer(Game *gm) {
    game=gm;
    //Drawer only draws 2D, quad shader should be enough
    quadShader = new ShaderProgram();
    quadShader->load("./shaders/quad_vertex.glsl", "./shaders/quad_fragment.glsl");

    quadBuffer = VertexBuffer::createQuad();
}

Drawer::~Drawer() {

}
