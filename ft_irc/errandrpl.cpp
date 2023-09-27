#include "errandrpl.h"


#include "User.h"
#include "Channel.h"
#include <iostream>

void messageSend(const std::string& serverHost, IrcMessage::eCommand command , IrcMessage& response, User* const pUser)
{
	response.SetPrefix(serverHost);
	response.SetCommand(command);	
	pUser->ForwardMessage(response);
}

//ERR_NOSUCHNICK	401
//"<nickname> :No such nick/channel"
void messageErrNoSuchNick_401(const std::string& serverHost, const std::string& otherName ,User* const pUser)
{
	IrcMessage response;
	
	response.AddParam(pUser->GetNickname());
	response.AddParam(otherName);
	response.AddParam("No such nick/channel");
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_NOSUCHNICK, response, pUser);
}

//ERR_NOSUCHCHANNEL	403
//"<channel name> :No such channel"
void messageErrNoSuchChannel_403(const std::string& serverHost, const std::string& channelName, User* const pUser)
{
	IrcMessage response;

	response.AddParam(pUser->GetNickname());
	response.AddParam(channelName);
	response.AddParam("No such channel");
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_NOSUCHCHANNEL, response, pUser);
}

//ERR_CANNOTSENDTOCHAN	404
//"<channel name> :Cannot send to channel"
void messageErrCanNotSendToChan_404(const std::string& serverHost, const std::string& channelName ,User* const pUser)
{
	IrcMessage response;

	response.AddParam(pUser->GetNickname());
	response.AddParam(channelName);
	response.AddParam("Cannot send to channel");	
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_CANNOTSENDTOCHAN, response, pUser);	
}

//405     ERR_TOOMANYCHANNELS
//"<channel name> :You have joined too many channels"
//- Sent to a user when they have joined the maximum
//number of allowed channels and they try to join
//another channel.
void messageErrTooManyChannles_405(const std::string& serverHost, User* const pUser)
{
	IrcMessage response;

	response.AddParam(pUser->GetNickname());
	response.AddParam("You have joined too many channels");
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_TOOMANYCHANNELS, response, pUser);	
}


//ERR_NORECIPIENT 411
//":No recipient given (<command>)"
void messageErrNoRecipent_411(const std::string& serverHost, const std::string& command,User* const pUser)
{
	IrcMessage response;
	std::string message = "No recipient given (";
	message += command;
	message += ")";

	response.AddParam(pUser->GetNickname());
	response.AddParam(message);
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_NORECIPIENT, response, pUser);
}


//ERR_NOTEXTTOSEND 412
//":No text to send"
void messageErrNoTextToSend_412(const std::string& serverHost, User* const pUser)
{
	IrcMessage response;

	response.AddParam(pUser->GetNickname());
	response.AddParam("No Textg to Send");	
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_NOTEXTTOSEND, response, pUser);
}


//ERR_NONICKNAMEGIVEN  431
//":No nickname given"
 //- Returned when a nickname parameter expected for a
//command and isn't found.
void messageErrNoNicknameGiven_431(const std::string& serverHost, User* const pUser)
{
	IrcMessage response;

	response.AddParam(pUser->GetNickname());
	response.AddParam("No nickname given");
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_NONICKNAMEGIVEN, response, pUser);	
}

//ERR_ERRONEUSNICKNAME  432
//"<nick> :Erroneus nickname"
//- Returned after receiving a NICK message which contains
//characters which do not fall in the defined set.  See
//section x.x.x for details on valid nicknames.
void messageErrNoOneusNickname_432(const std::string& serverHost, const std::string& selectName, User* const pUser)
{
	IrcMessage response;

	response.AddParam(pUser->GetNickname());
	response.AddParam(selectName);
	response.AddParam(std::string("Erroneus nickname"));	
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_ERRONEUSNICKNAME, response, pUser);	
}

//ERR_NICKNAMEINUSE	433
//"<nick> :Nickname is already in use"
//- Returned when a NICK message is processed that results
//in an attempt to change to a currently existing
//nickname.
void messageErrNickNameInUse_433(const std::string& serverHost, const std::string& selectName, User* const pUser)
{			
	IrcMessage response;

	response.AddParam(pUser->GetNickname());
	response.AddParam(selectName);
	response.AddParam("Nickname is already in use");
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_NICKNAMEINUSE, response, pUser);	
}

//ERR_NOTONCHANNEL 442
//"<channel> :You're not on that channel"
void messageErrNotOnChannel_442(const std::string& serverHost, const std::string& channelName, User* const pUser)
{
	IrcMessage response;

	response.AddParam(pUser->GetNickname());
	response.AddParam(channelName);
	response.AddParam("You are not on that channel");	
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_NOTONCHANNEL, response, pUser);
}


//ERR_NEEDMOREPARAMS 461
//:FTIRC 461 yoseo ::Not enough paramters
void messageErrNeedMoreParams_461(const std::string& serverHost, const std::string& command, User* const pUser)
{		
	IrcMessage response;

	

	response.AddParam(pUser->GetNickname());
	response.AddParam(command);
	response.AddParam("Not enough paramters");	

	messageSend(serverHost, IrcMessage::NUMERIC_ERR_NEEDMOREPARAMS, response, pUser);
}

//ERR_ALREADYREGISTRED 462   
//":You may not reregister"
void messageErrAleadyRegisterd_462(const std::string& serverHost, User* const pUser)
{
	IrcMessage response;
	
	response.AddParam(pUser->GetNickname());	
	response.AddParam("You may not reregister");
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_ALREADYREGISTRED, response, pUser);
}                        

//ERR_CHANNELISFULL 471
//"<channel> :Cannot join channel (+l)"
void messageErrChannelIsFull_471(const std::string& serverHost, const std::string& channelName ,User* const pUser)
{
	IrcMessage response;
	
	response.AddParam(pUser->GetNickname());
	response.AddParam(channelName);
	response.AddParam("Cannot join channel (+l)");	
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_CHANNELISFULL, response, pUser);
}



//ERR_UNKNOWNMODE 472
//"<char> :is unknown mode char to me"
void messageErrUnKnownMode_472(const std::string& serverHost, const char c ,User* const pUser)
{
	IrcMessage response;

	std::string ch = "";
	ch += c;

	response.AddParam(pUser->GetNickname());	
	response.AddParam(ch);
	response.AddParam("is unknown mode char to me");	
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_UNKNOWNMODE, response, pUser);	
}

//ERR_INVITEONLYCHAN 473
//"<channel> :Cannot join channel (+i)"
void messageErrInviteOnlyChan_473(const std::string& serverHost, const std::string& channelName ,User* const pUser)
{
	IrcMessage response;
	
	response.AddParam(pUser->GetNickname());
	response.AddParam(channelName);
	response.AddParam("Cannot join channel (+i)");
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_INVITEONLYCHAN, response, pUser);
}

//ERR_BANNEDFROMCHAN 474
//"<channel> :Cannot join channel (+b)"     
// void messageErrCanNotSendToChan_474(const std::string& serverHost, const std::string& channelName ,User* const pUser)
//{
//
//}

//475     ERR_BADCHANNELKEY
//"<channel> :Cannot join channel (+k)"
void messageErrBadChannelKey_475(const std::string& serverHost, const std::string& channelName ,User* const pUser)
{
	IrcMessage response;
	
	response.AddParam(pUser->GetNickname());
	response.AddParam(channelName);
	response.AddParam("Cannot join channel (+k)");
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_BADCHANNELKEY, response, pUser);
}

//ERR_ALREADYREGISTRED 479  
//":Illegle Channel Name"
void __messageErrIlleagleChannelName_479(const std::string& serverHost, const std::string& channelName,User* const pUser)
{
	IrcMessage response;
	
	response.AddParam(pUser->GetNickname());
	response.AddParam(channelName);
	response.AddParam("Illegle Channel Name");	
	messageSend(serverHost, IrcMessage::__NUMERIC_ERR_ILEGGLECHANNELNAME, response, pUser);
}


//ERR_NOPRIVILEGES 481
//":Permission Denied- You're not an IRC operator"
//- Any command requiring operator privileges to operate
//must return this error to indicate the attempt was
//unsuccessful.

void messageErrPermissionDenied_481(const std::string& serverHost, User* const pUser)
{
	IrcMessage response;

	response.AddParam(pUser->GetNickname());
	response.AddParam("Permission Denied- You're not an IRC operator");	
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_NOPRIVILEGES, response, pUser);
}


 //ERR_CHANOPRIVSNEEDED 482 
//"<channel> :You're not channel operator"
//- Any command requiring 'chanop' privileges (such as
//MODE messages) must return this error if the client
//making the attempt is not a chanop on the specified
//channel.
void messageErrChanOprivsNeeded_482(const std::string& serverHost, const std::string& channelName, User* const pUser)
{
	IrcMessage response;

	response.AddParam(pUser->GetNickname());
	response.AddParam(channelName);
	response.AddParam("You're not channel operator");
	messageSend(serverHost, IrcMessage::NUMERIC_ERR_CHANOPRIVSNEEDED, response, pUser);
}









/*
**RPL**
*/



//RPL_LISTSTART 321
//"Channel :Users  Name
void messageRplListStart_321(const std::string& serverHost, User* const pUser)
{
	IrcMessage response;

	response.AddParam(std::string(pUser->GetNickname()));
	response.AddParam("Channel");
	response.AddParam("Users\tName");	
	messageSend(serverHost, IrcMessage::NUMERIC_RPL_LISTSTART, response, pUser);
}

//RPL_TOPIC 332
//"<channel> :<topic>"
//- When sending a TOPIC message to determine the
//channel topic, one of two replies is sent.  If
//the topic is set, RPL_TOPIC is sent back else
//RPL_NOTOPIC.
void messageRplToppic_332(const std::string& serverHost, const std::string& channelName, const std::string& topic ,User* const pUser)
{
	IrcMessage response;

	response.AddParam(std::string(pUser->GetNickname()));
	response.AddParam(channelName);
	response.AddParam(topic);
	messageSend(serverHost, IrcMessage::NUMERIC_RPL_TOPIC, response, pUser);
}

//RPL_LIST 322
//"<channel> <# visible> :<topic>"
void messageRplList_322(const std::string& serverHost, Channel *channel, User* const pUser)
{
		
	IrcMessage response;

	response.AddParam(pUser->GetNickname());
	response.AddParam(channel->GetName());		

	//so.. #channelNam 2 :[+nit] topic
	const int userCount = channel->GetUserCount();
	char buff[20] = {};
	std::sprintf(buff, "%d", userCount);

	response.AddParam(std::string(buff));
	std::string option;
	option += "[";
	option += channel->GetChannelOption();
	option += "] ";
	option += channel->GetTopic();

	response.AddParam(option);	
	messageSend(serverHost, IrcMessage::NUMERIC_RPL_LIST, response, pUser);
}

//RPL_LISTEND 323
void messageRplEndOfList_323(const std::string& serverHost, User* const pUser)
{
	IrcMessage response;

	response.AddParam(pUser->GetNickname());	
	response.AddParam("End of /List");
	messageSend(serverHost, IrcMessage::NUMERIC_RPL_LISTEND, response, pUser);
}


//+intlk users pass
//324 RPL_CHANNELMODEIS 
//"<channel> <mode> <mode params>" 
void messageRplChannelModeIs_324(const std::string& serverHost, Channel *channel,  const std::string& mode, 
						const std::string& modeParams, User* const pUser)
{
	IrcMessage response;

	response.AddParam(pUser->GetNickname());
	response.AddParam(channel->GetName());
	response.AddParam(mode);
	response.AddParam(modeParams);
	messageSend(serverHost, IrcMessage::NUMERIC_RPL_CHANNELMODEIS, response, pUser);
}


// RPL_NOTOPIC 331
//"<channel> :No topic is set"
void messageRplNoTopic_331(const std::string& serverHost, Channel *channel, User* const pUser)
{
	IrcMessage response;

	response.AddParam(pUser->GetNickname());
	response.AddParam(channel->GetName());
	response.AddParam("No topic is set");
	messageSend(serverHost, IrcMessage::NUMERIC_RPL_NOTOPIC, response, pUser);
}

    

//RPL_ENDOFNAMES 366
void messageRplEndOfNames_366(const std::string& serverHost, const std::string& otherInfo, User* const pUser)
{
	IrcMessage response;		

	response.AddParam(pUser->GetNickname());
	response.AddParam(otherInfo);
	response.AddParam("End of /NAMES list.");
	messageSend(serverHost, IrcMessage::NUMERIC_RPL_ENDOFNAMES, response, pUser);
}
