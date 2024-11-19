#include "ObjectLoader.h"
#include "../EngineCore.h"
#include <iostream>
#include "Mesh.h"

#ifdef _DEBUG
#include "..\..\EngineCore\checkML.h"
#endif // _DEBUG

ObjectLoader::ObjectLoader()
{
}

//-------------------------------------------------------------------------

ObjectLoader::~ObjectLoader()
{

}

bool ObjectLoader::LoadOBJFile(const char* _path, Object* _parent, std::vector<Mesh*>& outMeshes_)
{
    Mesh* auxMesh = nullptr;

    char objectFolder[MAX_PATH];
    char objectFilename[64];

    strcpy_s(objectFolder, EngineCore::GetResourceFolder());
    strcat_s(objectFolder, "meshes\\");

    strcpy_s(objectFilename, _path);

    char filename[MAX_PATH];
    strcpy_s(filename, objectFolder);
    strcat_s(filename, objectFilename);


    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< glm::dvec3> temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;

    FILE* file;
    fopen_s(&file, filename, "r");
    if (file == NULL) {
        printf("Impossible to open the file !\n");
        return false;
    }

    while (1) {

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf_s(file, "%s", lineHeader, 128);
        if (res == EOF)
        {
            if (auxMesh && !temp_vertices.empty())
            {
                std::vector<glm::dvec3> auxVertices;

                // For each vertex of each triangle
                for (unsigned int i = 0; i < vertexIndices.size(); i++) {
                    unsigned int vertexIndex = vertexIndices[i];
                    glm::dvec3 vertex = temp_vertices[vertexIndex - 1];
                    auxVertices.push_back(vertex);
                }

                auxMesh->ParseFromOBJ(vertexIndices.size(), auxVertices);
                outMeshes_.push_back(auxMesh);
            }

            break; // EOF = End Of File. Quit the loop.
        }

        // else : parse lineHeader
        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);

        }
        else if (strcmp(lineHeader, "usemtl") == 0) {
            if (auxMesh)
            {
                std::vector<glm::dvec3> auxVertices;

                // For each vertex of each triangle
                for (unsigned int i = 0; i < vertexIndices.size(); i++) {
                    unsigned int vertexIndex = vertexIndices[i];
                    glm::dvec3 vertex = temp_vertices[vertexIndex - 1];
                    auxVertices.push_back(vertex);
                }

                auxMesh->ParseFromOBJ(vertexIndices.size(), auxVertices);
                outMeshes_.push_back(auxMesh);
            }
            auxMesh = new Mesh(_parent);
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0) {
            unsigned int vertexIndex, uvIndex, normalIndex;

            char line[128];
            int matches = 0;

            fgets(line, sizeof(line), file);

            int numberLength = 0;
            int valueCount = 0;

            for (int i = 1; i < sizeof(line); ++i)
            {
                if (line[i] == ' ')
                {
                    numberLength = 0;
                    valueCount = 0;
                    continue;
                }

                else if (line[i] == '/')
                {
                    if (line[i + 1] == '/')
                        ++i;
                    numberLength = 0;
                }

                else if (line[i] == '\n')
                {
                    break;
                }
                else
                {
                    numberLength++;

                    if (line[i + 1] == ' ' || line[i + 1] == '/')
                    {
                        char auxNumber[16];
                        std::string myString(line);
                        myString = myString.substr(i - numberLength + 1, i);
                        int myNumber = atoi(myString.c_str());

                        if (valueCount == 0)
                        {
                            vertexIndices.push_back(myNumber);
                        }

                        else if (valueCount == 1)
                        {
                            uvIndices.push_back(myNumber);
                        }
                        else
                        {
                            normalIndices.push_back(myNumber);
                        }

                        valueCount++;
                    }
                }

            }
        }
    }
    return true;
}