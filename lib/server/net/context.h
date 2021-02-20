#include <Poco/JSON/Object.h>

#include "lib/server/sql/ast.h"
#include "lib/server/storage/schema.h"

class IRowWriter
{
public:
	virtual void Write(const Row & row) = 0;
};

class RowWriter : public IRowWriter
{
public:
	explicit RowWriter(std::shared_ptr<Poco::JSON::Array> buffer);
	void Write(const Row & row) override;
	void Flush();

protected:
	uint32_t m_iWrittenLines = 0;
	std::shared_ptr<Poco::JSON::Array> m_pRoot;
};

struct Context
{
	std::shared_ptr<Schema> pTableSchema;
	std::shared_ptr<IRowWriter> pRowWriter;
	// std::shared_ptr<db::Connection> pTableConnection;
};
