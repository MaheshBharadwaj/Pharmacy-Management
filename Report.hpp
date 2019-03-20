///Report.hpp

/**
This Header file contains functions that:
    1. Write to report the details of:
        1.1- Expired batches of drugs
        1.2- Drugs low on stock
        1.3- Drugs having no stock
    2.Updating Report after each bill generated
    3.Generating a report on all drugs and sale for the day
    4.Viewing the generated report
**/

void expire(int&t,float &NetLoss,ofstream &f,Drug&d){
	f<<'\n'
     <<'\n'<<++t<<"\a)Drug: "<<d.getName()
     <<" Batch: "<<d.getBatchNo()<<" has expired!"
	 <<'\n'<<"  Loss incurred: "<<d.getLoss();
	 NetLoss+=d.getLoss();
}
void LowStock(int &t,const int stock,ofstream &f,Drug &d){
   	f<<'\n'
     <<'\n'<<++t<<"\a)Drug: "<<d.getName()<<" is low on stock ("<<stock
     <<" LEFT).Please order new stock"
     <<"\n  Supplier name: "<<d.getSupplierName()
     <<"\n  Contact Supplier: "<<d.getSupplierContact();
}
void NoStock(int &t,ofstream &f,Drug &d){
   	f<<"\n\n"<<++t<<"\a)Drug: "<<d.getName()<<" is un-available.Please stock"
   	 <<'\n'<<"  Supplier name: "<<d.getSupplierName()
   	 <<"\n  Contact Supplier: "<<d.getSupplierContact();
}
void UpdateReport(float total,int quantity){///Updating report after each bill
    char buffer[50];
    time_t t=time(0);
    tm *now=localtime(&t);
    int cdate=now->tm_mday,
        cmon=now->tm_mon+1,
		 cyear=now->tm_year+1900;
	int stock;
    double tot;
    ifstream f("Bin\\Report.txt",ios::in);
    int date,month,year;
    if(f){
		f>>buffer>>date>>month>>year;
		if(date==cdate&&month==cmon&&year==cyear){   ///If it is the same day
        f>>buffer>>buffer>>stock>>buffer>>buffer>>tot;
        quantity+=stock;   		///Previous values are added and carried over
        total+=tot;
			}
		f.close();
		ofstream fout("Bin\\Report.txt"); ///Writing to Report
		if(!fout)
			cout<<"\n\aUnable to create file: ";
		else{
		fout<<"Date: "<<cdate<<' '<<cmon<<' '<<cyear<<endl
            <<"Stock Sold: "<<quantity<<endl<<"Total Amount: "<<total;
		fout.close();
		}
    }
    else
		cout<<"\n\aUnable to access file";

}

void GenerateReport(const int currentDate,const int currentMonth,
                                          const int currentYear)
{
///Warnings to display to the administrator
	int stock=0;
	char  buffer[50]; ///to store junk
	double total=0;
	fstream f;	      ///file object for each drug file;

	ifstream R_old("Bin\\Report.txt");///to get previous data if possible
	if(R_old){
		int date,month,year;
		R_old>>buffer>>date>>month>>year>>buffer>>buffer
             >>stock>>buffer>>buffer>>total;
		if(currentYear==year&&currentMonth==month&&currentDate==date)
			;
		else
			stock=total=0;
		R_old.close();
	}

	ofstream Report("Bin\\Report.txt",ios::trunc); //generating fresh report
	if(Report){
		Report<<"Date: "<<currentDate<<' '<<currentMonth<<' '<<currentYear<<endl
              <<"Stock Sold: "<<stock<<endl<<"Total Amount: "<<total;

		Drug d;

		DIR *dir;		        ///object of type file folder(Directory)
		dirent *entry;          ///object of type: directory entry
		dir = opendir ("Medicines\\");  ///linking directory

		int count=0;	        ///Number of messages
		float NetLoss=0;
		if (dir) {		    	///the directory exists
		  entry=readdir(dir);	///attempt reading directory

		  while (entry) {		///if attempt was successful
				if(*(entry->d_name)!='.'){

					char Filename[45]="Medicines\\";///for accessing file
					strcat(Filename,entry->d_name);	///appending 'entry' to Filename
					f.open(Filename,ios::binary|ios::in|ios::out);
					if(!f)
						cout<<"\nUnable to access file";
					else{
						int Stock=CurrentStock(f);  ///Total stock across batches
						f.seekg(0L);
						if(Stock>0){
							short int i=1;
							while(i<=5){
								f.read((char*)&d,sizeof(Drug));
								if(d.getExpiry()){
									expire(count,NetLoss,Report,d);

									///To avoid displaying expiry message every time
									d.setExpiryFalse();

									f.seekp((long)(-sizeof(Drug)),ios::cur);
									f.write((char*)&d,sizeof(Drug));
								}
								i++;
							}
							if(Stock<50)
								LowStock(count,Stock,Report,d);
							}
						else{
							for(short int i=0;i<5;i++){
								f.read((char*)&d,sizeof(Drug));
								if(d.getExpiry()){
									expire(count,NetLoss,Report,d);
									d.setExpiryFalse();
									f.seekp((long)(-sizeof(Drug)),ios::cur);
									f.write((char*)&d,sizeof(Drug));
								}
							}
							NoStock(count,Report,d);
						}
						f.close();
					}
				}
			entry = readdir (dir); ///attempt to read further in the given directory
		  }
		  closedir (dir);           ///closing directory

		  if(NetLoss)				///Due to expired drugs
				Report<<"\n\n"<<"NET LOSS: "<<NetLoss;

		}

		else
			cout<<"\nUnable to generate report!";

		Report.close();
		}
}

void DisplayReport(){
	system(CLEAR);
	cout<<AlignV();
	cout<<'\n'<<AlignL()<<"Processing report";
	for(int i=0;i<5;i++){
		cout<<"...";
		Sleep(500);
	}
   ifstream f("Bin\\Report.txt");
   char ch;
   if(!f)
		cout<<"\n\aUnable to access report";
	else{
        system(CLEAR);
        cout<<"\n\n\n\n\n";
		cout<<"\n\t\t\t\t";
            Div(77);
        cout<<"\n\t\t\t\t"<<"                           REPORT VIEWING WINDOW"
            <<"\n\t\t\t\t";
            Div(77);
        cout<<"\n\t\t\t\t";

		while(f.read(&ch,1)){
            cout<<ch;
			if(ch=='\n')
                cout<<"\t\t\t\t";
		}
        cout<<"\n\t\t\t\t";
            Div(77);
        cout<<"\n\t\t\t\t"<<"Press any key to continue............"
            <<"\n\t\t\t\t";
        getch();
        f.close();
        }
}


