#pragma once

#include <chrono>
#include "Math/MathTypes.h"

#ifndef FORCEINLINE
	#define FORCEINLINE __forceinline
#endif

typedef std::size_t SizeType;

//#ifdef MOD_DEBUG
	//#define ASSERT(Condition, Message) if (!(Condition)) { __debugbreak(); }
	#define ASSERT(Condition, Message) { __debugbreak(); }
//#endif

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

static constexpr int32 G_VIEWPORT_WIDTH = 1920;
static constexpr int32 G_VIEWPORT_HEIGHT = 1080;

/* A duration of time in seconds. */
struct STimespan
{
	using SClock = std::chrono::high_resolution_clock;
	using STimePoint = std::chrono::time_point<SClock>;
	using SDuration = std::chrono::duration<float>;

	STimePoint Start;
	STimePoint Current;
	SDuration DeltaTime;

	STimespan()
	{
		Start = SClock::now();
		Current = Start;
		DeltaTime = SDuration(0);
	}

	void Update()
	{
		auto NewTime = SClock::now();
		DeltaTime = NewTime - Current;
		Current = NewTime;
	}

	FORCEINLINE float GetDeltaTime() const
	{
		return DeltaTime.count();
	}

	FORCEINLINE float GetCurrentTime() const
	{
		return std::chrono::duration<float>(Current - Start).count();
	}

	FORCEINLINE float GetStartTime() const
	{
		return std::chrono::duration<float>(Start.time_since_epoch()).count();
	}
};

class CScene;
class CRenderer;

/* Global pointers */
extern class CWindow* GWindow;
//extern class CEngine* GEngine;

class CEngine
{
public:
	void Start();
	void Run();
	void Stop();

	virtual void OnUpdate(float DeltaTime) = 0;
	
	STimespan Time;

	CScene* GetScene() const;
	CRenderer* GetRenderer() const;

	inline static CEngine* Get()
	{
		return GEngine; 
	}

private:
	CScene* Scene;
	CRenderer* Renderer;

	static CEngine* GEngine;
};

// Entrypoint as defined externally
CEngine* CreateEngine();