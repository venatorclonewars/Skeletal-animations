#include "meshSkeleton.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices)


void MeshSkeleton::importMesh(const char* filename)
{
	
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(filename, ASSIMP_LOAD_FLAGS);
	
	if (!pScene)
	{
		printf("Error parsing '%s' : '%s'\n", filename, importer.GetErrorString());
	}

	parseScene(pScene);
}

void MeshSkeleton::parseSingleBone(int boneIdx, const aiBone* pBone)
{

	for (int i = 0; i < pBone->mNumWeights; i++)
	{
		const aiVertexWeight& vw = pBone->mWeights[i];
	}
}



void MeshSkeleton::parseScene(const aiScene* pScene)
{
	parseMeshes(pScene);
}

void MeshSkeleton::parseMeshes(const aiScene* pScene)
{
	printf("*******************************************************\n");
	printf("Parsing %d meshes\n\n", pScene->mNumMeshes);


	int totalVertices = 0;
	int totalIndices = 0;
	int totalBones = 0;

	for (int i = 0; i < pScene->mNumMeshes; i++)
	{
		const aiMesh* pMesh = pScene->mMeshes[i];

		int numVertices = pMesh->mNumVertices;
		int numIndices = pMesh->mNumFaces * 3;
		int numBones = pMesh->mNumBones;
		printf("  Mesh %d '%s': vertices %d indices %d bones %d\n\n", i, pMesh->mName.C_Str(), numVertices, numIndices, numBones);
		totalVertices += numVertices;
		totalIndices += numIndices;
		totalBones += numBones;

		if (pMesh->HasBones())
		{
			parseMeshBones(pMesh);
		}
	}
}

void MeshSkeleton::parseMeshBones(const aiMesh* pMesh)
{
	for (int i = 0; i < pMesh->mNumBones; i++)
	{
		parseSingleBone(i, pMesh->mBones[i]);
	}
}

//int main(int argc, char* argv[])
//{
//	if (argc != 2)
//		return 1;
//
//	char* filename = argv[1];
//
//	Assimp::Importer importer;
//	const aiScene* pScene = importer.ReadFile(filename, ASSIMP_LOAD_FLAGS);
//
//	if (!pScene)
//	{
//		printf("Error parsing '%s' : '%s'\n", filename, importer.GetErrorString());
//	}
//
//
//}