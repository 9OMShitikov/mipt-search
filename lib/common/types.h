#pragma once

#include <cinttypes>
#include <vector>
#include <string>
#include <unordered_map>
#include <cassert>
#include <memory>

#define c_size(container) static_cast<int>((container).size())

struct IndexStats {
    uint32_t m_uDocumentCount = 0;
    uint32_t m_uDocumentTotalLen = 0;
};

struct WordMetadata {
    uint32_t m_iDocumentCount = 0;
};

using IndexMetadata = std::unordered_map<std::wstring, WordMetadata>;

struct Match {
    uint32_t m_iDocumentId;
};

struct Hit {
    uint32_t m_iDocumentId;
    uint8_t m_bFieldId;
    uint8_t m_bHitPos;
};

enum class RankerType {
    DummyRanker,
    BM25
};

enum class IndexType {
    Template,
    Dummy,
    Plain,
    RT
};

inline IndexType GetIndexTypeFromName(const std::string &name) {
    if (name == "template") {
        return IndexType::Template;
    } else if (name == "dummy") {
        return IndexType::Dummy;
    } else if (name == "plain") {
        return IndexType::Plain;
    } else if (name == "rt") {
        return IndexType::RT;
    }

    throw std::runtime_error("Unknown index name");
}

inline std::string GetIndexNameFromType(IndexType type) {
    switch (type) {
        case IndexType::Template:
            return "template";
        case IndexType::Dummy:
            return "dummy";
        case IndexType::Plain:
            return "plain";
        case IndexType::RT:
            return "rt";
    }

    assert(0);
}

struct Context;

struct Query {
    std::string m_sIndexName;
	int m_iLimit = -1;

    std::vector<std::pair<std::wstring, uint32_t>> m_dMatchFieldMask;

    RankerType m_iRankerType;

    std::shared_ptr<Context> m_pContext;
};

inline bool QueryHasMatch(const Query &query) {
    return !query.m_dMatchFieldMask.empty();
}
