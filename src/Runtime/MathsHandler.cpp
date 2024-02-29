#include "MathsHandler.h"

#include <string>
#include <math.h>

/*
/---------------------------------------------------------------\
| This code is a little messy. I'm not sure of a better way tbh |
\---------------------------------------------------------------/
*/

inline static Astral::result_t Success(Astral::Type::atype_t* val)
{
	return { Astral::result_t::ResultType::R_OK, val };
}

inline static Astral::result_t FailTypes()
{
	return { Astral::result_t::ResultType::R_INVALID_TYPES, nullptr };
}

static Astral::result_t Factorial_Number(Astral::Type::number_t* val)
{
	int fact = 1;
	for (int i = 1; i <= (int)val->Value(); ++i)
		fact *= i;

	return Success(new Astral::Type::number_t((float)fact));
}

static Astral::result_t Power_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = powf(lhs->Value(), rhs->Value());

	return Success(new Astral::Type::number_t(res));
}

static Astral::result_t Modulo_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = (float)((int)lhs->Value() % (int)rhs->Value());

	return Success(new Astral::Type::number_t(res));
}

static Astral::result_t Addition_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = lhs->Value() + rhs->Value();

	return Success(new Astral::Type::number_t(res));
}

static Astral::result_t Addition_String_String(Astral::Type::string_t* lhs, Astral::Type::string_t* rhs)
{
	std::string result = std::string(lhs->Value()) + rhs->Value();

	return Success(new Astral::Type::string_t(result));
}

static Astral::result_t Subtraction_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = lhs->Value() - rhs->Value();

	return Success(new Astral::Type::number_t(res));
}

static Astral::result_t Multiplication_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = lhs->Value() * rhs->Value();

	return Success(new Astral::Type::number_t(res));
}

static Astral::result_t Division_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float rv = rhs->Value();
	if (rv == 0) //Division by zero
		return { Astral::result_t::ResultType::R_DIV_BY_ZERO, nullptr };

	float res = lhs->Value() / rhs->Value();

	return Success(new Astral::Type::number_t(res));
}

Astral::result_t Astral::Maths::Addition(Type::atype_t* lhs, Type::atype_t* rhs)
{
	if (
		!lhs ||
		!rhs ||
		dynamic_cast<Type::void_t*>(lhs) ||
		dynamic_cast<Type::void_t*>(rhs)
		)
		return { Astral::result_t::ResultType::R_VOID_REFERENCE, nullptr };

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);
	Type::string_t* lhs_string = dynamic_cast<Type::string_t*>(lhs);

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);
	Type::string_t* rhs_string = dynamic_cast<Type::string_t*>(rhs);

	if (lhs_number && rhs_number)
		return Addition_Number_Number(lhs_number, rhs_number);
	else if (lhs_string && rhs_string)
		return Addition_String_String(lhs_string, rhs_string);
	else
		return FailTypes();
}

Astral::result_t Astral::Maths::Subtraction(Type::atype_t* lhs, Type::atype_t* rhs)
{
	if (
		!lhs ||
		!rhs ||
		dynamic_cast<Type::void_t*>(lhs) ||
		dynamic_cast<Type::void_t*>(rhs)
		)
		return { Astral::result_t::ResultType::R_VOID_REFERENCE, nullptr };

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

	if (lhs_number && rhs_number)
		return Subtraction_Number_Number(lhs_number, rhs_number);
	else
		return FailTypes();
}

Astral::result_t Astral::Maths::Multiplication(Type::atype_t* lhs, Type::atype_t* rhs)
{
	if (
		!lhs ||
		!rhs ||
		dynamic_cast<Type::void_t*>(lhs) ||
		dynamic_cast<Type::void_t*>(rhs)
		)
		return { Astral::result_t::ResultType::R_VOID_REFERENCE, nullptr };

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

	if (lhs_number && rhs_number)
		return Multiplication_Number_Number(lhs_number, rhs_number);
	else
		return FailTypes();
}

Astral::result_t Astral::Maths::Divide(Type::atype_t* lhs, Type::atype_t* rhs)
{
	if (
		!lhs ||
		!rhs ||
		dynamic_cast<Type::void_t*>(lhs) ||
		dynamic_cast<Type::void_t*>(rhs)
		)
		return { Astral::result_t::ResultType::R_VOID_REFERENCE, nullptr };

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

	if (lhs_number && rhs_number)
		return Division_Number_Number(lhs_number, rhs_number);
	else
		return FailTypes();
}

Astral::result_t Astral::Maths::Power(Type::atype_t* lhs, Type::atype_t* rhs)
{
	if (
		!lhs ||
		!rhs ||
		dynamic_cast<Type::void_t*>(lhs) ||
		dynamic_cast<Type::void_t*>(rhs)
		)
		return { Astral::result_t::ResultType::R_VOID_REFERENCE, nullptr };

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

	if (lhs_number && rhs_number)
		return Power_Number_Number(lhs_number, rhs_number);
	else
		return FailTypes();
}

Astral::result_t Astral::Maths::Modulo(Type::atype_t* lhs, Type::atype_t* rhs)
{
	if (
		!lhs ||
		!rhs ||
		dynamic_cast<Type::void_t*>(lhs) ||
		dynamic_cast<Type::void_t*>(rhs)
		)
		return { Astral::result_t::ResultType::R_VOID_REFERENCE, nullptr };

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

	if (lhs_number && rhs_number)
		return Modulo_Number_Number(lhs_number, rhs_number);
	else
		return FailTypes();
}

Astral::result_t Astral::Maths::Minus(Type::atype_t* val)
{
	if (
		!val ||
		dynamic_cast<Type::void_t*>(val)
		)
		return { Astral::result_t::ResultType::R_VOID_REFERENCE, nullptr };

	if (Type::number_t* num = dynamic_cast<Type::number_t*>(val))
	{
		//We can reuse the pointer and we don't have to create a new object
		num->SetValue(num->Value() * -1);
		return Success(num);
	}
	else
		return FailTypes();
}

Astral::result_t Astral::Maths::Factorial(Type::atype_t* val)
{
	if (
		!val ||
		dynamic_cast<Type::void_t*>(val)
		)
		return { Astral::result_t::ResultType::R_VOID_REFERENCE, nullptr };

	if (Type::number_t* num = dynamic_cast<Type::number_t*>(val))
		return Factorial_Number(num);
	else
		return FailTypes();

	return result_t();
}
