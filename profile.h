#ifndef PROFILE_H
#define PROFILE_H
#include <string>

struct profile{
    std::string user_name;
    std::string first_name;
    std::string last_name;
    std::string contactno;
    std::string profile_pic=":/profile/resources/Profile_avatar_placeholder_large.png";
    int id=-1;
};

enum STATUS{
    LOGIN_SUCCESSFUL,
    LOGIN_FAILED,

    SIGNUP_SUCCESSFUL,
    SIGNUP_FAILED,

    REGULAR_CHAT,
    GROUP_CHAT
};




#endif // PROFILE_H
