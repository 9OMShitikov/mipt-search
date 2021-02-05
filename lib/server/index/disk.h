#include "index.h"

#include <unordered_map>
#include <vector>
#include <string>

namespace search {

class DiskSegment : public Index {
public:
	void ExecuteSelect(const Query& tQuery) override;
private:
	// Your code goes here
	// Recommendation: write PlainPostingView

private:
	std::unordered_map<std::string, std::vector<Hit>> m_dDataIndex;
};

}