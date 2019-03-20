///Employee Management.cpp

void employee::Add(){
    system(CLEAR);
    cout<<AlignV();

    cout<<'\n'<<AlignL();
        Div(55);
    cout<<'\n'<<AlignL()<<"               EMPLOYEE ADDITION WINDOW"
        <<'\n'<<AlignL();
        Div(55);

    int eno=0,count=0;
    char opt='\0';
    Employee e;
    unsigned int nor;
    bool retry=true;

    fstream GetMemno("Bin\\Employee Count.bin",ios::binary|ios::in|ios::out);

    if(!GetMemno)
        cout<<'\n'<<AlignL()<<"\aUnable to add employee!";
    else{
        cout<<'\n'<<AlignL()
                  <<"Are you sure you want to add a new employee? Y/N: ";
        cin>>opt;
        cin.sync();
        if(opt=='y'||opt=='Y'){
            ifstream fin("Bin\\Employees.dat",ios::binary);
            if(!fin)
                cout<<'\n'<<AlignL()<<"Unable to add employee";
            else{

                fin.seekg(0L,ios::end);
                nor = fin.tellg()/sizeof(Employee);
                fin.seekg(0L);

                fin.read((char*)&e,sizeof(Employee));
                while(!fin.eof()&&retry==true){
                    eno++;
                    if(e.geteno()==0)
                        retry=false;
                    fin.read((char*)&e,sizeof(Employee));
                    }
                fin.close();
                GetMemno.read((char*)&count,sizeof(int));
                fstream f("Bin\\Employees.dat",ios::binary|ios::in|ios::out);
                if(!f)
                    cout<<'\n'<<AlignL()<<"\aUnable to add Employee";
                else{
                    if(eno<nor&&eno!=0){//for rewriting a DELETED EMPLOYEE
                        count++;
                        Employee e(eno);
                        e.accept();
                        f.seekp((long)(eno-1)*sizeof(Employee),ios::beg);
                        f.write((char*)&e,sizeof(Employee));

                        cout<<'\n'<<AlignL()<<"nSuccessfully added employee!";
                        }
                    else{          //creating new employee
                        count++;
                        Employee e(count);
                        e.accept();
                        f.seekp(0L,ios::end);
                        f.write((char*)&e,sizeof(Employee));

                        cout<<'\n'<<AlignL()<<"Successfully added employee!";
                        }
                    f.close();
                    }

                GetMemno.seekp(0L);
                GetMemno.write((char*)&count,sizeof(int));
                }
        }
        else
            cout<<'\n'<<AlignL()<<"Returning to Employee Management window";

    GetMemno.close();
    }
}





void employee::Delete(){
    int eno;
    long recPos;
    char opt;
    fstream f("Bin\\Employees.dat",ios::binary|ios::in|ios::out);
    if(!f)
        cout<<'\n'<<AlignL()<<"aError Accessing the file";
    else{
        system(CLEAR);
        cout<<AlignV();

        cout<<'\n'<<AlignL();
            Div(52);
        cout<<'\n'<<AlignL()<<"              EMPLOYEE DELETION WINDOW"
            <<'\n'<<AlignL();
            Div(52);

        Employee e;

        cout<<'\n'<<AlignL()<<"Enter employee number: ";
        cin>>eno;
        cin.get();
        if(!cin){
            cin.clear();
            cin.sync();
            eno=-1;
        }
        if(eno>0){
            recPos=(long)(eno-1)*sizeof(Employee);
            f.seekg(recPos,ios::beg);
            f.read((char*)&e,sizeof(Employee));
            if(!f.eof()){
                if(e.geteno()==0)
                    cout<<'\n'<<AlignL()<<"Employee already deleted!"
                        <<'\n'<<AlignL()
                        <<"Returning to Employee management window";
                else{
                    cout<<'\n'<<AlignL()<<"Verify Details: ";
                    e.Display();
                    cout<<'\n'<<AlignL()<<"Y/N: ";
                    cin>>opt;
                    cin.sync();
                    if(opt=='y'||opt=='Y'){
                        fstream mc("Bin\\Employee count.bin",
                                    ios::binary|ios::in|ios::out);
                        if(!mc)
                            cout<<'\n'<<AlignL()<<"Unable to delete Employee!";
                        else{
                            int count;
                            mc.read((char*)&count,sizeof(int));
                            count--;
                            mc.seekp(0L);
                            mc.write((char*)&count,sizeof(int));
                            e.Delete();

                            f.seekp(recPos,ios::beg);
                            f.write((char*)&e,sizeof(Employee));

                            cout<<'\n'<<AlignL()<<"Success!";
                            mc.close();
                        }
                    }
                    else
                        cout<<'\n'<<AlignL()
                            <<"Returning to employee management window!";
                }
            }
            else
                cout<<'\n'<<AlignL()<<"No such Employee exists!"
                    <<'\n'<<AlignL()
                    <<"Returning to Employee management window!";
        f.close();
        }
        else
            cout<<'\n'<<AlignL()<<"No such Employee exists!"
                <<'\n'<<AlignL()<<"Returning to Employee management window!";
    }

}

void employee::Modify(){
    long Recpos;
    char retry='y',confirm='y';
    char opt;
    int eno;
    Employee e;

    fstream f("Bin\\Employees.dat",ios::binary|ios::in|ios::out);
    if(!f)
        cout<<'\n'<<AlignL()<<"\aError Accessing file!";
    else{
        f.seekp((long)-sizeof(Employee),ios::end);
        long lastRec=f.tellp();
        f.seekp(0L);
        system(CLEAR);
        cout<<AlignV();

        cout<<'\n'<<AlignL();
            Div(54);
        cout<<'\n'<<AlignL()<<"         EMPLOYEE DETAILS MODIFICATION WINDOW"
            <<'\n'<<AlignL();
            Div(54);
        cout<<'\n'<<AlignL()<<"Enter employee number: ";
        cin>>eno;
        cin.get();
        if(!cin){
            cin.clear();
            cin.sync();
            eno=-1;
        }
        if(eno>0){

            Recpos=long((eno-1)*sizeof(Employee));
            if(Recpos>lastRec)
                cout<<'\n'<<AlignL()<<"\aGiven record does not exit!"
                    <<'\n'<<AlignL()<<"Returning to Employee management window";
            else{
                f.seekg(Recpos,ios::beg);
                f.read((char*)&e,sizeof(Employee));

                if(e.geteno()==0)  ///deleted employee
                    cout<<'\n'<<AlignL()<<"\nEmployee has been deleted!"
                        <<'\n'<<AlignL()
                        <<"Returning  to employee management window";

                else{
                    cout<<'\n'<<AlignL()<<"Verify details: ";
                    e.Display();
                    cout<<'\n'<<AlignL()<<"Y/N: ";
                    cin>>opt;
                    cin.sync();
                    if(opt=='y'||opt=='Y'){
                        f.seekp(Recpos,ios::beg);
                        e.accept(false);
                        f.write((char*)&e,sizeof(Employee));
                        cout<<'\n'<<AlignL()<<"Success!";
                    }
                    else
                        cout<<'\n'<<AlignL()
                                  <<"Returning to Employee management window";
                }
            }
        }
        else
            cout<<'\n'<<AlignL()<<"\aInvalid input!"
                <<'\n'<<AlignL()<<"Returning  to Employee management window";

    f.close();
    }
}
 void employee::ChangePassword(){
    Employee e;
    int eno;
    long RecPos;
    fstream f("Bin\\Employees.dat",ios::binary|ios::in|ios::out);
    if(!f)
        cout<<'\n'<<AlignL()<<"\aError accessing file!";
    else{
        system(CLEAR);
        cout<<AlignV();

        cout<<'\n'<<AlignL();
            Div(55);
        cout<<'\n'<<AlignL()<<"         EMPLOYEE PASSWORD MODIFICATION WINDOW"
            <<'\n'<<AlignL();
            Div(55);

        cout<<'\n'<<AlignL()<<"Enter employee number: ";
        cin>>eno;
        if(!cin){
            cin.clear();
            cin.sync();
            eno=-1;
        }
        if(eno>0){
            cin.get();
            RecPos=long((eno-1)*sizeof(Employee));
            f.seekg(RecPos,ios::beg);
            f.read((char*)&e,sizeof(Employee));
            if(!f.eof()){
                e.Change_Password();
                f.seekp(RecPos,ios::beg);
                f.write((char*)&e,sizeof(Employee));
            }
            else
                cout<<'\n'<<AlignL()<<"Please try again!";
        }
        else
            cout<<'\n'<<AlignL()<<"No such Employee exists!"
                <<'\n'<<AlignL()<<"Returning to Employee management window!";
    }
 }

 void employee::ViewDetails(){
    system(CLEAR);
    cout<<AlignV();
    cout<<'\n'<<AlignL()<<"_________________________________________________"
        <<'\n'<<AlignL()<<"         EMPLOYEE DETAILS VIEWING WINDOW         "
        <<'\n'<<AlignL()<<"_________________________________________________";
    int eno;
    Employee e;

    do{
        cout<<'\n'<<AlignL()<<"Enter employee no: ";
        cin>>eno;
        cin.get();
        if(!cin){
            cin.clear();
            cin.sync();
            eno=-1;
        }
        if(eno<=0)
            cout<<AlignL()<<"Invalid!";
    }while(eno<=0);

    ifstream f("Bin\\Employees.dat",ios::binary);
    f.seekg((long)(eno-1)*sizeof(Employee));
    f.read((char*)&e,sizeof(Employee));
    if(f.good())
        if(e.geteno())
            e.Display();
        else
            cout<<'\n'<<AlignL()<<"Employee has been deleted!"
                <<'\n'<<AlignL()<<"Returning to employee management window";
    else
        cout<<'\n'<<AlignL()<<"Invalid Employee no!"
            <<'\n'<<AlignL()<<"Returning to Employee Management window";
}



bool ClerkConfirm(){//To Verify if the operator is the one processing the bill
system(CLEAR);
cout<<AlignV();
cout<<'\n'<<AlignL()<<"_______________________________________________"
    <<'\n'<<AlignL()<<"              EMPLOYEE LOGIN WINDOW            "
    <<'\n'<<AlignL()<<"_______________________________________________";
int empno;
Employee e;

cout<<'\n'<<AlignL()<<"Enter Employee number: ";

cin>>empno;
cin.get();
if(!cin){
    cin.clear();
    cin.sync();
    empno=-1;
}
if(empno <= 0){
     cout<<AlignL()<<"\aError invalid employee number!\n"
         <<AlignL()<<"Press any key to continue......\n"<<AlignL();
          getch();
    return false;
}
fstream f("Bin\\Employees.dat",ios::binary|ios::in|ios::out);
 if(!f)
    cout<<"\nUnable to access file";
 else{
     f.seekg( (long)(empno-1)*sizeof(Employee),ios::beg);
     f.read((char*)&e,sizeof(Employee));
     if(!f.eof()&&e.geteno()!=0)
          return e.check();
     else{
          cout<<'\n'<<AlignL()<<"\aError invalid employee number!\n"
                    <<AlignL()<<"Press any key to continue......\n"
                    <<AlignL();
          getch();
          return false;
     }
 }
}
