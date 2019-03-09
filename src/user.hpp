
#include <string>
#include <vector>
#include "medication.hpp"

using namespace std;

typedef int fingerIdType;

class User
{
  private:
    static int nextId;
    string Name;
    int UserId;
    fingerIdType Fingerprint;
    vector<Medication> Prescriptions;
    bool Trusted;

  public:
    string getName(void);
    int getUserId(void);
    bool isTrusted(void);
    bool elevateTrust(User &admin);
}