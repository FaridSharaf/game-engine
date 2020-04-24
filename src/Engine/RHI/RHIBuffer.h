
#ifndef ENGINE_RHI_RHIBUFFER_H
#define ENGINE_RHI_RHIBUFFER_H

#include "RHIResource.h"

class RHIHardwareBuffer;
class RHIVertexBuffer;
class RHIIndexBuffer;
class RHIUniformBuffer;
class RHIStructuredBuffer;
typedef std::shared_ptr<RHIHardwareBuffer> RHIHardwareBuffer_ptr;
typedef std::shared_ptr<RHIVertexBuffer> RHIVertexBuffer_ptr;
typedef std::shared_ptr<RHIIndexBuffer> RHIIndexBuffer_ptr;
typedef std::shared_ptr<RHIUniformBuffer> RHIUniformBuffer_ptr;
typedef std::shared_ptr<RHIStructuredBuffer> RHIStructuredBuffer_ptr;

enum RHIHardwareBufferUsage : uint8_t
{
	// we could specify general uses, such as STREAM_DRAW
	HWBU_STATIC = 1 << 0, // to be filled once
	HWBU_DYNAMIC = 1 << 2, // to be modified more often
	HWBU_DISCARD = 1 << 3, // to be streamed every frame

	// other uses with buffer data
	HWBU_WRITE_ONLY = 1 << 4, // contents are not read back
	HWBU_READ_ONLY = 1 << 5, // contents are to be read from the gpu, often RT usage

	HWBU_STATIC_WRITE_ONLY = HWBU_STATIC | HWBU_WRITE_ONLY, // optimal buffer usage
	HWBU_DYNAMIC_WRITE_ONLY = HWBU_DYNAMIC | HWBU_WRITE_ONLY, // write only dynamic

	HWBU_DYNAMIC_WRITE_ONLY_DISCARD = HWBU_DYNAMIC_WRITE_ONLY | HWBU_DISCARD, // dyanmic, write only discardable buffer for regular refilling
};

enum RHIIndexBufferType {
	IBT_16,
	IBT_32,
};

class RHIHardwareBuffer : public RHIResource
{
public:
	RHIHardwareBuffer(RHIHardwareBufferUsage usage)
		: m_usage(usage) {}

	RHIHardwareBuffer(RHIHardwareBuffer&) = delete; // delete copy constructor

	OBJECT_GETACCESSOR(RHIHardwareBufferUsage, RHIHardwareBufferUsage, usage);
	OBJECT_GETACCESSOR(size_t, size_t, size);

	virtual void ReadData(size_t size, size_t offset, void* dest) = 0;
	virtual void WriteData(void* src, size_t size, size_t offset, bool discard) = 0;

protected:
	RHIHardwareBufferUsage m_usage;
	size_t m_size;
};

class RHIVertexBuffer : public RHIHardwareBuffer
{
public:
	RHIVertexBuffer(size_t verticesCount, size_t vertexSize, RHIHardwareBufferUsage usage)
		: RHIHardwareBuffer(usage) {
		m_size = verticesCount * vertexSize;
	}

	OBJECT_GETACCESSOR(size_t, size_t, verticesCount);
	OBJECT_GETACCESSOR(size_t, size_t, vertexSize);

private:
	size_t m_verticesCount;
	size_t m_vertexSize;
};

class RHIIndexBuffer : public RHIHardwareBuffer
{
public:
	RHIIndexBuffer(size_t indicesCount, RHIHardwareBufferUsage usage, RHIIndexBufferType indexType = RHIIndexBufferType::IBT_32)
		: RHIHardwareBuffer(usage), m_indicesCount(indicesCount) {
		m_indexSize = indexType == RHIIndexBufferType::IBT_16
			? sizeof(uint16_t)
			: sizeof(uint32_t);
		m_size = indicesCount * m_indexSize;
	}

	size_t getIndexSize() const { return m_indexSize; }

private:
	size_t m_indicesCount;
	size_t m_indexSize;
};

class RHIUniformBuffer : public RHIHardwareBuffer
{

};

#endif // ENGINE_RHI_RHIBUFFER_H