///Discount Management.hpp

/**
This header file contains functions catering to discount
management in the pharmacy
    1.Set discount rate to be applied on all bills
    2.To modify the previously set rate
    3.To reset the discount value to 0
*/

void SetDiscount(float *Disc){
    system(CLEAR);
    cout<<AlignV();
    cout<<'\n'<<AlignL()<<"__________________________________________"
        <<'\n'<<AlignL()<<"      DISCOUNT IMPLEMENTATION WINDOW      "
        <<'\n'<<AlignL()<<"__________________________________________";
    char ch;
    do{
        cout<<'\n'<<AlignL()<<"Enter discount rate(%) for the day: ";
        cin>>*Disc;

        if(!cin){
            cin.clear();
            cin.sync();
            *Disc=-1;
        }

        if(*Disc<=0||*Disc>=100)
            cout<<'\n'<<AlignL()<<"\aInvalid";

    }while(*Disc<=0||*Disc>=100);

    cout<<'\n'<<AlignL()<<"Confirm? Y/N: ";
    cin>>ch;
    cin.sync();
    *Disc=((ch=='Y'||ch=='y')?(*Disc):0);
    cout<<'\n'<<AlignL()<<"Returning to offers management window";
}

void ModifyDiscount(float* Disc){
    system(CLEAR);
    cout<<AlignV();
    cout<<'\n'<<AlignL()<<"___________________________________________"
        <<'\n'<<AlignL()<<"     DISCOUNT RATE MODIFICATION WINDOW     "
        <<'\n'<<AlignL()<<"___________________________________________";

    char ch;
    cout<<'\n'<<AlignL()<<"Current rate: "<<*Disc<<"%"
        <<'\n'<<AlignL()<<"Modify? Y/N: ";
    cin>>ch;
    cin.sync();
    if(ch=='y'||ch=='Y'){
        do{
            cout<<'\n'<<AlignL()<<"Enter the new discount rate: ";
            cin>>*Disc;

            if(!cin){
                cin.clear();
                cin.sync();
                *Disc=-1;
            }

            if(*Disc<=0||*Disc>=100)
                cout<<AlignL()<<"\aInvalid";

        }while(*Disc<=0||*Disc>=100);
    }
    else
        cout<<'\n'<<AlignL()<<"Returning to Offer management window";
}

void ResetDiscount(float* Disc){
    system(CLEAR);
    cout<<AlignV();
    cout<<'\n'<<AlignL()<<"_________________________________________"
        <<'\n'<<AlignL()<<"       REMOVE DISCOUNT RATE WINDOW       "
        <<'\n'<<AlignL()<<"_________________________________________";
    char ch;
    if(!(*Disc))
        cout<<'\n'<<AlignL()<<"No discounts applied!"
            <<'\n'<<AlignL()<<"Returning to offers management window";
    else{
        cout<<'\n'<<AlignL()<<"Confirm? Y/N: ";
        cin>>ch;
        cin.sync();
        *Disc=((ch=='y'||ch=='Y')?0:(*Disc));
        cout<<'\n'<<AlignL()<<
            ((ch=='y'||ch=='Y')?
            "Successfully reset discount!" :
            "Returning to offers management window");
       }

}


void DiscountManagement(float* Disc){
    int opt;
    char ch;
    bool retry=true;
    while(retry){
        system(CLEAR);
        cout<<AlignV();
        cout<<'\n'<<AlignL()<<"_____________________________________________"
            <<'\n'<<AlignL()<<"           OFFER MANAGEMENT WINDOW           "
            <<'\n'<<AlignL()<<"_____________________________________________"
            <<'\n'<<AlignL()<<"1 - Set discount"
            <<'\n'<<AlignL()<<"2 - Modify discount"
            <<'\n'<<AlignL()<<"3 - Remove discount"
            <<'\n'<<AlignL()<<"0 - Back"
            <<'\n'
            <<'\n'<<AlignL()<<"_____________________________________________"
            <<'\n'<<AlignL()<<"Enter your choice: ";

        cin>>opt;
        cin.get();
        if(!cin){
            cin.clear();
            cin.sync();
            opt=-1;
        }
        switch(opt){
            case 1 : SetDiscount(Disc);      break;
            case 2 : ModifyDiscount(Disc);   break;
            case 3 : ResetDiscount(Disc);    break;
            case 0 : retry = false;          break;
            default: cout<<'\a';
        }

        if(retry==true){
            cout<<'\n'<<AlignL()<<"Press any key to continue.............."
                <<'\n'<<AlignL();
            getch();
            }
      }
}

