///Pharmacy.cpp

#include <iostream>
#include <sstream>		///String Stream
#include <string>
#include <iomanip>		///Output alignment
#include <conio.h>		///getch()
#include <fstream>
#include <ctime>	    ///current date-time
#include <queue>		///STL Queue
#include <dirent.h>     ///directory accessing
#include <windows.h>
using namespace std;
    void SetupScreen(){
        ///EMULATING ALT + ENTER KEY PRESS
        keybd_event(VK_MENU,0x38,0,0);
        keybd_event(VK_RETURN,0x1c,0,0);
        keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
        keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
        ///SETTING COLOUR
        system("color 9F");
    }
    inline const char* AlignL(){ ///HORIZONTAL ALIGNMENT
//********ASSUMING NEW COURIER SIZE 20********
        return "\t\t\t\t\t  ";
    }
    inline const char* AlignV(){ ///VERTICAL ALIGNMENT
        return "\n\n\n\n\n\n\n\n\n\n";
    }
    inline void Div(int w){
        for(int i=0;i<w;i++)
            cout<<"_";
    }


#define CLEAR "cls"



///FUNCTION AND CLASS PROTOTYPES
#include "Prototypes.hpp"
#include "Member Management.hpp"
#include "Employee Management.hpp"
#include "Drug Management.hpp"

///CLASS DEFINITION(S)
#include "Class_Drug.hpp"
#include "Class_Member.hpp"
#include "Class_Employee.hpp"

///FUNCTION DEFINITION(S)
#include "Member Management.cpp"
#include "Employee Management.cpp"
#include "Daily Operations.hpp"
#include "Verification.hpp"
#include "Drug Management.cpp"
#include "Report.hpp"
#include "Discount Management.hpp"
#include "Administrator.hpp"
#include "Billing.hpp"



int main(int argc,char** argv){
	SetupScreen();       //Colour and full screen
	bool login=false;    //Login reqd for billing
    float Discount=0;    //Discount for every bill(default discount)

	time_t t=time(0);
	struct tm*now = localtime(&t);
	const int  CY = now->tm_year + 1900,
               CM = now->tm_mon + 1,
               CD = now->tm_mday;

	Check_For_Expiry(CD,CM,CY);

	short int opt;
	while(true){
		system(CLEAR);
		cout<<AlignV();
		cout<<'\n'<<AlignL();
                Div(54);
        cout<<'\n'<<AlignL()<<"            PHARMACY MANAGEMENT SYSTEM V3.0.6"
            <<'\n'<<AlignL();
            Div(54);
        cout<<'\n'
            <<'\n'<<AlignL()<<"1 - ADMIN ACCESS"
            <<'\n'<<AlignL()<<"2 - BILLING"
            <<'\n'<<AlignL()<<"0 - EXIT"
            <<'\n'
            <<'\n'<<AlignL();
            Div(54);
        cout<<'\n'<<AlignL()<<"Enter your choice: ";
		cin>>opt;
		cin.get();
		if(!cin){
            cin.clear();
            cin.sync();
            opt=-1;
        }
        switch(opt){
            case 1 : if( Verify ( login ) )            ///Upon verification
                        admin( login , &Discount , CY , CM , CD );
                    break;

            case 2 : Bill ( login , Discount ); break; ///to compute bill

            case 0 : return EXIT_SUCCESS; break;       ///User terminated

            default:cout<<'\a';
        }
    }
	return EXIT_FAILURE;        ///(Nearly)impossible as loop is infinite.
}


