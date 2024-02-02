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
			stack.push(Maths::Addition(lhs, rhs));
			break;
		}
		case OpType::SUB:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			stack.push(Maths::Subtraction(lhs, rhs));
			break;
		}
		case OpType::MUL:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			stack.push(Maths::Multiplication(lhs, rhs));
			break;
		}
		case OpType::DIV:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			stack.push(Maths::Divide(lhs, rhs));
			break;
		}
		case OpType::POW:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			stack.push(Maths::Power(lhs, rhs));
			break;
		}
		case OpType::MOD:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			stack.push(Maths::Modulo(lhs, rhs));
			break;
		}
		case OpType::UNARY_MINUS:
		{
			Type::atype_t* val = Pop();
			stack.push(Maths::Minus(val));

			break;
		}
		case OpType::EQUALITY:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			stack.push(Boolean::Equality(lhs, rhs));
			break;
		}
		case OpType::NEQUALITY:
		{
			Type::atype_t* rhs = Pop();
			Type::atype_t* lhs = Pop();
			stack.push(Boolean::Nequality(lhs, rhs));
			break;
		}
		default:
			throw "oop";
	}
}

void Astral::Interpreter::Execute()
{
	while (pc < rom.size())
		ExecuteInstruction(rom[pc++]);

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