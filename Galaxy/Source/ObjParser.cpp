#include "ObjParser.h"
#include <fstream>
#include <iostream>
#include "Log.h"

namespace Galaxy 
{
    ObjData ObjParser::ParseFile(const std::string& filepath)
    {
        std::ifstream stream(filepath, std::ios::in);
        if (!stream.is_open())
        {
            LOG_ERROR("[OBJPARSER] Unable to open file: File doesn't exist!\n");
            return {};
        }
        std::string line;
        std::string content;

        unsigned int hcount  = 0;
        unsigned int ocount  = 0;
        unsigned int vcount  = 0;
        unsigned int vtcount = 0;
        unsigned int vncount = 0;
        unsigned int fcount  = 0;

        std::vector<glm::ivec3> tmp_ind = std::vector<glm::ivec3>(3);
        glm::fvec3 tempvec = glm::fvec3(0, 0, 0);
        glm::fvec2 tempvec2 = glm::fvec2(0, 0);

        ObjData data;

        // Begin parse data from obj file
        while (std::getline(stream, line))
        {
            if (line[0] == '#')
            {
                hcount++;
                line = line.substr(2, line.size());               
            }

            if (line[0] == 'o')
            {
                ocount++;
                line = line.substr(2, line.size());
                data.objectnames.push_back(line);          
            }

            if (line[0] == 'v' && line[1] == ' ')
            {
                vcount++;
                line = line.substr(2, line.size());
                sscanf(line.c_str(), "%f %f %f", &tempvec.x, &tempvec.y, &tempvec.z);
                data.positions.push_back(tempvec);
            }

            if (line[0] == 'v' && line[1] == 't')
            {
                vtcount++;
                line = line.substr(3, line.size());
                sscanf(line.c_str(), "%f %f", &tempvec2.x, &tempvec2.y);
                data.texCoords.push_back(tempvec2);
            }

            if (line[0] == 's')
            {
                // Do nothing
            }

            if (line[0] == 'v' && line[1] == 'n')
            {
                vncount++;
                line = line.substr(3, line.size());
                sscanf(line.c_str(), "%f %f %f", &tempvec.x, &tempvec.y, &tempvec.z);
                data.normals.push_back(tempvec);
            }

            if (line[0] == 'f')
            {
                fcount++;
                line = line.substr(2, line.size());

                sscanf(line.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", 
                    &tmp_ind[0].x, &tmp_ind[0].y, &tmp_ind[0].z,
                    &tmp_ind[1].x, &tmp_ind[1].y, &tmp_ind[1].z,
                    &tmp_ind[2].x, &tmp_ind[2].y, &tmp_ind[2].z);

                data.indices.push_back(tmp_ind[0]);
                data.indices.push_back(tmp_ind[1]);
                data.indices.push_back(tmp_ind[2]);
            }
        }
        stream.close();

        LOG_TRACE("[OBJPARSER]---Comments:  {}", hcount);
        LOG_TRACE("[OBJPARSER]----Objects:  {}", ocount);
        LOG_TRACE("[OBJPARSER]---Vertices:  {}", vcount);
        LOG_TRACE("[OBJPARSER]--TexCoords:  {}", vtcount);
        LOG_TRACE("[OBJPARSER]----Normals:  {}", vncount);
        LOG_TRACE("[OBJPARSER]------Faces:  {}", fcount);
        LOG_TRACE("[OBJPARSER] Finished parsing .obj file!\n");
        return data;
    }

    
    std::vector<Vertex> ObjParser::DataToVertices(const ObjData& objdata, std::vector<unsigned int>& out_glindices)
    {
        std::vector<Vertex> vertices = std::vector<Vertex>(objdata.indices.size());
        out_glindices = std::vector<unsigned int>();

        for (unsigned int i = 0; i < objdata.indices.size(); i++)
        {
            vertices[i] = {
            .position = objdata.positions[objdata.indices[i].x - 1],
            .texCoord = objdata.texCoords[objdata.indices[i].y - 1],
            .normal = objdata.normals[objdata.indices[i].z - 1],
            .color = glm::fvec4(1.0)
            };
            out_glindices.push_back(objdata.indices[i].x - 1);
        }
        
        LOG_TRACE("[OBJPARSER] Converting .obj data to std::vector<Vertex>.\n");
        return vertices;
    }

    std::vector<Vertex> ObjParser::DataToVertices(const ObjData& objdata)
    {
        std::vector<Vertex> vertices = std::vector<Vertex>(objdata.indices.size());

        for (unsigned int i = 0; i < objdata.indices.size(); i++)
        {
            vertices[i] = {
            .position = objdata.positions[objdata.indices[i].x - 1],
            .texCoord = objdata.texCoords[objdata.indices[i].y - 1],
            .normal = objdata.normals[objdata.indices[i].z - 1],
            .color = glm::fvec4(1.0)
            };
        }

        LOG_TRACE("[OBJPARSER] Converting .obj data to std::vector<Vertex>.\n");
        return vertices;
    }
}
