#ifndef PROFILE_H
#define PROFILE_H
#include <string>
#include <QPixmap>

///This macro refers to default Profile pic path in Qt resourses path
#define DEFAULT_PROFILE_PIC ":/profile/resources/Profile_avatar_placeholder_large.png"
///This structure stores the information of a profile details like a global object.
/// So this will allow Every class can access the user info
struct profile{
    std::string user_name;
    std::string first_name;
    std::string last_name;
    std::string contactno;
    QPixmap profile_pic = QPixmap(DEFAULT_PROFILE_PIC);
    int id=-1;
};

///This is the state enum So,the task manager can work with respect to state.
/// This will help the App in what state it has to process.
enum STATUS{
    LOGIN_SUCCESSFUL,
    LOGIN_FAILED,

    SIGNUP_SUCCESSFUL,
    SIGNUP_FAILED,

    REGULAR_CHAT,
    GROUP_CHAT
};
#endif // PROFILE_H
