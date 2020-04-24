
#include "pch.h"

#include "ResourceManager.h"

#include <physfs.h>

bool ResourceManager::Init()
{
	if (m_initialized)
		return true;

	m_initialized = PHYSFS_init(nullptr) != 0;
	return m_initialized;
}

void ResourceManager::Terminate()
{
	PHYSFS_deinit();
}

bool ResourceManager::mount(std::string directory)
{
	return PHYSFS_mount(directory.c_str(), nullptr, 0) != 0;
}

bool ResourceManager::exists(std::string directory) {
	return PHYSFS_exists(directory.c_str());
}

File_ptr ResourceManager::openRead(std::string filename)
{
	PHYSFS_File* file = PHYSFS_openRead(filename.c_str());
	if (!file)
		return nullptr;

	return std::move(std::make_shared<File>(file));
}

File_ptr ResourceManager::openWrite(std::string filename)
{
	PHYSFS_File* file = PHYSFS_openWrite(filename.c_str());
	if (!file)
		return nullptr;

	return std::move(std::make_shared<File>(file));
}

Model_ptr ResourceManager::loadModel(std::string filename)
{
	// todo; store the importer instead of creating a new one for every model
	Assimp::Importer importer;
	importer.SetIOHandler(new AssimpIOSystem);

	uint32_t flags = aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType;
	const aiScene* scene = importer.ReadFile(filename, flags); // TODO: give the user the choice of flags?
	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		return nullptr;
	}

	auto model = std::make_shared<Model>(filename, scene);
	return model;
}