#include "messageutils.h"

#include "IrcMessage.h"

#include "User.h"
#include "Channel.h"

#include <iostream>

std::string mynickuserhostname(const User* const pUser)
{
	std::string result = "";
	
	result.reserve(100);

	result += pUser->GetNickname();
	result += "!";
	result += pUser->GetUserName();
	result += "@";
	result += pUser->GetHostName();	
	return result;
}

void messagemodeutill(User* pUser, Channel* pChannel, const std::string& option, const std::string& other)
{
	IrcMessage response;
	response.SetPrefix(mynickuserhostname(pUser));
	response.SetCommand((IrcMessage::COMMAND_MODE));
	response.AddParam(pChannel->GetName());
	response.AddParam(option);
	response.AddParam(other);

	pChannel->ForwardMessage(response);
}

void messagemodeutill(User* pUser, Channel* pChannel, const std::string& option)
{
	IrcMessage response;
	response.SetPrefix(mynickuserhostname(pUser));
	response.SetCommand((IrcMessage::COMMAND_MODE));
	response.AddParam(pChannel->GetName());
	response.AddParam(option);

	pChannel->ForwardMessage(response);
}
