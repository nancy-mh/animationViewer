#include "objimageloader.h"

objImageLoader::objImageLoader()
{

}

objImageLoader::~ objImageLoader()
{

}


void objImageLoader::loadMesh(std::vector<std::string> objFileVec, bool stopOBJLoading, int meshNum)
{

    // hold name of obj file
    std::string filePath;
    // Initialize Loader
    objl::Loader Loader;



    // struct of obj image
    imageElements image;

    if (meshNum > objFileVec.size())
    {
        std:: cout << "global counter exceeds the number of obj files" << std::endl;
    }


        for (meshNum; meshNum < objFileVec.size(); meshNum++)
        {

            if (stopOBJLoading == true)
                break;

            // choose first file
            filePath = objFileVec[meshNum];

            // Load .obj File
            bool loadout = Loader.LoadFile(filePath);

            // Check to see if it loaded

            // If so continue and display


            if (loadout)
            {

                // Go through each loaded mesh and out its contents
                for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
                {

                    // Copy one of the loaded meshes to be our current mesh
                    objl::Mesh curMesh = Loader.LoadedMeshes[0];


                    // Go through each vertex and print its number,
                    //  position, normal, and texture coordinate
                    for (int j = 0; j < curMesh.Vertices.size(); j++)
                    {
                        // object holds x,y,z position of each face
                        image.X = curMesh.Vertices[j].Position.X;
                        image.Y = curMesh.Vertices[j].Position.Y;
                        image.Z = curMesh.Vertices[j].Position.Z;
                        // object holds normals
                        image.normalX = curMesh.Vertices[j].Normal.X;
                        image.normalY = curMesh.Vertices[j].Normal.Y;
                        image.normalZ = curMesh.Vertices[j].Normal.Z;
                        // object holds texture coordinates
                        image.textCoorX = curMesh.Vertices[j].TextureCoordinate.X;
                        image.textCoorY = curMesh.Vertices[j].TextureCoordinate.Y;

                        image.facePosition = curMesh.Vertices[j].Face.X;
                        image.faceNormal = curMesh.Vertices[j].Face.Y;
                        image.faceTexture = curMesh.Vertices[j].Face.Z;
                        OBJContainer.push_back(image);

                    }


                }

            }
            // If not output an error
            else
            {

                // Output Error
                std::cout << "Failed to Load File. May have failed to find it or it was not an .obj file." << std::endl;


            }

        }


}
