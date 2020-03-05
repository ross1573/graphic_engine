#define API_OPENGL
#define DEBUG_MODE
#include "core_engine.h"
#include "iostream"


class game_engine : public graphic_engine {
private:
    component cmp;
    
    glm::mat4 projection;
    glm::mat4 view;
    
public:
    game_engine(window_settings settings)
    : graphic_engine(settings) {}
    
private:
    void setting() override {
        glEnable(GL_POLYGON_SMOOTH);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_BLEND);
    }
    
    void setup() override {
        cmp.create_all();
        cmp.insert(make_regular<geometry<vertex<dim2_t, ntexture_t>>>(3, glm::vec3(0.9f, 0.1f, 0.5f)));
        cmp.shader()->insert(get_path().append("Shader/opengl_2d_nontexture_vertex.glsl"), GL_VERTEX_SHADER);
        cmp.shader()->insert(get_path().append("Shader/opengl_2d_nontexture_fragment.glsl"), GL_FRAGMENT_SHADER);
        cmp.shader()->compile();
        cmp.render()->insert(cmp.geometry<geometry<vertex<dim2_t, ntexture_t>>>());
        cmp.transform()->insert(glm::mat4(1.0f));
        
        GLint width, height;
        get_size(width, height);
        projection = glm::perspective(45.0f, (GLfloat)width/(GLfloat)height, -10.0f, 5.0f);
        view = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    
    void render() override {
        cmp.shader()->use();
        cmp.shader()->uniform("projection", projection);
        cmp.shader()->uniform("view", view);
        cmp.draw();
    }
};


int main() {
    window_settings settings;
    settings.transparent = true;
    try {
        game_engine game(settings);
        game.run();
    }
    catch (std::runtime_error error) {
        std::cout << error.what() << std::endl;
    }
}
