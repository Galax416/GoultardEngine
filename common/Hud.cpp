#include <common/Hud.hpp>

Hud::Hud(Shader* shaderHUD, Shader* shaderText) {
	m_shaderHUD = shaderHUD;
	m_textShader = shaderText;

    initCrosshair();
    //initHealthBar();
    initText();
}
void Hud::initCrosshair() {
    m_crosshairTextureID = TextureFromFile("crosshair.png", "../data/hud/", true);
    if (m_crosshairTextureID == 0) {
        std::cerr << "Error: Loading crosshair image failed" << std::endl;
        return;
    }
}

void Hud::initText() {
	// Text
	if (FT_Init_FreeType(&m_ft)) {
		std::cerr << "Error: FreeType: Could not init FreeType Library" << std::endl;
		return;
	}
	if (FT_New_Face(m_ft, "../data/AmazDooM.ttf", 0, &m_face)) {
		std::cerr << "Error: FreeType: Failed to load font" << std::endl;
		return;
	}
	FT_Set_Pixel_Sizes(m_face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (unsigned char c = 0; c < 128; c++){
		// Load character glyph 
		if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			m_face->glyph->bitmap.width,
			m_face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			m_face->glyph->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// now store character for later use
		Character character = {
			texture,
			glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
			glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
			static_cast<unsigned int>(m_face->glyph->advance.x)
		};
		Characters.insert(std::pair<char, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
    // destroy FreeType once we're finished
    FT_Done_Face(m_face);
    FT_Done_FreeType(m_ft);

	glGenVertexArrays(1, &m_textVAO);
    glGenBuffers(1, &m_textVBO);
    glBindVertexArray(m_textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
}

void Hud::render(int windowWidth, int windowHeight, int health, int maxHealth) {
    m_shaderHUD->use();

    // Calculer la largeur de la barre de vie en fonction des points de vie actuels
    float healthPercentage = static_cast<float>(health) / static_cast<float>(maxHealth);
    float barWidth = 2.0f * 0.2f * healthPercentage; // Largeur de la barre de vie en fonction du pourcentage de santé

    // Définir les coordonnées des sommets de la barre de vie
    float barHeight = 0.1f; // Hauteur de la barre de vie
    float barX = -0.9f; // Position X de la barre de vie
    float barY = -0.9f; // Position Y de la barre de vie

    // Définir les coordonnées des sommets de la barre de vie
    GLfloat healthBarVertices[] = {
        // Bas gauche
        barX, barY,
        // Bas droit
        barX + barWidth, barY,
        // Haut droit
        barX + barWidth, barY + barHeight,
        // Haut gauche
        barX, barY + barHeight
    };

    // Créer et configurer les buffers OpenGL pour la barre de vie
    GLuint healthBarVAO, healthBarVBO;
    glGenVertexArrays(1, &healthBarVAO);
    glGenBuffers(1, &healthBarVBO);

    glBindVertexArray(healthBarVAO);
    glBindBuffer(GL_ARRAY_BUFFER, healthBarVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(healthBarVertices), healthBarVertices, GL_STATIC_DRAW);

    // Configuration des attributs de vertex pour la position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

    // Dessiner la barre de vie
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // Nettoyer
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLfloat crosshairVertices[] = {
        // Position
        -0.05f, -0.05f,
         0.05f, -0.05f,
         0.05f,  0.05f,
        -0.05f,  0.05f
    };

    GLfloat texCoords[] = {
        // UV
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    // Créer et configurer les buffers OpenGL pour le viseur
    GLuint crosshairVAO, crosshairVBO;
    glGenVertexArrays(1, &crosshairVAO);
    glGenBuffers(1, &crosshairVBO);

    glBindVertexArray(crosshairVAO);
    glBindBuffer(GL_ARRAY_BUFFER, crosshairVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(crosshairVertices) + sizeof(texCoords), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(crosshairVertices), crosshairVertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(crosshairVertices), sizeof(texCoords), texCoords);

    // Position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

    // Texture coordinate attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)(sizeof(crosshairVertices)));

    // Dessiner le viseur (crosshair)
    glActiveTexture(GL_TEXTURE0);
    m_shaderHUD->setInt("texHud", 0);
    glBindTexture(GL_TEXTURE_2D, m_crosshairTextureID);
    glBindVertexArray(crosshairVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


	// Text
	renderText("This is sample text", 25.0f, 25.0f, 10.0f, glm::vec3(0.5, 0.8f, 0.2f));

    // Nettoyer
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Hud::renderText(std::string text, float x, float y, float scale, glm::vec3 color) {
    // activate corresponding render state	
    m_textShader->use();
    glUniform3f(glGetUniformLocation(m_textShader->getID(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_textVAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) 
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, m_textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
