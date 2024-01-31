#include "Lexer.h"

#define FILTER_WHITE(c) (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\b')
#define FILTER_NUMBER(c) (c >= '0' && c <= '9')
#define FILTER_IDEN(c) \
(\
	(c >= 'a' && c <= 'z') ||\
	(c >= 'A' && c <= 'Z') ||\
	FILTER_NUMBER(c) ||\
	(c == '_')\
)

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

char Astral::Lexer::Peek()
{
	if (bufferpos + 1ull >= data.size())
		return '\0';

	return data[bufferpos + 1ull];
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

Astral::Token Astral::Lexer::GenerateString(char strChar)
{
	//Skip the open string character
	Advance();

	Lexeme lex;
	lex.fname = fname;
	lex.line = line;
	lex.positionInBuffer = bufferpos;
	lex.positionInLine = posOnLine;

	std::string data = "";

	while (currentChar != strChar)
	{
		//Handle escape sequences
		if (currentChar == '\\')
		{
			Advance();

			switch (currentChar)
			{
			case 'n':
				data += '\n';
				break;
			case 't':
				data += '\t';
				break;
			case 'r':
				data += '\r';
				break;
			case 'b':
				data += '\b';
				break;
			case '\'':
				data += '\'';
				break;
			case '\"':
				data += '\"';
				break;
			case '\\':
				data += '\\';
				break;
			case '0':
				data += '\0';
			case '\0':
			{
				lex.lexeme = data;
				Token token;
				token.SetLexeme(lex);
				Error("Unterminated string", token);
				failed = true;

				break;
			}
			default:
			{
				lex.positionInBuffer = bufferpos - 1;
				lex.positionInLine = posOnLine - 1;
				lex.lexeme = "\\" + currentChar;
				Token token;
				token.SetLexeme(lex);
				Error("Unknown escape sequence", token);
				failed = true;

				break;
			}
			}
		}

		//Handle an unterminated string, either EOF or EOL
		if (currentChar == '\n' || currentChar == '\0')
		{
			lex.lexeme = data;
			Token token;
			token.SetLexeme(lex);
			Error("Unterminated string", token);
			failed = true;
			break;
		}

		data += currentChar;
		Advance();
	}

	//Skip the close string character
	Advance();

	lex.lexeme = data;
	Token token;
	token.SetLexeme(lex);
	token.SetType(TokenType::STRING);
	return token;
}

Astral::Token Astral::Lexer::GenerateIdentifier()
{
	filepos beginPos = bufferpos;
	filepos beginFilePos = posOnLine;

	std::string iden = "";

	do
	{
		iden += currentChar;

		Advance();
	} while (FILTER_IDEN(currentChar));

	Lexeme lex;
	lex.fname = fname;
	lex.lexeme = iden;
	lex.line = line;
	lex.positionInBuffer = beginPos;
	lex.positionInLine = beginFilePos;

	Token token;
	token.SetLexeme(lex);
	token.SetType(TokenType::IDEN);
	return token;
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
		else if (currentChar == '(')
		{
			CHAR_TOKEN("(", TokenType::L_BRA);
			PUSH_TOKEN();
			Advance();
		}
		else if (currentChar == ')')
		{
			CHAR_TOKEN(")", TokenType::R_BRA);
			PUSH_TOKEN();
			Advance();
		}
		else if (currentChar == '{')
		{
			CHAR_TOKEN("{", TokenType::L_CURLY);
			PUSH_TOKEN();
			Advance();
		}
		else if (currentChar == '}')
		{
			CHAR_TOKEN("}", TokenType::R_CURLY);
			PUSH_TOKEN();
			Advance();
		}
		else if (currentChar == ';')
		{
			CHAR_TOKEN(";", TokenType::SEMICOLON);
			PUSH_TOKEN();
			Advance();
		}
		else if (currentChar == '=')
		{
			if (Peek() == '=')
			{
				CHAR_TOKEN("==", TokenType::EQUALS);
				PUSH_TOKEN();
				Advance();
				Advance();
			}
			else
			{
				CHAR_TOKEN("=", TokenType::ASSIGNMENT);
				PUSH_TOKEN();
				Advance();
			}
		}
		else if (currentChar == '<')
		{
			if (Peek() == '=')
			{
				CHAR_TOKEN("<=", TokenType::LESS_THAN_EQUAL);
				PUSH_TOKEN();
				Advance();
				Advance();
			}
			else
			{
				CHAR_TOKEN("=", TokenType::LESS_THAN);
				PUSH_TOKEN();
				Advance();
			}
		}
		else if (currentChar == '>')
		{
			if (Peek() == '=')
			{
				CHAR_TOKEN(">=", TokenType::GREATER_THAN_EQUAL);
				PUSH_TOKEN();
				Advance();
				Advance();
			}
			else
			{
				CHAR_TOKEN("=", TokenType::GREATER_THAN);
				PUSH_TOKEN();
				Advance();
			}
		}
		else if (currentChar == '.')
		{
			CHAR_TOKEN(".", TokenType::DOT);
			PUSH_TOKEN();
			Advance();
		}
		else if (currentChar == ',')
		{
			CHAR_TOKEN(",", TokenType::COMMA);
			PUSH_TOKEN();
			Advance();
		}
		else if (currentChar == '!')
		{
			CHAR_TOKEN("!", TokenType::NOT);
			PUSH_TOKEN();
			Advance();
		}
		else if (currentChar == '"')
			tokens.push_back(GenerateString('"'));

		else if (currentChar == '\'')
			tokens.push_back(GenerateString('\''));

		else if (FILTER_NUMBER(currentChar))
			tokens.push_back(GenerateNumber());

		else if (FILTER_IDEN(currentChar))
			tokens.push_back(GenerateIdentifier());
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