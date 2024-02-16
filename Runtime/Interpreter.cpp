#include "Interpreter.h"

Astral::Interpreter* Astral::Interpreter::instance = nullptr;

void Astral::Interpreter::ExecuteInstruction(Bytecode& instruction)
{
	OpType op = (OpType)instruction.op;
	switch (op)
	{
		case OpType::WHILE_BEG:
			break;
		case OpType::WHILE_END:
			While_JumpToBegin();
			break;
		case OpType::GC:
			GarbageCollector::Instance().Cleanup();
			break;
		case OpType::WHILE_COND:
		{
			Type::atype_t* result = Pop();
			if (Type::number_t* num = dynamic_cast<Type::number_t*>(result))
			{
				if (!num->Value())
					While_ExitLoop();
			}
			else
			{
				Error("Could not evaluate expression to a boolean value", instruction.lexeme);
				failed = true;
				return;
			}

			break;
		}
		case OpType::WHILE_CONTINUE:
		{
			While_JumpToBegin();
			break;
		}
		case OpType::WHILE_BREAK:
		{
			While_ExitLoop();
			break;
		}
		case OpType::LIT_NUMBER:
		{
			float v = std::stof(instruction.lexeme.lexeme);
			Astral::Type::atype_t* number = new Type::number_t(v);
			GarbageCollector::Instance().RegisterDanglingPointer(number);
			Push(number);
			break;
		}
		case OpType::LIT_STRING:
		{
			Astral::Type::atype_t* string = new Type::string_t(instruction.lexeme.lexeme.c_str());
			GarbageCollector::Instance().RegisterDanglingPointer(string);
			Push(string);
			break;
		}
		case OpType::ADD:
		{
			Astral::Type::atype_t* rhs = Pop();
			Astral::Type::atype_t* lhs = Pop();
			result_t res = Maths::Addition(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
			else if (res.type == result_t::ResultType::R_VOID_REFERENCE)
			{
				Error("Void reference", instruction.lexeme);
				failed = true;
			}
			else
			{
				Error("Cannot add types", instruction.lexeme);
				failed = true;
			}

			break;
		}
		case OpType::SUB:
		{
			Astral::Type::atype_t* rhs = Pop();
			Astral::Type::atype_t* lhs = Pop();
			result_t res = Maths::Subtraction(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
			else
			{
				Error("Cannot subtract types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::MUL:
		{
			Astral::Type::atype_t* rhs = Pop();
			Astral::Type::atype_t* lhs = Pop();
			result_t res = Maths::Multiplication(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
			else
			{
				Error("Cannot multiply types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::DIV:
		{
			Astral::Type::atype_t* rhs = Pop();
			Astral::Type::atype_t* lhs = Pop();
			result_t res = Maths::Divide(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
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
			Astral::Type::atype_t* rhs = Pop();
			Astral::Type::atype_t* lhs = Pop();
			result_t res = Maths::Power(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
			else
			{
				Error("Cannot calculate power with types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::MOD:
		{
			Astral::Type::atype_t* rhs = Pop();
			Astral::Type::atype_t* lhs = Pop();
			result_t res = Maths::Modulo(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
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
			Astral::Type::atype_t* val = Pop();
			result_t res = Maths::Minus(val);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
			else
			{
				Error("Type does not support minus operator", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::FACTORIAL:
		{
			Astral::Type::atype_t* val = Pop();
			result_t res = Maths::Factorial(val);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
			else
			{
				Error("Type does not support factorial", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::AND:
		{
			Astral::Type::atype_t* lhs = Pop();
			Astral::Type::atype_t* rhs = Pop();
			result_t res = Boolean::And(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
			else
			{
				Error("Invalid boolean operator types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::OR:
		{
			Astral::Type::atype_t* lhs = Pop();
			Astral::Type::atype_t* rhs = Pop();
			result_t res = Boolean::Or(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
			else
			{
				Error("Invalid boolean operator types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::EQUALITY:
		{
			Astral::Type::atype_t* rhs = Pop();
			Astral::Type::atype_t* lhs = Pop();
			result_t res = Boolean::Equality(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
			else
			{
				Error("Invalid boolean operator types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::NEQUALITY:
		{
			Astral::Type::atype_t* rhs = Pop();
			Astral::Type::atype_t* lhs = Pop();
			result_t res = Boolean::Nequality(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
			else
			{
				Error("Invalid boolean operator types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::GREATER:
		{
			Astral::Type::atype_t* rhs = Pop();
			Astral::Type::atype_t* lhs = Pop();
			result_t res = Boolean::Greater(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
			else
			{
				Error("Invalid boolean operator types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::GREATER_EQUALS:
		{
			Astral::Type::atype_t* rhs = Pop();
			Astral::Type::atype_t* lhs = Pop();
			result_t res = Boolean::GreaterEquals(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
			else
			{
				Error("Invalid boolean operator types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::LESS:
		{
			Astral::Type::atype_t* rhs = Pop();
			Astral::Type::atype_t* lhs = Pop();
			result_t res = Boolean::Less(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
			else
			{
				Error("Invalid boolean operator types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::LESS_EQUALS:
		{
			Astral::Type::atype_t* rhs = Pop();
			Astral::Type::atype_t* lhs = Pop();
			result_t res = Boolean::LessEquals(lhs, rhs);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
			else
			{
				Error("Invalid boolean operator types", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::NOT:
		{
			Astral::Type::atype_t* val = Pop();
			result_t res = Boolean::Not(val);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
			else
			{
				Error("Invalid boolean operator type", instruction.lexeme);
				failed = true;
			}
			break;
		}
		case OpType::PRINT:
		{
			Astral::Type::atype_t* val = Pop();

			//If we do not know the type we are printing, just print the address
			if (Type::number_t* number_t = dynamic_cast<Type::number_t*>(val))
				std::cout << number_t->Value() << '\n';
			else if (Type::string_t* string_t = dynamic_cast<Type::string_t*>(val))
				std::cout << string_t->Value() << '\n';
			else if (Type::void_t* void_t = dynamic_cast<Type::void_t*>(val))
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
				Error("Variable does not exist", instruction.lexeme);
				failed = true;
				break;
			}

			Push(variables.GetValue(name.c_str())->Copy());

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

			Type::atype_t* value = Pop();
			if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(value))
				variables.UpdateRef(name.c_str(), ref->GetBlock());
			else
				variables.UpdateValue(name.c_str(), value);

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

			Type::atype_t* value = Pop();
			if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(value))
				variables.UpdateRef(name.c_str(), ref->GetBlock());
			else
				variables.UpdateValue(name.c_str(), value);

			break;
		}
		case OpType::VARIABLE_REF:
		{
			std::string name = instruction.lexeme.lexeme;
			if (!variables.DoesVariableExist(name.c_str()))
			{
				Error("Variable does not exist", instruction.lexeme);
				failed = true;
				break;
			}

			Push(new Type::ref_t(variables.GetVariable(name.c_str())->Value()));
			break;
		}
		case OpType::SCOPE_BEG:
			variables.AddScope();
			break;
		case OpType::SCOPE_END:
			variables.RemoveScope();
			break;
		case OpType::IF:
		{
			Type::atype_t* result = Pop();
			if (Type::number_t* num = dynamic_cast<Type::number_t*>(result))
			{
				//If the result is not true, skip the block
				if (!num->Value())
					SkipBlock();
			}
			else
			{
				Error("Could not evaluate expression to a boolean value", instruction.lexeme);
				failed = true;
				return;
			}

			break;
		}
		case OpType::IF_ELSE:
		{
			Type::atype_t* result = Pop();
			if (Type::number_t* num = dynamic_cast<Type::number_t*>(result))
			{
				//If the result is not true, skip the block
				if (!num->Value())
				{
					SkipBlock();
					++pc; //Skip the skipblock instruction
				}
			}
			else
			{
				Error("Could not evaluate expression to a boolean value", instruction.lexeme);
				failed = true;
				return;
			}

			break;
		}
		case OpType::SKIP_BLOCK:
			SkipBlock();
			break;
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
	//GC will clear up our stack
	GarbageCollector::FreeInstance();
}