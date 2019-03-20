///Prototypes.hpp

class Member;
class Employee;
class Drug;
class BillData;


int main(int,char**);

//DAILY OPERATION
void SortDrug(fstream &f);
void CheckExpiry (const int,const int,const int,fstream&);
void Check_For_Expiry (const int,const int,const int);

//ADMINISTRATOR
void admin(bool&,float*,const int,const int,const int);

void Membership (char *const, int& , float&);

void GenerateReport (const int,const int,const int);
void DisplayReport ();

void EmployeeManagement();

void SetDiscount (float*);
void ModifyDiscount (float*);
void ResetDiscount (float*);

void DiscountManagement (float*);
//END OF ADMINISTRATOR

//VERIFICATION
void verify (bool&);
void Password_Hide (char*const );
bool stringcmp (const char*const ,const char*const );
void Hash (char*const );
void ChangePassword();
void ChangeAdmin();
//END OF VERIFICAION

//BILLING
void Bill (bool&);
bool Process_Bill(const char* const,int&,double,queue<BillData> &bill,bool&);
void UpdateReport (float ,int);

//END OF BILLING

