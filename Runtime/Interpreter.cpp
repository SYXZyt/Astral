#include "Interpreter.h"

void Astral::Interpreter::ExecuteInstruction(Bytecode& instruction)
{
	OpType op = (OpType)instruction.op;
	switch (op)
	{
		case OpType::LIT_NUMBER:
		{
			float v = std::stof(instruction.lexeme.lexeme);
			Type::number_t* number = new Type::number_t(v);
			stack.push(number);
			break;
		}
		case OpType::LIT_STRING:
		{
			Type::string_t* string = new Type::string_t(instruction.lexeme.lexeme.c_str());
			stack.push(string);
			break;
		}
		case OpType::ADD:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			result_t res = Maths::Addition(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				stack.push(res.result);
			else
			{
				Error("Cannot add types", instruction.lexeme);
				failed = true;
			}

			break;
		}
		case OpType::SUB:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			result_t res = Maths::Subtraction(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				stack.push(res.result);
			else
			{
				Error("Cannot subtract types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::MUL:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			result_t res = Maths::Multiplication(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				stack.push(res.result);
			else
			{
				Error("Cannot multiply types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::DIV:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			result_t res = Maths::Divide(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				stack.push(res.result);
			else if (res.type == result_t::ResultType::R_DIV_BY_ZERO)
			{
				Error("Division by zero", instruction.lexeme);
				failed = true;
			}
			else
			{
				Error("Cannot divide types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::POW:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			result_t res = Maths::Power(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				stack.push(res.result);
			else
			{
				Error("Cannot calculate power with types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::MOD:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			result_t res = Maths::Modulo(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				stack.push(res.result);
			else if (res.type == result_t::ResultType::R_DIV_BY_ZERO)
			{
				Error("Division by zero", instruction.lexeme);
				failed = true;
			}
			else
			{
				Error("Cannot calculate modulo with types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::UNARY_MINUS:
		{
			Type::atype_t* val = Pop();
			result_t res = Maths::Minus(val);

			if (res.type == result_t::ResultType::R_OK)
				stack.push(res.result);
			else
			{
				Error("Type does not support minus operator", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::EQUALITY:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			result_t res = Boolean::Equality(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				stack.push(res.result);
			else
			{
				Error("Invalid boolean operator types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::NEQUALITY:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			result_t res = Boolean::Nequality(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				stack.push(res.result);
			else
			{
				Error("Invalid boolean operator types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::GREATER:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			result_t res = Boolean::Greater(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				stack.push(res.result);
			else
			{
				Error("Invalid boolean operator types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::GREATER_EQUALS:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			result_t res = Boolean::GreaterEquals(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				stack.push(res.result);
			else
			{
				Error("Invalid boolean operator types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::LESS:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			result_t res = Boolean::Less(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				stack.push(res.result);
			else
			{
				Error("Invalid boolean operator types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::LESS_EQUALS:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			result_t res = Boolean::LessEquals(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				stack.push(res.result);
			else
			{
				Error("Invalid boolean operator types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::NOT:
		{
			Type::atype_t* val = Pop();
			result_t res = Boolean::Not(val);

			if (res.type == result_t::ResultType::R_OK)
				stack.push(res.result);
			else
			{
				Error("Invalid boolean operator type", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::PRINT:
		{
			Type::atype_t* val = Pop();

			//If we do not know the type we are printing, just print the address
			if (Type::number_t* number_t = dynamic_cast<Type::number_t*>(val))
				std::cout << number_t->Value() << '\n';
			else if (Type::string_t* string_t = dynamic_cast<Type::string_t*>(val))
				std::cout << string_t->Value() << '\n';
			else
				std::cout << '$' << val << '\n';

			delete val;

			break;
		}
		case OpType::VARIABLE:
		{
			std::string name = instruction.lexeme.lexeme;
			if (!variables.DoesVariableExist(name.c_str()))
			{
				Error("Variables does not exist", instruction.lexeme);
				failed = true;
				break;
			}

			stack.push(variables.GetValue(name.c_str()));

			break;
		}
		default:
			throw "oop";
	}
}

void Astral::Interpreter::Execute()
{
	while (pc < rom.size())
	{
		ExecuteInstruction(rom[pc++]);

		if (failed)
			break;
	}
}

Astral::Interpreter::~Interpreter()
{
	while (!stack.empty())
	{
		Type::atype_t* value = Pop();

		delete value;
	}
}