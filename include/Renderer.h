



#ifndef __SpyE_Renderer__
#define __SpyE_Renderer__

class ShaderProgram;

class Scene;

class Renderer {
    ShaderProgram* generalShader;

    private:

        void loadGeneralShader();

    public:
        Renderer();
        ~Renderer();
        void render();


};

#endif


