#include "medication.hpp"
#include "user.hpp"
#include <vector>
#include <algorithm>

class System
{
  private:
    int numUsers;
    int numMeds;
    vector<User> UserList;
    vector<Medication> MedicationList;

  public:
    int addUser(string name, fingerIdType fingerprint);
    bool removeUser(int userId, fingerIdType fingerprint);
    bool elevateUser(int userId, fingerIdType fingerIdType fingerprint);
    User &getUser(int userId);
    User &getUser(fingerIdType fingerprint);
}