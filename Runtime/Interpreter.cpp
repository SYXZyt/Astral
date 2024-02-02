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

	if (!stack.empty())
		std::cout << dynamic_cast<Type::number_t*>(Pop())->Value() << '\n';
}

Astral::Interpreter::~Interpreter()
{
	while (!stack.empty())
	{
		Type::atype_t* value = Pop();

		delete value;
	}
}