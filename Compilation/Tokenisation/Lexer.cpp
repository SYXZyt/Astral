#include "Lexer.h"

#define FILTER_WHITE(c) (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\b')
#define FILTER_NUMBER(c) (c >= '0' && c <= '9')

#define CHAR_TOKEN(tokenLexeme, type)	\
Lexeme lex;								\
lex.fname = fname;						\
lex.lexeme = tokenLexeme;				\
lex.line = line;						\
lex.positionInBuffer = bufferpos;		\
lex.positionInLine = posOnLine;			\
										\
Token token;							\
token.SetType(type);					\
token.SetLexeme(lex)

#define PUSH_TOKEN() tokens.push_back(token)

void Astral::Lexer::Advance()
{
	++bufferpos;
	++posOnLine;
	
	//If we have ran out of characters, we need to use the null characters so we can tell the lexer that we have reached EOF
	if (bufferpos >= data.size())
		currentChar = '\0';
	else
		currentChar = data[bufferpos];

	if (currentChar == '\n')
	{
		posOnLine = 0;
		++line;
	}
}

Astral::Token Astral::Lexer::GenerateNumber()
{
	filepos startpos = bufferpos;
	filepos startlinepos = posOnLine;

	std::string strRepr = "";
	int decimalCount = 0;

	do
	{
		if (currentChar == '.')
			++decimalCount;

		strRepr += currentChar;
		Advance();

	} while (currentChar == '.' || FILTER_NUMBER(currentChar));

	Lexeme lex;
	lex.fname = fname;
	lex.lexeme = strRepr;
	lex.line = line;
	lex.positionInBuffer = startpos;
	lex.positionInLine = startlinepos;

	Token tok;
	tok.SetLexeme(lex);
	tok.SetType(TokenType::NUMBER);

	//Prevents a number like 12.34.56 being used
	if (decimalCount > 1)
	{
		Astral::Error("Malformed numeric value", tok);
		failed = true;
	}

	return tok;
}

void Astral::Lexer::Tokenise()
{
	while (currentChar != '\0')
	{
		//If we have a whitespace character, we need to skip it since they are unused Astral
		if (FILTER_WHITE(currentChar))
		{
			Advance();
			continue;
		}

		if (currentChar == '+')
		{
			CHAR_TOKEN("+", TokenType::PLUS);
			PUSH_TOKEN();
			Advance();
		}
		else if (currentChar == '-')
		{
			CHAR_TOKEN("-", TokenType::MINUS);
			PUSH_TOKEN();
			Advance();
		}
		else if (currentChar == '/')
		{
			CHAR_TOKEN("/", TokenType::DIVIDE);
			PUSH_TOKEN();
			Advance();
		}
		else if (currentChar == '*')
		{
			CHAR_TOKEN("*", TokenType::ASTERISK);
			PUSH_TOKEN();
			Advance();
		}
		else if (FILTER_NUMBER(currentChar))
		{
			tokens.push_back(GenerateNumber());
		}
		else
		{
			CHAR_TOKEN(std::string(1, currentChar), TokenType::_EOF);
			Astral::Error((std::string("Illegal character '") + currentChar + "' found").c_str(), token);
			Advance();
			failed = true;
		}
	}
}

Astral::Lexer::Lexer(const std::string& data, const std::string& fname) : fname(fname), bufferpos(-1), posOnLine(-1), line(0), currentChar('\0'), failed(false), data(data)
{
	Advance();
}