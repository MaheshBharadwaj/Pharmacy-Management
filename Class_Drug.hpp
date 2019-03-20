///Class_Drug.hpp

class Drug{
private:
	bool expire;
	unsigned int batch_no;
	char name[25];
	char Supplier_name[30];
	char Supplier_contact[30];
    unsigned int stock;
	float price,loss;
    short int date,month,year;
public:

   Drug(){
        expire = false;
        batch_no = 0;
        stock = price = 0;
        date = month = year = 0;
        name[0] = '\0';
        loss = 0;
        Supplier_contact[0] = '\0';
        Supplier_name[0] = '\0';
    }

    void Display(){
        cout<<'\n'<<AlignL()<<batch_no<<"\t\t"<<stock<<"\t"<<price;
    }

    void setName(const char* const N){
        strcpy(name,N);
     }
    void setStock(const int st){
		stock=st;
		expire=false;
    }
    void setPrice(const float p){
		price=p;

    }
    void setDate(const int D){
		date=D;
    }
    void setMonth(const int M){
		month=M;
    }
    void setYear(const int Y){
		year=Y;
    }
    void setSupplierName(const char * const str){
    	strcpy(Supplier_name,str);
    }

    void setSupplierContact(const char * const str){
    	strcpy(Supplier_contact,str);
    }
    void SetBatchNo(const int a){
      batch_no=a;
    }
    void setExpiryFalse(){
    	expire=false;
    }

    char* getName(){
    	return name;
       }

    int getStock(){
        return stock;}

    float getPrice(){
        return price;}

    float getLoss(){
        return loss;}

    int getDate(){
        return date;}

    int getMonth(){
        return month;}

    int getYear(){
        return year;}

    char* getSupplierName(){
		return Supplier_name;}

	 char* getSupplierContact(){
		return Supplier_contact;}

	 int getBatchNo(){
		return batch_no;}

	 bool getExpiry(){
		return expire;}

	 void Expire(){
		expire = true;
        loss = price * stock;
        stock = 0;
		}
};
