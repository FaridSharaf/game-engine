//
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

#ifndef ENGINE_PHYSICS_SCENE_QUERY_H
#define ENGINE_PHYSICS_SCENE_QUERY_H

#include "physx/PxPhysicsAPI.h"
#include "PActor.h"

class PRaycastHit;
class PSweepHit;
class POverlapHit;

typedef std::shared_ptr<PRaycastHit> PRaycastHit_ptr;
typedef std::shared_ptr<PSweepHit> PSweepHit_ptr;
typedef std::shared_ptr<POverlapHit> POverlapHit_ptr;

class PQueryHit 
{
public:
	~PQueryHit();

	PActor_ptr GetActor() const;
	PCollider_ptr GetCollider() const;

protected:
	physx::PxQueryHit* mQueryHit = nullptr;
};

class PPointHit
{
public:
	~PPointHit();

	PActor_ptr GetActor() const;
	PCollider_ptr GetCollider() const;

	float GetDistance() const;
	glm::vec3 GetNormal() const;
	glm::vec3 GetPosition() const;

protected:
	physx::PxLocationHit* mPointHit = nullptr;
};

class PRaycastHit : public PPointHit 
{
public:
	void CreateHit(physx::PxRaycastHit* pRaycastHit);

private:
	physx::PxRaycastHit* mRaycastHit = nullptr;
};

class PSweepHit : public PPointHit 
{
public:
	void CreateHit(physx::PxSweepHit* pSweepHit);

private:
	physx::PxSweepHit* mSweepHit = nullptr;
};

class POverlapHit : public PQueryHit 
{
public:
	void CreateHit(physx::PxOverlapHit* pOverlapHit);

private:
	physx::PxOverlapHit* mOverlapHit = nullptr;
};

#endif