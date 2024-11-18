#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
using namespace std;

class MeshSkeleton
{
public:
	void importMesh(const char* filename);
	void parseSingleBone(int boneIdx, const aiBone* pBone);
	void parseScene(const aiScene* pScene);
	void parseMeshes(const aiScene* pScene);
	void parseMeshBones(const aiMesh* pMesh);
};

