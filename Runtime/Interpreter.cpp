#include "Interpreter.h"

void Astral::Interpreter::ExecuteInstruction(Bytecode& instruction)
{
	OpType op = (OpType)instruction.op;
	switch (op)
	{
		case OpType::LIT_NUMBER:
		{
			float v = std::stof(instruction.lexeme.lexeme);
			std::shared_ptr<Type::atype_t> number(new Type::number_t(v));
			stack.push(number);
			break;
		}
		case OpType::LIT_STRING:
		{
			std::shared_ptr<Type::atype_t> string(new Type::string_t(instruction.lexeme.lexeme.c_str()));
			stack.push(string);
			break;
		}
		case OpType::ADD:
		{
			std::shared_ptr<Type::atype_t> rhs = Pop();
			std::shared_ptr<Type::atype_t> lhs = Pop();
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
			std::shared_ptr<Type::atype_t> rhs = Pop();
			std::shared_ptr<Type::atype_t> lhs = Pop();
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
			std::shared_ptr<Type::atype_t> lhs = Pop();
			std::shared_ptr<Type::atype_t> rhs = Pop();
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
			std::shared_ptr<Type::atype_t> rhs = Pop();
			std::shared_ptr<Type::atype_t> lhs = Pop();
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
			std::shared_ptr<Type::atype_t> rhs = Pop();
			std::shared_ptr<Type::atype_t> lhs = Pop();
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
			std::shared_ptr<Type::atype_t> rhs = Pop();
			std::shared_ptr<Type::atype_t> lhs = Pop();
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
			std::shared_ptr<Type::atype_t> val = Pop();
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
			std::shared_ptr<Type::atype_t> rhs = Pop();
			std::shared_ptr<Type::atype_t> lhs = Pop();
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
			std::shared_ptr<Type::atype_t> rhs = Pop();
			std::shared_ptr<Type::atype_t> lhs = Pop();
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
			std::shared_ptr<Type::atype_t> rhs = Pop();
			std::shared_ptr<Type::atype_t> lhs = Pop();
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
			std::shared_ptr<Type::atype_t> rhs = Pop();
			std::shared_ptr<Type::atype_t> lhs = Pop();
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
			std::shared_ptr<Type::atype_t> rhs = Pop();
			std::shared_ptr<Type::atype_t> lhs = Pop();
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
			std::shared_ptr<Type::atype_t> rhs = Pop();
			std::shared_ptr<Type::atype_t> lhs = Pop();
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
			std::shared_ptr<Type::atype_t> val = Pop();
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
			std::shared_ptr<Type::atype_t> val = Pop();

			//If we do not know the type we are printing, just print the address
			if (Type::number_t* number_t = dynamic_cast<Type::number_t*>(val.get()))
				std::cout << number_t->Value() << '\n';
			else if (Type::string_t* string_t = dynamic_cast<Type::string_t*>(val.get()))
				std::cout << string_t->Value() << '\n';
			else if (Type::void_t* void_t = dynamic_cast<Type::void_t*>(val.get()))
			{
				Error("void reference", instruction.lexeme);
				failed = true;
				break;
			}
			else
				std::cout << '$' << val << '\n';

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
		case OpType::ASSIGN_VOID:
		{
			std::string name = instruction.lexeme.lexeme;
			if (variables.DoesVariableExistInHighestScope(name.c_str()))
			{
				Error("Variable redefinition", instruction.lexeme);
				failed = true;
				break;
			}

			variables.AddVariable(name.c_str());

			break;
		}
		case OpType::ASSIGN:
		{
			std::string name = instruction.lexeme.lexeme;
			if (variables.DoesVariableExistInHighestScope(name.c_str()))
			{
				Error("Variable redefinition", instruction.lexeme);
				failed = true;
				break;
			}

			variables.AddVariable(name.c_str());
			variables.UpdateValue(name.c_str(), Pop());

			break;
		}
		case OpType::UPDATE_VAR:
		{
			std::string name = instruction.lexeme.lexeme;
			if (!variables.DoesVariableExist(name.c_str()))
			{
				Error("Variable does not exist", instruction.lexeme);
				failed = true;
				break;
			}

			variables.UpdateValue(name.c_str(), Pop());

			break;
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
	//while (!stack.empty())
	//{
	//	std::shared_ptr<Type::atype_t> value = Pop();

	//	delete value;
	//}
}