#include "ObjParser.h"
#include <fstream>
#include <iostream>
#include "Log/Log.h"

namespace Galaxy 
{
    typedef uint32_t uint;
    typedef uint16_t ushort;
    typedef uint8_t  ubyte;

    ObjData ObjParser::ParseFile(const std::string filepath)
    {
        std::ifstream stream(filepath, std::ios::in);
        if (!stream.is_open())
        {
            LOG_ERROR("[OBJPARSER] Unable to open file: File doesn't exist!");
            return {};
        }
        std::string line;
        std::string content;
        std::vector<std::string> names;

        uint hcount  = 0;
        uint ocount  = 0;
        uint vcount  = 0;
        uint vtcount = 0;
        uint vncount = 0;
        uint fcount  = 0;

        glm::fvec3 tempvec = glm::fvec3(0, 0, 0);
        glm::fvec2 tempvec2 = glm::fvec2(0, 0);

        std::vector<glm::fvec3> pos;
        std::vector<glm::fvec2> uv;
        std::vector<glm::fvec3> nrm;
        std::vector<uint> indices;
        
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
                names.push_back(line);               
            }

            if (line[0] == 'v' && line[1] == ' ')
            {
                vcount++;
                line = line.substr(2, line.size());
                sscanf_s(line.c_str(), "%f %f %f", &tempvec.x, &tempvec.y, &tempvec.z);
                pos.push_back(tempvec);
            }

            if (line[0] == 'v' && line[1] == 't')
            {
                vtcount++;
                line = line.substr(3, line.size());
                sscanf_s(line.c_str(), "%f %f", &tempvec2.x, &tempvec2.y);
                uv.push_back(tempvec2);
            }

            if (line[0] == 's')
            {
                // Do nothing
            }

            if (line[0] == 'v' && line[1] == 'n')
            {
                vncount++;
                line = line.substr(3, line.size());
                sscanf_s(line.c_str(), "%f %f %f", &tempvec.x, &tempvec.y, &tempvec.z);
                nrm.push_back(tempvec);
            }

            if (line[0] == 'f')
            {
                fcount++;
            }
        }

        std::cout << "-------Name:  " << names[0] << std::endl;
        std::cout << "---Comments:  " << hcount << std::endl;
        std::cout << "----Objects:  " << ocount << std::endl;
        std::cout << "---Vertices:  " << vcount << std::endl;
        std::cout << "--TexCoords:  " << vtcount << std::endl;
        std::cout << "----Normals:  " << vncount << std::endl;
        std::cout << "------Faces:  " << fcount << std::endl;

        return {};
    }
}
