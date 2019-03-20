///ReadBill.cpp

/**
This program is used to read and display the bill generated to the customer
    @param argc : No.of parameters passed
    @param argv : ptr to 2-D array of Parameters of which one is
                  default ie the location of the executable and
                  the second string is location of bill file
                  passed by Display bill method in billing.h
*/
#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdlib.h>
using namespace std;
   inline const char* AlignL(){ ///HORIZONTAL ALIGNMENT
       //ASSUMING NEW COURIER SIZE 20
        return "\t\t\t\t\t  ";
    }
   inline const char* AlignV(){ ///VERTICAL ALIGNMENT
        return "\n\n\n\n\n\n\n\n\n";
    }

int main(int argc,char **argv){
	char ch;

	if(argc<2)///No argument passed
        return -1;

	ifstream f( argv[1] );
	if(!f)
		return -1;

	cout<<AlignV()<<AlignL();

	while(f.read(&ch,1)){
		cout<<ch;
		if(ch=='\n')
            cout<<AlignL();
	}
	f.close();
	cout<<'\n'<<AlignL()<<"Press any key to continue......";
	getch();

}
