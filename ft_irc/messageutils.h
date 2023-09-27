#ifndef MESSAGE_UTILS_H
#define MESSAGE_UTILS_H

#include <string>

class User;
class Channel;

std::string mynickuserhostname(const User* const pUser);

void messagemodeutill(User* pUser, Channel* channel, const std::string& option, const std::string& other);
void messagemodeutill(User* pUser, Channel* channel, const std::string& option);

#endif
