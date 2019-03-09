#include "user.hpp"

User::User(string name, fingerIdType fingerprint)
{
    this.Name = name;
    this.UserId = this.nextId++;
    this.Fingerprint = fingerprint;
    this.Trusted = false;
}

string User::getName(void)
{
    return this.Name;
}

int User::getUserId(void)
{
    return this.UserId;
}

bool User::isTrusted(void)
{
    return this.Trusted;
}

bool User::elevateTrust(User &admin)
{
    if (admin.isTrusted())
        this.Trusted = true;

    return this.Trusted;
}
