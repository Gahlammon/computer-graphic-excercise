/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#include "model.h"

namespace Models {
	void Model::drawWire(bool smooth)
    {
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		drawSolid(smooth);

		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}

    void Model::drawSolid(bool smooth)
    {

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, verticesCompiled);
        glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, normalsCompiled);
        glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, texCoordsCompiled);

        glDrawArrays(GL_TRIANGLES, 0, faceCount);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
    }

    void Model::meshImport(std::string path)
    {
        std::vector<glm::vec3> vertices = std::vector<glm::vec3>();
        std::vector<glm::vec3> normals = std::vector<glm::vec3>();
        std::vector<glm::vec2> uv = std::vector<glm::vec2>();

        std::string reader;
        std::ifstream file(path);
        glm::vec3 vector;
        std::vector<std::string> faces;
        int cut1, cut2;

        vertices.clear();
        normals.clear();
        uv.clear();
        faces.clear();

        if (!file) return;

        while (file >> reader)
        {
            if (reader == "v")
            {
                file >> vector.x >> vector.y >> vector.z;
                //printf("v: %f %f %f\n", vector.x, vector.y, vector.z);
                vertices.push_back(vector);
            }
            if (reader == "vn")
            {
                file >> vector.x >> vector.y >> vector.z;
                //printf("n: %f %f %f\n", vector.x, vector.y, vector.z);
                normals.push_back(vector);
            }
            if (reader == "vt")
            {
                file >> vector.x >> vector.y;
                //printf("t: %f %f %f\n", vector.x, vector.y, vector.z);
                uv.push_back(vector);
            }
            if (reader == "f")
            {
                //printf("f\n");
                for (int i = 0; i < 3; i++)
                {
                    file >> reader;
                    faces.push_back(reader);
                }
            }
        }

        faceCount = faces.size();
        verticesCompiled = new float[4 * faces.size()];
        normalsCompiled = new float[4 * faces.size()];
        texCoordsCompiled = new float[2 * faces.size()];

        for (int i = 0; i < faces.size(); i++)
        {
            //printf("%d\n", i);

            cut1 = faces[i].find('/');
            cut2 = faces[i].substr(cut1 + 1, faces[i].length() - cut1 - 1).find('/') + cut1 + 1;

            //printf("v: %d/%d, %d/%d\n", i * 4 + 0, 4 * faces.size(), atoi(faces[i].substr(0, cut1).c_str()) - 1, vertices.size());

            verticesCompiled[i * 4 + 0] = vertices[atoi(faces[i].substr(0, cut1).c_str()) - 1].x;
            verticesCompiled[i * 4 + 1] = vertices[atoi(faces[i].substr(0, cut1).c_str()) - 1].y;
            verticesCompiled[i * 4 + 2] = vertices[atoi(faces[i].substr(0, cut1).c_str()) - 1].z;
            verticesCompiled[i * 4 + 3] = 1.0f;

            //printf("n: %d/%d, %d/%d\n", i * 2 + 0, 2 * faces.size(), atoi(faces[i].substr(cut1 + 1, cut2 - cut1 - 1).c_str()) - 1, uv.size());

            texCoordsCompiled[i * 2 + 0] = uv[atoi(faces[i].substr(cut1 + 1, cut2 - cut1 - 1).c_str()) - 1].x;
            texCoordsCompiled[i * 2 + 1] = uv[atoi(faces[i].substr(cut1 + 1, cut2 - cut1 - 1).c_str()) - 1].y;

            //printf("n: %d/%d, %d/%d\n", i * 4 + 0, 4 * faces.size(), atoi(faces[i].substr(cut2 + 1, faces[i].length() - cut2 - 1).c_str()) - 1, normals.size());

            normalsCompiled[i * 4 + 0] = normals[atoi(faces[i].substr(cut2 + 1, faces[i].length() - cut2 - 1).c_str()) - 1].x;
            normalsCompiled[i * 4 + 1] = normals[atoi(faces[i].substr(cut2 + 1, faces[i].length() - cut2 - 1).c_str()) - 1].y;
            normalsCompiled[i * 4 + 2] = normals[atoi(faces[i].substr(cut2 + 1, faces[i].length() - cut2 - 1).c_str()) - 1].z;
            normalsCompiled[i * 4 + 3] = 0.0f;

            //printf("\n");
        }
        //printf("VERTICES:\n");
        //for (int i = 0; i < faces.size(); i++)
        //{
        //    printf("%f %f %f\n", verticesCompiled[i * 4 + 0], verticesCompiled[i * 4 + 1], verticesCompiled[i * 4 + 2]);
        //}
        //printf("NORMALS:\n");
        //for (int i = 0; i < faces.size(); i++)
        //{
        //    printf("%f %f %f\n", normalsCompiled[i * 4 + 0], normalsCompiled[i * 4 + 1], normalsCompiled[i * 4 + 2]);
        //}
        //printf("UVs:\n");
        //for (int i = 0; i < faces.size(); i++)
        //{
        //    printf("%f %f\n", texCoordsCompiled[i * 2 + 0], texCoordsCompiled[i * 2 + 1]);
        //}
    }

    Model::Model(std::string path)
    {
        if (path != "")
        {
            meshImport(path);
        }
    }
}
