#pragma once
#define GL_SILENCE_DEPRECATION

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <stdexcept>

#include "../../ObjectEngine/geometry"
#include "../../ObjectEngine/type"

#define __INIT_STATE(x) (x->__type != 0)
#define __TYPE_SAFE(x) (type_value<x>::value == __type)


namespace __base_ {
    class __render_ : private node_t {
    public:
        virtual ~__render_() = default;
    };
}

    
class render : private __base_::__render_ {
private:
    GLuint __vao;
    GLuint __vbo;
    GLuint __ebo;
    GLuint __type;
    
public:
    render();
    virtual ~render();
    
    template <typename _gT>
    void insert(_gT*);
    inline void draw();
    
private:
    template <typename _gT>
    inline void __init_(_gT*);
    template <typename _gT>
    inline void __buff_(_gT*);
};


render::render()
: __vao(0)
, __vbo(0)
, __ebo(0)
, __type(0) {
    glGenVertexArrays(1, &__vao);
    glGenBuffers(1, &__vbo);
    glGenBuffers(1, &__ebo);
}

render::~render() {
    if (__INIT_STATE(this)) {
        glDeleteBuffers(1, &__ebo);
        glDeleteBuffers(1, &__vbo);
        glDeleteVertexArrays(1, &__vao);
    }
}

template <typename _gT>
void render::insert(_gT* geometric) {
    if (__INIT_STATE(this) && __TYPE_SAFE(_gT)) __buff_(geometric);
    else                                        __init_(geometric);
}

void render::draw() {
    glBindVertexArray(__vao);
    glDrawElements(GL_TRIANGLES, (__type-2)*3, GL_UNSIGNED_INT, (void*)0);
}

template <>
void render::__init_(geometry<vertex<dim2_t, ntexture_t>>* geometric) {
    __type = (GLuint)geometric->__vertex.size();
    glBindVertexArray(__vao);
    glBindBuffer(GL_ARRAY_BUFFER, __vbo);
    glBufferData(GL_ARRAY_BUFFER, __type*sizeof(typename geometry<vertex<dim2_t, ntexture_t>>::vertex_t), &(geometric->__vertex[0]), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, __ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (__type-2)*3*sizeof(GLuint), &(geometric->__index[0]), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(typename geometry<vertex<dim2_t, ntexture_t>>::vertex_t), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(typename geometry<vertex<dim2_t, ntexture_t>>::vertex_t), (void*)sizeof(glm::vec3));
}

template <>
void render::__buff_(geometry<vertex<dim2_t, ntexture_t>>* geometric) {
    glBindVertexArray(__vao);
    glBindBuffer(GL_ARRAY_BUFFER, __vbo);
    glBufferData(GL_ARRAY_BUFFER, __type*sizeof(typename geometry<vertex<dim2_t, ntexture_t>>::vertex_t), &(geometric->__index[0]), GL_STATIC_DRAW);
}
