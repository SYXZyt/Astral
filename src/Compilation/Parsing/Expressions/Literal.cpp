#include "Literal.h"

#include "../../../ErrorManager.h"

void Astral::Literal::Dump(int indent)
{
    std::cout << std::string(indent * 2, ' ');
    std::cout << "{ Literal Value " << token.GetLexeme().lexeme << " }\n";
}

Astral::Literal::~Literal()
{
    if (data)
    {
        switch (type)
        {
            case LiteralType::NUMBER:
                delete (float*)data;
                break;
            case LiteralType::BOOLEAN:
                delete (bool*)data;
                break;
            case LiteralType::IDENTIFER:
            case LiteralType::REFERENCE:
                delete (std::string*)data;
                break;
            case LiteralType::STRUCT_ACCESS:
            case LiteralType::STRUCT_ACCESS_LEAF:
            case LiteralType::STRUCT_ACCESS_LERT:
            case LiteralType::STRUCT_ACCESS_ROOT:
                delete (Literal*)data;
            default:
            {
                Error("Unknown literal type");
                break;
            }
        }
    }
}