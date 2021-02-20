#pragma once

#include <array>

// Varint decoders; read more about this
struct LEB128
{
	static inline void Encode(uint32_t uValue, unsigned char *& pBuf)
	{
		// Your code goes here...
	}

	static inline uint32_t Decode(unsigned char *& pBuf)
	{
		// Your code goes here...
		return 0;
	}
};

// Question: why we use templates instead of virtual in decoders?
template <class Compressor>
struct DeltaEncoder
{
	inline void operator()(uint32_t uValue, unsigned char *& pBuf)
	{
		// Your code goes here...
	}

	// Your code goes here...
};

template <class Compressor>
struct DeltaDecoder
{
	inline uint32_t operator()(unsigned char *& pBuf)
	{
		// Your code goes here...
		return 0;
	}

	// Your code goes here...
};
