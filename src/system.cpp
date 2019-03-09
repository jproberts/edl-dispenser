#include "system.hpp"

User &System::getUser(int userId)
{
    for (auto const &user : UserList)
    {
        if (user.UserId = userId)
            return user;
    }
    return nullptr;
}

User &System::getUser(fingerIdType fingerprint)
{
    for (auto const &user : UserList)
    {
        if (user.Fingerprint = fingerprint)
            return user;
    }
    return nullptr;
}

int System::addUser(string name, fingerIdType fingerprint)
{
    User newUser = User(name, fingerprint);
    UserList.push_back(newUser);
    return newUser.getUserId();
}

bool System::removeUser(int userId, fingerIdType fingerprint)
{
    User admin = getUser(fingerprint);
    if (admin == nullptr || !admin.isTrusted())
        return false;
    else
        UserList.erase(remove(UserList.begin(), UserList.end(), getUser(userId)));
    return true;
}

bool System::elevateUser(int userId, fingerIdType fingerprint)
{
    User admin = getUser(fingerprint);
    User user = getUser(userId);

    if (admin == nullptr || user == nullptr)
        return false;
    else
        return user.elevateTrust(admin);
}