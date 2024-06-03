#pragma once

#ifndef FORCEINLINE
	#define FORCEINLINE __forceinline
#include <atomic>
#include <thread>
#endif

#ifdef MOD_DEBUG
	#define ASSERT(Condition, Message) if (!(Condition)) { __debugbreak(); }
#endif

/* Global pointers */
static class CEngine* GEngine = nullptr;
static class CWindow* GWindow = nullptr;

class CEngine
{
public:
	void Start();
	void Run();
	void Stop();
};
