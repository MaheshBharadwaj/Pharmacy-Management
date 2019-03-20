///Member Management.cpp

void member::Add(){
system(CLEAR);
cout<<AlignV();
cout<<'\n'<<AlignL()<<"____________________________________________________"
    <<'\n'<<AlignL()<<"               MEMBER ADDITION WINDOW               "
    <<'\n'<<AlignL()<<"____________________________________________________";
int mno=0,
    count=0;
char opt='\0';
Member m;
bool retry=true;

fstream GetMemno("Bin\\Member Count.dat",ios::binary|ios::in|ios::out);
if(!GetMemno)
    cout<<'\n'<<AlignL()<<"\aUnable to add member!";
else{
    cout<<'\n'<<AlignL()<<"Are you sure you want to add a new member? Y/N: ";
    cin>>opt;
    cin.sync();
    if(opt=='y'||opt=='Y'){
        ifstream fin("Bin\\Members.dat",ios::binary);
        if(!fin)
            cout<<'\n'<<AlignL()<<"Unable to add member";
        else{
            unsigned int nor;
            fin.seekg (0L,ios::end);
            nor=fin.tellg() / sizeof(Member);
            fin.seekg(0L);

            fin.read((char*)&m,sizeof(Member));
            while( !fin.eof() && retry==true ){
                mno++;
                if(m.GetMno()==0)
                    retry=false;
                fin.read((char*)&m,sizeof(Member));
                }
            fin.close();
            GetMemno.read((char*)&count,sizeof(int));
            fstream f("Bin\\Members.dat",ios::binary|ios::in|ios::out);
            if(!f)
                cout<<'\n'<<AlignL()<<"\aUnable to add member";
            else{
                if(mno<nor && mno!=0){//DELETED MEMBERS
                    count++;
                    Member m(mno);
                    m.accept();
                    f.seekp((long)(mno-1)*sizeof(Member),ios::beg);
                    f.write((char*)&m,sizeof(Member));
                    cout<<'\n'<<AlignL()<<"Successfully added member!";
                    }
                else{               //NO DELETED MEMBERS
                    count++;
                    Member m(count);
                    m.accept();
                    f.seekp(0L,ios::end);
                    f.write((char*)&m,sizeof(Member));

                    cout<<'\n'<<AlignL()<<"Successfully added member!";
                    }
                f.close();
                }

            GetMemno.seekp(0L);      //INCREAMENTING MEMBER COUNT
            GetMemno.write((char*)&count,sizeof(int));
            }
    }
    else
        cout<<'\n'<<AlignL()<<"Returning to Member Management window";

GetMemno.close();
}

}

void member::Delete(){
int mno;
long recPos;
char opt;
fstream f("Bin\\Members.dat",ios::binary|ios::in|ios::out);
if(!f)
    cout<<"\n\aError Accessing the file";
else{
    system(CLEAR);
    cout<<AlignV();
    cout<<'\n'<<AlignL()<<"____________________________________________________"
        <<'\n'<<AlignL()<<"               MEMBER DELETION WINDOW               "
        <<'\n'<<AlignL()<<"____________________________________________________";

    Member m;

    cout<<'\n'<<AlignL()<<"Enter member number: ";
    cin>>mno;
    cin.get();
    if(!cin){
        cin.clear();
        cin.sync();
        mno=-1;
    }
    if(mno>0){
        recPos=(long)(mno-1)*sizeof(Member);
        f.seekg(recPos,ios::beg);
        f.read((char*)&m,sizeof(Member));
        if(!f.eof()){
            if(m.GetMno()==0)
                cout<<'\n'<<AlignL()<<"Member already deleted!"
                    <<'\n'<<AlignL()<<"Returning to member management window";
            else{
                cout<<'\n'<<AlignL()<<"Verify Details: ";
                m.Display();
                cout<<'\n'<<AlignL()<<"Y/N: ";
                cin>>opt;
                cin.sync();
                if(opt=='y'||opt=='Y'){
                    fstream mc("Bin\\Member count.dat",ios::binary|ios::in|ios::out);
                    if(!mc)
                        cout<<'\n'<<AlignL()<<"Unable to delete member!";
                    else{
                        int c;
                        mc.read((char*)&c,sizeof(int));
                        c--;
                        mc.seekp(0L);
                        mc.write((char*)&c,sizeof(int));
                        m.Delete();
                        f.seekp(recPos,ios::beg);
                        f.write((char*)&m,sizeof(Member));

                        cout<<'\n'<<AlignL()<<"Successfully deleted member!";
                        mc.close();
                        }
                    }
                else
                    cout<<'\n'<<AlignL()<<"Returning to member management window!";
            }
        }
        else
            cout<<'\n'<<AlignL()<<"No such member exists!"
                <<'\n'<<AlignL()<<"Returning to member management window!";
    f.close();
    }
    else
        cout<<'\n'<<AlignL()<<"No such member exists!"
            <<'\n'<<AlignL()<<"Returning to member management window!";
    }

}

void member::Modify(){
long Recpos;
char retry='y',confirm='y';
char opt;
int mno;
fstream f("Bin\\Members.dat",ios::binary|ios::in|ios::out);
if(!f)
    cout<<"\n\aError Accessing file!";
else{
    f.seekp((long)-sizeof(Member),ios::end);
    long lastRec=f.tellp();
    f.seekp(0L);
    system(CLEAR);
    cout<<AlignV();
    cout<<'\n'<<AlignL()<<"______________________________________________________"
        <<'\n'<<AlignL()<<"          MEMBER DETAILS MODIFICATION WINDOW          "
        <<'\n'<<AlignL()<<"______________________________________________________"
        <<'\n'
        <<'\n'<<AlignL()<<"Enter member number: ";
    cin>>mno;
    cin.get();
    if(!cin){
        cin.clear();
        cin.sync();
        mno=-1;
    }
    if(mno>0){
        Member m;
        Recpos=long((mno-1)*sizeof(Member));

        if(Recpos>lastRec)
            cout<<'\n'<<AlignL()<<"\aGiven record does not exit!"
                <<'\n'<<AlignL()<<"Returning  to member management window";
        else{
            f.seekg(Recpos,ios::beg);
            f.read((char*)&m,sizeof(Member));
            if(m.GetMno()==0)//deleted member
                cout<<'\n'<<AlignL()<<"Member has been deleted!"
                    <<'\n'<<AlignL()<<"Returning  to member management window";
            else{
                cout<<'\n'<<AlignL()<<"Verify details: ";
                m.Display();
                cout<<'\n'<<AlignL()<<"Y/N: ";
                cin>>opt;
                cin.sync();
                if(opt=='y'||opt=='Y'){
                    f.seekp(Recpos,ios::beg);
                    m.accept(false);
                    f.write((char*)&m,sizeof(Member));
                    cout<<'\n'<<AlignL()<<"Successfully modified member details!";
                }
                else
                    cout<<'\n'<<AlignL()<<"Returning  to member management window";
            }
        }
    }
    else
        cout<<'\n'<<AlignL()<<"\aInvalid input!"
            <<'\n'<<AlignL()<<"Returning  to member management window";

f.close();

    }
}
void member::ViewDetails(){
system(CLEAR);
cout<<AlignV();
cout<<'\n'<<AlignL()<<"_____________________________________________________"
    <<'\n'<<AlignL()<<"            MEMBER DETAILS VIEWING WINDOW            "
    <<'\n'<<AlignL()<<"_____________________________________________________";

int mno;
Member m;
do{
    cout<<'\n'<<AlignL()<<"Enter member no: ";
    cin>>mno;
    cin.get();
    if(!cin){
        cin.clear();
        cin.sync();
        mno=-1;
    }
    if(mno<=0)
        cout<<AlignL()<<"Invalid!";
}while(mno<=0);
ifstream f("Bin\\Members.dat",ios::binary);

f.seekg((long)(mno-1)*sizeof(Member));
f.read((char*)&m,sizeof(Member));
if(f.good())
    if(m.GetMno())
        m.Display();
    else
        cout<<'\n'<<AlignL()<<"Member has been deleted!"
            <<'\n'<<AlignL()<<"Returning to member management window";
else
    cout<<'\n'<<AlignL()<<"Invalid Member no!"
        <<'\n'<<AlignL()<<"Returning to Member Management window";
}


void member::SearchByName(Member &m){
char  name[25];
ifstream fin("Bin\\Members.dat",ios::binary);
if(!fin)
    cout<<'\n'<<AlignL()<<"Unable to access records!";
else{
    cout<<'\n'<<AlignL()<<"Enter the name: ";
    cin.getline(name,25);
    cin.sync();

    fin.read((char*)&m,sizeof(Member));

    while(!fin.eof()){
        if ( stringcmp( name, m.getName() )==true && m.GetMno() )
            m.Display();
        fin.read((char*)&m,sizeof(Member));
    }
    fin.close();
    }
}

void member::SearchByContact(Member &m){
char ph[11];
ifstream fin("Bin\\Members.dat",ios::binary);
if(!fin)
    cout<<'\n'<<AlignL()<<"Unable to access records!";
else{
    cout<<'\n'
        <<'\n'<<AlignL()<<"Enter the Phone number: ";
    cin.getline(ph,11);
    cin.sync();
    fin.read((char*)&m,sizeof(Member));

    while(!fin.eof()){
        if ( stringcmp( ph, m.getPH() )==true && m.GetMno() )
            m.Display();
        fin.read((char*)&m,sizeof(Member));
    }
    fin.close();
}
}

Member member::Search(){
int opt;
Member m;
system(CLEAR);
cout<<AlignV();
cout<<'\n'<<AlignL()<<"____________________________________________________"
    <<'\n'<<AlignL()<<"          MEMBERSHIP DETAILS SEARCH WINDOW          "
    <<'\n'<<AlignL()<<"____________________________________________________"
    <<'\n'
    <<'\n'<<AlignL()<<"1 - Search By name"
    <<'\n'<<AlignL()<<"2 - Search By contact details"
    <<'\n'<<AlignL()<<"0 - Exit"
    <<'\n'
    <<'\n'<<AlignL()<<"____________________________________________________"
    <<'\n'<<AlignL()<<"Enter your choice: ";

cin>>opt;
cin.get();
if(!cin){
    cin.clear();
    cin.sync();
    opt=-1;
}

switch(opt){
    case -1: cout<<'\n'<<AlignL()<<"Invalid input"
                 <<'\n'<<AlignL()<<"Returning to Member management window";
             break;

    case 1: system(CLEAR);
            cout<<AlignV();
            cout<<'\n'<<AlignL();
                Div(56);
            cout<<'\n'<<AlignL()<<"               SEARCH FOR MEMBERS BY NAME"
                <<'\n'<<AlignL();
                Div(56);

            SearchByName(m);
            break;

    case 2: system(CLEAR);
            cout<<AlignV();
            cout<<'\n'<<AlignL();
                Div(56);
            cout<<'\n'<<AlignL()<<"             SEARCH FOR MEMBERS BY CONTACT"
                <<'\n'<<AlignL();
                Div(56);
            SearchByContact(m);
            break;
    }
return m;
}

 void Membership( char* const Mname, int &Mno, float &D){
///FOR BILLING PURPOSES ONLY

    int sw;
    Member m;
    int memno;
    char status;
    bool verify=false;      ///If proper access, true
    bool retry=true;        ///User terminated loop
    fstream f;

    while(retry){
        system(CLEAR);
        cout<<AlignV();
        cout<<'\n'<<AlignL()
                  <<"_____________________________________________________"
            <<'\n'<<AlignL()
                  <<"           CUSTOMER BILL GENERATION WINDOW "
            <<'\n'<<AlignL()
                  <<"_____________________________________________________"
            <<'\n'
            <<'\n'<<AlignL()<<"1 - Enter member number"
            <<'\n'<<AlignL()<<"2 - Search by contact"
            <<'\n'<<AlignL()<<"3 - Search By name"
            <<'\n'<<AlignL()<<"0 - Exit"
            <<'\n'
            <<'\n'<<AlignL()
                  <<"_____________________________________________________"
            <<'\n'<<AlignL()<<"Enter your choice: ";
        cin>>sw;
        cin.get();

        if(!cin){
            cin.clear();
            sw=-1;
            cin.sync();
        }
        cout<<'\n'
            <<'\n'<<AlignL()
            <<"_____________________________________________________";

        switch (sw) {
            case 1:{
                    f.open("Bin\\Members.dat",ios::binary|ios::in);
                    cout<<'\n'<<AlignL()<<"Enter member number: ";
                    cin>>memno;
                    if(!cin){
                        cin.clear();
                        cin.sync();
                        memno=-1;
                    }
                    if(memno > 0){
                        f.seekg ((long)(memno-1)*sizeof(Member),ios::beg);
                        f.read ((char*)&m,sizeof(Member));

                        if(f.eof())
                            cout<<'\a';
                        else
                            if( !m.GetMno() ){
                                cout<<'\n'<<AlignL()<<"Member has been deleted!"
                                    <<'\n'<<AlignL()
                                    <<"Press any key to continue........."
                                    <<'\n'<<AlignL();
                                getch();
                            }
                            else{
                                m.Display();
                                cout<<'\n'<<AlignL()<<"Verify details Y/N: ";
                                cin>>status;
                                cin.sync();

                                retry = status=='y'||status=='Y' ? false : true;
                                verify = ! retry;
                            }
                        }
                    f.close();
                    }
                    break;
            case 2:
                {
                member::SearchByContact(m);
                f.open("Bin\\Members.dat",ios::binary|ios::in);
                cout<<'\n'<<AlignL()
                    <<"_____________________________________________________"
                    <<'\n'<<AlignL()
                    <<"Enter the member number if found else enter '0' : ";
                cin>>memno;

                if(!cin||memno<0){
                    cin.clear();
                    cin.sync();
                    memno=0;
                }
                if(memno){
                    f.seekg((long)(memno-1)*sizeof(Member),ios::beg);
                    if( f.good() ){
                        f.read((char*)&m,sizeof(Member));
                        if( m.GetMno() ){
                            retry=false;
                            verify=true;
                            }
                        }
                    }
                f.close();
                }
                    break;
            case 3:{
                    member::SearchByName(m);
                    f.open("Bin\\Members.dat",ios::binary|ios::in);
                    cout<<'\n'<<AlignL()
                        <<"_____________________________________________________"
                        <<'\n'
                        <<AlignL()
                        <<"Enter the member number if found else enter '0' : ";
                    cin>>memno;

                    if(!cin||memno<0){
                        cin.clear();
                        cin.sync();
                        memno=0;
                    }
                    if(memno){
                        f.seekg((long)(memno-1)*sizeof(Member),ios::beg);
                        if( f.good() ){
                            f.read((char*)&m,sizeof(Member));
                            if( m.GetMno() ){
                                retry=false;
                                verify=true;
                                }
                            }
                        }
                    f.close();
                    }
                    break;
            case 0:retry=false;
                   break;
            default:
                    cout<<'\a';
        }
    }

    if(verify){
        f.open("Bin\\Members.dat",ios::binary|ios::in|ios::out);

        ///PLACING FILE POINTER TO NEXT OBJECT
        f.seekg((long)(memno)*sizeof(Member));

        strcpy(Mname, m.getName() );
        Mno=memno;
        D=m.GetMdisc(f);
        f.close();
    }
 }

