#include "ranking.h"

#include <stdexcept>

void DummyRanker::Init(IndexStats stats) {
	// Your code goes here
	UNUSED(stats);
};

void DummyRanker::ProceedHit(Hit hit) {
	// Your code goes here
	UNUSED(hit);
};

double DummyRanker::Complete() {
	// Your code goes here
	return 0;
}

void BM25Ranker::Init(IndexStats stats) {
	// Your code goes here
	UNUSED(stats);
}

void BM25Ranker::ProceedHit(Hit hit) {
	// Your code goes here
	UNUSED(hit);
}

double BM25Ranker::Complete() {
	// Your code goes here
	return 0;
}

std::shared_ptr<IRanker> CreateRanker(RankerType rankerType) {
	switch (rankerType) {
		case RankerType::DummyRanker: {
			return std::make_shared<DummyRanker>();
		}
		case RankerType::BM25: {
			return std::make_shared<BM25Ranker>();
		}
		default: throw std::runtime_error("Unimplemented ranker");
	}
}