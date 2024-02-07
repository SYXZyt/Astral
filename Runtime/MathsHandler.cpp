#include "MathsHandler.h"

#include <string>

/*
/---------------------------------------------------------------\
| This code is a little messy. I'm not sure of a better way tbh |
\---------------------------------------------------------------/
*/

#include <math.h>

inline static void Cleanup(Astral::Type::atype_t* lhs, Astral::Type::atype_t* rhs)
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

static Astral::result_t Power_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float res = powf(lhs->Value(), rhs->Value());
    //Cleanup(lhs, rhs);

    return Success(std::shared_ptr<Astral::Type::atype_t>(new Astral::Type::number_t(res)));
}

static Astral::result_t Modulo_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float res = (int)lhs->Value() % (int)rhs->Value();
    //Cleanup(lhs, rhs);

    return Success(std::shared_ptr<Astral::Type::atype_t>(new Astral::Type::number_t(res)));
}

static Astral::result_t Addition_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float res = lhs->Value() + rhs->Value();
    //Cleanup(lhs, rhs);

    return Success(std::shared_ptr<Astral::Type::atype_t>(new Astral::Type::number_t(res)));
}

static Astral::result_t Addition_String_String(Astral::Type::string_t* lhs, Astral::Type::string_t* rhs)
{
    std::string result = std::string(lhs->Value()) + rhs->Value();
    //Cleanup(lhs, rhs);

    return Success(std::shared_ptr<Astral::Type::atype_t>(new Astral::Type::string_t(result)));
}

static Astral::result_t Addition_Number_String(Astral::Type::number_t* lhs, Astral::Type::string_t* rhs)
{
    std::string num = std::to_string(lhs->Value());
    num.erase(num.find_last_not_of('0') + 1, std::string::npos);
    num.erase(num.find_last_not_of('.') + 1, std::string::npos);

    std::string result = num + rhs->Value();
    //Cleanup(lhs, rhs);

    return Success(std::shared_ptr<Astral::Type::atype_t>(new Astral::Type::string_t(result)));
}

static Astral::result_t Addition_String_Number(Astral::Type::string_t* lhs, Astral::Type::number_t* rhs)
{
    std::string num = std::to_string(rhs->Value());
    num.erase(num.find_last_not_of('0') + 1, std::string::npos);
    num.erase(num.find_last_not_of('.') + 1, std::string::npos);

    std::string result = lhs->Value() + num;
    //Cleanup(lhs, rhs);

    return Success(std::shared_ptr<Astral::Type::atype_t>(new Astral::Type::string_t(result)));
}

static Astral::result_t Subtraction_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float res = lhs->Value() - rhs->Value();
    //Cleanup(lhs, rhs);

    return Success(std::shared_ptr<Astral::Type::atype_t>(new Astral::Type::number_t(res)));
}

static Astral::result_t Multiplication_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float res = lhs->Value() * rhs->Value();
    //Cleanup(lhs, rhs);

    return Success(std::shared_ptr<Astral::Type::atype_t>(new Astral::Type::number_t(res)));
}

static Astral::result_t Division_Number_Number(Astral::Type::number_t* lhs, Astral::Type::number_t* rhs)
{
    float rv = rhs->Value();
    if (rv == 0) //Division by zero
    {
        //Cleanup(lhs, rhs);
        return { Astral::result_t::ResultType::R_DIV_BY_ZERO, nullptr };
    }

    float res = lhs->Value() / rhs->Value();
    //Cleanup(lhs, rhs);

    return Success(std::shared_ptr<Astral::Type::atype_t>(new Astral::Type::number_t(res)));
}

Astral::result_t Astral::Maths::Addition(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs)
{
    if (!lhs || !rhs)
    {
        //Cleanup(lhs, rhs);
        return { Astral::result_t::ResultType::R_FAIL, nullptr };
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs.get());
    Type::string_t* lhs_string = dynamic_cast<Type::string_t*>(lhs.get());

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs.get());
    Type::string_t* rhs_string = dynamic_cast<Type::string_t*>(rhs.get());

    if (lhs_number && rhs_number)
        return Addition_Number_Number(lhs_number, rhs_number);
    else if (lhs_number && rhs_string)
        return Addition_Number_String(lhs_number, rhs_string);
    else if (lhs_string && rhs_number)
        return Addition_String_Number(lhs_string, rhs_number);
    else if (lhs_string && rhs_string)
        return Addition_String_String(lhs_string, rhs_string);
    else
    {
        //Cleanup(lhs, rhs);
        return FailTypes();
    }
}

Astral::result_t Astral::Maths::Subtraction(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs)
{
    if (!lhs || !rhs)
    {
        //Cleanup(lhs, rhs);
        return { Astral::result_t::ResultType::R_FAIL, nullptr };
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs.get());

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs.get());

    if (lhs_number && rhs_number)
        return Subtraction_Number_Number(lhs_number, rhs_number);
    else
    {
        //Cleanup(lhs, rhs);
        return FailTypes();
    }
}

Astral::result_t Astral::Maths::Multiplication(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs)
{
    if (!lhs || !rhs)
    {
        //Cleanup(lhs, rhs);
        return { Astral::result_t::ResultType::R_FAIL, nullptr };
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs.get());

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs.get());

    if (lhs_number && rhs_number)
        return Multiplication_Number_Number(lhs_number, rhs_number);
    else
    {
        //Cleanup(lhs, rhs);
        return FailTypes();
    }
}

Astral::result_t Astral::Maths::Divide(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs)
{
    if (!lhs || !rhs)
    {
        //Cleanup(lhs, rhs);
        return { Astral::result_t::ResultType::R_FAIL, nullptr };
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs.get());

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs.get());

    if (lhs_number && rhs_number)
        return Division_Number_Number(lhs_number, rhs_number);
    else
    {
        //Cleanup(lhs, rhs);
        return FailTypes();
    }
}

Astral::result_t Astral::Maths::Power(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs)
{
    if (!lhs || !rhs)
    {
        //Cleanup(lhs, rhs);
        return { Astral::result_t::ResultType::R_FAIL, nullptr };
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs.get());

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs.get());

    if (lhs_number && rhs_number)
        return Power_Number_Number(lhs_number, rhs_number);
    else
    {
        //Cleanup(lhs, rhs);
        return FailTypes();
    }
}

Astral::result_t Astral::Maths::Modulo(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs)
{
    if (!lhs || !rhs)
    {
        //Cleanup(lhs, rhs);
        return { Astral::result_t::ResultType::R_FAIL, nullptr };
    }

    Type::number_t* lhs_number = dynamic_cast<Type::number_t*>(lhs.get());

    Type::number_t* rhs_number = dynamic_cast<Type::number_t*>(rhs.get());

    if (lhs_number && rhs_number)
        return Modulo_Number_Number(lhs_number, rhs_number);
    else
    {
        //Cleanup(lhs, rhs);
        return FailTypes();
    }
}

Astral::result_t Astral::Maths::Minus(std::shared_ptr<Type::atype_t> val)
{
    if (!val.get())
        return { Astral::result_t::ResultType::R_FAIL, nullptr };

    if (Type::number_t* num = dynamic_cast<Type::number_t*>(val.get()))
    {
        //We can reuse the pointer and we don't have to create a new object
        num->SetValue(num->Value() * -1);
        return Success(val);
    }
    else
    {
        return FailTypes();
    }
}
