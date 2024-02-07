#include "BooleanHandler.h"

static inline void Cleanup(Astral::Type::atype_t* lhs, Astral::Type::atype_t* rhs)
{
	if (lhs)
		delete lhs;

	if (rhs)
		delete rhs;
}

inline static Astral::result_t Success(std::shared_ptr<Astral::Type::atype_t> val)
{
	return { Astral::result_t::ResultType::R_OK, val };
}

inline static Astral::result_t FailTypes()
{
	return { Astral::result_t::ResultType::R_INVALID_TYPES, nullptr };
}

static Astral::result_t Equality_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = lhs->Value() == rhs->Value();
	//Cleanup(lhs, rhs);
	return Success(std::shared_ptr<Astral::Type::atype_t>(new Astral::Type::number_t(res)));
}

static Astral::result_t Nequality_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = lhs->Value() != rhs->Value();
	Cleanup(lhs, rhs);
	return Success(std::shared_ptr<Astral::Type::atype_t>(new Astral::Type::number_t(res)));
}

static Astral::result_t Greater_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = lhs->Value() > rhs->Value();
	Cleanup(lhs, rhs);
	return Success(std::shared_ptr<Astral::Type::atype_t>(new Astral::Type::number_t(res)));
}

static Astral::result_t Greater_Equals_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = lhs->Value() >= rhs->Value();
	Cleanup(lhs, rhs);
	return Success(std::shared_ptr<Astral::Type::atype_t>(new Astral::Type::number_t(res)));
}

static Astral::result_t Less_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = lhs->Value() < rhs->Value();
	Cleanup(lhs, rhs);
	return Success(std::shared_ptr<Astral::Type::atype_t>(new Astral::Type::number_t(res)));
}

static Astral::result_t Less_Equals_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
	float res = lhs->Value() <= rhs->Value();
	Cleanup(lhs, rhs);
	return Success(std::shared_ptr<Astral::Type::atype_t>(new Astral::Type::number_t(res)));
}

static Astral::result_t Not_Number(Astral::Type::number_t* val)
{
	float res = val->Value();
	delete val;
	return Success(std::shared_ptr<Astral::Type::atype_t>(new Astral::Type::number_t(!res)));
}

Astral::result_t Astral::Boolean::Equality(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs)
{
	if (!lhs || !rhs)
	{
		//Cleanup(lhs, rhs);
		return { Astral::result_t::ResultType::R_FAIL, nullptr };
	}

	Astral::Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs.get());

	Astral::Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs.get());

	if (lhs_number && rhs_number)
		return Equality_Number_Number(lhs_number, rhs_number);
	else
	{
		//Cleanup(lhs, rhs);
		return FailTypes();
	}
}

Astral::result_t Astral::Boolean::Nequality(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs)
{
	if (!lhs || !rhs)
	{
		//Cleanup(lhs, rhs);
		return { Astral::result_t::ResultType::R_FAIL, nullptr };
	}

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs.get());

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs.get());

	if (lhs_number && rhs_number)
		return Nequality_Number_Number(lhs_number, rhs_number);
	else
	{
		//Cleanup(lhs, rhs);
		return FailTypes();
	}
}

Astral::result_t Astral::Boolean::Greater(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs)
{
	if (!lhs || !rhs)
	{
		//Cleanup(lhs, rhs);
		return { Astral::result_t::ResultType::R_FAIL, nullptr };
	}

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs.get());

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs.get());

	if (lhs_number && rhs_number)
		return Greater_Number_Number(lhs_number, rhs_number);
	else
	{
		//Cleanup(lhs, rhs);
		return FailTypes();
	}
}

Astral::result_t Astral::Boolean::GreaterEquals(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs)
{
	if (!lhs || !rhs)
	{
		//Cleanup(lhs, rhs);
		return { Astral::result_t::ResultType::R_FAIL, nullptr };
	}

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs.get());

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs.get());

	if (lhs_number && rhs_number)
		return Greater_Equals_Number_Number(lhs_number, rhs_number);
	else
	{
		//Cleanup(lhs, rhs);
		return FailTypes();
	}
}

Astral::result_t Astral::Boolean::Less(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs)
{
	if (!lhs || !rhs)
	{
		//Cleanup(lhs, rhs);
		return { Astral::result_t::ResultType::R_FAIL, nullptr };
	}

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs.get());

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs.get());

	if (lhs_number && rhs_number)
		return Less_Number_Number(lhs_number, rhs_number);
	else
	{
		//Cleanup(lhs, rhs);
		return FailTypes();
	}
}

Astral::result_t Astral::Boolean::LessEquals(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs)
{
	if (!lhs || !rhs)
	{
		//Cleanup(lhs, rhs);
		return { Astral::result_t::ResultType::R_FAIL, nullptr };
	}

	Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs.get());

	Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs.get());

	if (lhs_number && rhs_number)
		return Less_Equals_Number_Number(lhs_number, rhs_number);
	else
	{
		//Cleanup(lhs, rhs);
		return FailTypes();
	}
}

Astral::result_t Astral::Boolean::Not(std::shared_ptr<Type::atype_t> val)
{
	if (!val)
		return { Astral::result_t::ResultType::R_FAIL, nullptr };

	Type::number_t* val_number = dynamic_cast<Type::number_t*>(val.get());

	if (val_number)
		return Not_Number(val_number);
	else
	{
		//delete val;
		return FailTypes();
	}
}