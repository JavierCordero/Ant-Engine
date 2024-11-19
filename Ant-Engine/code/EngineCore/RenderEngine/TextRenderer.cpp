#include "TextRenderer.h"
#include "../EngineCore.h"
#include <iostream>
#include "../Texture/Texture.h"
#include "../../../include/glm/gtc/matrix_transform.hpp"
#include "../Interface/Interface.h"
#include "RenderLib.h"

#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG

#include <filesystem>
namespace fs = std::filesystem;

#define GL_CLAMP_TO_EDGE 0x812F 

char TextRenderer::m_TextureFolder[MAX_PATH] = "";
std::map<char, TextRenderer::Character> TextRenderer::Characters;
Texture TextRenderer::FontTexture;
TTF_Font* TextRenderer::m_FontPointer = nullptr;

bool TextRenderer::InitTextRenderer()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    strcpy_s(m_TextureFolder, EngineCore::GetResourceFolder());
    strcat_s(m_TextureFolder, "fonts\\");

    std::vector<std::string> allFontsInFolder;
    GetALlFilesInFolderWithExtension(m_TextureFolder, ".ttf", allFontsInFolder);

    if (allFontsInFolder.empty())
    {
        std::cout << "		      |---- No fonts loaded.\n";
        return -1;
    }

    TTF_Init();

    LoadFont(allFontsInFolder[0].c_str());

    for (std::string file : allFontsInFolder)
    {
        /*FT_Face face;
        if (FT_New_Face(ft, file.c_str(), 0, &face))
        {
            std::cout << "ERROR::FREETYPE: Failed to load font: " << file << std::endl;
            break;
        }
        StoreCharacters(face);
        FT_Done_Face(face);*/
    }
    
    //FT_Done_FreeType(ft);
}

void TextRenderer::StoreCharacters(FT_Face _face)
{
    FT_Set_Pixel_Sizes(_face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(_face, c, FT_LOAD_RENDER))
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
            _face->glyph->bitmap.width,
            _face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            _face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
            glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
            _face->glyph->advance.x
        };
        TextRenderer::Characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::LoadFont(const char* _fontFile)
{
    //Open the font
    m_FontPointer = TTF_OpenFont(_fontFile, 12);
    std::cout << TTF_GetError() << std::endl;
    if (m_FontPointer == nullptr) {
        //logSDLError(std::cout, "TTF_OpenFont");
        return;
    }
    //EN ALGUN MOMENTO TTF_CloseFont(m_FontPointer);

}

void TextRenderer::RenderText(const char* message)
{
    //We need to first render to a surface as that's what TTF_RenderText
   //returns, then load that surface into a texture
    SDL_Surface* surf = TTF_RenderText_Blended(m_FontPointer, message, {0,0,0,255});
    if (surf == nullptr) {
        TTF_CloseFont(m_FontPointer);
        return;
    }

    FontTexture.CreateFromSurface(surf);

    //Clean up the surface and font
    Interface sprite = Interface(FontTexture, 500, 100, 300, 300);
    glm::mat4 projection = glm::ortho(0, RenderLib::GetWindowWidth(), RenderLib::GetWindowHeight(), 0);
    sprite.Render(projection);
   
    //return texture;
}

//void TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
//{
//    // activate corresponding render state	
//    
//    //glUniform3f(glGetUniformLocation(s.Program, "textColor"), color.x, color.y, color.z);
//    //glActiveTexture(GL_TEXTURE0);
//    //glBindVertexArray(VAO);
//
//    // iterate through all characters
//    std::string::const_iterator c;
//    for (c = text.begin(); c != text.end(); c++)
//    {
//        Character ch = Characters[*c];
//
//        float xpos = x + ch.Bearing.x * scale;
//        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
//
//        float w = ch.Size.x * scale;
//        float h = ch.Size.y * scale;
//        // update VBO for each character
//        float vertices[6][4] = {
//            { xpos,     ypos + h,   0.0f, 0.0f },
//            { xpos,     ypos,       0.0f, 1.0f },
//            { xpos + w, ypos,       1.0f, 1.0f },
//
//            { xpos,     ypos + h,   0.0f, 0.0f },
//            { xpos + w, ypos,       1.0f, 1.0f },
//            { xpos + w, ypos + h,   1.0f, 0.0f }
//        };
//
//        glEnable(GL_TEXTURE_2D);
//        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//
//        glBegin(GL_QUADS);
//
//        glTexCoord2f(0, 0); glVertex3f(xpos, ypos, 0);
//        glTexCoord2f(0, 1); glVertex3f(xpos, ypos + h, 0);
//        glTexCoord2f(1, 1); glVertex3f(xpos + w, ypos + h, 0);
//        glTexCoord2f(1, 0); glVertex3f(xpos + w, ypos, 0);
//        glEnd();
//
//        // render glyph texture over quad
//        //glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//        // update content of VBO memory
//        //glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//        //glBindBuffer(GL_ARRAY_BUFFER, 0);
//        // render quad
//        //glDrawArrays(GL_TRIANGLES, 0, 6);
//        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
//        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
//    }
//    //glBindVertexArray(0);
//    //glBindTexture(GL_TEXTURE_2D, 0);
//}

void TextRenderer::GetALlFilesInFolderWithExtension(const char* _root, const char* _ext, std::vector<std::string>& _outVector_)
{
    // This structure would distinguish a file from a
    // directory
    struct stat sb;

    // Looping until all the items of the directory are
    // exhausted
    for (const auto& entry : fs::directory_iterator(_root)) {

        // Converting the path to const char * in the
        // subsequent lines
        fs::path outfilename = entry.path();
        std::string outfilename_str = outfilename.string();
        std::string extension = entry.path().extension().string();
        std::string filename = entry.path().filename().string();

        char path[64];
        strcpy_s(path, outfilename_str.c_str());

        // Testing whether the path points to a
        // non-directory or not If it does, displays path
        if (strcmp(extension.c_str(), _ext) == 0 && stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR))
        {
            std::cout << "		      |---- Font Name: " << filename << "\n";
            _outVector_.push_back(outfilename_str);
        }       
    }
}