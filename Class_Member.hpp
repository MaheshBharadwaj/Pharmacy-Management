///Class_Member.hpp

class Member{

private:
	unsigned short int mno;
	char name[25];
	char mtype; 		///S-Silver(5%),
                        ///G-Gold(7.5%),
                        ///P-Platinum(10%)
	char ph[11];
	unsigned short int count;

	float discount(){
		float Disc;
		switch(mtype){
			case 'P':
			case 'p': Disc=10.0;break;
			case 'G':
			case 'g': Disc=7.5;break;
			case 'S':
			case 's': Disc=5.0;break;
			default: Disc=0.0;
                    }
    return Disc;
        }

public:
	Member(const unsigned short int m){
		count=0;
		mno=m;
		mtype='S';
	}
	Member(){
		mno=count=0;
		mtype=ph[0]=name[0]='\0';
		}
	void setcount(const int a){
		count=a;
	}
	void accept(bool temp=true){	///to decide as to whether member no.
                                    ///has to be display
		cin.sync();
		cout<<'\n'<<AlignL()<<"Enter Name(MAX 25): ";
		cin.getline(name,25);

        cout<<AlignL()<<"Enter Phone No.: ";

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
        cin.get();//TO REMOVE ENTER CHARACTER

        ph[10]='\0';

		if(temp)
			cout<<'\n'<<AlignL()<<"Your unique membership No.: "<<mno;
	}

	void Delete(){
		mno=0;
	}

	void Display(){
		cout<<'\n'<<AlignL()<<"Mno: "<<mno<<" Name: "<<name
            <<"  Ph: "<<ph<<"  Membership type: ";

		cout<<((mtype=='s'||mtype=='S')?"Silver":
              ((mtype=='P'||mtype=='p')?"Platinum": "Gold"));
	}
	int GetMno(){
		return mno;
	}
	char* getName(){
		return name;
		}
    char * getPH(){
        return ph;
    }

	double GetMdisc(fstream &f){
		if(count>99)
			mtype='P';
		else if(count>49)
			mtype='G';
		count++;
		f.seekp(long(-sizeof(Member)),ios::cur);
		f.write((char*)this,sizeof(Member));
		return discount();
	}
};



