///Drug Management.cpp

void DrugOps::Add(const int CD,const int CM, const int CY){
	system(CLEAR);
	cout<<AlignV();

	cout<<'\n'<<AlignL()<<"______________________________________________________"
        <<'\n'<<AlignL()<<"               NEW DRUG ADDITION WINDOW               "
        <<'\n'<<AlignL()<<"______________________________________________________";

	char Fileloc[45]="Medicines\\";
	char name[25];
	char buff[30];
	char opt;
	int stock=0;
	short int date=0,month=0,year=0;
	float price=0;

	Drug d;     ///Actual first batch
	Drug d1;    ///Copies for Batch templates

	cout<<"\n\n"<<AlignL()<<"Are you sure you want to add a new drug? Y/N: ";
	cin>>opt;
	cin.sync();
	if(opt=='y'||opt=='Y'){
		cout<<'\n'<<AlignL()<<"Enter the name of the drug: ";
		cin.getline(name,25);

		strcat(Fileloc,name);
		strcat(Fileloc,".bin");
		ifstream temp(Fileloc,ios::binary);
		if(temp.good())
			cout<<'\n'<<AlignL()<<"Given Drug already exists!"
                <<'\n'<<AlignL()<<"Returning to Drug management window";
		else{
			ofstream fout(Fileloc,ios::binary);
			if(!fout)
				cout<<'\n'<<AlignL()<<"\aUnable to create file!"
                    <<'\n'<<AlignL()<<"Returning to Drug management window";
			else{

				d.setName(name);
				d1.setName(name);
				d.SetBatchNo(1);

				cout<<'\n'<<AlignL()<<"Enter supplier name: ";
				cin.getline(buff,30);

				d.setSupplierName(buff);
				d1.setSupplierName(buff);

				cout<<'\n'<<AlignL()<<"Enter supplier contact: ";
				cin.getline(buff,30);

				d.setSupplierContact(buff);
				d1.setSupplierContact(buff);

				do{
					cout<<'\n'<<AlignL()<<"Enter stock: ";
					cin>>stock;
					cin.get();
					if(!cin){
						cin.clear();
						cin.sync();
						stock=-1;
					}
					if(stock<0)
						cout<<AlignL()<<"Invalid!";
				}while(stock<0);

				d.setStock(stock);

				do{
					cout<<'\n'<<AlignL()<<"Enter price: ";
					cin>>price;
					cin.get();
					if(!cin){
						cin.clear();
						cin.sync();
						price=-1;
					}
					if(price<=0)
						cout<<AlignL()<<"Invalid!";
				}while(price<=0);

				d.setPrice(price);
				d1.setPrice(price);
				do{
					cout<<'\n'<<AlignL()<<"Enter  expiry date DD MM YYYY: ";
					cin>>date>>month>>year;
					cin.get();
					if(!cin){
						cin.clear();
						cin.sync();
						date=-1;
					}
					if(date<1||date>31||month>12||month<1||year<CY||
                        (year==CY&&month==CM&&date<=CD)||
                        (year==CY&&month<CM)||(month==4||month==6 ||
                        month==7 || month==9 || month==11) && date>30||
                        (year%4!=0)&&(month==2)&&date>28 ||
                        (year%4==0)&&(month==2)&&date>29)
                    cout<<AlignL()<<"Invalid!";

				}while(date<1||date>31||month>12||month<1||year<CY||
                        (year==CY&&month==CM&&date<=CD)||
                        (year==CY&&month<CM)||(month==4||month==6 ||
                        month==7||month==9||month==11)&&date>30||
                        (year%4!=0)&&(month==2)&&date>28||
                        (year%4==0)&&(month==2)&&date>29);

				d.setDate(date);
				d.setMonth(month);
				d.setYear(year);

				fout.seekp(0L);
				for(short int i=1;i<=4;i++)         ///4 Batch templates
					fout.write((char*)&d1,sizeof(Drug));

				fout.write((char*)&d,sizeof(Drug));///1st Batch inserted at the end

				fout.close();
				cout<<'\n'<<AlignL()<<"Successfully added drug";
					}
				}
		}
	else
		cout<<'\n'<<AlignL()<<"Returning to drug management window";
}

void DrugOps::Delete(){
	system(CLEAR);
	cout<<AlignV();
	cout<<'\n'<<AlignL()<<"_________________________________________________"
        <<'\n'<<AlignL()<<"               DRUG REMOVAL WINDOW               "
        <<'\n'<<AlignL()<<"_________________________________________________";

	char name[45]="Medicines\\";
	char opt;
	char DrugName[25];
	cout<<'\n'<<AlignL()<<"Enter the name of the drug to be removed: ";
	cin.getline(DrugName,25);

	strcat(name,DrugName);
	strcat(name,".bin");
	ifstream test(name);
	if(!test)		//To check if given drug exists
		cout<<'\n'<<AlignL()<<"\aNo such drug exits!"
            <<'\n'<<AlignL()<<"Returning to drug management window";
	else{
		test.close();//To delete
		cout<<'\n'<<AlignL()<<"\aAre you sure you want to remove "
            <<DrugName<<"? Y/N: ";
		cin>>opt;
		cin.get();
		cin.sync();

		if(opt=='y'||opt=='Y')
            remove(name);
		else
			cout<<'\n'<<AlignL()<<"Returning to drug management window";
	}
}

void DrugOps::DeleteBatch(){
	system(CLEAR);
	cout<<AlignV();
	cout<<'\n'<<AlignL()<<"___________________________________________________"
        <<'\n'<<AlignL()<<"               BATCH DELETION WINDOW               "
        <<'\n'<<AlignL()<<"___________________________________________________";
	char ch;
	int bno;
	Drug d;

	bool found=false;
	char name[45]="Medicines\\";
	char DrugName[25];

	cout<<'\n'<<AlignL()<<"Enter the name of drug: ";
	cin.getline(DrugName,25);

	strcat(name,DrugName);
	strcat(name,".bin");
	fstream f(name,ios::binary|ios::in|ios::out);
	if(f){
		do{
			cout<<'\n'<<AlignL()<<"Enter batch no: ";
			cin>>bno;
			cin.get();
			if(!cin){
				cin.clear();
				cin.sync();
				bno=-1;
			}
			if(bno<=0)
				cout<<AlignL()<<"Invalid!";
		}while(bno<=0);

		for(int i=0;i<5;i++){
			f.read((char*)&d,sizeof(Drug));
			if(d.getBatchNo()==bno){
				found=true;
				i=6;
			}
		}
		if(found){
				if(d.getStock()==0)
					cout<<'\n'<<AlignL()<<"This batch has already been deleted"
                                        <<"//is empty"
                        <<'\n'<<AlignL()<<"Returning to drug management window";
				else{
                    cout<<'\n'<<AlignL()<<"Are you sure you want to delete"
                                        <<"this batch? Y/N: ";
                    cin>>ch;
                    cin.sync();
                    if(ch=='y'||ch=='Y'){
                            d.setStock(0);
                            f.seekp((long)(-sizeof(Drug)),ios::cur);
                            f.write((char*)&d,sizeof(Drug));
                            cout<<'\n'<<AlignL()<<"Successfully deleted batch!";
                    }
                    else
                        cout<<'\n'<<AlignL()<<"Returning to drug management window";
				}
		}
		else
			cout<<'\n'<<AlignL()<<"Invalid Batch no!"
                <<'\n'<<AlignL()<<"Returning to drug management window";
	f.close();
	}
	else
		cout<<'\n'<<AlignL()<<"No such drug exists!"
            <<'\n'<<AlignL()<<"Returning to drug management window";
}
void DrugOps::AddStock(const int CD,const int CM, const int CY){
	system(CLEAR);
	cout<<AlignV();
	cout<<'\n'<<AlignL()<<"_______________________________________________________"
        <<'\n'<<AlignL()<<"               NEW STOCK ADDITION WINDOW               "
        <<'\n'<<AlignL()<<"_______________________________________________________";
	char filename[45]="Medicines\\";
	char name[25]="\0";
 	int new_stock;
 	char opt,ch='y';
 	Drug d,temp;


 	cout<<'\n'<<AlignL()<<"Enter the drug name: ";
	cin.getline(name,25);
 	strcat(filename,name);
 	strcat(filename,".bin");

 	fstream f(filename,ios::binary|ios::in|ios::out);
    if(f){                       //If the drug exists
        cout<<'\n'<<AlignL()<<"Current Stock: "<<CurrentStock(f)
            <<'\n'<<AlignL()<<"Are you sure you want to increase the stock of "
            <<name<<" Y/N: ";
		cin>>opt;
		cin.sync();
		if(opt=='y'||opt=='Y'){

			f.read((char*)&d,sizeof(Drug));
            ///To obtain other details like supplier etc
			f.seekg(0L);


			if(CurrentStock(f)){
				bool full=true;
				for(int i=0;i<5;i++){
					f.read((char*)&temp,sizeof(Drug));
					if(!temp.getStock()){
						i=8;
						full=false;
						}
				}
				if(full){
					cout<<'\n'<<AlignL()<<"Warning! All batches have drugs left!"
                        <<'\n'<<AlignL()<<"Adding stock will lead to "
                                        <<"loss of goods "
                                        <<"(Oldest batch will be dumped)"
						<<'\n'<<'\n'
						<<AlignL()<<"Are you sure you want to continue? Y/N: ";
					cin>>ch;
					cin.sync();
				}
			}
			if(ch=='y'||ch=='Y'){
				do{
					cout<<'\n'<<AlignL()<<"Enter the new Stock: ";
					cin>>new_stock;
					cin.get();
					if(!cin){
							cin.clear();
							cin.sync();
							new_stock=-1;
					}
					if(new_stock<0)
						cout<<AlignL()<<"Invalid!";

				}while(new_stock<0);

				d.setStock(new_stock);
				float a;
				do{
					cout<<'\n'<<AlignL()<<"Enter the price: ";
					cin>>a;
					cin.get();
					if(!cin){
						cin.clear();
						cin.sync();
						a=-1;
					}

					if(a<=0)
						cout<<AlignL()<<"Invalid!";
				}while(a<=0);

				d.setPrice(a);
				short int date,month,year;

				do{
					cout<<'\n'<<AlignL()<<"Enter expiry date DD MM YYYY: ";
					cin>>date>>month>>year;
					cin.get();
					if(!cin){
						cin.clear();
						cin.sync();
						date=-1;
					}
					if(date<1||date>31||month>12||month<1||year<CY||
                        (year==CY&&month==CM&&date<=CD)||
                        (year==CY&&month<CM)||
                        (month==4||month==6||month==7||month==9||month==11)&&date>30
                        ||(year%4!=0)&&(month==2)&&date>28||
                        (year%4==0)&&(month==2)&&date>29)
						cout<<AlignL()<<"Invalid date!";

				}while(date<1||date>31||month>12||month<1||year<CY||
                       (year==CY&&month==CM&&date<=CD)||
                       (year==CY&&month<CM)||
                       (month==4||month==6||month==7||month==9||month==11)&&date>30
                       ||(year%4!=0)&&(month==2)&&date>28||
                       (year%4==0)&&(month==2)&&date>29);

            d.setDate(date);
			d.setMonth(month);
			d.setYear(year);
			f.seekg(0L);

            Drug drug[5];

            short int i;

            f.read((char*)drug,5*sizeof(Drug));
            int last_batch=drug[0].getBatchNo();

            for(i=1;i<5;i++){
                if(drug[i].getBatchNo()>last_batch)
                    last_batch=drug[i].getBatchNo();
                }
            cout<<'\n'<<AlignL()<<"Batch no: "<<last_batch+1;

            d.SetBatchNo(last_batch+1);

            f.seekp(0L,ios::beg);
            f.write((char*)&d,sizeof(Drug));
            SortDrug(f);

            cout<<'\n'<<AlignL()<<"Successfully Added stock!";
			}
			else
				cout<<'\n'<<AlignL()<<"Returning to drug management window";
            f.close();
        }
        else
            cout<<"\nReturning to drug management window";
    }
     else
          cout<<'\n'<<AlignL()<<"\aError,Medicine does not exist"
              <<'\n'<<AlignL()<<"Returning to drug management window";

 }

void DrugOps::ChangePrice(){
	system(CLEAR);
	cout<<AlignV();
	cout<<'\n'<<AlignL()<<"_______________________________________________________"
        <<'\n'<<AlignL()<<"               PRICE MODIFICATION WINDOW               "
        <<'\n'<<AlignL()<<"_______________________________________________________";
	char filename[45]="Medicines\\";
	char name[25]="\0";
	char opt='y';
 	float new_price;

 	Drug d;
 	cout<<'\n'<<AlignL()<<"Enter the drug name: ";
	cin.getline(name,25);

 	strcat(filename,name);
 	strcat(filename,".bin");

 	fstream f(filename,ios::binary|ios::in|ios::out);
 	if(!f)
		cout<<'\n'<<AlignL()<<"\aNo such drug exists!"
            <<'\n'<<AlignL()<<"Returning to drug management window";
	else{
		cout<<'\n'<<AlignL()<<"Are you sure you want to modify the price of "
                  <<name<<" ?Y/N: ";
		cin>>opt;
		cin.sync();
		if(opt=='y'||opt=='Y'){
			f.read((char*)&d,sizeof(Drug));

			cout<<'\n'<<AlignL()<<"Current Price: "<<d.getPrice();
			do{
				cout<<'\n'<<AlignL()<<"Enter the new price: ";
				cin>>new_price;
				cin.get();
				if(!cin){
					cin.clear();
					cin.sync();
					new_price=-1;
					}

				if(new_price<=0)
					cout<<AlignL()<<"Invalid!";

				}while(new_price<=0);



			f.seekp(0L);
			f.write((char*)&d,sizeof(Drug));///First Batch
			short int i=1;
			while(i<=4){		            ///Rest of the batches
				f.read((char*)&d,sizeof(Drug));
				if(d.getStock()){
					d.setPrice(new_price);
					f.seekp(long(-sizeof(Drug)),ios::cur);
					f.write((char*)&d,sizeof(Drug));
				}
				i++;
			}

			cout<<'\n'<<AlignL()<<"Price successfully updated!";
			}
		else
		cout<<'\n'<<AlignL()<<"Returning to drug management window";
	f.close();
	}

}

void DrugOps::ChangeSupplier(){
	system(CLEAR);
	cout<<AlignV();
	cout<<'\n'<<AlignL();
        Div(66);
    cout<<'\n'<<AlignL()<<"               SUPPLIER DETAILS MODIFICATION WINDOW"
        <<'\n'<<AlignL();
        Div(66);
	char name[45]="Medicines\\";
	char opt;
	char DrugName[25],buff1[30],buff2[30];
	Drug d;
	cout<<'\n'<<AlignL()<<"Enter the name of the drug: ";
	cin.getline(DrugName,25);

	strcat(name,DrugName);
	strcat(name,".bin");
	fstream f(name,ios::binary|ios::in|ios::out);

	if(!f)///To check if given drug exists
		cout<<'\n'<<AlignL()<<"\aNo such drug exits!";

	else{
		cout<<'\n'<<AlignL()<<"Are you sure you want to change the supplier of "
                            <<DrugName<<" ?Y/N: ";
		cin>>opt;
		cin.sync();
		if(opt=='y'||opt=='Y'){
			cout<<'\n'<<AlignL()<<"nEnter new supplier: ";
			cin.getline(buff1,30);

			cout<<'\n'<<AlignL()<<"Enter supplier contact: ";
			cin.getline(buff2,30);

			f.seekp(0L);
			short int i=0;
			while(i<5){
				f.read((char*)&d,sizeof(Drug));
				d.setSupplierName(buff1);
				d.setSupplierContact(buff2);
				f.seekp((long)(-sizeof(Drug)),ios::cur);
				f.write((char*)&d,sizeof(Drug));
				i++;
			}
			f.close();
			cout<<"\n\n"<<AlignL()<<"Successfully modified Supplier details!";
		}
		else
			cout<<'\n'<<AlignL()<<"Returning to drug management window";
	}
}

void DrugOps::ViewDetails(){
    system(CLEAR);
    cout<<AlignV();
    cout<<'\n'<<AlignL();
        Div(57);
    cout<<'\n'<<AlignL()<<"               DRUG DETAILS VIEWING WINDOW"
        <<'\n'<<AlignL();
        Div(57);

    Drug d;
    char Drugname[50]="Medicines\\",buff[25];

    cout<<'\n'<<AlignL()<<"Enter the name of the drug: ";
    cin.getline(buff,25);

    strcat(Drugname,buff);
    strcat(Drugname,".bin");

    fstream fin(Drugname,ios::binary|ios::in);
    if(!fin)
        cout<<'\n'<<AlignL()<<"No such drug exists!";
    else{
        cout<<AlignL()<<"Name of drug: "<<buff
            <<'\n'<<AlignL()<<"Total stock: "<<CurrentStock(fin)
            <<'\n'
            <<'\n'<<AlignL()<<"____________________________"
            <<'\n'<<AlignL()<<"Batch no\tStock\tPrice"
            <<'\n'<<AlignL()<<"____________________________";
        fin.seekg(0L);
        while(fin.read((char*)&d,sizeof(Drug)))
            if(d.getBatchNo())
                if(d.getStock())            //NON EXPIRED STOCK
                    d.Display();
                else if(d.getExpiry()==true){//STOCK 0 SINCE IT HAS EXPIRED
                    d.Display();
                    cout<<AlignL()<<"(Expired)";
                }

        cout<<'\n'
            <<'\n'<<AlignL();
            Div(57);
        }
}
