#pragma once

#include <chrono>

#ifndef FORCEINLINE
	#define FORCEINLINE __forceinline
#include <atomic>
#include <thread>
#endif

#ifdef MOD_DEBUG
	#define ASSERT(Condition, Message) if (!(Condition)) { __debugbreak(); }
#endif

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

struct STime
{
	using SClock = std::chrono::high_resolution_clock;
	using STimePoint = std::chrono::time_point<SClock>;
	using SDuration = std::chrono::duration<float>;

	STimePoint Start;
	STimePoint Current;
	SDuration DeltaTime;

	STime()
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
class CEvent;

/* Global pointers */
static class CEngine* GEngine = nullptr;
static class CWindow* GWindow = nullptr;

class CEngine
{
public:
	void Start();
	void Run();
	void Stop();

	STime Time;
private:
	CScene* Scene;
};
