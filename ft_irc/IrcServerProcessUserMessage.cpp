#include "IrcServer.h"
#include "IrcMessage.h"

#include "yoseoutil.h"

#include "errandrpl.h"
#include "messageutils.h"

#include "User.h"
#include "Channel.h"

#include <iostream>

//https://datatracker.ietf.org/doc/html/rfc1459
int IrcServer::processUserMessage(const IrcMessage& message, User* pUser)
{
	int err;
	switch (message.GetCommand())
	{
		case IrcMessage::COMMAND_PASS:
			err = processUserMessagePass(message, pUser);
			break;
		case IrcMessage::COMMAND_NICK:
			err = processUserMessageNick(message, pUser);
			break;
		case IrcMessage::COMMAND_USER:
			err = processUserMessageUser(message, pUser);
			break;
		case IrcMessage::COMMAND_QUIT:
			err = processUserMessageQuit(message, pUser);
			break;
		case IrcMessage::COMMAND_JOIN:
			err = processUserMessageJoin(message, pUser);
			break;
		case IrcMessage::COMMAND_PART:
			err = processUserMessagePart(message, pUser);
			break;
		case IrcMessage::COMMAND_MODE:
			err = processUserMessageMode(message, pUser);
			break;
		case IrcMessage::COMMAND_TOPIC:
			err = processUserMessageTopic(message, pUser);
			break;
		case IrcMessage::COMMAND_INVITE:
			err = processUserMessageInvite(message, pUser);
			break;
		case IrcMessage::COMMAND_KICK:
			err = processUserMessageKick(message, pUser);
			break;
		case IrcMessage::COMMAND_PRIVMSG:
			err = processUserMessagePrivmsg(message, pUser);
			break;
		case IrcMessage::COMMAND_LIST:
			err = processUserMessageList(message, pUser);
			break;
		case IrcMessage::COMMAND_PING:
			err = processUserMessagePing(pUser);
			break;
		case IrcMessage::COMMAND_NAMES:
			err = processUserMessageNames(message, pUser);
			break;
		default:
			err = ERR_INVALID_MESSAGE;
			break;
	}
	return err;
}

//Command: NAMES
//Parameters: [<channel>{,<channel>}]
//RPL_NAMREPLY RPL_ENDOFNAMES
int IrcServer::processUserMessageNames(const IrcMessage& message, User* pUser)
{
	ParamCollection::ConstIterator paramIter = message.GetParams().Begin();
	std::vector<std::string> recives;
	recives.reserve(100);

	if (paramIter == message.GetParams().End())
	{
		messageRplEndOfNames_366(mHostname, "*", pUser);
		return ERR_NONE;
	}

	const std::string &channelName = *paramIter;
	
	Channel *channel = pUser->GetChannelOrNullByName(channelName);

	if (NULL != channel)
	{
		// 353 RPL_NAMREPLY
		IrcMessage response2;
		std::string usersSep("");
		
		usersSep += channel->GetUsersSepSpace(pUser);
		response2.SetPrefix(mHostname);
		response2.SetCommand(IrcMessage::NUMERIC_RPL_NAMREPLY);
		response2.AddParam(pUser->GetNickname());
		response2.AddParam("=");
		response2.AddParam(channelName);
		response2.AddParam(usersSep);
		pUser->ForwardMessage(response2);		
	}

	messageRplEndOfNames_366(mHostname, channelName, pUser);
	return ERR_NONE;
}

// Command: PASS
// Parameters: <password>
int IrcServer::processUserMessagePass(const IrcMessage& message, User* pUser)
{
	const size_t paramsCount = message.GetParams().GetSize();
	if (paramsCount < 1)
	{
		messageErrNeedMoreParams_461(mHostname, "PASS", pUser);		
	}	
	else
	{		
		messageErrAleadyRegisterd_462(mHostname, pUser);
	}

	return ERR_NONE;
}



//Command: USER
//Parameters: <username> <hostname> <servername> <realname>
//Numeric Replies: ERR_NEEDMOREPARAMS ERR_ALREADYREGISTRED         
int IrcServer::processUserMessageUser(const IrcMessage& message, User* pUser)
{
	const size_t paramsCount = message.GetParams().GetSize();
	
	if (paramsCount < 4)	
	{
		messageErrNeedMoreParams_461(mHostname, "USER", pUser);
	}			
	else
	{
		messageErrAleadyRegisterd_462(mHostname, pUser);		
	}

	return ERR_NONE;
}




//ERR_NICKCOLLISION(server to server) X
//Command: NICK
//Parameters: <nickname>
//ERR_NONICKNAMEGIVEN, ERR_ERRONEUSNICKNAME, ERR_NICKNAMEINUSE
int IrcServer::processUserMessageNick(const IrcMessage& message, User* const pUser)
{
	ParamCollection::ConstIterator paramIter = message.GetParams().Begin();
	const std::string& selectName = *paramIter;

	if ( message.GetParams().End() == paramIter)
	{
		messageErrNoNicknameGiven_431(mHostname, pUser);
	}
	else if (pUser->GetNickname() == selectName)
	{
		//내가 내이름으로 바꾸려하면 아무것도안함
	}
	else if (false == isValidNickname(selectName))
	{
		messageErrNoOneusNickname_432(mHostname, selectName, pUser);
	}
	else if(mUsers.End() != mUsers.FindByNickname(selectName))
	{		
		messageErrNickNameInUse_433(mHostname, selectName, pUser);
	}	
	else
	{
		IrcMessage response;
			
		response.SetPrefix(mynickuserhostname(pUser));
    	response.SetCommand(IrcMessage::COMMAND_NICK);
		response.AddParam(selectName);
		pUser->SetNickName(selectName);
		if (IrcServer::ERR_NONE != pUser->ForwardMessageFriendsAndMe(response))
		{
			return IrcServer::ERR_USERS_FAIL;
		}
	}
	return ERR_NONE;
}




//ERR_NOSUCHSERVER RPL_LISTSTART
//RPL_LIST RPL_LISTEND
int IrcServer::processUserMessageList(const IrcMessage& message, User* pUser)
{
	(void)message;

	ChannelCollection::Iterator channelIter = mChannels.Begin();

	messageRplListStart_321(mHostname, pUser);
	for (; channelIter != mChannels.End(); )
	{
		messageRplList_322(mHostname, *channelIter, pUser);
		++channelIter;
	}
	messageRplEndOfList_323(mHostname ,pUser);
	return ERR_NONE;
}

//ERR_BADCHANMASK  X
//Command: KICK
//Parameters: <channel> <user> [<comment>]
//ERR_NEEDMOREPARAMS 461 ERR_NOSUCHCHANNEL 403
//ERR_CHANOPRIVSNEEDED 482
//ERR_NOTONCHANNEL 442
int IrcServer::processUserMessageKick(const IrcMessage& message, User* pUser)
{
	ParamCollection::ConstIterator iterator = message.GetParams().Begin();
	if (iterator == message.GetParams().End())
	{		
		messageErrNeedMoreParams_461(mHostname, "KICK", pUser);
		return ERR_NONE;
	}
	const std::string& channelName = *iterator;

	++iterator;
	if (iterator == message.GetParams().End())
	{		
		messageErrNeedMoreParams_461(mHostname, "KICK", pUser);
		return ERR_NONE;
	}
	const std::string& nickName = *iterator;
	
	ChannelCollection::Iterator channelIter = mChannels.FindByName(channelName);
	if (channelIter == mChannels.End())	
	{		
		messageErrNoSuchChannel_403(mHostname, channelName, pUser);
		return ERR_NONE;
	}
		
	User* const pChannelUser = (*channelIter)->GetUserOrNull(nickName);
	if (NULL ==  pChannelUser)
	{				
		messageErrNotOnChannel_442(mHostname, channelName, pUser);
		return ERR_NONE;
	}
	
	if (false == (*channelIter)->IsOperator(pUser))
	{
		messageErrChanOprivsNeeded_482(mHostname, channelName, pUser);
		return ERR_NONE;
	}

	IrcMessage response;
	response.SetPrefix(mynickuserhostname(pUser));
	response.SetCommand(IrcMessage::COMMAND_KICK);
	response.AddParam(channelName);
	response.AddParam(pChannelUser->GetNickname());

	++iterator;
	if (iterator != message.GetParams().End())
	{
		response.AddParam(*iterator);	//[commment]
	}

	(*channelIter)->ForwardMessage(response);

	(*channelIter)->RemoveUser(pChannelUser);
	return ERR_NONE;
}



//Command: PART
//Parameters: <channel>{,<channel>}
//Numeric Replies: ERR_NEEDMOREPARAMS ERR_NOSUCHCHANNEL ERR_NOTONCHANNEL            
int IrcServer::processUserMessagePart(const IrcMessage& message, User* pUser)
{
	ParamCollection::ConstIterator paramIter = message.GetParams().Begin();
	std::vector<std::string> recives;
	recives.reserve(100);

	if (paramIter == message.GetParams().End())
	{
		messageErrNeedMoreParams_461(mHostname, "PART", pUser);
		return ERR_NONE;
	}
	splitString(*paramIter, ',', &recives);

	for (size_t i = 0; i < recives.size(); ++i)
	{
		const std::string &channelName = recives[i];
		Channel *channel = pUser->GetChannelOrNullByName(channelName);

		if (mChannels.FindByName(channelName) == mChannels.End())
		{
			messageErrNoSuchChannel_403(mHostname, channelName, pUser);
		}
		else if (NULL == channel)
		{
			messageErrNotOnChannel_442(mHostname, channelName, pUser);
		}
		else
		{
			IrcMessage response;
			response.SetPrefix(mynickuserhostname(pUser));
			response.SetCommand(IrcMessage::COMMAND_PART);
			response.AddParam(std::string(channelName));

			channel->ForwardMessage(response);
			channel->RemoveUser(pUser);
		}
	}
	return ERR_NONE;
}


//ERR_NOTOPLEVEL ERR_WILDTOPLEVEL X 
//Command: PRIVMSG
//Parameters: <receiver>{,<receiver>} <text to be sent>
//ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
//ERR_CANNOTSENDTOCHAN
//ERR_NOSUCHNICK
int IrcServer::processUserMessagePrivmsg(const IrcMessage& message, User* pUser)
{
	IrcMessage str = message;

	ParamCollection::ConstIterator paramIter = message.GetParams().Begin();	
	if (paramIter == message.GetParams().End())
	{		
		messageErrNoRecipent_411(mHostname, "PRIVMSG", pUser);
		return ERR_NONE;
	}
	
	std::vector<std::string> recives;
	recives.reserve(100);
	splitString(*paramIter, ',', &recives);

	++paramIter;
	if (paramIter == message.GetParams().End() || recives.empty())
	{		
		messageErrNoTextToSend_412(mHostname, pUser);
		return ERR_NONE;
	}
	const std::string &sendMessage = *paramIter;

	for (size_t i = 0; i < recives.size(); ++i)
	{
		char flag = recives[i][0];
		switch (flag)
		{
		case '$':
			// Server  고성능 확성기			
			break;
		case '#':
		case '&':
		{			
			ChannelCollection::Iterator channelIter = mChannels.FindByName(recives[i]);
			if (channelIter != mChannels.End())
			{
				const std::string &channelName = (*channelIter)->GetName();

				if (NULL == (*channelIter)->GetUserOrNull(pUser->GetNickname()))
				{
					messageErrCanNotSendToChan_404(mHostname, channelName, pUser);
				}				
				else //+n option X
				{
					IrcMessage response;

					response.SetPrefix(mynickuserhostname(pUser));
					response.SetCommand(IrcMessage::COMMAND_PRIVMSG);
					response.AddParam(channelName);
					response.AddParam(sendMessage);
					(*channelIter)->ForwardMessageExceptFor(response, *pUser);
				}
			}
			else
			{
				messageErrNoSuchNick_401(mHostname, recives[i], pUser);
			}
		}		
		break;
		default:
		{
			// User
			UserCollection::Iterator userIter = mUsers.FindByNickname(recives[i]);
			if (userIter != mUsers.End())
			{
				IrcMessage response;

				response.SetPrefix(mynickuserhostname(pUser));
				response.SetCommand(IrcMessage::COMMAND_PRIVMSG);
				response.AddParam((*userIter)->GetNickname());
				response.AddParam(sendMessage);
				(*userIter)->ForwardMessage(response);
			}
			else
			{
				messageErrNoSuchNick_401(mHostname, recives[i], pUser);
			}
		}
		break;
		}
	}

	return ERR_NONE;
}



//ERR_BANNEDFROMCHAN

/*
ERR_BADCHANMASK ERR_BADCHANNELKEY
*/
//Command: JOIN
//Parameters: <channel>{,<channel>} [<key>{,<key>}]
//ERR_NEEDMOREPARAMS   
//ERR_INVITEONLYCHAN   
//ERR_CHANNELISFULL    
//ERR_NOSUCHCHANNEL
//ERR_TOOMANYCHANNELS
//RPL_TOPIC
int IrcServer::processUserMessageJoin(const IrcMessage& message, User* const pUser)
{
	//need fix
	const int maxChannelCount = 10;

	ParamCollection::ConstIterator channelNameIter = message.GetParams().Begin();
	if (pUser->GetChannelCount() >= maxChannelCount)
	{
		messageErrTooManyChannles_405(mHostname, pUser);
		return ERR_NONE;
	}
	else if (channelNameIter == message.GetParams().End())
	{		
		messageErrNeedMoreParams_461(mHostname, "JOIN", pUser);
		return ERR_NONE;
	}

	//콤마제거햇는데 아무것도없으면
	std::vector<std::string> channelNames;
	channelNames.reserve(100);
	splitString(*channelNameIter, ',', &channelNames);

	if (channelNames.empty())	
	{		
		return ERR_NONE;
	}

	//password split
	++channelNameIter;
	ParamCollection::ConstIterator channelpasswordIter = channelNameIter;
	std::vector<std::string> channelPasswords;
	channelPasswords.reserve(100);

	if (channelpasswordIter != message.GetParams().End())
	{
		splitString(*channelpasswordIter, ',', &channelPasswords);				
	}	
	const int diffLen = channelNames.size() - channelPasswords.size();

	for (int i = 0; i < diffLen; ++i)
	{
		channelPasswords.push_back("");
	}

	for (size_t i = 0; i < channelNames.size(); ++i)
	{		
		const std::string& channelName = channelNames[i];
		const std::string& channelPassword = channelPasswords[i];

		ChannelCollection::Iterator channelIter = mChannels.FindByName(channelName);

		if (false == isValidChannelname(channelName))
		{
			//ielgle test
			__messageErrIlleagleChannelName_479(mHostname, channelName, pUser);			
			continue;
		}
		if (mChannels.End() == channelIter)
		{			
			Channel* channel = mChannels.CreateChannel(channelName, pUser);
			messageChannelHelloWorld(message, pUser, channel);
			continue;	
		}		
		if ((*channelIter)->IsUser(pUser))
		{			
			//이미 참가중인 채널 이라면?? 아무것도안함
			continue;
		}
		if ((*channelIter)->IsLimitMode())
		{			
			
			//풀방임...
			if ((*channelIter)->IsFull())
			{
				messageErrChannelIsFull_471(mHostname, channelName, pUser);
				continue;
			}
		}		
		if ((*channelIter)->IsInviteMode())
		{			
			//초대장없었네...
			if (false == (*channelIter)->IsInviteUser(pUser))
			{
				messageErrInviteOnlyChan_473(mHostname, channelName, pUser);
				continue;
			}
		}		
		if ((*channelIter)->IsKeyeMode())
		{			
			//패스워드가틀리네			
			if (false == (*channelIter)->IsKeySame(channelPassword))
			{
				messageErrBadChannelKey_475(mHostname, channelName, pUser);
				continue;
			}
		}		

		//입장가능!
		(*channelIter)->AddUser(pUser);
		messageChannelHelloWorld(message, pUser, *channelIter);
	}
	return ERR_NONE;
}	

//Command: QUIT
//Parameters: [<Quit message>]
//Numeric Replies: NONE
int IrcServer::processUserMessageQuit(const IrcMessage& message, User* pUser)
{
	IrcMessage response;
	std::string reazon("<No reason supplied>");

	response.SetPrefix(mynickuserhostname(pUser));
	response.SetCommand(IrcMessage::COMMAND_QUIT);

	ParamCollection::ConstIterator paramIter = message.GetParams().Begin();
	if (paramIter != message.GetParams().End())
	{
		reazon = *paramIter;
	}

	response.AddParam(reazon);
	pUser->ForwardMessageFriends(response);
	mUsers.RegisterToFlush(pUser);
	return ERR_NONE;
}



//itkol
//-i-i
int IrcServer::processUserMessageMode(const IrcMessage& message, User* pUser)
{
	ParamCollection::ConstIterator paramIter = message.GetParams().Begin();
	if (paramIter == message.GetParams().End())	
	{
		messageErrNeedMoreParams_461(mHostname, "MODE", pUser);
		return ERR_NONE;
	}

	if (mUsers.FindByNickname(*paramIter) != mUsers.End())
	{
		return ERR_NONE;		
	}

	ChannelCollection::Iterator channelIter =  mChannels.FindByName(*paramIter);
	if (channelIter == mChannels.End())
	{
		messageErrNoSuchChannel_403(mHostname, *paramIter, pUser);
		return ERR_NONE;
	}
	//valid channel!

	Channel* const channel = *channelIter;

	//is valid option?
	++paramIter;	
	if (paramIter == message.GetParams().End())
	{
		std::string modeParams("");
		if (channel->IsOperator(pUser))
		{
			modeParams += channel->GetOperatorModePrams();			 
		}
		else
		{
			modeParams += channel->GetModePrams();
		}
	
		messageRplChannelModeIs_324(mHostname, channel, channel->GetChannelOption(), modeParams, pUser);		
		return ERR_NONE;
	}

	//valid option!
	if (false == channel->IsOperator(pUser))
	{		
		messageErrChanOprivsNeeded_482(mHostname, channel->GetName(), pUser);
		return ERR_NONE;
	}

	const std::string modeOption = *paramIter;

	++paramIter;
	return processCommandMode(pUser, channel, modeOption, paramIter, message.GetParams().End());
}



int IrcServer::processUserMessageTopic(const IrcMessage& message, User* pUser)
{
	ParamCollection::ConstIterator iterator = message.GetParams().Begin();
	if (iterator == message.GetParams().End())
	{
		messageErrNeedMoreParams_461(mHostname, "TOPIC", pUser);
		return ERR_NONE;
	}
	
	const std::string& channelName = *iterator;	
	ChannelCollection::Iterator channelIter = mChannels.FindByName(channelName);
	if (channelIter == mChannels.End())	
	{
		messageErrNoSuchChannel_403(mHostname, channelName, pUser);
		return ERR_NONE;
	}

	++iterator;	
	if (iterator == message.GetParams().End())
	{		
		if ((*channelIter)->GetTopic().length() == 0)
		{
			messageRplNoTopic_331(mHostname, (*channelIter), pUser);
		}
		else
		{
			messageRplToppic_332(mHostname, channelName, (*channelIter)->GetTopic(), pUser);		
		}		
	}	
	else if (false == (*channelIter)->IsUser(pUser)) 	//채널에접속중도아닌데 토픽바꾸려고함
	{
		messageErrNotOnChannel_442(mHostname, channelName, pUser);		
	}
	else if((*channelIter)->IsTopicMode() == true && (*channelIter)->IsOperator(pUser) == false)
	{	
		messageErrChanOprivsNeeded_482(mHostname, channelName, pUser);		
	}
	else
	{
		const std::string& topic = *iterator;

		IrcMessage response;

		response.SetPrefix(mynickuserhostname(pUser));
		response.SetCommand(IrcMessage::COMMAND_TOPIC);
		response.AddParam(channelName);
		response.AddParam(topic);

		(*channelIter)->ForwardMessage(response);
		(*channelIter)->SetTopic(topic);	
	}

	return ERR_NONE;
}



//Invite Segment Fault 있음
int IrcServer::processUserMessageInvite(const IrcMessage& message, User* pUser)
{		
	ParamCollection::ConstIterator iterator = message.GetParams().Begin();
	


	if (iterator == message.GetParams().End())
	{
		//파라미터부족
		messageErrNeedMoreParams_461(mHostname, "INVITE", pUser);
		return ERR_NONE;
	}

	const std::string& nickName = *iterator;
	
	++iterator;
	if (iterator == message.GetParams().End())
	{
		//파라미터부족
		messageErrNeedMoreParams_461(mHostname, "INVITE", pUser);
		return ERR_NONE;

	}
	UserCollection::Iterator userIter = mUsers.FindByNickname(nickName);	
	const std::string& channelName = *iterator;



	if (userIter == mUsers.End())	
	{		
		messageErrNoSuchNick_401(mHostname, nickName, pUser);
		return ERR_NONE;
	}

	
	ChannelCollection::Iterator channelIter = mChannels.FindByName(channelName);
	if (channelIter == mChannels.End())	
	{	
		messageErrNoSuchChannel_403(mHostname, channelName, pUser);
		return ERR_NONE;
	}

	//내가 해당 채널에 접속중인가
	if (NULL == (*channelIter)->GetUserOrNull(pUser->GetNickname()))	
	{
		messageErrNotOnChannel_442(mHostname, channelName, pUser);		
		return ERR_NONE;
	}

	//내가 채널 관리자인가
	if (false == (*channelIter)->IsOperator(pUser))
	{
		//482 you are not channel operaotr
		messageErrChanOprivsNeeded_482(mHostname, channelName, pUser);;
		return ERR_NONE;
	}

	//초대메세지
	IrcMessage response;

	response.SetPrefix(mynickuserhostname(pUser));
	response.SetCommand(IrcMessage::COMMAND_INVITE);
	response.AddParam((*userIter)->GetNickname());
	response.AddParam((*channelIter)->GetName());

	(*userIter)->ForwardMessage(response);
	(*channelIter)->AddInviteUser(*userIter);

	IrcMessage response2;

	//341     RPL_INVITING
	//"<channel> <nick>"
	response2.SetPrefix(mHostname);
	response2.SetCommand(IrcMessage::NUMERIC_RPL_INVITING);
	response2.AddParam(pUser->GetNickname());
	response2.AddParam((*userIter)->GetNickname());
	response2.AddParam((*channelIter)->GetName());
	pUser->ForwardMessage(response2);
	return ERR_NONE;	
}	

int IrcServer::messageChannelHelloWorld(const IrcMessage& message, User* pUser, Channel* channel)
{	
	(void)message;

	const std::string channelName = channel->GetName();

	IrcMessage response;

	//유저들한테 접속알리기	JOIN
	response.SetPrefix( mynickuserhostname(pUser) );
	response.SetCommand(IrcMessage::COMMAND_JOIN);
	response.AddParam(std::string(channelName));
	channel->ForwardMessage(response);

	//topic
	if (channel->GetTopic().length() != 0)
	{
		messageRplToppic_332(mHostname, channelName, channel->GetTopic(), pUser);
	}

	//353 RPL_NAMREPLY
	IrcMessage response2;
	std::string usersSep("");

	usersSep += channel->GetUsersSepSpace(pUser);
	response2.SetPrefix(mHostname);
	response2.SetCommand(IrcMessage::NUMERIC_RPL_NAMREPLY);
	response2.AddParam(pUser->GetNickname());
	response2.AddParam("=");
	response2.AddParam(channelName);			
	response2.AddParam(usersSep);
	pUser->ForwardMessage(response2);	

	messageRplEndOfNames_366(mHostname, channelName, pUser);
	
	return ERR_NONE;
}

int IrcServer::processUserMessagePing(User* pUser)
{
	IrcMessage pong;
	pong.SetPrefix(mHostname);
	pong.SetCommand(IrcMessage::COMMAND_PONG);
	pong.AddParam(mHostname);
	pUser->ForwardMessage(pong);
	return ERR_NONE;
}
