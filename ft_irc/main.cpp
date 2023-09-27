#include <sstream>
#include "IrcServer.h"

enum eErr
{
	ERR_NONE = 0,
	ERR_ARGS_DIFF_NUMBER,
	ERR_ARGS_INVALID,
	ERR_LISTEN_FAIL,
	ERR_UNKNOWN
};

int parseToPort(const char* str, unsigned short* pPort)
{
	if (isdigit(*str) == false)
	{
		return ::ERR_ARGS_INVALID;
	}
	std::stringstream ss;
	ss << str;
	ss >> *pPort;
	if (ss.fail() || ss.eof() == false)
	{
		return ::ERR_ARGS_INVALID;
	}
	return ::ERR_NONE;
}

int main(int argc, char** argv)
{
	int err;

	if (argc != 3)
	{
		return ::ERR_ARGS_DIFF_NUMBER;
	}

	unsigned short port;
	err = parseToPort(argv[1], &port);
	if (err)
	{
		return ::ERR_ARGS_INVALID;
	}
	std::string password(argv[2]);

	IrcServer ircServer(port, "ft.irc", password, "superuser", "topsecret");
	err = ircServer.Run();
	if (err)
	{
		switch (err)
		{
			case IrcServer::ERR_LISTEN_FAIL:
				return ::ERR_LISTEN_FAIL;
				break;
			default:
				return ::ERR_UNKNOWN;
				break;
		}
	}

	return ::ERR_NONE;
}
