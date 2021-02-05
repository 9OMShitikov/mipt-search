#include <catch.hpp>

#include "lib/server/net/context.h"
#include "ram.h"
#include "disk.h"

#include <algorithm>
#include <memory>
#include <sstream>

using TResult = std::vector<std::pair<uint32_t, double>>;

bool ResultEqual(TResult &&first,
                 TResult &&second) {
    if (first.size() != second.size()) {
        return false;
    }
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());
    for (size_t i = 0; i < first.size(); ++i) {
        if (first[i] != second[i]) {
            return false;
        }
    }
    return true;
}

class TestRowWriter : public IRowWriter {
public:
    explicit TestRowWriter(std::wostream &out) : m_oOut(out) {
    }

    void Write(const Row &row) override {
        for (size_t i = 0; i < row.size() - 1; ++i) {
            PrintColumnValue(row[i]);
            m_oOut << " ";
        }
        PrintColumnValue(row.back());
        m_oOut << std::endl;
        m_oOut.flush();
    }

private:
    void PrintColumnValue(const Column &column) {
        switch (column.index()) {
            case 0:
                m_oOut << std::get<int>(column);
                break;
            case 1:
                m_oOut << std::get<double>(column);
                break;
            case 2:
                m_oOut << std::get<uint32_t>(column);
                break;
            case 3:
                m_oOut << std::get<std::wstring>(column);
                break;
        }
    }

    std::wostream &m_oOut;
};

TResult GetQueryResult(std::vector<std::pair<std::wstring, uint32_t>> &&dFieldMask,
                       Index &tIndex) {
    auto context = std::make_shared<Context>();
    std::wstring sBuffer;
    std::wstringstream sStream(sBuffer);

    context->pRowWriter = std::make_shared<TestRowWriter>(sStream);
    context->pTableSchema = nullptr;
    context->pTableConnection = nullptr;

    Query tQuery{"Dummy", -1, dFieldMask, RankerType::DummyRanker, context};
    tIndex.ExecuteSelect(tQuery);

    TResult tResult;
    uint32_t iDocumentId;
    double lfWeight;

    while (sStream >> iDocumentId) {
        sStream >> lfWeight;
        tResult.emplace_back(iDocumentId, lfWeight);
    }
    return tResult;
}

TEST_CASE("(DummyIndex) One word") {
    search::RamSegment::IndexData tData;
    tData[L"a"] = {{0, 0, 0},
                   {1, 0, 0},
                   {2, 0, 0}};
	search::RamSegment tIndex(tData);
    REQUIRE(ResultEqual(GetQueryResult({{L"a", 3}}, tIndex),
                        {{0, 1},
                         {1, 1},
                         {2, 1}}));

}

TEST_CASE("(DummyIndexer) Category indexing") {
	search::RamSegment indexer("../bin/mystem");
    indexer.IndexFiles({"../data/category_0.csv"},
                       "../category_0.txt");
    auto pIndexConfig = IndexConfig::DummyIndexConfig(
            "../data/category_0.csv",
            "../index_data/category_0.txt");
	search::RamSegment tIndex(pIndexConfig);
}