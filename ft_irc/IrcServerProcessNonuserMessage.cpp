#include "IrcServer.h"
#include "IrcMessage.h"
#include "Nonuser.h"

int IrcServer::processNonuserMessage(const IrcMessage& message, Nonuser* pNonuser)
{
	int err = ERR_NONE;
	switch (message.GetCommand())
	{
		case IrcMessage::COMMAND_PASS:
			err = processNonuserMessagePass(message, pNonuser);
			break;
		case IrcMessage::COMMAND_NICK:
			err = processNonuserMessageNick(message, pNonuser);
			break;
		case IrcMessage::COMMAND_USER:
			err = processNonuserMessageUser(message, pNonuser);
			break;
		case IrcMessage::COMMAND_QUIT:
			err = processNonuserMessageQuit(pNonuser);
		default:
			err = ERR_INVALID_MESSAGE;
			break;
	}
	return err;
}

int IrcServer::processNonuserMessagePass(const IrcMessage& message, Nonuser* pNonuser)
{
	if (message.GetParams().GetSize() == 0)
	{
		IrcMessage response;
		response.SetCommand(IrcMessage::NUMERIC_ERR_NEEDMOREPARAMS);
		response.AddParam(std::string("PASS"));
		response.AddParam(std::string("Not enoght parameters"));
		pNonuser->ForwardMessage(response);
		return ERR_NONE;
	}
	pNonuser->SetPassword(*message.GetParams().Begin());
	return ERR_NONE;
}

int IrcServer::processNonuserMessageNick(const IrcMessage& message, Nonuser* pNonuser)
{
	if (message.GetParams().GetSize() == 0)
	{
		IrcMessage response;
		response.SetCommand(IrcMessage::NUMERIC_ERR_NONICKNAMEGIVEN);
		response.AddParam(std::string("No nickname given"));
		pNonuser->ForwardMessage(response);
		return ERR_NONE;
	}
	const std::string& nickname = *message.GetParams().Begin();
	if (isValidNickname(nickname) == false)
	{
		IrcMessage response;
		response.SetCommand(IrcMessage::NUMERIC_ERR_ERRONEUSNICKNAME);
		response.AddParam(nickname);
		response.AddParam(std::string("Erroneus nickname"));
		pNonuser->ForwardMessage(response);
		return ERR_NONE;
	}
	if (mUsers.FindByNickname(nickname) != mUsers.End()
			|| mNonusers.IsReservedNickname(nickname))
	{
		IrcMessage response;
		response.SetCommand(IrcMessage::NUMERIC_ERR_NICKNAMEINUSE);
		response.AddParam(nickname);
		response.AddParam(std::string("Nickname is already in use"));
		pNonuser->ForwardMessage(response);
		return ERR_NONE;
	}
	pNonuser->SetNickname(nickname);
	if (pNonuser->IsUsernamed())
	{
		return createUser(pNonuser);
	}
	return ERR_NONE;
}

int IrcServer::processNonuserMessageUser(const IrcMessage& message, Nonuser* pNonuser)
{
	if (message.GetParams().GetSize() < 4)
	{
		IrcMessage response;
		response.SetCommand(IrcMessage::NUMERIC_ERR_NEEDMOREPARAMS);
		response.AddParam(std::string("USER"));
		response.AddParam(std::string("Not enoght parameters"));
		pNonuser->ForwardMessage(response);
		return ERR_NONE;
	}
	ParamCollection::ConstIterator it = message.GetParams().Begin();
	const std::string& username = *it;
	pNonuser->SetUsername(username);
	++it;
	//ignore mode
	++it;
	//ignore hostname
	++it;
	const std::string& realname = *it;
	pNonuser->SetRealname(realname);
	if (pNonuser->IsNicknamed())
	{
		return createUser(pNonuser);
	}
	return ERR_NONE;
}

int IrcServer::processNonuserMessageQuit(Nonuser* pNonuser)
{
	pNonuser->RegisterToFlush();
	return ERR_NONE;
}
