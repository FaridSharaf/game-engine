
#ifndef ENGINE_FILESYSTEM_FILE_H
#define ENGINE_FILESYSTEM_FILE_H

struct PHYSFS_File;

class File;
typedef std::shared_ptr<File> File_ptr;

class File : public std::enable_shared_from_this<File>
{
public:
	explicit File(PHYSFS_File* handle);
	~File();

	bool close();
	bool flush();

	bool seek(uint64_t position);
	uint64_t tell();
	uint64_t length();
	uint64_t read(void* buf, uint32_t len, uint32_t count = 1);
	uint64_t write(const void* buf, uint32_t len, uint32_t count = 1);

private:
	PHYSFS_File* m_handle;
};

#endif // ENGINE_FILESYSTEM_FILE_H