
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#ifndef ENGINE_CORE_IMAGE_H
#define ENGINE_CORE_IMAGE_H

class Texture;
typedef std::shared_ptr<Texture> Texture_ptr;

enum textureType_t
{
	TEXTURE_TYPE_2D,
	TEXTURE_TYPE_3D,
	TEXTURE_TYPE_CUBE
};

enum textureWrapMode_t
{
	TEXTURE_WRAPMODE_CLAMP,
	TEXTURE_WRAPMODE_REPEAT,
	TEXTURE_WRAPMODE_MIRROR,
};

enum textureFilterMode_t
{
	TEXTURE_FILTERMODE_POINT,	
	TEXTURE_FILTERMODE_BILINEAR,
	TEXTURE_FILTERMODE_TRILINEAR,
};

struct TextureSettings
{
	textureType_t type;
	textureWrapMode_t wrapMode;
	textureFilterMode_t filterMode;
};

class Texture
{
public:
	Texture();
protected:
	bool Load(const std::string& fileName);
	void Unload();

	void Bind();
	int GetWidth() const{ return mWidth; }
	int GetHeight() const { return mHeight; }
private:
	unsigned int mTextureID;
	int mWidth;
	int mHeight;

	TextureSettings mTextureSettings;
};

#endif // ENGINE_CORE_IMAGE_H