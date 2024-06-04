#pragma once

#ifndef FORCEINLINE
	#define FORCEINLINE __forceinline
#include <atomic>
#include <thread>
#endif

#ifdef MOD_DEBUG
	#define ASSERT(Condition, Message) if (!(Condition)) { __debugbreak(); }
#endif

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

class CEvent;
/* Global pointers */
static class CEngine* GEngine = nullptr;
static class CWindow* GWindow = nullptr;

class CEngine
{
public:
	void Start();
	void ProcessInput();
	void Run();
	void Stop();
};
