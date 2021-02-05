#include "ast.h"

namespace sql {

Ast::Ast(AstType type) : type(type)
{}

String::String(AstType type, std::string value) : Ast(type), value(value)
{}

Number::Number(int value) : Ast(AstType::number), value(value)
{}

List::List(std::shared_ptr<Ast> element) : Ast(AstType::list), list{element}
{}

void List::append(std::shared_ptr<Ast> element)
{
	list.push_back(element);
}

std::shared_ptr<Ast> new_name(std::string value)
{
	return std::make_shared<String>(AstType::name, std::move(value));
}

std::shared_ptr<Ast> new_string(std::string value)
{
	return std::make_shared<String>(AstType::string, std::move(value));
}

std::shared_ptr<Ast> new_number(int value)
{
	return std::make_shared<Number>(value);
}

std::shared_ptr<List> new_list(std::shared_ptr<Ast> operand)
{
	return std::make_shared<List>(operand);
}

// Your code goes here...

}