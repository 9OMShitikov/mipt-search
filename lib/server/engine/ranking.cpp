#include "ranking.h"

#include <stdexcept>

void DummyRanker::Init(IndexStats) {
	// Your code goes here
};

void DummyRanker::ProceedHit(Hit hit) {
	// Your code goes here
};

double DummyRanker::Complete() {
	// Your code goes here
	return 0;
}

void BM25Ranker::Init(IndexStats stats) {
	// Your code goes here
}

void BM25Ranker::ProceedHit(Hit hit) {
	// Your code goes here
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
		default:
			throw std::runtime_error("Unimplemented ranker");
	}
}