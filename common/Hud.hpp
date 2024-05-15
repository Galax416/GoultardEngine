#pragma once

#include <common/Entity.hpp>
#include <ft2build.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
 #include <glm/gtc/type_ptr.hpp>
#include FT_FREETYPE_H  

struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class Hud {

private:

    Shader *m_shaderHUD;
    int windowWidth; 
    int windowHeight;
    float texCoords[8] = {
        0.0f, 0.0f, // 0
        1.0f, 0.0f, // 1
        1.0f, 1.0f, // 2
        0.0f, 1.0f  // 3
    };

    // Crosshair
    GLuint m_crosshairTextureID;
    GLuint crosshairVAO, crosshairVBO;
    // Health bar
    GLuint healthTextureID;
    GLuint healthBarVAO, healthBarVBO;
    
    // Text
    Shader *m_textShader;
    FT_Library m_ft;
    FT_Face m_face;
    GLuint m_textVAO, m_textVBO;

    std::map<GLchar, Character> Characters;

public:

    Hud(Shader *shaderHUD, Shader *textShader, int windowWidth, int windowHeight);

    void render(int health, int maxHealth, int bullets);
    void renderCrosshair();
    void renderHealthBar(float health, int maxHealth);
    void renderText(std::string text, float x, float y, float scale, glm::vec3 color);

    void initText();
    void initHealthBar();
    void initCrosshair();
};