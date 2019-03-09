
#include <string>
#include "medication.hpp"
using namespace std;

typedef int fingerIdType;

class User
{
  private:
    string Name;
    int UserId;
    int Fingerprint;
    Medication *Prescriptions;
    bool Trusted;

  public:
    int addUser(string name, fingerIdType fingerprint);
    bool removeUser(int userId, fingerIdType fingerprint);
    bool elevateUser(int userId, fingerIdType fingerIdType fingerprint);
}