///Verification.hpp

/**
This header file contains functions that are related to verification
    1.To mask the password entered
    2.To encrypt the password using XOR
    3.To compare two strings
    4.To verify administrator details for access
    5.To change administrator name and password upon request
**/

void Password_Hide(char *const str){//Masking entered characters
	str[0]='\0';
	int i=-1;
	cin.sync();
	char c=1;
	while(c!=13){				//till enter key is pressed
		c=getch();
		if(c!=13){
			if((c>=0&&c<=7)||(c>=9&&c<=12)||(c>=14&&c<=32)||(c>=39&&c<=47)||
               (c>=58&&c<=63)||(c>=91&&c<=96)||(c>=123&&c<=127)||c<0)
            ///ignore special char
                ;
			else{
				if(c==8){		   ///backspace
					if(i>=0){
					cout<<"\b \b";///removing last character on console
					str[i]='\0';
					i--;
					}
				}
				else {
					str[++i]=c;
					cout<<'*';
					str[i+1]='\0';///converting to string
				}
			}
		}
	}
	cout<<endl;
}

bool stringcmp(const char *const a,const char *const b){/// compares two strings
    int temp=0 , v ;
	if(strlen(a)==strlen(b)){            ///ASCII Difference of each element
		for(int i=0;a[i]&&b[i];i++){
            v= a[i]-b[i];
            if(v<0)
                v=-v;
            temp+=v;
		}
        ///if temp is non zero, unlike
		if(temp)
			return false;
        else
			return true;
	}

    ///If unequal lengths,They obviously don't match
    else
		return false;
}

void Hash( char *const str){ 		///randomizes the entered string
   for(int i=0;str[i];i++)
		str[i]=str[i]^2;	        ///XOR
}


void ChangePassword(){   		///changing  Administrator password
	char opt='n';
	char Admin[40];

	fstream f("Bin\\password.txt",ios::in|ios::out);

	if(!f)
		cout<<"\nUnable to access file";
	else{
		f.getline(Admin,40);
		system(CLEAR);
		cout<<AlignV();
		cout<<'\n'<<AlignL()<<"____________________________________________________"
            <<'\n'<<AlignL()<<"     ADMINISTRATOR PASSWORD MODIFICATION WINDOW     "
            <<'\n'<<AlignL()<<"____________________________________________________"
            <<'\n'<<AlignL()<<"\aAre you sure you want to modify password? Y/N: ";
		cin>>opt;
		cin.get();
		if(opt=='y'||opt=='Y'){
			char p_new[50];
			do{
				cout<<'\n'<<AlignL()<<"Enter the new password: ";
				cin>>p_new;
				cout<<'\n'<<AlignL()<<"Verify password "<<p_new<<" Y/N: ";
				cin>>opt;
				cin.get();
				if(opt=='y'||opt=='Y'){
					Hash(p_new);   ///Hashes the new password
					f.close();
					f.open("Bin\\password.txt",ios::out);
					f<<Admin<<endl<<p_new;
					opt='n';
				}
				else{
					cout<<'\n'<<AlignL()<<"Do you want to try again? Y/N: ";
					cin>>opt;
					cin.get();
					}
			}while(opt=='y'||opt=='Y');

		}
		f.close();
	}
}

void ChangeAdmin(){
	char Admin[40];
	char password[25];
	int count=1;
	char opt;
	system(CLEAR);
	cout<<AlignV();
	cout<<'\n'<<AlignL()<<"____________________________________________________"
        <<'\n'<<AlignL()<<"         ADMINISTRATOR NAME CHANGING WINDOW         "
        <<'\n'<<AlignL()<<"____________________________________________________"
        <<'\n'
        <<'\n'
        <<'\n'<<AlignL()<<"Are you sure you want to modify Administrator name? Y/N: ";
	cin>>opt;
	cin.get();
	if(opt=='y'||opt=='Y'){
		fstream f("Bin\\password.txt",ios::in|ios::out);
		if(!f)
			cout<<"\n\aUnable to access file";
		else{
			f.getline(Admin,40);
			f.getline(password,25);
			do{
				cout<<AlignL()<<"Enter new name: ";
				cin.getline(Admin,40);
				cout<<'\n'<<AlignL()<<"Verify "<<Admin<<" Y/N: ";
				cin>>opt;
				cin.get();
				if(opt=='y'||opt=='Y'){
					f.close();
					f.open("Bin\\password.txt",ios::out);
					f<<Admin<<'\n'<<password;
					opt='n';
				}
				else{
					cout<<'\n'<<AlignL()<<"Do you want to try again?Y/N: ";
					cin>>opt;
					cin.get();
				}
			}while(opt=='y'||opt=='Y');

			f.close();
		}
	}
	else
		cout<<'\n'<<AlignL()<<"Returning to Administrator window";
}

bool Verify(bool &login){     //To verify admin
	ifstream fin;
	ofstream fout;
	char password[25],name[40],actual_password[25],Admin[40];
	char opt;
	ifstream pass;
	pass.open("Bin\\password.txt");

	///File deleted or empty
	if(! pass.good() || pass.peek()==EOF ||pass.peek()=='\n' ||
        pass.peek()=='\r' || pass.peek()==' '|| pass.peek()=='\t')
		return false;

	pass.getline(Admin,40);

    ///Smart guy removes password alone from password.txt
	if( pass.peek()==EOF ||pass.peek()=='\n' ||
        pass.peek()=='\r' || pass.peek()==' '|| pass.peek()=='\t')
       return false ;
	pass.getline(actual_password,25);

    system(CLEAR);
    cout<<AlignV();
    cout<<'\n'<<AlignL()<<"________________________________________________"
        <<'\n'<<AlignL()<<"           ADMINISTRATOR LOGIN WINDOW           "
        <<'\n'<<AlignL()<<"________________________________________________"
        <<'\n'<<AlignL()<<"Enter the name: ";
	cin.getline(name,25);

	if(stringcmp(name,Admin)){			///if the name is admin
        int count=0;
		bool retry=true,verify=false;
		do{
            if(count)
                cout<<'\n'<<AlignL()
                    <<"________________________________________________\n";

			cout<<AlignL()<<"Enter password: ";

			Password_Hide(password);

			Hash(password);			  ///For sake of comparison

			count++;                  ///Max 3 attempts

			if(stringcmp(password,actual_password)){
				retry=false;
				verify=true;
			}

			else{
				bool Caps=GetKeyState(0x14);
                cout<<'\n'<<AlignL()<<((Caps)?"Warning ! Caps lock is on":"");
				cout<<'\n'<<AlignL()<<"Incorrect password!"
                    <<'\n'
                    <<'\n'<<AlignL()
                    <<"________________________________________________"
                    <<'\n'<<AlignL()<<"Do you want to try again Y/N: ";
				cin>>opt;
				cin.get();
				retry=(opt=='y'||opt=='Y');

				}

		}while(retry&&(count<3));
		fin.close();

       if(verify){             		///Successfully verified
			 login=true;
			 return true;
       }
       else
			 cerr<<'\n'<<AlignL()<<"\aPlease enter the correct password!";


	}
	else{
		fin.close();
		cout<<'\n'<<AlignL()<<"Invalid Name!"
            <<"\n\n"<<AlignL()<<"Press any key to continue......\n"<<AlignL();
		getch();
	}
   return false;
}

