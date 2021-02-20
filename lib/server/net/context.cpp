#include "context.h"

#include <exception>
#include <iostream>
#include <utility>

RowWriter::RowWriter(std::shared_ptr<Poco::JSON::Array> buffer)
	: m_pRoot(std::move(buffer)) {}

void RowWriter::Write(const Row &row) {
	auto json_row = std::make_shared<Poco::JSON::Array>(true);
	for (size_t i = 0; i < row.size(); ++i) {
		switch (row[i].index()) {
			case 0: json_row->set(i, std::get<int>(row[i])); break;
			case 1: json_row->set(i, std::get<double>(row[i])); break;
			case 2: json_row->set(i, std::get<uint32_t>(row[i])); break;
			case 3: json_row->set(i, std::get<std::wstring>(row[i])); break;
		}
	}
	m_pRoot->add(*json_row);
}
