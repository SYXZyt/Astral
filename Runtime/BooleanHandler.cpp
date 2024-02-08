#include "BooleanHandler.h"

inline static Astral::result_t Success(Astral::Type::number_t* val)
{
	return { Astral::result_t::ResultType::R_OK, new RefCount<Astral::Type::atype_t>(val) };
}

inline static Astral::result_t FailTypes()
{
	return { Astral::result_t::ResultType::R_INVALID_TYPES, nullptr };
}

static Astral::result_t Equality_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = lhs->Value() == rhs->Value();
	return Success(new Astral::Type::number_t(res));
}

static Astral::result_t Nequality_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = lhs->Value() != rhs->Value();
	return Success(new Astral::Type::number_t(res));
}

static Astral::result_t Greater_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = lhs->Value() > rhs->Value();
	return Success(new Astral::Type::number_t(res));
}

static Astral::result_t Greater_Equals_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = lhs->Value() >= rhs->Value();
	return Success(new Astral::Type::number_t(res));
}

static Astral::result_t Less_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = lhs->Value() < rhs->Value();
	return Success(new Astral::Type::number_t(res));
}

static Astral::result_t Less_Equals_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = lhs->Value() <= rhs->Value();
	return Success(new Astral::Type::number_t(res));
}

static Astral::result_t Not_Number(Astral::Type::number_t* val)
{
	float res = val->Value();
	return Success(new Astral::Type::number_t(!res));
}

Astral::result_t Astral::Boolean::Equality(Type::atype_t* lhs, Type::atype_t* rhs)
{
	if (!lhs || !rhs)
	{
		return { Astral::result_t::ResultType::R_FAIL, nullptr };
	}

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

	if (lhs_number && rhs_number)
		return Equality_Number_Number(lhs_number, rhs_number);
	else
	{
		return FailTypes();
	}
}

Astral::result_t Astral::Boolean::Nequality(Type::atype_t* lhs, Type::atype_t* rhs)
{
	if (!lhs || !rhs)
	{
		return { Astral::result_t::ResultType::R_FAIL, nullptr };
	}

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

	if (lhs_number && rhs_number)
		return Nequality_Number_Number(lhs_number, rhs_number);
	else
	{
		return FailTypes();
	}
}

Astral::result_t Astral::Boolean::Greater(Type::atype_t* lhs, Type::atype_t* rhs)
{
	if (!lhs || !rhs)
	{
		return { Astral::result_t::ResultType::R_FAIL, nullptr };
	}

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

	if (lhs_number && rhs_number)
		return Greater_Number_Number(lhs_number, rhs_number);
	else
	{
		return FailTypes();
	}
}

Astral::result_t Astral::Boolean::GreaterEquals(Type::atype_t* lhs, Type::atype_t* rhs)
{
	if (!lhs || !rhs)
	{
		return { Astral::result_t::ResultType::R_FAIL, nullptr };
	}

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

	if (lhs_number && rhs_number)
		return Greater_Equals_Number_Number(lhs_number, rhs_number);
	else
	{
		return FailTypes();
	}
}

Astral::result_t Astral::Boolean::Less(Type::atype_t* lhs, Type::atype_t* rhs)
{
	if (!lhs || !rhs)
	{
		return { Astral::result_t::ResultType::R_FAIL, nullptr };
	}

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

	if (lhs_number && rhs_number)
		return Less_Number_Number(lhs_number, rhs_number);
	else
	{
		return FailTypes();
	}
}

Astral::result_t Astral::Boolean::LessEquals(Type::atype_t* lhs, Type::atype_t* rhs)
{
	if (!lhs || !rhs)
	{
		return { Astral::result_t::ResultType::R_FAIL, nullptr };
	}

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

	if (lhs_number && rhs_number)
		return Less_Equals_Number_Number(lhs_number, rhs_number);
	else
	{
		return FailTypes();
	}
}

Astral::result_t Astral::Boolean::Not(Type::atype_t* val)
{
	if (!val)
		return { Astral::result_t::ResultType::R_FAIL, nullptr };

	Type::number_t* val_number = dynamic_cast<Type::number_t*>(val);

	if (val_number)
		return Not_Number(val_number);
	else
	{
		delete val;
		return FailTypes();
	}
}