//
// Created by Taha Doğan Güneş on 02/04/15.
//

#ifndef SPYE_PRIMITIVES_H
#define SPYE_PRIMITIVES_H


struct Rect {
    float x;
    float y;
    float w;
    float h;

    Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) { }
};


struct Color {
    float r;
    float g;
    float b;

    Color(float r, float g, float b) : r(r), g(g), b(b) { }

    Color static red() {
        return Color(1, 0, 0);
    }

    Color static blue() {
        return Color(0, 0, 1);
    }

    Color static green() {
        return Color(0, 1, 0);
    }

    Color static white() {
        return Color(1, 1, 1);
    }

    Color static black() {
        return Color(0, 0, 0);
    }
};


#endif //SPYE_PRIMITIVES_H
