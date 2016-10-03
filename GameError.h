/*
Copyright (c) 2011 by Chrles Kelly
C++�� DirectX�� ���� ������ �����ϸ� ���� 2D ���� ���α׷��� ����
*/
#pragma once
#include <string>
#include <exception>
using namespace std;

namespace GameErrorDefine
{
	enum ErrorCode
	{
		FATAL_ERROR = -1,
		Caution = 1,
	};
}

class GameError : public exception
{
public:
	GameError() throw() : errorCode(GameErrorDefine::FATAL_ERROR), message("���� ������ �� �� ���� ������ �߻��߽��ϴ�.") { };
	GameError(const GameError &e) throw() : exception(e), errorCode(e.GetCode()), message(e.GetErrorMessage()) { }
	GameError(int code, const string &s) throw() : errorCode(code), message(s) { }
	GameError &operator= (const GameError &rhs) throw()
	{
		exception::operator=(rhs);
		this->errorCode = rhs.errorCode;
		this->message = rhs.message;
	}
	virtual ~GameError() throw() { };
	virtual const char* what() const throw() { return this->GetErrorMessage();  }
	const char* GetErrorMessage() const throw() { return message.c_str(); }
	int GetCode() const throw() { return errorCode;  }
private:
	int errorCode;
	string message;
};

