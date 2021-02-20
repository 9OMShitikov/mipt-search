#include <catch.hpp>
#include <cstring>
#include <sstream>

#include "compression.h"

TEST_CASE("(Compression) LEB128")
{
	unsigned char buffer[1024];
	memset(buffer, 0, sizeof(buffer));

	unsigned char * head = buffer;
	LEB128::Encode(1u, head);
	head = buffer;
	REQUIRE(LEB128::Decode(head) == 1u);

	head = buffer;
	LEB128::Encode(138u, head);
	head = buffer;
	REQUIRE(LEB128::Decode(head) == 138u);

	head = buffer;
	LEB128::Encode(13842u, head);
	head = buffer;
	REQUIRE(LEB128::Decode(head) == 13842u);

	head = buffer;
	for (uint32_t i = 0; i < sizeof(buffer) / sizeof(uint32_t); ++i)
	{
		LEB128::Encode(i, head);
	}

	REQUIRE(head - buffer < 512);
}

TEST_CASE("(Compression) Delta-compression")
{
	unsigned char buffer[1024];
	auto numbers = { 2u, 11u, 49u, 168u, 1999u, 2000u, 2020u };

	DeltaEncoder<LEB128> encoder;
	auto * head = buffer;
	for (auto x : numbers)
	{
		encoder(x, head);
	}

	DeltaDecoder<LEB128> decoder;
	head = buffer;
	for (auto x : numbers)
	{
		REQUIRE(x == decoder(head));
	}

	REQUIRE(head - buffer == 8);
}
