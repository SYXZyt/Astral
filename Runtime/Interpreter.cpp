#include "Interpreter.h"

Astral::Interpreter* Astral::Interpreter::instance = nullptr;

void Astral::Interpreter::ExecuteInstruction(Bytecode& instruction)
{
	OpType op = (OpType)instruction.op;
	switch (op)
	{
		case OpType::POP:
			Pop();
			break;
		case OpType::WHILE_BEG:
			break;
		case OpType::WHILE_END:
			While_JumpToBegin();
			break;
		case OpType::GC:
			//GarbageCollector::Instance().Cleanup();
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
			//if (!IsInWhileLoop())
			//{
			//	Error("Continue can only be used inside of while loop", instruction.lexeme);
			//	failed = true;
			//	return;
			//}

			--pc;
			While_JumpToBegin();
			break;
		}
		case OpType::WHILE_BREAK:
		{
			//if (!IsInWhileLoop())
			//{
			//	Error("Break can only be used inside of while loop", instruction.lexeme);
			//	failed = true;
			//	return;
			//}

			While_ExitLoop();
			break;
		}
		case OpType::LIT_VOID:
		{
			Type::void_t* null = new Type::void_t();
			GarbageCollector::Instance().RegisterDanglingPointer(null);
			Push(null);
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
			GarbageCollector::Instance().RegisterDanglingPointer(res.result);

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
			GarbageCollector::Instance().RegisterDanglingPointer(res.result);

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
			GarbageCollector::Instance().RegisterDanglingPointer(res.result);

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
			GarbageCollector::Instance().RegisterDanglingPointer(res.result);

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
			GarbageCollector::Instance().RegisterDanglingPointer(res.result);

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
			GarbageCollector::Instance().RegisterDanglingPointer(res.result);

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
			GarbageCollector::Instance().RegisterDanglingPointer(res.result);

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
			GarbageCollector::Instance().RegisterDanglingPointer(res.result);

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
			GarbageCollector::Instance().RegisterDanglingPointer(res.result);

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
			GarbageCollector::Instance().RegisterDanglingPointer(res.result);

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
			GarbageCollector::Instance().RegisterDanglingPointer(res.result);

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
			GarbageCollector::Instance().RegisterDanglingPointer(res.result);

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
			GarbageCollector::Instance().RegisterDanglingPointer(res.result);

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
			GarbageCollector::Instance().RegisterDanglingPointer(res.result);

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
			GarbageCollector::Instance().RegisterDanglingPointer(res.result);

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
			GarbageCollector::Instance().RegisterDanglingPointer(res.result);

			if (res.type == result_t::ResultType::R_OK)
				Push(res.result);
			else
			{
				Error("Invalid boolean operator type", instruction.lexeme);
				failed = true;
			}
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

			Type::atype_t* copy = variables.GetValue(name.c_str())->Copy();
			GarbageCollector::Instance().RegisterDanglingPointer(copy);
			Push(copy);
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

			Type::ref_t* varRef = new Type::ref_t(variables.GetVariable(name.c_str())->Value());
			GarbageCollector::Instance().RegisterDanglingPointer(varRef);
			Push(varRef);
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
		case OpType::FUNC_BEG:
			SkipFunction();
			break;
		case OpType::FUNC_END:
			//Take the top stack value and add it to the return value
			//SetReturnValue(Pop());
			Return();
			break;
		case OpType::FUNC_RET:
			//Take the top stack value and add it to the return value
			//SetReturnValue(Pop());
			--pc;
			Func_CleanStackFrame();
			Return();
			break;
		case OpType::CALL:
		{
			std::string funcName = instruction.lexeme.lexeme;

			if (!variables.DoesVariableExist(funcName.c_str()))
			{
				Error("Function does not exist", instruction.lexeme);
				failed = true;
				break;
			}

			Type::atype_t* var = variables.GetValue(funcName.c_str());
			Type::func_t* func = dynamic_cast<Type::func_t*>(var);
			Type::externfunc_t* externfunc = dynamic_cast<Type::externfunc_t*>(var);
			if (!func && !externfunc)
			{
				Error("Variable was not a callable type", instruction.lexeme);
				failed = true;
				break;
			}

			//Check for stack overflow
			//Astral spec limits to 4k calls
			if (callstack.size() >= 4096)
			{
				Error("Stack overflow", instruction.lexeme);
				failed = true;
				break;
			}

			int providedCount = (int)((Type::number_t*)Pop())->Value();

			if (func)
			{
				if (providedCount != func->ParamCount())
				{
					Error("Incorrect number of parameters", instruction.lexeme);
					failed = true;
					break;
				}

				callstack.push(pc);
				pc = (int)func->Address();
			}

			if (externfunc)
			{
				if (providedCount != externfunc->GetFunction().ParamCount())
				{
					Error("Incorrect number of parameters", instruction.lexeme);
					failed = true;
					break;
				}

				std::vector<Type::atype_t*> parameters;
				for (int i = 0; i < providedCount; ++i)
					parameters.push_back(Pop());

				//Due to the stack our parameters are backwards so we need to fix that
				std::reverse(parameters.begin(), parameters.end());

				Type::atype_t* returnValue = externfunc->GetFunction().Call(parameters, *this, instruction.lexeme);

				//If we returned null, we need to convert that to void
				if (!returnValue)
					returnValue = new Type::void_t();

				GarbageCollector::Instance().RegisterDanglingPointer(returnValue);
				Push(returnValue);
			}

			break;
		}
		default:
			throw "oop";
	}
}

void Astral::Interpreter::PreloadFunctions()
{
	for (auto& func : _rom.GetFunction())
	{
		variables.AddVariable(func.name);
		variables.UpdateValue(func.name, func.func);
	}
}

void Astral::Interpreter::Bind_Function(BindFunction& func)
{
	Variable* funcVar = variables.CreateVariableInGlobalScope(func.Name());
	Type::externfunc_t* f = new Type::externfunc_t(func);
	funcVar->SetValue(f);
}

void Astral::Interpreter::Execute()
{
	time_t elapsed = time(NULL);

	while (pc < rom.size())
	{
		ExecuteInstruction(rom[pc++]);

		if (elapsed != time(NULL))
		{
			elapsed = time(NULL);
			GarbageCollector::Instance().Cleanup();
		}

		if (failed)
			break;
	}
}

Astral::Interpreter::~Interpreter()
{
	//GC will clear up our stack
	GarbageCollector::FreeInstance();
}