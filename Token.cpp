#include "Token.h"
#include <iostream>
#include <string>

using namespace std;

Token::Token()
{
	//token = "id";
}

void Token::checkKeyword(string lexText)
{
	map<string, string>::iterator i = keywordsToken.find(lexText);
	if (i != keywordsToken.end()) token = i->second;
	else token = "id";
}

void Token::checkOperation(string lexText)
{
	map<string, string>::iterator i = operationToken.find(lexText);
	if (i != keywordsToken.end()) token = i->second;
	else token = "BadChar";
}
//Token::Token()
//{
//	keywordsMap["begin"] = BEGIN;
//	keywordsMap["forward"] = FORWARD;
//	keywordsMap["do"] = DO;
//	keywordsMap["else"] = ELSE;
//	keywordsMap["end"] = END;
//	keywordsMap["for"] = FOR;
//	keywordsMap["function"] = FUNCTION;
//	keywordsMap["if"] = IF;
//	keywordsMap["array"] = ARRAY;
//	keywordsMap["of"] = OF;
//	keywordsMap["procedure"] = PROCEDURE;
//	keywordsMap["program"] = PROGRAM;
//	keywordsMap["record"] = RECORD;
//	keywordsMap["then"] = THEN;
//	keywordsMap["to"] = TO;
//	keywordsMap["type"] = TYPE;
//	keywordsMap["var"] = VAR;
//	keywordsMap["while"] = WHILE;
//	keywordsMap["break"] = BREAK;
//	keywordsMap["continue"] = CONTINUE;
//	keywordsMap["downto"] = DOWNTO;
//	keywordsMap["exit"] = EXIT;
//	keywordsMap["repeat"] = REPEAT;
//	keywordsMap["until"] = UNTIL;
//}

//void Token::lexemToToken(string s)
//{
//	map<string, token>::iterator i = keywordsMap.find(s);
//	if (i == keywordsMap.end())
//	{
//		tok = ID;
//	}
//	else tok = i->second;
//}

//string Token::tokenToString()
//{
//	switch (tok)
//	{
//		case ID : return "id"; break;
//		case OP : return "op"; break;
//		case BEGIN : return "begin"; break;
//		case FORWARD : return "forward"; break;
//		case DO : return "do"; break;
//		case ELSE : return "else"; break;
//		case END : return "end"; break;
//		case FOR : return "for"; break;
//		case FUNCTION : return "function"; break;
//		case IF : return "if"; break;
//		case ARRAY : return "array"; break;
//		case OF : return "of"; break;
//		case PROCEDURE : return "procedure"; break;
//		case PROGRAM : return "program"; break;
//		case RECORD : return "record"; break;
//		case THEN : return "then"; break;
//		case TO : return "to"; break;
//		case TYPE : return "type"; break;
//		case VAR : return "var"; break;
//		case WHILE : return "while"; break;
//		case BREAK : return "break"; break;
//		case CONTINUE : return "continue"; break;
//		case DOWNTO : return "downto"; break;
//		case EXIT : return "exit"; break;
//		case REPEAT : return "repeat"; break;
//		case UNTIL : return "until"; break;
//		default: return "error";
//	}
//}

