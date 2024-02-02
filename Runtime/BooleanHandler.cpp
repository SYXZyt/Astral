#include "BooleanHandler.h"

static inline void Cleanup(Astral::Type::atype_t* lhs, Astral::Type::atype_t* rhs)
{
    if (lhs)
        delete lhs;

    if (rhs)
        delete rhs;
}

static Astral::Type::atype_t* Equality_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float res = lhs->Value() == rhs->Value();
    Cleanup(lhs, rhs);
    return new Astral::Type::number_t(res);
}

static Astral::Type::atype_t* Nequality_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float res = lhs->Value() != rhs->Value();
    Cleanup(lhs, rhs);
    return new Astral::Type::number_t(res);
}

static Astral::Type::atype_t* Greater_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float res = lhs->Value() > rhs->Value();
    Cleanup(lhs, rhs);
    return new Astral::Type::number_t(res);
}

static Astral::Type::atype_t* Greater_Equals_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float res = lhs->Value() >= rhs->Value();
    Cleanup(lhs, rhs);
    return new Astral::Type::number_t(res);
}

static Astral::Type::atype_t* Less_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float res = lhs->Value() < rhs->Value();
    Cleanup(lhs, rhs);
    return new Astral::Type::number_t(res);
}

static Astral::Type::atype_t* Less_Equals_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float res = lhs->Value() <= rhs->Value();
    Cleanup(lhs, rhs);
    return new Astral::Type::number_t(res);
}

static Astral::Type::atype_t* Not_Number(Astral::Type::number_t* val)
{
    float res = val->Value();
    delete val;
    return new Astral::Type::number_t(!res);
}

Astral::Type::atype_t* Astral::Boolean::Equality(Type::atype_t* lhs, Type::atype_t* rhs)
{
    if (!lhs || !rhs)
    {
        Cleanup(lhs, rhs);
        return nullptr;
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

    if (lhs_number && rhs_number)
        return Equality_Number_Number(lhs_number, rhs_number);
    else
        throw "oop";

    return nullptr;
}

Astral::Type::atype_t* Astral::Boolean::Nequality(Type::atype_t* lhs, Type::atype_t* rhs)
{
    if (!lhs || !rhs)
    {
        Cleanup(lhs, rhs);
        return nullptr;
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

    if (lhs_number && rhs_number)
        return Nequality_Number_Number(lhs_number, rhs_number);
    else
        throw "oop";

    return nullptr;
}

Astral::Type::atype_t* Astral::Boolean::Greater(Type::atype_t* lhs, Type::atype_t* rhs)
{
    if (!lhs || !rhs)
    {
        Cleanup(lhs, rhs);
        return nullptr;
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

    if (lhs_number && rhs_number)
        return Greater_Number_Number(lhs_number, rhs_number);
    else
        throw "oop";

    return nullptr;
}

Astral::Type::atype_t* Astral::Boolean::GreaterEquals(Type::atype_t* lhs, Type::atype_t* rhs)
{
    if (!lhs || !rhs)
    {
        Cleanup(lhs, rhs);
        return nullptr;
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

    if (lhs_number && rhs_number)
        return Greater_Equals_Number_Number(lhs_number, rhs_number);
    else
        throw "oop";

    return nullptr;
}

Astral::Type::atype_t* Astral::Boolean::Less(Type::atype_t* lhs, Type::atype_t* rhs)
{
    if (!lhs || !rhs)
    {
        Cleanup(lhs, rhs);
        return nullptr;
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

    if (lhs_number && rhs_number)
        return Less_Number_Number(lhs_number, rhs_number);
    else
        throw "oop";

    return nullptr;
}

Astral::Type::atype_t* Astral::Boolean::LessEquals(Type::atype_t* lhs, Type::atype_t* rhs)
{
    if (!lhs || !rhs)
    {
        Cleanup(lhs, rhs);
        return nullptr;
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

    if (lhs_number && rhs_number)
        return Less_Equals_Number_Number(lhs_number, rhs_number);
    else
        throw "oop";

    return nullptr;
}

Astral::Type::atype_t* Astral::Boolean::Not(Type::atype_t* val)
{
    if (!val)
        return nullptr;

    Type::number_t* val_number = dynamic_cast<Type::number_t*>(val);

    if (val_number)
        return Not_Number(val_number);
    else
        throw "oop";
}