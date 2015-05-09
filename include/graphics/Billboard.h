//
// Created by Taha Doğan Güneş on 09/05/15.
//

#ifndef SPYE_BILLBOARD_H
#define SPYE_BILLBOARD_H

#include <string>
class Camera;
class ShaderProgram;
class VertexBuffer;

class Billboard {
    void load(std::string fileName);

public:
    Billboard();
    ~Billboard();
    ShaderProgram* shaderProgram;
    VertexBuffer* vbo;


    void draw(Camera* camera);


};

#endif //SPYE_BILLBOARD_H
