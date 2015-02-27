



#ifndef __SpyE_Renderer__
#define __SpyE_Renderer__

#include <GL/glew.h>

class ShaderProgram;
class Scene;
class ObjLoader;
class VertexBuffer;
class Camera;

class Renderer {
    ShaderProgram* generalShader;
    ObjLoader* objLoader;
    VertexBuffer* generalBuffer;
    GLuint vaoid;

    private:

        void loadGeneralShader();

    public:
        Renderer();
        ~Renderer();
        void render(Camera* camera);


};

#endif


