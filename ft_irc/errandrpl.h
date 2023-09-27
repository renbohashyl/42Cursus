#ifndef ERR_AND_RPL_H
#define ERR_AND_RPL_H

#include <string>
#include "IrcMessage.h"


class User;
class Channel;

//
void messageSend(const std::string& serverHost, IrcMessage::eCommand command , IrcMessage& response, User* const pUser);



//ERR
void messageErrNoSuchNick_401(const std::string& serverHost, const std::string& otherName ,User* const pUser);
void messageErrNoSuchChannel_403(const std::string& serverHost, const std::string& channelName, User* const pUser);
void messageErrCanNotSendToChan_404(const std::string& serverHost, const std::string& channelName ,User* const pUser);
void messageErrTooManyChannles_405(const std::string& serverHost, User* const pUser);

//411     ERR_NORECIPIENT
       //                 ":No recipient given (<command>)"
void messageErrNoRecipent_411(const std::string& serverHost,const std::string& command, User* const pUser);

//     412     ERR_NOTEXTTOSEND
                        //":No text to send"
void messageErrNoTextToSend_412(const std::string& serverHost, User* const pUser);

void messageErrNoNicknameGiven_431(const std::string& serverHost, User* const pUser);
void messageErrNoOneusNickname_432(const std::string& serverHost, const std::string& selectName, User* const pUser);
void messageErrNickNameInUse_433(const std::string& serverHost, const std::string& selectName, User* const pUser);   

void messageErrNotOnChannel_442(const std::string& serverHost, const std::string& channelName, User* const pUser);

void messageErrNeedMoreParams_461(const std::string& serverHost, const std::string& command, User* const pUser);	
void messageErrAleadyRegisterd_462(const std::string& serverHost, User* const pUser);

void messageErrChannelIsFull_471(const std::string& serverHost, const std::string& channelName ,User* const pUser);
void messageErrUnKnownMode_472(const std::string& serverHost, const char c, User* const pUser);
void messageErrInviteOnlyChan_473(const std::string& serverHost, const std::string& channelName ,User* const pUser);
// void messageErrCanNotSendToChan_474(const std::string& serverHost, const std::string& channelName ,User* const pUser);
void messageErrBadChannelKey_475(const std::string& serverHost, const std::string& channelName ,User* const pUser);

void __messageErrIlleagleChannelName_479(const std::string& serverHost, const std::string& channelName, User* const pUser);

void messageErrPermissionDenied_481(const std::string& serverHost, User* const pUser);

void messageErrChanOprivsNeeded_482(const std::string& serverHost, const std::string& channelName, User* const pUser);

//RPL
void messageRplEndOfList_323(const std::string& serverHost, User* const pUser);

void messageRplToppic_332(const std::string& serverHost, const std::string& channelName, const std::string& topic ,User* const pUser);

void messageRplListStart_321(const std::string& serverHost, User* const pUser);

void messageRplList_322(const std::string& serverHost, Channel *channel, User* const pUser);


void messageRplChannelModeIs_324(const std::string& serverHost, Channel *channel, const std::string& mode, const std::string& modeParams ,User* const pUser);

void messageRplNoTopic_331(const std::string& serverHost, Channel *channel, User* const pUser);

    

void messageRplEndOfNames_366(const std::string& serverHost, const std::string& otherInfo, User* const pUser);
 


#endif
