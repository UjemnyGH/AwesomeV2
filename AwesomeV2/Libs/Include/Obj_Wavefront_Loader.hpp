#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

namespace Obj
{
    struct MeshData
    {
        std::vector<float> vertices;
        std::vector<float> textureCoordinates;
        std::vector<float> normals;

        std::vector<unsigned int> indices;
        std::vector<unsigned int> indicesTexture;
        std::vector<unsigned int> indicesNormals;

        MeshData& operator=(const MeshData& m_data)
        {
            this->vertices.clear();
            this->textureCoordinates.clear();
            this->normals.clear();
            this->indices.clear();
            this->indicesTexture.clear();
            this->indicesNormals.clear();

            this->vertices = m_data.vertices;
            this->textureCoordinates = m_data.textureCoordinates;
            this->normals = m_data.normals;
            this->indices = m_data.indices;
            this->indicesTexture = m_data.indicesTexture;
            this->indicesNormals = m_data.indicesNormals;

            return *this;
        }
    };

    struct BufferMeshData
    {
        std::vector<float> vertices;
        std::vector<float> textureCoordinates;
        std::vector<float> normals;

        BufferMeshData& operator=(const BufferMeshData& b_data)
        {
            this->vertices.clear();
            this->textureCoordinates.clear();
            this->normals.clear();

            this->vertices = b_data.vertices;
            this->textureCoordinates = b_data.textureCoordinates;
            this->normals = b_data.normals;

            return *this;
        }
    };

    struct MaterialData
    {
        std::vector<float> ambient;
        std::vector<float> diffuse;
        std::vector<float> specular;

        std::vector<float> transparent;
        std::vector<float> transmissionFilter;
        std::vector<float> density;
        std::vector<short> illumination;
    };

    MeshData LoadMesh(const std::string & meshPath, bool loadOnlyvertIndices = false)
    {
        MeshData m_data;
        MeshData* mp_data = new MeshData;

        std::ifstream f;
    
        f.open(meshPath, std::ios::binary);

        if(!f)
        {
            std::cout << "File error: " << meshPath.c_str() << std::endl;
        }

        std::string line;

        while(!f.eof())
        {
            getline(f, line);

            if(line.find("v ") == 0)
            {
                std::stringstream ss(line.c_str() + 2);

                float x, y, z;

                ss >> x >> y >> z;

                m_data.vertices.push_back(x);
                m_data.vertices.push_back(y);
                m_data.vertices.push_back(z);
            }
            else if(line.find("vt ") == 0)
            {
                std::stringstream ss(line.c_str() + 3);

                float u, v;

                ss >> u >> v;

                mp_data->textureCoordinates.push_back(u);
                mp_data->textureCoordinates.push_back(v);
            }
            else if(line.find("vn ") == 0)
            {
                std::stringstream ss(line.c_str() + 3);

                float nx, ny, nz;

                ss >> nx >> ny >> nz;

                mp_data->normals.push_back(nx);
                mp_data->normals.push_back(ny);
                mp_data->normals.push_back(nz);
            }
            else if(line.find("f ") == 0)
            {
                int slashNum = 0;
                size_t lastSlash;
                bool doubleSlash = false;

                for(size_t i = 0; i < line.size(); i++)
                {
                    if(line[i] == '/')
                    {
                        if(line[i] == '/' && line[i + 1] == '/')
                        {
                            doubleSlash = true;

                            line[i] = ' ';
                            line[i + 1] = ' ';

                            lastSlash = i;
                            slashNum += 2;
                        }
                        else
                        {
                            line[i] = ' ';

                            lastSlash = i;
                            slashNum++;
                        }
                    }
                }

                std::stringstream ss(line.c_str() + 2);

                float ivX, itX, inX, ivY, itY, inY, ivZ, itZ, inZ, ivW, itW, inW;
                if(loadOnlyvertIndices)
                {
                    if(doubleSlash)
                    {
                        ss >> ivX >> inX >> ivY >> inY >> ivZ >> inZ >> ivW >> inW;

                        m_data.indices.push_back(ivX - 1);
                        m_data.indices.push_back(ivY - 1);
                        m_data.indices.push_back(ivZ - 1);
                        
                        m_data.indices.push_back(ivX - 1);
                        m_data.indices.push_back(ivZ - 1);
                        m_data.indices.push_back(ivW - 1);

                        m_data.normals.push_back(mp_data->normals[(inX - 1) * 3]);
                        m_data.normals.push_back(mp_data->normals[(inX - 1) * 3 + 1]);
                        m_data.normals.push_back(mp_data->normals[(inX - 1) * 3 + 2]);

                        m_data.normals.push_back(mp_data->normals[(inY - 1) * 3]);
                        m_data.normals.push_back(mp_data->normals[(inY - 1) * 3 + 1]);
                        m_data.normals.push_back(mp_data->normals[(inY - 1) * 3 + 2]);

                        m_data.normals.push_back(mp_data->normals[(inZ - 1) * 3]);
                        m_data.normals.push_back(mp_data->normals[(inZ - 1) * 3 + 1]);
                        m_data.normals.push_back(mp_data->normals[(inZ - 1) * 3 + 2]);

                        m_data.normals.push_back(mp_data->normals[(inX - 1) * 3]);
                        m_data.normals.push_back(mp_data->normals[(inX - 1) * 3 + 1]);
                        m_data.normals.push_back(mp_data->normals[(inX - 1) * 3 + 2]);

                        m_data.normals.push_back(mp_data->normals[(inZ - 1) * 3]);
                        m_data.normals.push_back(mp_data->normals[(inZ - 1) * 3 + 1]);
                        m_data.normals.push_back(mp_data->normals[(inZ - 1) * 3 + 2]);

                        m_data.normals.push_back(mp_data->normals[(inW - 1) * 3]);
                        m_data.normals.push_back(mp_data->normals[(inW - 1) * 3 + 1]);
                        m_data.normals.push_back(mp_data->normals[(inW - 1) * 3 + 2]);
                    }
                    else
                    {
                        ss >> ivX >> itX >> inX >> ivY >> itY >> inY >> ivZ >> itZ >> inZ >> ivW >> itW >> inW;

                        m_data.indices.push_back(ivX - 1);
                        m_data.indices.push_back(ivY - 1);
                        m_data.indices.push_back(ivZ - 1);
                        
                        m_data.indices.push_back(ivX - 1);
                        m_data.indices.push_back(ivZ - 1);
                        m_data.indices.push_back(ivW - 1);

                        m_data.textureCoordinates.push_back(mp_data->textureCoordinates[(itX - 1) * 2]);
                        m_data.textureCoordinates.push_back(mp_data->textureCoordinates[(itX - 1) * 2 + 1]);

                        m_data.textureCoordinates.push_back(mp_data->textureCoordinates[(itY - 1) * 2]);
                        m_data.textureCoordinates.push_back(mp_data->textureCoordinates[(itY - 1) * 2 + 1]);

                        m_data.textureCoordinates.push_back(mp_data->textureCoordinates[(itZ - 1) * 2]);
                        m_data.textureCoordinates.push_back(mp_data->textureCoordinates[(itZ - 1) * 2 + 1]);

                        m_data.textureCoordinates.push_back(mp_data->textureCoordinates[(itX - 1) * 2]);
                        m_data.textureCoordinates.push_back(mp_data->textureCoordinates[(itX - 1) * 2 + 1]);

                        m_data.textureCoordinates.push_back(mp_data->textureCoordinates[(itZ - 1) * 2]);
                        m_data.textureCoordinates.push_back(mp_data->textureCoordinates[(itZ - 1) * 2 + 1]);

                        m_data.textureCoordinates.push_back(mp_data->textureCoordinates[(itW - 1) * 2]);
                        m_data.textureCoordinates.push_back(mp_data->textureCoordinates[(itW - 1) * 2 + 1]);

                        m_data.normals.push_back(mp_data->normals[(inX - 1) * 3]);
                        m_data.normals.push_back(mp_data->normals[(inX - 1) * 3 + 1]);
                        m_data.normals.push_back(mp_data->normals[(inX - 1) * 3 + 2]);

                        m_data.normals.push_back(mp_data->normals[(inY - 1) * 3]);
                        m_data.normals.push_back(mp_data->normals[(inY - 1) * 3 + 1]);
                        m_data.normals.push_back(mp_data->normals[(inY - 1) * 3 + 2]);

                        m_data.normals.push_back(mp_data->normals[(inZ - 1) * 3]);
                        m_data.normals.push_back(mp_data->normals[(inZ - 1) * 3 + 1]);
                        m_data.normals.push_back(mp_data->normals[(inZ - 1) * 3 + 2]);

                        m_data.normals.push_back(mp_data->normals[(inX - 1) * 3]);
                        m_data.normals.push_back(mp_data->normals[(inX - 1) * 3 + 1]);
                        m_data.normals.push_back(mp_data->normals[(inX - 1) * 3 + 2]);

                        m_data.normals.push_back(mp_data->normals[(inZ - 1) * 3]);
                        m_data.normals.push_back(mp_data->normals[(inZ - 1) * 3 + 1]);
                        m_data.normals.push_back(mp_data->normals[(inZ - 1) * 3 + 2]);

                        m_data.normals.push_back(mp_data->normals[(inW - 1) * 3]);
                        m_data.normals.push_back(mp_data->normals[(inW - 1) * 3 + 1]);
                        m_data.normals.push_back(mp_data->normals[(inW - 1) * 3 + 2]);
                    }
                }
                else
                {
                    if(doubleSlash)
                    {
                        ss >> ivX >> inX >> ivY >> inY >> ivZ >> inZ >> ivW >> inW;

                        m_data.indices.push_back(ivX - 1);
                        m_data.indices.push_back(ivY - 1);
                        m_data.indices.push_back(ivZ - 1);
                        
                        m_data.indices.push_back(ivX - 1);
                        m_data.indices.push_back(ivZ - 1);
                        m_data.indices.push_back(ivW - 1);

                        m_data.indicesNormals.push_back(inX - 1);
                        m_data.indicesNormals.push_back(inY - 1);
                        m_data.indicesNormals.push_back(inZ - 1);

                        m_data.indicesNormals.push_back(inX - 1);
                        m_data.indicesNormals.push_back(inZ - 1);
                        m_data.indicesNormals.push_back(inW - 1);
                    }
                    else
                    {
                        ss >> ivX >> itX >> inX >> ivY >> itY >> inY >> ivZ >> itZ >> inZ >> ivW >> itW >> inW;

                        m_data.indices.push_back(ivX - 1);
                        m_data.indices.push_back(ivY - 1);
                        m_data.indices.push_back(ivZ - 1);
                        
                        m_data.indices.push_back(ivX - 1);
                        m_data.indices.push_back(ivZ - 1);
                        m_data.indices.push_back(ivW - 1);

                        m_data.indicesTexture.push_back(itX - 1);
                        m_data.indicesTexture.push_back(itY - 1);
                        m_data.indicesTexture.push_back(itZ - 1);

                        m_data.indicesTexture.push_back(itX - 1);
                        m_data.indicesTexture.push_back(itZ - 1);
                        m_data.indicesTexture.push_back(itW - 1);

                        m_data.indicesNormals.push_back(inX - 1);
                        m_data.indicesNormals.push_back(inY - 1);
                        m_data.indicesNormals.push_back(inZ - 1);

                        m_data.indicesNormals.push_back(inX - 1);
                        m_data.indicesNormals.push_back(inZ - 1);
                        m_data.indicesNormals.push_back(inW - 1);
                    }
                }
            }
        }

        if(!loadOnlyvertIndices)
        {
            m_data.textureCoordinates = mp_data->textureCoordinates;
            m_data.normals = mp_data->normals;
        }

        delete mp_data;

        f.close();

        return m_data;
    }

    BufferMeshData LoadMeshBuffer(const std::string & meshPath)
    {
        BufferMeshData b_data;
        BufferMeshData* bp_data = new BufferMeshData;

        std::ifstream f;

        f.open(meshPath, std::ios::binary);

        if(f.bad())
        {
            std::cout << "File error: " << meshPath.c_str() << std::endl;
        }

        std::string line;

        while (!f.eof())
        {
            getline(f, line);

            if(line.find("v ") == 0)
            {
                std::stringstream ss(line.c_str() + 2);

                float x, y, z;

                ss >> x >> y >> z;

                bp_data->vertices.push_back(x);
                bp_data->vertices.push_back(y);
                bp_data->vertices.push_back(z);
            }
            else if(line.find("vt ") == 0)
            {
                std::stringstream ss(line.c_str() + 3);

                float u, v;

                ss >> u >> v;

                bp_data->textureCoordinates.push_back(u);
                bp_data->textureCoordinates.push_back(v);
            }
            else if(line.find("vn ") == 0)
            {
                std::stringstream ss(line.c_str() + 3);

                float nx, ny, nz;

                ss >> nx >> ny >> nz;

                bp_data->normals.push_back(nx);
                bp_data->normals.push_back(ny);
                bp_data->normals.push_back(nz);
            }
            else if(line.find("f ") == 0)
            {
                int slashNum = 0;
                size_t lastSlash;
                bool doubleSlash = false;

                for(size_t i = 0; i < line.size(); i++)
                {
                    if(line[i] == '/')
                    {
                        if(line[i] == '/' && line[i + 1] == '/')
                        {
                            doubleSlash = true;

                            line[i] = ' ';
                            line[i + 1] = ' ';

                            lastSlash = i;
                            slashNum += 2;
                        }
                        else
                        {
                            line[i] = ' ';

                            lastSlash = i;
                            slashNum++;
                        }
                    }
                }

                std::stringstream ss(line.c_str() + 2);

                float ivX, itX, inX, ivY, itY, inY, ivZ, itZ, inZ, ivW, itW, inW;

                if(doubleSlash)
                {
                    ss >> ivX >> inX >> ivY >> inY >> ivZ >> inZ >> ivW >> inW;

                    b_data.vertices.push_back(bp_data->vertices[(ivX - 1) * 3]);
                    b_data.vertices.push_back(bp_data->vertices[(ivX - 1) * 3 + 1]);
                    b_data.vertices.push_back(bp_data->vertices[(ivX - 1) * 3 + 2]);

                    b_data.vertices.push_back(bp_data->vertices[(ivY - 1) * 3]);
                    b_data.vertices.push_back(bp_data->vertices[(ivY - 1) * 3 + 1]);
                    b_data.vertices.push_back(bp_data->vertices[(ivY - 1) * 3 + 2]);

                    b_data.vertices.push_back(bp_data->vertices[(ivZ - 1) * 3]);
                    b_data.vertices.push_back(bp_data->vertices[(ivZ - 1) * 3 + 1]);
                    b_data.vertices.push_back(bp_data->vertices[(ivZ - 1) * 3 + 2]);

                    b_data.vertices.push_back(bp_data->vertices[(ivX - 1) * 3]);
                    b_data.vertices.push_back(bp_data->vertices[(ivX - 1) * 3 + 1]);
                    b_data.vertices.push_back(bp_data->vertices[(ivX - 1) * 3 + 2]);

                    b_data.vertices.push_back(bp_data->vertices[(ivZ - 1) * 3]);
                    b_data.vertices.push_back(bp_data->vertices[(ivZ - 1) * 3 + 1]);
                    b_data.vertices.push_back(bp_data->vertices[(ivZ - 1) * 3 + 2]);

                    b_data.vertices.push_back(bp_data->vertices[(ivW - 1) * 3]);
                    b_data.vertices.push_back(bp_data->vertices[(ivW - 1) * 3 + 1]);
                    b_data.vertices.push_back(bp_data->vertices[(ivW - 1) * 3 + 2]);

                    b_data.normals.push_back(bp_data->normals[(inX - 1) * 3]);
                    b_data.normals.push_back(bp_data->normals[(inX - 1) * 3 + 1]);
                    b_data.normals.push_back(bp_data->normals[(inX - 1) * 3 + 2]);

                    b_data.normals.push_back(bp_data->normals[(inY - 1) * 3]);
                    b_data.normals.push_back(bp_data->normals[(inY - 1) * 3 + 1]);
                    b_data.normals.push_back(bp_data->normals[(inY - 1) * 3 + 2]);

                    b_data.normals.push_back(bp_data->normals[(inZ - 1) * 3]);
                    b_data.normals.push_back(bp_data->normals[(inZ - 1) * 3 + 1]);
                    b_data.normals.push_back(bp_data->normals[(inZ - 1) * 3 + 2]);

                    b_data.normals.push_back(bp_data->normals[(inX - 1) * 3]);
                    b_data.normals.push_back(bp_data->normals[(inX - 1) * 3 + 1]);
                    b_data.normals.push_back(bp_data->normals[(inX - 1) * 3 + 2]);

                    b_data.normals.push_back(bp_data->normals[(inZ - 1) * 3]);
                    b_data.normals.push_back(bp_data->normals[(inZ - 1) * 3 + 1]);
                    b_data.normals.push_back(bp_data->normals[(inZ - 1) * 3 + 2]);

                    b_data.normals.push_back(bp_data->normals[(inW - 1) * 3]);
                    b_data.normals.push_back(bp_data->normals[(inW - 1) * 3 + 1]);
                    b_data.normals.push_back(bp_data->normals[(inW - 1) * 3 + 2]);
                }
                else
                {
                    ss >> ivX >> itX >> inX >> ivY >> itY >> inY >> ivZ >> itZ >> inZ >> ivW >> itW >> inW;

                    b_data.vertices.push_back(bp_data->vertices[(ivX - 1) * 3]);
                    b_data.vertices.push_back(bp_data->vertices[(ivX - 1) * 3 + 1]);
                    b_data.vertices.push_back(bp_data->vertices[(ivX - 1) * 3 + 2]);

                    b_data.vertices.push_back(bp_data->vertices[(ivY - 1) * 3]);
                    b_data.vertices.push_back(bp_data->vertices[(ivY - 1) * 3 + 1]);
                    b_data.vertices.push_back(bp_data->vertices[(ivY - 1) * 3 + 2]);

                    b_data.vertices.push_back(bp_data->vertices[(ivZ - 1) * 3]);
                    b_data.vertices.push_back(bp_data->vertices[(ivZ - 1) * 3 + 1]);
                    b_data.vertices.push_back(bp_data->vertices[(ivZ - 1) * 3 + 2]);

                    b_data.vertices.push_back(bp_data->vertices[(ivX - 1) * 3]);
                    b_data.vertices.push_back(bp_data->vertices[(ivX - 1) * 3 + 1]);
                    b_data.vertices.push_back(bp_data->vertices[(ivX - 1) * 3 + 2]);

                    b_data.vertices.push_back(bp_data->vertices[(ivZ - 1) * 3]);
                    b_data.vertices.push_back(bp_data->vertices[(ivZ - 1) * 3 + 1]);
                    b_data.vertices.push_back(bp_data->vertices[(ivZ - 1) * 3 + 2]);

                    b_data.vertices.push_back(bp_data->vertices[(ivW - 1) * 3]);
                    b_data.vertices.push_back(bp_data->vertices[(ivW - 1) * 3 + 1]);
                    b_data.vertices.push_back(bp_data->vertices[(ivW - 1) * 3 + 2]);

                    b_data.textureCoordinates.push_back(bp_data->textureCoordinates[(itX - 1) * 2]);
                    b_data.textureCoordinates.push_back(bp_data->textureCoordinates[(itX - 1) * 2 + 1]);

                    b_data.textureCoordinates.push_back(bp_data->textureCoordinates[(itY - 1) * 2]);
                    b_data.textureCoordinates.push_back(bp_data->textureCoordinates[(itY - 1) * 2 + 1]);

                    b_data.textureCoordinates.push_back(bp_data->textureCoordinates[(itZ - 1) * 2]);
                    b_data.textureCoordinates.push_back(bp_data->textureCoordinates[(itZ - 1) * 2 + 1]);

                    b_data.textureCoordinates.push_back(bp_data->textureCoordinates[(itX - 1) * 2]);
                    b_data.textureCoordinates.push_back(bp_data->textureCoordinates[(itX - 1) * 2 + 1]);

                    b_data.textureCoordinates.push_back(bp_data->textureCoordinates[(itZ - 1) * 2]);
                    b_data.textureCoordinates.push_back(bp_data->textureCoordinates[(itZ - 1) * 2 + 1]);

                    b_data.textureCoordinates.push_back(bp_data->textureCoordinates[(itW - 1) * 2]);
                    b_data.textureCoordinates.push_back(bp_data->textureCoordinates[(itW - 1) * 2 + 1]);

                    b_data.normals.push_back(bp_data->normals[(inX - 1) * 3]);
                    b_data.normals.push_back(bp_data->normals[(inX - 1) * 3 + 1]);
                    b_data.normals.push_back(bp_data->normals[(inX - 1) * 3 + 2]);

                    b_data.normals.push_back(bp_data->normals[(inY - 1) * 3]);
                    b_data.normals.push_back(bp_data->normals[(inY - 1) * 3 + 1]);
                    b_data.normals.push_back(bp_data->normals[(inY - 1) * 3 + 2]);

                    b_data.normals.push_back(bp_data->normals[(inZ - 1) * 3]);
                    b_data.normals.push_back(bp_data->normals[(inZ - 1) * 3 + 1]);
                    b_data.normals.push_back(bp_data->normals[(inZ - 1) * 3 + 2]);

                    b_data.normals.push_back(bp_data->normals[(inX - 1) * 3]);
                    b_data.normals.push_back(bp_data->normals[(inX - 1) * 3 + 1]);
                    b_data.normals.push_back(bp_data->normals[(inX - 1) * 3 + 2]);

                    b_data.normals.push_back(bp_data->normals[(inZ - 1) * 3]);
                    b_data.normals.push_back(bp_data->normals[(inZ - 1) * 3 + 1]);
                    b_data.normals.push_back(bp_data->normals[(inZ - 1) * 3 + 2]);

                    b_data.normals.push_back(bp_data->normals[(inW - 1) * 3]);
                    b_data.normals.push_back(bp_data->normals[(inW - 1) * 3 + 1]);
                    b_data.normals.push_back(bp_data->normals[(inW - 1) * 3 + 2]);
                }
            }
        }
        
        delete bp_data;

        f.close();

        return b_data;
    }
}