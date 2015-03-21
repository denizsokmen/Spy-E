//
// Created by deniz on 21/03/15.
//


#include <graphics/Drawable.h>
#include <world/Camera.h>
#include <GL/glew.h>
#include "graphics/Drawer.h"
#include "logic/Game.h"
#include "world/Scene.h"
#include "graphics/Shader.h"
#include "graphics/VertexBuffer.h"


void Drawer::draw(Drawable *drawable, glm::vec2 position) {
    DrawObj obj;
    obj.drawable = drawable;
    obj.position = position;

    drawList.push_back(obj);

	//Drawer only draws 2D, quad shader should be enough
	quadShader = new ShaderProgram();
	quadShader->load("./shaders/quad_vertex.glsl", "./shaders/quad_fragment.glsl");

	quadBuffer = VertexBuffer::createQuad();
}


void Drawer::drawAll() {
    Camera *cam = game->scene->camera;
    cam->ortho(0, 800, 0, 600);
	glUseProgram(quadShader->id);



    glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
    DrawObj *obj = NULL;
    for(auto it = drawList.begin(); it != drawList.end(); it++) {
        obj = &(*it);
        glm::mat4 MVP = cam->projection  * glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(obj->position.x, obj->position.y, 0.0f)),glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(glGetUniformLocation(quadShader->id, "MVP"), 1, GL_FALSE, &MVP[0][0]);
		//glUniform1i(glGetUniformLocation(quadShader->id, "texture"), obj->drawable->getTexture());
		quadBuffer->bind();
		quadBuffer->draw();
		quadBuffer->unbind();

    }

    glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
    drawList.clear();
}
