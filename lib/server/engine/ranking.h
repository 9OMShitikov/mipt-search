#pragma once

#include <memory>
#include <unordered_map>

#include "lib/common/types.h"
#include "lib/std/logger.h"

// Common interface for ranker
// Init - make some initialization before proceeding query
// ProceedHit - proceed hit in one document
// Complete - marks that document hits completed and returns weight
class IRanker {
   public:
	virtual void Init(IndexStats stat) = 0;
	virtual void ProceedHit(Hit hit) = 0;
	virtual double Complete() = 0;
};

// Ranking by count of hits
class DummyRanker : public IRanker {
   public:
	DummyRanker() = default;

	virtual void Init(IndexStats stat);
	virtual void ProceedHit(Hit hit);
	virtual double Complete();

   private:
	int hit_count_;
};

class BM25Ranker : public IRanker {
   public:
	BM25Ranker() = default;

	virtual void Init(IndexStats stat);
	virtual void ProceedHit(Hit hit);
	virtual double Complete();

   private:
	// default params for BM25
	constexpr static double m_dB = 0.75;
	constexpr static double m_dK = 2.0;

	IndexStats m_sStats;
	std::unordered_map<std::string, uint32_t> m_hWordCount;
};

std::shared_ptr<IRanker> CreateRanker(RankerType rankerType);
