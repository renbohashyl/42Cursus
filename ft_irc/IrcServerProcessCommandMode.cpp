#include "IrcServer.h"
#include "User.h"
#include "Channel.h"
#include "ParamCollection.h"

#include "IrcMessage.h"
#include "messageutils.h"
#include "errandrpl.h"

int IrcServer::processCommandMode(
		User* pUser,
		Channel* pChannel,
		const std::string& modes,
		ParamCollection::ConstIterator it,
		ParamCollection::ConstIterator endIt)
{
	bool bPlus = true;
	for (size_t pos = 0; pos < modes.size(); ++pos)
	{
		int err = 0;
		switch (modes[pos])
		{
			case '+':
				bPlus = true;
				break;
			case '-':
				bPlus = false;
				break;
			case 'i':
			{
				if (bPlus)
				{
					err = processCommandModePlusI(pUser, pChannel);
				}
				else
				{
					err = processCommandModeMinusI(pUser, pChannel);
				}
				break;
			}
			case 't':
			{
				if (bPlus)
				{
					err = processCommandModePlusT(pUser, pChannel);
				}
				else
				{
					err = processCommandModeMinusT(pUser, pChannel);
				}
				break;
			}
			case 'k':
			{
				if (bPlus)
				{
					if (it == endIt)
					{
						err = processCommandModePlusK(pUser, pChannel);
					}
					else
					{
						err = processCommandModePlusK(pUser, pChannel, *it++);
					}
				}
				else
				{
					err = processCommandModeMinusK(pUser, pChannel);
				}
				break;
			}
			case 'o':
			{
				if (bPlus)
				{
					if (it == endIt)
					{
						err = processCommandModePlusO(pUser, pChannel);
					}
					else
					{
						err = processCommandModePlusO(pUser, pChannel, *it++);
					}
				}
				else	
				{
					if (it == endIt)
					{
						err = processCommandModeMinusO(pUser, pChannel);
					}
					else
					{
						err = processCommandModeMinusO(pUser, pChannel, *it++);
					}
				}
				break;
			}
			case 'l':
			{
				if (bPlus)
				{
					if (it == endIt)
					{
						err = processCommandModePlusL(pUser, pChannel);
					}
					else
					{
						err = processCommandModePlusL(pUser, pChannel, *it++);
					}
				}
				else
				{
					err = processCommandModeMinusL(pUser, pChannel);
				}
				break;
			}
			default:
				err = processCommandModeUnknown(pUser, pChannel, modes[pos]);
				break;
		}
		if (err != ERR_NONE)
		{
			return err;
		}
	}
	return ERR_NONE;
}

int IrcServer::processCommandModePlusI(User* pUser, Channel* pChannel)
{
	messagemodeutill(pUser, pChannel, "+i");
	pChannel->SetMode(Channel::INVIE);
	return ERR_NONE;
}
int IrcServer::processCommandModePlusT(User* pUser, Channel* pChannel)
{
	messagemodeutill(pUser, pChannel, "+t");
	pChannel->SetMode(Channel::TOPIC);
	return ERR_NONE;
}
int IrcServer::processCommandModePlusK(User* pUser, Channel* pChannel)
{
	(void)pUser;
	(void)pChannel;
	//진짜아무것도안함
	return ERR_NONE;
}
int IrcServer::processCommandModePlusK(User* pUser, Channel* pChannel, const std::string& arg)
{
	const std::string psw = arg;
	
	pChannel->SetKey(psw);
	pChannel->SetMode(Channel::KEY);	

	messagemodeutill(pUser, pChannel, "+k", psw);
	return ERR_NONE;
}
int IrcServer::processCommandModePlusO(User* pUser, Channel* pChannel)
{
	(void)pUser;
	(void)pChannel;

	//암것도안한다.
	return ERR_NONE;
}
int IrcServer::processCommandModePlusO(User* pUser, Channel* pChannel, const std::string& arg)
{
	//pChannel->is
	User* const pSelectUser = pChannel->GetUserOrNull(arg);
	if (NULL == pSelectUser)
	{		
		messageErrNoSuchNick_401(mHostname, arg, pUser);
		return ERR_NONE;
	}	

	messagemodeutill(pUser, pChannel, "+o", arg);

	pChannel->AddOperator(pSelectUser);
	return ERR_NONE;
}

int IrcServer::processCommandModePlusL(User* pUser, Channel* pChannel)
{
	(void)pUser;
	(void)pChannel;

	//아무것도안함
	return ERR_NONE;
}

int IrcServer::processCommandModePlusL(User* pUser, Channel* pChannel, const std::string& arg)
{
	(void)pUser;
	(void)pChannel;
	(void)arg;

	int len = std::atoi(arg.c_str());
	if (len < 0 || len > 100)
	{
		return ERR_NONE;
	}

	messagemodeutill(pUser, pChannel, "+l", arg);

	pChannel->SetMode(Channel::LMT);
	pChannel->SetLimit(len);

	return ERR_NONE;
}

int IrcServer::processCommandModeMinusI(User* pUser, Channel* pChannel)
{
	(void)pUser;
	(void)pChannel;

	messagemodeutill(pUser, pChannel, "-i");
	pChannel->RemoveMode(Channel::INVIE);
	return ERR_NONE;
}
int IrcServer::processCommandModeMinusT(User* pUser, Channel* pChannel)
{
	(void)pUser;
	(void)pChannel;

	messagemodeutill(pUser, pChannel, "-t");
	pChannel->RemoveMode(Channel::TOPIC);
	return ERR_NONE;
}
int IrcServer::processCommandModeMinusK(User* pUser, Channel* pChannel)
{
	(void)pUser;
	(void)pChannel;

	messagemodeutill(pUser, pChannel, "-k");
	pChannel->RemoveMode(Channel::KEY);
	return ERR_NONE;
}
int IrcServer::processCommandModeMinusO(User* pUser, Channel* pChannel)
{
	(void)pUser;
	(void)pChannel;

	//아무것도안함
	return ERR_NONE;
}
int IrcServer::processCommandModeMinusO(User* pUser, Channel* pChannel, const std::string& arg)
{
	(void)pUser;
	(void)pChannel;
	(void)arg;

	User* const pSelectUser = pChannel->GetUserOrNull(arg);
	if (NULL == pSelectUser)
	{
		//nosearch user...
		messageErrNoSuchNick_401(mHostname, arg, pUser);
		return ERR_NONE;
	}

	messagemodeutill(pUser, pChannel, "-o", arg);
	pChannel->RemoveOerator(pSelectUser);
	return ERR_NONE;
}

int IrcServer::processCommandModeMinusL(User* pUser, Channel* pChannel)
{
	(void)pUser;
	(void)pChannel;

	messagemodeutill(pUser, pChannel, "-l");
	pChannel->RemoveMode(Channel::LMT);
	return ERR_NONE;
}

int IrcServer::processCommandModeUnknown(User* pUser, Channel* pChannel, char c)
{
	(void)pUser;
	(void)pChannel;

	messageErrUnKnownMode_472(mHostname, c, pUser);
	return ERR_NONE;
}
