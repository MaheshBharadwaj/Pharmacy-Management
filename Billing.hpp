///Billing.hpp

/**
This header files contain functions necessary for billing:
    1.ClerkConfirm - in order to verify that the person billing
                     is an employee of the store
    2.Bill - Actual order placed by the customer
    3.Display Bill - Displays the bill for the customer
    4.Find Month - Converts month no. to the appropriate string
*/

class BillData{     		///To accept details required to compute bill
public:
	char name[30];
	unsigned int quantity;
	float rate;
};

void SupplyDrug (const BillData& drug){///Reduce stock based on order
    char Fileloc[40]="Medicines\\";
    strcat(Fileloc,drug.name);
    strcat(Fileloc,".bin");
    int q=drug.quantity;
    fstream f(Fileloc,ios::binary|ios::in|ios::out);
    if(!f)
        cerr<<'\n'<<AlignL()<<"Error supplying "<<drug.name;
    else{
        Drug d;
        bool supply=false;      ///Indicates if order has been delivered

        for(short int i=0;i<5&&!supply;i++){
            f.read((char*)&d,sizeof(Drug));
            if(d.getStock() <= q){
                q -= d.getStock();
                d.setStock(0);
            }
            else{
                d.setStock ( d.getStock()-q );
                supply=true;    ///Successfully delivered
            }

            f.seekp(long(-sizeof(Drug)),ios::cur);
            f.write((char*)&d,sizeof(Drug));
            }
    }
    f.close();
}

string FindMonth(unsigned short int mno){
///FINDS MONTH BASED ON MONTH NUMBER
    string month;
	switch(mno){
		case 1:  month = "January";  break;
		case 2:  month = "February"; break;
		case 3:  month = "March";    break;
		case 4:  month = "April";    break;
		case 5:  month = "May";      break;
		case 6:  month = "June";     break;
		case 7:  month = "July";     break;
		case 8:  month = "August";   break;
		case 9:  month = "September";break;
		case 10: month = "October";  break;
		case 11: month = "November"; break;
		case 12: month = "December"; break;
	}
    return month;
}



void Bill ( bool& login , const float DefaultDiscount ) {

	if( login == false) ///NO CLERK HAS LOGGED IN
		login = ClerkConfirm();

	if(login == true){
    /**
    After verifying it is a valid employee,
        1.Drugs required are accepted one by one
        2.Membership details,if needed is accessed
        3.Entire bill is transferred to the process module along with
          data required like memno, mem name and applicable discount
    */

		queue<BillData> bill;
		int count=0;   ///No of Items
		char opt='Y';
		char tmp_name[25];
		fstream f;
		while( opt=='y' || opt=='Y' ){
			system(CLEAR);
			cout<<AlignV();
			cout<<'\n'<<AlignL();
                    Div(54);
            cout<<'\n'<<AlignL()<<"           CUSTOMER BILL GENERATION WINDOW"
                    <<'\n'<<AlignL();
                    Div(54);
            cout<<'\n'
                    <<'\n'<<AlignL()<<"Enter the name of drug: ";

			cin.getline(tmp_name,25);
			cin.sync();

			BillData drug;
			Drug d;

			char Fileloc[40]="Medicines\\";			//location of drug file
			strcat(Fileloc,tmp_name);
			strcat(Fileloc,".bin");

			f.open(Fileloc,ios::binary|ios::in|ios::out);

			if(!f)
                cout<<AlignL()<<"\aNo such drug exists";
			else{
                cout<<AlignL()<<"Available stock: "<<CurrentStock(f);
				int q;               ///Quantity

                if(CurrentStock(f)){ ///IF STOCK AVAILABLE
                    do{
                        cout<<'\n'<<AlignL()<<"Enter  Quantity: ";
                        cin>>q;
                        cin.get();
                        if(!cin){
                            cin.clear();
                            cin.sync();
                            q=-1;
                        }
                        if(q<=0)
                            cout<<'\n'<<AlignL()<<"\aInvalid!";
                    }while(q<=0);
                }
                else
                    q=1;           ///REFER NEXT CONDITION

			if( CurrentStock(f) >= q){
            ///It is possible to deliver given order
				f.seekg((long)(-sizeof(Drug)) , ios::end);
				f.read((char*)&d,sizeof(Drug));   ///Latest price
				drug.quantity=q;                  ///Billing Purposes
                drug.rate = d.getPrice();         ///       "
                strcpy ( drug.name , tmp_name);   ///       "
				bill.push(drug);	              ///appending to bill queue
				count++;
			}
			else
				cout<<'\n'<<AlignL()<<"\aRequired quantity un-available";
            f.close();
			}

        do{
            cout<<'\n'<<AlignL()<<"Do you want to continue billing? Y/N? ";
            cin>>opt;
            cin.sync();
            if(opt!='y'&&opt!='Y'&&opt!='n'&&opt!='N')
                cout<<AlignL()<<"Invalid";
        }while(opt!='y'&&opt!='Y'&&opt!='n'&&opt!='N');



        if(opt=='n'||opt=='N'){
            opt='\0';       ///Reusing opt
            system(CLEAR);
            cout<<AlignV()
                    <<'\n'<<AlignL();
                    Div(54);
            cout<<'\n'<<AlignL()<<"           CUSTOMER BILL GENERATION WINDOW"
                    <<'\n'<<AlignL();
                    Div(54);
            cout<<'\n'
                    <<'\n'<<AlignL()<<"Total items: "<<count;

            do{
                cout<<'\n'<<AlignL()<<"Proceed to bill Y/N? ";
                cin>>opt;
                cin.sync();
                if(opt!='y'&&opt!='Y'&&opt!='n'&&opt!='N')
                    cout<<AlignL()<<"Invalid";
            }while(opt!='y'&&opt!='Y'&&opt!='n'&&opt!='N');

            if(opt=='n'||opt=='N')     ///Empty queue to prevent billing
                while (bill.empty() == false)
                    bill.pop();

            opt='n';     ///To terminate external loop
            }
		}

		if(bill.empty() == false){
            ///DRUGS TO BE BILLED
			system(CLEAR);
			cout<<AlignV();
			cout<<'\n'<<AlignL();
                    Div(54);
            cout<<'\n'<<AlignL()<<"           CUSTOMER BILL GENERATION WINDOW"
                    <<'\n'<<AlignL();
                    Div(54);

			float Discount=0; 	    ///Used for the discount percentage
			char Mname[25]="";
			char status;
			int Mno=0;
			int memno;
			char confirm;

			do{
                cout<<'\n'<<AlignL()<<"Are you a member? Y/N: ";
                cin>>status;
                cin.sync();
                if(status!='y'&&status!='Y'&&status!='n'&&status!='N')
                    cout<<AlignL()<<"Invalid!";
			}while(status!='y'&&status!='Y'&&status!='n'&&status!='N');

			if(status=='y'||status=='Y')///To access membership details if necessary
                Membership(Mname,Mno,Discount);


            Process_Bill( Mname,  ///Array passed if member is validated else Null
                          Mno,    ///Member number passed if Member Validated
                          DefaultDiscount + Discount,
                          bill,   ///Bill queue
                          login); ///Logout / Login
        }

        ///In case of an empty bill
		else{
            cout<<'\n'<<AlignL()<<"Do you want to logout? Y/N: ";
            char ch;
            cin>>ch;
            cin.get();
            login=!(ch=='y'||ch=='Y');
        }
    }
}

bool Process_Bill(const char* const Mname,int &Mno,
                  double discount,queue<BillData> &bill,bool &login){
	int sno=1,Quantity=0;
	float Rate , subtotal,
          total = 0,
          tax , disc_amt=0;

	fstream f("Billing_history\\billnocount.txt");
	if(!f){
		cout<<"\nUnable to generate bill";
		return false;
	}
	unsigned int billno;
	///Getting last billno. generated
	f>>billno;
	///Incrementing for current bill
	billno++;

    stringstream ss;
    ss<<billno;
    string temp=ss.str();
    ///temp is a string containing the current bill number

	time_t t = time(0);
    tm *now = localtime(&t);
    const unsigned short int month_no = now->tm_mon+1;
	char *date = ctime(&t);    ///date as string

	string Fileloc="Billing_history\\";
	string month;
	month=FindMonth(month_no);

    /// To get fileloc in the form: Billing_history\Month\Billno.txt
	Fileloc = Fileloc + month + "\\" + temp + ".txt";
	ofstream fout(Fileloc.c_str(),ios::trunc);

	if(!fout){
		cout<<"\nUnable to generate bill: ";
		f.close();
		return false;
	}

	fout<<date;
	fout<<"Bill number: "<<billno<<endl;
	if(Mno)
		fout<<"Member no: "<<Mno<<" Name: "<<Mname;
	fout<<setprecision(2)<<fixed;                   ///two decimal places
	fout<<"\n-------------------------------------------------------\n";
	fout<<"S.No"<<setw(7)<<"Name"<<setw(24)<<"Quantity"<<setw(7)
        <<"Rate"<<setw(13)<<"SUBTOTAL";
	fout<<"\n-------------------------------------------------------\n";


	BillData drug;							///object to temporarily store data
	while(!bill.empty()){	    		///run till 'bill queue' is empty
		drug=bill.front();				///current drug's data
		bill.pop();						///removing from queue after copying data
        SupplyDrug(drug);               ///Reducing stock
		int l=strlen(drug.name);    	///for output alignment

		subtotal = drug.quantity * drug.rate;
		total += subtotal;
        Quantity += drug.quantity;      /// For updating daily report

      fout<<setw(2)<<sno<<setw(5+l)<<drug.name<<setw(25-l)<<drug.quantity
          <<setw(11)<<drug.rate<<setw(11)<<subtotal<<endl;

      sno++;
	}
	fout<<"\n\n-------------------------------------------------------\n";
    fout<<setw(48)<<"Total: "<<total;
    fout<<"\n-------------------------------------------------------\n";
	disc_amt = total * (discount/100);
	total = total - disc_amt;
	tax = total * (18.0/100);				///GST set at 18%
	total += tax;

	fout<<"\nDiscount @"<<discount<<"% : "<<disc_amt
		<<"\nTax@18% :\nCGST = "<<tax/2<<" SGST = "<<tax/2<<" Total tax: "<<tax
	    <<"\nAMOUNT PAYABLE: "<<total;
	fout.close();

	UpdateReport(total,Quantity);

    ShellExecute( 0,
                 "open",             ///Operation to be done
                 "ReadBill.exe",     ///Operand

                 ///Arguments to be passed to the application
                 (month+"\\"+temp+".txt").c_str(),

                 "Billing_history\\",///Working directory of the application
                 SW_SHOWMAXIMIZED ); ///Window display options

    ///Bill successfully  generated
    f.seekp(0L);
    ///Updating bill count file
	f<<billno;
	f.close();

char opt;
cout<<'\n'<<AlignL();
    Div(54);

do{
    cout<<'\n'<<AlignL()<<"Do you want to logout? Y/N :";
    cin>>opt;
    cin.sync();
    if(opt!='y'&&opt!='Y'&&opt!='N'&&opt!='n')
        cout<<AlignL()<<"Invalid";
}while(opt!='y'&&opt!='Y'&&opt!='N'&&opt!='n');

login = !(opt=='y'||opt=='Y');
}
