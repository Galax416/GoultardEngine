#include <common/Hud.hpp>

Hud::Hud(Shader* shaderHUD, Shader* shaderText, int width, int height) {
	m_shaderHUD = shaderHUD;
	m_textShader = shaderText;
    windowWidth = width;
    windowHeight = height;

    // Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    initCrosshair();
    initHealthBar();
    initText();
}

void Hud::initCrosshair() {
    // Texture bind
    m_crosshairTextureID = TextureFromFile("crosshair.png", "../data/hud/", true);
    if (m_crosshairTextureID == 0) {
        std::cerr << "Error: Loading crosshair image failed" << std::endl;
        return;
    }

    GLfloat crosshairVertices[] = {
        // Position
        -0.05f, -0.05f,
         0.05f, -0.05f,
         0.05f,  0.05f,
        -0.05f,  0.05f
    };

    // Bind VAO/VBO
    glGenVertexArrays(1, &crosshairVAO);
    glGenBuffers(1, &crosshairVBO);

    glBindVertexArray(crosshairVAO);
    glBindBuffer(GL_ARRAY_BUFFER, crosshairVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(crosshairVertices) + sizeof(texCoords), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(crosshairVertices), crosshairVertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(crosshairVertices), sizeof(texCoords), texCoords);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)(sizeof(crosshairVertices)));
}

void Hud::initHealthBar() {
    // Texture bind
    healthTextureID = TextureFromFile("health.png", "../data/hud/", true);
    if (healthTextureID == 0) {
        std::cerr << "Error: Loading crosshair image failed" << std::endl;
        return;
    }
}

void Hud::initText() {
    m_textShader->use();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(windowWidth), 0.0f, static_cast<float>(windowHeight));
    glUniformMatrix4fv(glGetUniformLocation(m_textShader->getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
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

    // Text rendering
	glGenVertexArrays(1, &m_textVAO);
    glGenBuffers(1, &m_textVBO);
    glBindVertexArray(m_textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    m_shaderHUD->use();
}

void Hud::render(int health, int maxHealth, int bullets) {
    m_shaderHUD->use();

    // Health bar
    renderHealthBar(health, maxHealth);

    // Dessiner le viseur (crosshair)
    renderCrosshair();

	// Text
    std::string bullet = "Bullets: " + std::to_string(bullets);
	renderText(bullet, windowWidth - 300.0f, 25.0f, 1.0f, glm::vec3(0.45, 0.065f, 0.0f));
}

void Hud::renderHealthBar(float health, int maxHealth) {
    // since the health need to be updated, we will update the VBO each time we render the health bar
    float healthPercentage = static_cast<float>(health) / static_cast<float>(maxHealth);
    float barWidth = 2.0f * 0.2f * healthPercentage; 

    float barHeight = 0.1f; // Height
    float barX = -0.9f; // X
    float barY = -0.9f; // Y

    float healthBarVertices[8] = {
        barX, barY,
        barX + barWidth, barY,
        barX + barWidth, barY + barHeight,
        barX, barY + barHeight
    };

    // Bind VAO/VBO
    glGenVertexArrays(1, &healthBarVAO);
    glGenBuffers(1, &healthBarVBO);

    glBindVertexArray(healthBarVAO);
    glBindBuffer(GL_ARRAY_BUFFER, healthBarVBO);
    // Fill buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(healthBarVertices) + sizeof(texCoords), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(healthBarVertices), healthBarVertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(healthBarVertices), sizeof(texCoords), texCoords);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)(sizeof(healthBarVertices)));

    glActiveTexture(GL_TEXTURE0);
    m_shaderHUD->setInt("texHud", 0);
    glBindTexture(GL_TEXTURE_2D, healthTextureID);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
     
    // clean up
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Hud::renderCrosshair() {
    // draw crosshair
    glBindVertexArray(crosshairVAO);
    glActiveTexture(GL_TEXTURE0);
    m_shaderHUD->setInt("texHud", 0);
    glBindTexture(GL_TEXTURE_2D, m_crosshairTextureID);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // clean up
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
