



#ifndef __SpyE_Renderer__
#define __SpyE_Renderer__

#include <GL/glew.h>
#include <vector>

class ShaderProgram;
class Scene;
class ObjLoader;
class VertexBuffer;
class Camera;
class Renderable;

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
        void render(Camera* camera, std::vector<Renderable*> renderList);


};

#endif

