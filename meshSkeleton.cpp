#include "meshSkeleton.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices)


unsigned int MeshSkeleton::getBoneID(const aiBone* pBone)
{

	int boneID = 0;
	string boneName(pBone->mName.C_Str());

	// If not found we create one, else return found one
	if (boneNameToIndexMap.find(boneName) == boneNameToIndexMap.end())
	{
		boneID = boneNameToIndexMap.size();
		boneNameToIndexMap[boneName] = boneID;
	}
	else
		boneID = boneNameToIndexMap[boneName];

	return boneID;
}

void MeshSkeleton::parseSingleBone(int meshIndex, const aiBone* pBone)
{

	int boneID = getBoneID(pBone);

	for (int i = 0; i < pBone->mNumWeights; i++)
	{
		const aiVertexWeight& vw = pBone->mWeights[i];
		
		unsigned int globalVertexID = meshBaseVertex[meshIndex] + vw.mVertexId;
		printf("Vertex id %d ", globalVertexID);
		assert(globalVertexID < vertexToBones.size());
		vertexToBones[globalVertexID].addBoneData(boneID, vw.mWeight);
	}
}


void MeshSkeleton::parseMeshBones(int meshIndex,const aiMesh* pMesh)
{
	for (int i = 0; i < pMesh->mNumBones; i++)
	{
		parseSingleBone(meshIndex, pMesh->mBones[i]);
	}
}

void MeshSkeleton::parseMeshes(const aiScene* pScene)
{
	printf("*******************************************************\n");
	printf("Parsing %d meshes\n\n", pScene->mNumMeshes);

	meshBaseVertex.resize(pScene->mNumMeshes);

	int totalVertices = 0;
	int totalIndices = 0;
	int totalBones = 0;

	for (int i = 0; i < pScene->mNumMeshes; i++)
	{
		const aiMesh* pMesh = pScene->mMeshes[i];

		int numVertices = pMesh->mNumVertices;
		int numIndices = pMesh->mNumFaces * 3;
		int numBones = pMesh->mNumBones;
		meshBaseVertex[i] = totalVertices;
		printf("  Mesh %d '%s': vertices %d indices %d bones %d\n\n", i, pMesh->mName.C_Str(), numVertices, numIndices, numBones);
		totalVertices += numVertices;
		totalIndices += numIndices;
		totalBones += numBones;

		vertexToBones.resize(totalVertices);

		if (pMesh->HasBones())
		{
			parseMeshBones(i, pMesh);
		}
	}
}


void MeshSkeleton::parseScene(const aiScene* pScene)
{
	parseMeshes(pScene);
}

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
