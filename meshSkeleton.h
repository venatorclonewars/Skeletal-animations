#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <map>
#include "prerequisites.h"

using namespace std;

class MeshSkeleton
{
public:
	
	unsigned int getBoneID(const aiBone* pBone);
	void parseSingleBone(int meshIndex, const aiBone* pBone);
	void parseMeshBones(int meshIndex, const aiMesh* pMesh);
	void parseMeshes(const aiScene* pScene);
	void parseScene(const aiScene* pScene);
	void importMesh(const char* filename);
	vector<VertexBoneData> vertexToBones;
	vector<int> meshBaseVertex;
	map<string, unsigned int> boneNameToIndexMap;
};

