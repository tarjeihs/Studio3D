#pragma once
#include <cstddef>
#include <cstdint>

struct SUUID 
{
	SUUID();
	SUUID(uint64_t InUUID);
	SUUID(const SUUID&) = default;

	operator uint64_t() const { return UUID; }
private:
	uint64_t UUID;
};

namespace std
{
	template <typename T> struct hash;

	template<>
	struct hash<SUUID>
	{
		std::size_t operator()(const SUUID& uuid) const
		{
			return (uint64_t)uuid;
		}
	};
};