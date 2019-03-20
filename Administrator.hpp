///Administrator.hpp

/**
This header file contains functions that cover the possible operations required
by the administrator:
    1.Drug Management
    2.Employee management
    3.Member Management
    4.A function to create the Administrator UI

*/

void DrugManagement(const int CD,const int CM, const int CY){
	using namespace DrugOps;
	int opt;
	char ch;
	bool retry=true;

	while(retry){
        system(CLEAR);
		cout<<AlignV();
		cout<<'\n'<<AlignL();
            Div(54);
        cout<<'\n'<<AlignL()<<"               DRUG MANAGEMENT WINDOW"
            <<'\n'<<AlignL();
            Div(54);
        cout<<'\n'
            <<'\n'<<AlignL()<<"1 - Add new drug"
            <<'\n'<<AlignL()<<"2 - Delete drug"
            <<'\n'<<AlignL()<<"3 - Delete Batch"
            <<'\n'<<AlignL()<<"4 - New stock"
            <<'\n'<<AlignL()<<"5 - Change price"
            <<'\n'<<AlignL()<<"6 - Change supplier details"
            <<'\n'<<AlignL()<<"7 - View Details of a drug"
            <<'\n'<<AlignL()<<"0 - back"
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
			case 1 : Add(CD,CM,CY); break;
			case 2 : Delete();      break;
			case 3 : DeleteBatch();     break;
			case 4 : AddStock(CD,CM,CY);break;
			case 5 : ChangePrice() ;    break;
			case 6 : ChangeSupplier();  break;
			case 7 : ViewDetails();     break;
			case 0 : retry=false;       break;
			default:cout<<'\a';
		}

		if( retry==true && (opt>=0&&opt<=7) ) {
			cout<<'\n'<<AlignL()<<"Press any key to continue........."
                <<'\n'<<AlignL();
			getch();
		}
	}
}

void MemberManagement( ){
    using namespace member;
	int opt=0;
	char ch;
	bool retry=true;

	while(retry){
		system(CLEAR);
		cout<<AlignV();
		cout<<'\n'<<AlignL()<<"____________________________________________"
            <<'\n'<<AlignL()<<"          MEMBER MANAGEMENT WINDOW          "
            <<'\n'<<AlignL()<<"____________________________________________"
            <<'\n'
            <<'\n'<<AlignL()<<"1 - Add Member"
            <<'\n'<<AlignL()<<"2 - Delete member"
            <<'\n'<<AlignL()<<"3 - Modify member details"
            <<'\n'<<AlignL()<<"4 - View Details"
            <<'\n'<<AlignL()<<"5 - Search for member"
            <<'\n'<<AlignL()<<"0 - Back"
            <<'\n'
            <<'\n'<<AlignL()<<"____________________________________________"
            <<'\n'<<AlignL()<<"Enter your choice: ";
		cin>>opt;
		cin.get();

		if(!cin){
            cin.clear();
            cin.sync();
            opt=-1;
		}

		switch(opt){
			case 1 : Add();        break;
			case 2 : Delete();     break;
			case 3 : Modify();     break;
			case 4 : ViewDetails();break;
			case 5 : Search();     break;
			case 0 : retry=false;  break;
			default:cout<<'\a';
		}

		if(retry==true){
			cout<<'\n'<<AlignL()<<"Press any key to continue........."
                <<'\n'<<AlignL();
			getch();
		}
	}
}

void EmployeeManagement(){
    using namespace employee;

    using employee::ChangePassword;

    bool retry=true;
    int opt;
    while(retry){
		 system(CLEAR);
		 cout<<AlignV();
		 cout<<'\n'<<AlignL()<<"____________________________________________"
             <<'\n'<<AlignL()<<"         EMPLOYEE MANAGEMENT WINDOW         "
             <<'\n'<<AlignL()<<"____________________________________________"
             <<'\n'
             <<'\n'<<AlignL()<<"1 - Add employee"
             <<'\n'<<AlignL()<<"2 - Delete employee"
             <<'\n'<<AlignL()<<"3 - Modify employee"
             <<'\n'<<AlignL()<<"4 - Change Password"
             <<'\n'<<AlignL()<<"5 - View Details"
             <<'\n'<<AlignL()<<"0 - Back"
             <<'\n'
             <<'\n'<<AlignL()<<"____________________________________________"
             <<'\n'<<AlignL()<<"Enter your choice: ";
		 cin>>opt;
		 cin.get();
		if(!cin){
            cin.clear();
            cin.sync();
            opt=-1;
		}
		  switch(opt){
		  case 1 : Add();            break;
		  case 2 : Delete();         break;
		  case 3 : Modify();         break;
		  case 4 : ChangePassword(); break;
		  case 5 : ViewDetails();    break;
		  case 0 : retry=false;      break;
		  default: cout<<'\a';
			}
		if(retry==true&&(opt>=0&&opt<=5)){
			cout<<'\n'<<AlignL()<<"Press any key to continue........."
                    <<'\n'<<AlignL();
			getch();
			}
    }
}


void admin(bool &login, float * Disc,const int CY,const int CM, const int CD){
	int choice=0;
	bool retry=true;
	char opt;

   while(retry){
		system(CLEAR);
		cout<<AlignV();
		cout<<'\n'<<AlignL()<<"__________________________________________________"
            <<'\n'<<AlignL()<<"               Administrator Access               "
            <<'\n'<<AlignL()<<"__________________________________________________"
            <<'\n'
            <<'\n'<<AlignL()<<"0 - Home Menu"
            <<'\n'<<AlignL()<<"1 - Drug Management"
            <<'\n'<<AlignL()<<"2 - Employee Management"
            <<'\n'<<AlignL()<<"3 - Member Management"
            <<'\n'<<AlignL()<<"4 - View Daily Report"
            <<'\n'<<AlignL()<<"5 - Change admin name"
            <<'\n'<<AlignL()<<"6 - Change Password"
            <<'\n'<<AlignL()<<"7 - Discount Management"
            <<'\n'
            <<'\n'<<AlignL()<<"__________________________________________________"
            <<'\n'<<AlignL()<<"Enter your choice: ";
 		cin>>choice;
 		cin.get();

		if(!cin){
            cin.clear();
            cin.sync();
            choice=-1;
		}

		switch(choice){
            case 0 : retry=false;              break;
			case 1 : DrugManagement(CD,CM,CY); break;
			case 2 : EmployeeManagement();     break;
			case 3 : MemberManagement();       break;
			case 4 : GenerateReport(CD,CM,CY);
                     DisplayReport();          break;
			case 5 : ChangeAdmin();            break;
			case 6 : ChangePassword();         break;
			case 7 : DiscountManagement(Disc); break;
			default: cout<<'\a';
        }

      if(retry==false){
        do{
            cout<<'\n'<<AlignL()<<"Do you want to logout? Y/N: ";
            cin>>opt;
            cin.sync();
            if(opt!='y'&&opt!='Y'&&opt!='N'&&opt!='n')
                cout<<AlignL()<<"Invalid";
            }while(opt!='y'&&opt!='Y'&&opt!='N'&&opt!='n');
        login=!(opt=='y'||opt=='Y');
        }
    }
}

