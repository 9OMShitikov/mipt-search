#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>

namespace sql {

enum class AstType {
	name,
	string,
	number,
	list,
	// Your code goes here...
};

struct Ast {
	AstType type;

	Ast(AstType type);
	virtual ~Ast() = default;
};

struct String : public Ast
{
	std::string value;

	String(AstType type, std::string value);
};

struct Number : public Ast
{
	int value;

	Number(int value);
};

struct List : public Ast
{
	std::vector<std::shared_ptr<Ast>> list;

	List(std::shared_ptr<Ast> element);
	void append(std::shared_ptr<Ast> element);
};

// Your code goes here...

template <class AstClass>
inline std::shared_ptr<AstClass> As(std::shared_ptr<Ast> ast)
{
	return std::dynamic_pointer_cast<AstClass>(ast);
}

std::shared_ptr<Ast> new_name(std::string value);
std::shared_ptr<Ast> new_string(std::string value);
std::shared_ptr<Ast> new_number(int value);
std::shared_ptr<List> new_list(std::shared_ptr<Ast> element);
// Your code goes here...

}