///Class_Employee

class Employee{
private:
	char name[30];
	unsigned short int eno,age;
	char ph[11];
	char password[25];

public:
	Employee(){
		eno=age=0;
		password[0]=name[0]=ph[0]='\0';
		}
	Employee(int x){
		eno=x;
		password[0]=name[0]=ph[0]='\0';
	}

	int geteno(){
		 return eno;
		}

	void Delete(){
		eno=0;
	}

	void accept(bool x=true){
		cout<<'\n'<<AlignL()<<"Enter name(MAX 30): ";
		cin.getline(name,30);
		do{
            cout<<'\n'<<AlignL()<<"Enter age(>15): ";
            cin>>age;
            cin.get();

            if(!cin){
                cin.clear();
                cin.ignore();
                age=-1;
            }

            if(age<15)
                cout<<AlignL()<<"Invalid!";
		}while(age<15);

        cout<<'\n'<<AlignL()<<"Enter Phone No.: ";

        short int i=-1;
        char ch='\0';
        while(i<9){
            ch=getch();
            if(ch>='0'&&ch<='9'){
                cout<<ch;
                ph[++i]=ch;
                }
            else if(ch==8&&i>=0){
                i--;
                cout<<"\b \b";
                }
        }
        cin.get();
        ph[10]='\0';


		cout<<'\n'<<AlignL()<<"Enter password (MAX 25): ";
		cin.getline(password,25);
		if(x)
			cout<<AlignL()<<"Your unique Employee number is: "<<eno;
	}



	void Display(){
		cout<<'\n'<<AlignL()<<"Name: "<<name<<"   Age: "<<age<<" Employee no: "<<eno
                            <<" Phone: "<<ph<<" Password: "<<password;
	}

	bool check(){
		char opt='Y';
		char pass[25];
		bool r=false;
		while(opt=='y'||opt=='Y'){
			cout<<AlignL()<<"Enter password: ";
			Password_Hide(pass);
			if(stringcmp(pass,password)){
				opt='n';
				r=true;
			}
			else{
				do{
				cout<<'\n'<<AlignL()<<"Do you want to try again? Y/N: ";
				cin>>opt;
				cin.sync();
					}while(!(opt=='y'||opt=='n'||opt=='Y'||opt=='N'));
			}
		}

	return r;
	}
	void Change_Password(){
		if(check()){
			cout<<'\n'<<AlignL()<<"Enter new password(MAX 25): ";
			cin.getline(password,25);
			cin.sync();
			}
		else
			cout<<'\n'<<AlignL()<<"Please try again!";
	}

};


