#include <catch.hpp>
#include <sstream>

#include "stemming.h"

TEST_CASE("(Stemming) Basic") {
	auto stemmer = Stemmer("../bin/mystem");

	REQUIRE(stemmer.Process("красивее") == "красивый");
	REQUIRE(stemmer.Process("красивой") == "красивый");

	REQUIRE(stemmer.Process("новая") == "новый");

	REQUIRE(stemmer.Process("потрясающая  \n") == "потрясать");
	REQUIRE(stemmer.Process("ранняя закат") == "ранний");
}

TEST_CASE("(Stemming) Incorrect") {
	auto stemmer = Stemmer("../bin/mystem");

	REQUIRE(stemmer.Process("˙∆∆∆åß") == "˙∆∆∆åß");
}