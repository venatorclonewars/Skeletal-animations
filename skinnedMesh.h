#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <GL/glew.h>
#include <map>
#include "prerequisites.h"
#include "material.h"

using namespace std;

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices)
#define MAX_NUM_BONES_PER_VERTEX 4

#define COLOR_TEXTURE_UNIT_INDEX_0 0 
#define COLOR_TEXTURE_UNIT_0 GL_TEXTURE0 

#define SPECULAR_EXPONENT_UNIT_INDEX_0 6 
#define SPECULAR_EXPONENT_UNIT_0 GL_TEXTURE6

#define POSITION_LOCATION 0 
#define TEX_COORD_LOCATION 1 
#define NORMAL_LOCATION 2 
#define BONE_ID_LOCATION 3
#define BONE_WEIGHT_LOCATION 4

class SkinnedMesh
{
public:
	
	unsigned int getBoneID(const aiBone* pBone);
	void loadSingleBone(int meshIndex, const aiBone* pBone);
	void loadMeshBones(int meshIndex, const aiMesh* pMesh);
	void loadTextures(const string& dir, const aiMaterial* pMaterial, int index);
	void loadDiffuseTexture(const string& dir, const aiMaterial* pMaterial, int index);
	void loadSpecularTexture(const string& dir, const aiMaterial* pMaterial, int index);
	void loadColors(const string& dir, const aiMaterial* pMaterial, int index);
	bool initFromScene(const aiScene* pScene, const string& filename);
	void countVerticesAndIndices(const aiScene* pScene, unsigned int& numVertices, unsigned int& numIndices);
	void loadMesh(const char* filename);
	void initMaterials(const aiScene* pScene, const string& filename);
	void populateBuffers();
	void render();

private:

	void reserveSpace(unsigned int numVertices, unsigned int numIndices);
	void initSingleMesh(int meshIndex, const aiMesh* paiMesh);
	void initAllMeshes(const aiScene* pScene);

	enum BUFFER_TYPE
	{
		INDEX_BUFFER = 0,
		POS_VB = 1,
		TEXCOORD_VB = 2,
		NORMAL_VB = 3,
		BONE_VB = 4,
		WVP_MAT_VB = 5,
		WORLD_MAT_VB = 6,
		NUM_BUFFERS = 7
	};

#define INVALID_MATERIAL 0xFFFFFFFF

	struct BasicMeshEntry
	{
		BasicMeshEntry()
		{
			numIndices = 0;
			baseVertex = 0;
			baseIndex = 0;
			materialIndex = INVALID_MATERIAL;
		}

		unsigned int numIndices;
		unsigned int baseVertex;
		unsigned int baseIndex;
		unsigned int materialIndex;
	};

	GLuint m_VAO = -1;
	GLuint m_Buffers[NUM_BUFFERS] = { 0 };

	vector<BasicMeshEntry> m_meshes;
	vector<Material> m_materials;

	vector<Vector3f> m_positions;
	vector<Vector3f> m_normals;
	vector<Vector2f> m_texCoords;
	
	vector<VertexBoneData> m_bones;
	map<string, unsigned int> m_boneNameToIndexMap;

	vector<int> m_indices;

	Matrix4f m_worldTransform;
};

