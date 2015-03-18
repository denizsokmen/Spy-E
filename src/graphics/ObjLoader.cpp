#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>

#include "graphics/ObjLoader.h"
#include "graphics/VertexBuffer.h"

//Courtesy of https://github.com/syoyo/tinyobjloader/blob/master/tiny_obj_loader.cc
//TODO: MTL support
//

//TODO: Add debug print macros
//#define DEBUG_OBJLOADER 1
//
//#ifdef DEBUG_OBJLOADER
//# define DEBUG_PRINT(x) printf x
//#else
//# define DEBUG_PRINT(x) do {} while (0)
//#endif

static inline bool isSpace(const char c) { return (c == ' ') || (c == '\t'); }
static inline bool isNewLine(const char c) {
    return (c == '\r') || (c == '\n') || (c == '\0');
}

struct vertex_index {
    int v_idx, vt_idx, vn_idx;
    vertex_index(){};
    vertex_index(int idx) : v_idx(idx), vt_idx(idx), vn_idx(idx){};
    vertex_index(int vidx, int vtidx, int vnidx)
            : v_idx(vidx), vt_idx(vtidx), vn_idx(vnidx){};
};

// Tries to parse a floating point number located at s.
//
// s_end should be a location in the string where reading should absolutely
// stop. For example at the end of the string, to prevent buffer overflows.
//
// Parses the following EBNF grammar:
//   sign    = "+" | "-" ;
//   END     = ? anything not in digit ?
//   digit   = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
//   integer = [sign] , digit , {digit} ;
//   decimal = integer , ["." , integer] ;
//   float   = ( decimal , END ) | ( decimal , ("E" | "e") , integer , END ) ;
//
//  Valid strings are for example:
//   -0	 +3.1417e+2  -0.0E-3  1.0324  -1.41   11e2
//
// If the parsing is a success, result is set to the parsed value and true
// is returned.
//
// The function is greedy and will parse until any of the following happens:
//  - a non-conforming character is encountered.
//  - s_end is reached.
//
// The following situations triggers a failure:
//  - s >= s_end.
//  - parse failure.
//
static bool tryParseDouble(const char *s, const char *s_end, double *result)
{
    if (s >= s_end)
    {
        return false;
    }

    double mantissa = 0.0;
    // This exponent is base 2 rather than 10.
    // However the exponent we parse is supposed to be one of ten,
    // thus we must take care to convert the exponent/and or the
    // mantissa to a * 2^E, where a is the mantissa and E is the
    // exponent.
    // To get the final double we will use ldexp, it requires the
    // exponent to be in base 2.
    int exponent = 0;

    // NOTE: THESE MUST BE DECLARED HERE SINCE WE ARE NOT ALLOWED
    // TO JUMP OVER DEFINITIONS.
    char sign = '+';
    char exp_sign = '+';
    char const *curr = s;

    // How many characters were read in a loop.
    int read = 0;
    // Tells whether a loop terminated due to reaching s_end.
    bool end_not_reached = false;

    /*
        BEGIN PARSING.
    */

    // Find out what sign we've got.
    if (*curr == '+' || *curr == '-')
    {
        sign = *curr;
        curr++;
    }
    else if (isdigit(*curr)) { /* Pass through. */ }
    else
    {
        goto fail;
    }

    // Read the integer part.
    while ((end_not_reached = (curr != s_end)) && isdigit(*curr))
    {
        mantissa *= 10;
        mantissa += static_cast<int>(*curr - 0x30);
        curr++;	read++;
    }

    // We must make sure we actually got something.
    if (read == 0)
        goto fail;
    // We allow numbers of form "#", "###" etc.
    if (!end_not_reached)
        goto assemble;

    // Read the decimal part.
    if (*curr == '.')
    {
        curr++;
        read = 1;
        while ((end_not_reached = (curr != s_end)) && isdigit(*curr))
        {
            // NOTE: Don't use powf here, it will absolutely murder precision.
            mantissa += static_cast<int>(*curr - 0x30) * pow(10, -read);
            read++; curr++;
        }
    }
    else if (*curr == 'e' || *curr == 'E') {}
    else
    {
        goto assemble;
    }

    if (!end_not_reached)
        goto assemble;

    // Read the exponent part.
    if (*curr == 'e' || *curr == 'E')
    {
        curr++;
        // Figure out if a sign is present and if it is.
        if ((end_not_reached = (curr != s_end)) && (*curr == '+' || *curr == '-'))
        {
            exp_sign = *curr;
            curr++;
        }
        else if (isdigit(*curr)) { /* Pass through. */ }
        else
        {
            // Empty E is not allowed.
            goto fail;
        }

        read = 0;
        while ((end_not_reached = (curr != s_end)) && isdigit(*curr))
        {
            exponent *= 10;
            exponent += static_cast<int>(*curr - 0x30);
            curr++;	read++;
        }
        exponent *= (exp_sign == '+'? 1 : -1);
        if (read == 0)
            goto fail;
    }

    assemble:
    *result = (sign == '+'? 1 : -1) * ldexp(mantissa * pow(5, exponent), exponent);
    return true;
    fail:
    return false;
}



static inline float parseFloat(const char *&token) {
    token += strspn(token, " \t");
    const char *end = token + strcspn(token, " \t\r");
    double val = 0.0;
    tryParseDouble(token, end, &val);
    float f = static_cast<float>(val);
    token = end;
    return f;
}

static inline void parseFloat2(float &x, float &y, const char *&token) {
    x = parseFloat(token);
    y = parseFloat(token);
}


static inline void parseFloat3(float &x, float &y, float &z,
        const char *&token) {
    x = parseFloat(token);
    y = parseFloat(token);
    z = parseFloat(token);
}

// Make index zero-base, and also support relative index.
static inline int fixIndex(int idx, int n) {
    if (idx > 0) return idx - 1;
    if (idx == 0) return 0;
    return n + idx; // negative value = relative
}

// Parse triples: i, i/j/k, i//k, i/j
static vertex_index parseTriple(const char *&token, int vsize, int vnsize,
        int vtsize) {
    vertex_index vi(-1);

    vi.v_idx = fixIndex(atoi(token), vsize);
    token += strcspn(token, "/ \t\r");
    if (token[0] != '/') {
        return vi;
    }
    token++;

    // i//k
    if (token[0] == '/') {
        token++;
        vi.vn_idx = fixIndex(atoi(token), vnsize);
        token += strcspn(token, "/ \t\r");
        return vi;
    }

    // i/j/k or i/j
    vi.vt_idx = fixIndex(atoi(token), vtsize);
    token += strcspn(token, "/ \t\r");
    if (token[0] != '/') {
        return vi;
    }

    // i/j/k
    token++; // skip '/'
    vi.vn_idx = fixIndex(atoi(token), vnsize);
    token += strcspn(token, "/ \t\r");
    return vi;
}



VertexBuffer* ObjLoader::loadOBJ(const char * path) {



    printf("[ObjLoader] Loading OBJ file %s...\n", path);

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;


    std::ifstream inStream(path);



    if (!inStream) {
        printf("[ObjLoader] Impossible to open the file ! Are you in the right path ?\n");
        return NULL;
    }


    int maxChars = 8192; // allocating a buffer size
    int lineNumber = 0;
    std::vector<char> buffer(maxChars);
    while (inStream.peek() != -1 ){
        inStream.getline(&buffer[0], maxChars);
        std::string lineBuffer(&buffer[0]);

        //printf("[ObjLoader] Line Number: %i\n", lineNumber++);
        //***
        // Trim newline '\r\n' or '\n'
        if (lineBuffer.size() > 0) {
            if (lineBuffer[lineBuffer.size() - 1] == '\n')
                lineBuffer.erase(lineBuffer.size() - 1);
        }
        if (lineBuffer.size() > 0) {
            if (lineBuffer[lineBuffer.size() - 1] == '\r')
                lineBuffer.erase(lineBuffer.size() - 1);
        }

        // Skip if empty line.
        if (lineBuffer.empty()) {
            continue;
        }
        //***

        const char *token = lineBuffer.c_str();
        token += strspn(token, " \t");
        assert(token);
        if (token[0] == '\0')
            continue; // empty line

        if (token[0] == '#')
            continue; // comment line

        // vertex
        if (token[0] == 'v' && isSpace((token[1]))) {
            token += 2;
            float x, y, z;
            parseFloat3(x,y,z,token);
            glm::vec3 vertex = glm::vec3(x,y,z);
            temp_vertices.push_back(vertex);
            continue;
        }
        // normal
        if (token[0] == 'v' && token[1] == 'n' && isSpace((token[2]))) {
            token += 3;
            float x, y, z;
            parseFloat3(x, y, z, token);
            glm::vec3 normal = glm::vec3(x,y,z);
            temp_normals.push_back(normal);
            continue;
        }
        // texcoord
        if (token[0] == 'v' && token[1] == 't' && isSpace((token[2]))) {
            token += 3;
            float x, y;
            parseFloat2(x, y, token);
            glm::vec2 uv = glm::vec2 (x,y);
            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            temp_uvs.push_back(uv);
            continue;
        }

        // face
        if (token[0] == 'f' && isSpace((token[1]))) {
            token += 2;
            token += strspn(token, " \t");

            std::vector<vertex_index> face;
            while (!isNewLine(token[0])) {
                vertex_index vi =
                        parseTriple(token, temp_vertices.size() / 3, temp_normals.size() / 3, temp_uvs.size() / 2);

                face.push_back(vi);
                int n = strspn(token, " \t\r");
                token += n;
            }
            //printf("[ObjLoader] Face count: %i\n", face.size());



            vertexIndices.push_back(face[0].v_idx);
            vertexIndices.push_back(face[1].v_idx);
            vertexIndices.push_back(face[2].v_idx);

            uvIndices.push_back(face[0].vt_idx);
            uvIndices.push_back(face[1].vt_idx);
            uvIndices.push_back(face[2].vt_idx);

            normalIndices.push_back(face[0].vn_idx);
            normalIndices.push_back(face[1].vn_idx);
            normalIndices.push_back(face[2].vn_idx);



            continue;
        }


    }


    // For each vertex of each triangle

    VertexBuffer* vertexBuffer = new VertexBuffer();
    //printf("[ObjLoader] Vertex Indices: %i\n", vertexIndices.size());
    //printf("[ObjLoader] temp_vertices: %i\n", temp_vertices.size());
    //printf("[ObjLoader] temp_uvs: %i\n", temp_uvs.size());
    //printf("[ObjLoader] temp_normals: %i\n", temp_normals.size());
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        //printf("[ObjLoader] Vertex Index: i: %i\n", i);
        // Get the indices of its attributes
        int vertexIndex = vertexIndices[i];
        int uvIndex = uvIndices[i];
        int normalIndex = normalIndices[i];

        //printf("[ObjLoader] VertexIndex: %i\n", vertexIndex);
        //printf("[ObjLoader] uvIndex: %i\n", uvIndex);
        //printf("[ObjLoader] normalIndex: %i\n", normalIndex);
        // Get the attributes thanks to the index

        if (uvIndex >= 0 ) {
            glm::vec2 uv = temp_uvs[ uvIndex];
            vertexBuffer->addUV(uv);
        }


        if (vertexIndex >= 0) {
            glm::vec3 vertex = temp_vertices[ vertexIndex ];
            vertexBuffer->addVertex(vertex);
        }

        if (normalIndex >= 0) {
            glm::vec3 normal = temp_normals[normalIndex ];
            vertexBuffer->addNormal(normal);
        }



    }
    vertexBuffer->upload();

    return vertexBuffer;
}

ObjLoader::ObjLoader() {

}
