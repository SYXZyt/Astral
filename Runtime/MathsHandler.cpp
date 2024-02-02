#include "MathsHandler.h"

/*
/---------------------------------------------------------------\
| This code is a little messy. I'm not sure of a better way tbh |
\---------------------------------------------------------------/
*/

#include <math.h>

void Cleanup(Astral::Type::atype_t* lhs, Astral::Type::atype_t* rhs)
{
    if (lhs)
        delete lhs;

    if (rhs)
        delete rhs;
}

Astral::Type::number_t* Power_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float res = powf(lhs->Value(), rhs->Value());
    Cleanup(lhs, rhs);

    return new Astral::Type::number_t(res);
}

Astral::Type::number_t* Modulo_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float res = (int)lhs->Value() % (int)rhs->Value();
    Cleanup(lhs, rhs);

    return new Astral::Type::number_t(res);
}

Astral::Type::number_t* Addition_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float res = lhs->Value() + rhs->Value();
    Cleanup(lhs, rhs);

    return new Astral::Type::number_t(res);
}

Astral::Type::number_t* Subtraction_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float res = lhs->Value() - rhs->Value();
    Cleanup(lhs, rhs);

    return new Astral::Type::number_t(res);
}

Astral::Type::number_t* Multiplication_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float res = lhs->Value() * rhs->Value();
    Cleanup(lhs, rhs);

    return new Astral::Type::number_t(res);
}

Astral::Type::number_t* Division_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float rv = rhs->Value();
    if (rv == 0) //Division by zero
    {
        Cleanup(lhs, rhs);
        return nullptr;
    }

    float res = lhs->Value() / rhs->Value();
    Cleanup(lhs, rhs);

    return new Astral::Type::number_t(res);
}

Astral::Type::atype_t* Astral::Maths::Addition(Type::atype_t* lhs, Type::atype_t* rhs)
{
    if (!lhs || !rhs)
    {
        Cleanup(lhs, rhs);
        return nullptr;
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

    if (lhs_number && rhs_number)
        return Addition_Number_Number(lhs_number, rhs_number);
    else
        throw "oop";

    return nullptr;
}

Astral::Type::atype_t* Astral::Maths::Subtraction(Type::atype_t* lhs, Type::atype_t* rhs)
{
    if (!lhs || !rhs)
    {
        Cleanup(lhs, rhs);
        return nullptr;
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

    if (lhs_number && rhs_number)
        return Subtraction_Number_Number(lhs_number, rhs_number);
    else
        throw "oop";

    return nullptr;
}

Astral::Type::atype_t* Astral::Maths::Multiplication(Type::atype_t* lhs, Type::atype_t* rhs)
{
    if (!lhs || !rhs)
    {
        Cleanup(lhs, rhs);
        return nullptr;
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

    if (lhs_number && rhs_number)
        return Multiplication_Number_Number(lhs_number, rhs_number);
    else
        throw "oop";

    return nullptr;
}

Astral::Type::atype_t* Astral::Maths::Divide(Type::atype_t* lhs, Type::atype_t* rhs)
{
    if (!lhs || !rhs)
    {
        Cleanup(lhs, rhs);
        return nullptr;
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

    if (lhs_number && rhs_number)
        return Division_Number_Number(lhs_number, rhs_number);
    else
        throw "oop";

    return nullptr;
}

Astral::Type::atype_t* Astral::Maths::Power(Type::atype_t* lhs, Type::atype_t* rhs)
{
    if (!lhs || !rhs)
    {
        Cleanup(lhs, rhs);
        return nullptr;
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

    if (lhs_number && rhs_number)
        return Power_Number_Number(lhs_number, rhs_number);
    else
        throw "oop";

    return nullptr;
}

Astral::Type::atype_t* Astral::Maths::Modulo(Type::atype_t* lhs, Type::atype_t* rhs)
{
    if (!lhs || !rhs)
    {
        Cleanup(lhs, rhs);
        return nullptr;
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs);

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs);

    if (lhs_number && rhs_number)
        return Modulo_Number_Number(lhs_number, rhs_number);
    else
        throw "oop";

    return nullptr;
}

Astral::Type::atype_t* Astral::Maths::Minus(Type::atype_t* val)
{
    if (!val)
        return nullptr;

    if (Type::number_t* num = dynamic_cast<Type::number_t*>(val))
    {
        //We can reuse the pointer and we don't have to create a new object
        num->SetValue(num->Value() * -1);
        return num;
    }
    else
    {
        delete val;
        return nullptr;
    }
}
