///Daily Operations.hpp

/**
This header files has functions that:
    1.Check if given drug has expired
    2.Sorting drugs batch-wise to ensure oldest batch is
      sold first
    3.A function called daily to order and check for
      expired drugs in the pharmacy
    4.A function that returns available stock of a drug
**/

int CurrentStock(fstream &f){///Total available stock of a drug
   f.seekg(0L);
	Drug d;
	int stock=0;
   for(short int i=1;i<=5;i++){
		f.read((char*)&d,sizeof(Drug));
			stock+=d.getStock();
   }
   f.seekg(0L);
   return stock;
}

void CheckExpiry(const int CD,const int CM,const int CY,fstream &f){
	Drug d[5];
	f.seekg(0L);
	f.read((char*)d,sizeof(Drug)*5);
	for(short int i=0;i<5;i++){
		int Y=d[i].getYear(),M=d[i].getMonth(),D=d[i].getDate();
		if( Y&&D&&M && d[i].getStock()){   ///To ignore batch templates/
                                           ///Old empty batches
			///Expiry check:
			if(CY>Y)
				d[i].Expire();
			else if(CY==Y&&CM>M)
				d[i].Expire();
			else if(CY==Y&&CM==M&&CD>=D)
				d[i].Expire();
		}
	}
	f.seekp(0L);
	f.write((char*)d,sizeof(Drug)*5);
	f.seekp(0L);
}

void SortDrug(fstream &f){
///Sorts the given drug in ascending order of batch

	Drug d[5];
	f.seekg(0L);
	f.read((char*)d,5*sizeof(Drug));
	for(int i=4;i>=0;i--){///BINARY SORT SINCE SMALL ARRAY
		for(int j=0;j<i;j++){
			if(d[j].getBatchNo() > d[j+1].getBatchNo()){
				Drug tmp=d[j+1];
				d[j+1]=d[j];
				d[j]=tmp;
				}
			}
		}
		f.seekp(0L);
		f.write((char*)d,5*sizeof(Drug));
		f.seekp(0L);
}


void Check_For_Expiry(const int CD,const int CM,const int CY){
///Checks all drugs to check for expired drugs

   fstream f;
   Drug d[5];
   DIR *dir = opendir("Medicines\\");
   dirent *ent = readdir(dir);
   while(ent){
		char filename[45]="Medicines\\";
		strcat(filename,ent->d_name);
		f.open(filename,ios::binary|ios::in|ios::out);
		if(f.good())
			CheckExpiry(CD,CM,CY,f);

		f.close();
		ent = readdir(dir);
   }
   closedir(dir);
}




