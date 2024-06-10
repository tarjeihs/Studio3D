#pragma once

#include <chrono>
#include "Math/MathTypes.h"

#ifndef FORCEINLINE
	#define FORCEINLINE __forceinline
#endif

class CImGui;
typedef std::size_t SizeType;

//#ifdef MOD_DEBUG
	//#define ASSERT(Condition, Message) if (!(Condition)) { __debugbreak(); }
	#define ASSERT(Condition, Message) { __debugbreak(); }
//#endif

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

static constexpr int32 PARAMETER_VIEWPORT_WIDTH = 1600;
static constexpr int32 PARAMETER_VIEWPORT_HEIGHT = 1000;

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

	void Validate()
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

class CWindow;
class CRenderer;
class CScene;

class CApplication
{
public:
	CApplication(const std::string& InName, uint32 InWidth, uint32 InHeight)
		: Name(InName), Width(InWidth), Height(InHeight)
	{
	}
	
	virtual ~CApplication() = default;
	
	virtual void OnStart() = 0;
	virtual void OnUpdate(float DeltaTime) = 0;
	virtual void OnStop() = 0;

protected:
	std::string Name;
	uint32 Width, Height;
};

struct SMetrics
{
	uint32 DrawCallCounter;
	
	uint32 CurrentObjectAllocated;
	uint32 TotalObjectAllocated;

	size_t CurrentSizeAllocated;
	size_t TotalSizeAllocated;

	void Reset()
	{
		DrawCallCounter = 0;
	}
};

class CEngine
{
public:
	static inline CEngine* Get()
	{
		return GEngine; 
	}

	void Start();
	void Run();
	void Stop();

	CApplication* GetApplication() const;
	CWindow* GetWindow() const;
	CScene* GetScene() const;
	CRenderer* GetRenderer() const;
	CImGui* GetImGui() const;
	
	STimespan Time;
	SMetrics Metrics;
	
protected:
	CApplication* Application;
	CWindow* Window;
	CRenderer* Renderer;
	CScene* Scene;
	CImGui* ImGui;

	static CEngine* GEngine;

private:
	friend class CApplication;
};

// Entrypoint as defined externally
CApplication* CreateApplication();

static inline CEngine* GetEngine()
{
	return CEngine::Get();
}