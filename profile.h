#ifndef PROFILE_H
#define PROFILE_H
#include <string>
#include <QPixmap>

#define DEFAULT_PROFILE_PIC ":/profile/resources/Profile_avatar_placeholder_large.png"
struct profile{
    std::string user_name;
    std::string first_name;
    std::string last_name;
    std::string contactno;
    QPixmap profile_pic = QPixmap(DEFAULT_PROFILE_PIC);
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
