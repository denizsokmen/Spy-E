



#ifndef __SpyE_Renderer__
#define __SpyE_Renderer__

class ShaderProgram;

class Renderer {
    ShaderProgram* program;


    public:
    Renderer();
    ~Renderer();
    void render();


};

#endif


