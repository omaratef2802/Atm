#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct stClient{
    
    string NumberOfAccount;
    string PinCode;
    string Name;
    string Phone;
    double Balance;
};

vector<string> detleDalim(string FullName,string delim){
    
    short pos=0;
    vector<string> After;
    string Temp;
    while ((pos=FullName.find(delim))!=string::npos) {
        
        Temp=FullName.substr(0,pos);
        
        if (Temp!="") {
            After.push_back(Temp);
        }
        FullName.erase(0,delim.length()+pos);
        Temp="";
    }
    
    if (FullName!="") {
        After.push_back(FullName);
    }
    
    return After;
}

stClient LoadFromVectorFile(string delim,string FulName){
    
    vector<string> Temp=detleDalim(FulName, delim);
    stClient cls;
    
    cls.NumberOfAccount=Temp.at(0);
    cls.PinCode=Temp.at(1);
    cls.Name=Temp.at(2);
    cls.Phone=Temp.at(3);
    cls.Balance=stod(Temp.at(4));
    
    return cls;
}

string SaveToFile(stClient cls,string delim){
    
    string newclient;
    
    newclient=cls.NumberOfAccount+delim;
    newclient+=cls.PinCode+delim;
    newclient+=cls.Name+delim;
    newclient+=cls.Phone+delim;
    newclient+=to_string(cls.Balance);
    
    return newclient;
}

vector<stClient> LoadFromFile(string Name){
    
    fstream MyFile;
    stClient cls;
    vector<stClient> vcls;
    MyFile.open(Name,ios::in);
    
    while (MyFile.is_open()) {
     
        string Line;
        
        while (getline(MyFile,Line)){
            if (Line!="") {
                cls=LoadFromVectorFile("#//#", Line);
                vcls.push_back(cls);
            }
        }
        MyFile.close();
    }
    return vcls;
}

void SaveToFileAfterChange(stClient &cls){
    
    vector<stClient> vcls=LoadFromFile("MyFile.txt");

    fstream MyFile;
    string Line;
    
    MyFile.open("MyFile.txt",ios::out);
    
    while (MyFile.is_open()) {
        
        for (stClient & c : vcls) {
            
            if (c.NumberOfAccount!=cls.NumberOfAccount) {
                
            Line=SaveToFile(c,"#//#");
            MyFile<<Line<<endl;
                
            }   else {
                
                Line=SaveToFile(cls,"#//#");
                MyFile<<Line<<endl;
                
            }

        }
        
        MyFile.close();
    }

}

void HeaderForLogin(){
    
    cout<<"=================================================="<<endl;
    cout<<right<<setw(20)<<"Login Screen"<<endl;
    cout<<"=================================================="<<endl;

}

bool CheckFindUser(string Name,string Password,stClient & cls){
    
    vector<stClient> vcls=LoadFromFile("MyFile.txt");
    
    for (stClient & c : vcls) {
        
        if (c.NumberOfAccount==Name&&c.PinCode==Password) {
            cls=c;
            return 1;
        }
    }
    
    return 0;
}

void _4CheckBalance(stClient cls){
    
    cout<<"Your Balance is "<<cls.Balance<<endl<<endl;
    
}

void ChengeBalance(stClient &cls,int Depost){
    
    char C;
    cout<<endl<<"Are you sure you want perfrom this transaction? y/n ? ";cin>>C;
    
    if (tolower(C)=='y') {
        
        cls.Balance+=Depost;
    }

    cout<<endl<<endl<<"Done Successfully. New balance is : "<<cls.Balance<<endl<<endl;
    
    SaveToFileAfterChange(cls);
    
}

void Print1(){
    
    cout<<"=================================================="<<endl;
    cout<<"\t[1] 100\t\t\t [2] 500 "<<endl;
    cout<<"\t[3] 1000\t\t [5] 2000"<<endl;
    cout<<"\t[4] 3000\t\t [6] 4000 "<<endl;
    cout<<"\t[7] Exist"<<endl<<endl;
    cout<<"=================================================="<<endl<<endl;
    
}

int ChioseNumberOfWithDraw(){
    
    int Number;
    cout<<"Choose what to withdraw from [1] to [7] ? : ";cin>>Number;
    
    while (Number>7) {
        
        cout<<"The Invalid Number ,\n\n Please enter The Numebr from [1] to [6] ";cin>>Number;
        
    }
    
    return Number;
}

void _1Withdraw(stClient &cls){
    
    Print1();
    _4CheckBalance(cls);
    
    int Number=ChioseNumberOfWithDraw()-1;
    
    if (Number+1==7) {
        return;
    }
    
    int arr[]={100,500,1000,2000,3000,4000};
    
    while (arr[Number]>cls.Balance) {
         
        cout<<"The amount exceeds your balance, make another choice."<<endl<<endl;
        cout<<"Please enter The Number Not Greater Than "<<cls.Balance<<endl<<endl;
        Number=ChioseNumberOfWithDraw()-1;
    }
    
    
    ChengeBalance(cls,-arr[Number]);
    
}

void _2Withdraw(stClient &cls){
    
    int Number;
    cout<<"Enter a Withdarw Amount : ";cin>>Number;
    
    while (Number>cls.Balance) {
         
        cout<<"The amount exceeds your balance, make another choice."<<endl<<endl;
        cout<<"Please enter The Number Not Greater Than "<<cls.Balance<<"  : ";cin>>Number;
    }

    ChengeBalance(cls,-Number);

}

void _3Diagonst(stClient& cls){
        
    int Number;
    cout<<"Enter a positive Deposit Amount : ";cin>>Number;
    ChengeBalance(cls,Number);
    
}

void PrintAllMethods(int Number,stClient &cls){
    
    switch (Number) {
            
        case 1:_1Withdraw(cls);break;
        case 2:_2Withdraw(cls);break;
        case 3:_3Diagonst(cls);break;
        default:_4CheckBalance(cls);break;
    }
    
}

void MenuScreen(){
    
    cout<<"=================================================="<<endl;
    cout<<right<<setw(40)<<"Atm Main Menue Screen"<<endl;
    cout<<"=================================================="<<endl<<endl;

    cout<<right<<setw(30)<<"[1] Quick Withdraw."<<endl;
    cout<<right<<setw(31)<<"[2] Normal Withdraw."<<endl;
    cout<<right<<setw(23)<<"[3] Deposit."<<endl;
    cout<<right<<setw(29)<<"[4] Check Balance."<<endl;
    cout<<right<<setw(22)<<"[5] Logout."<<endl<<endl;
    cout<<"=================================================="<<endl;

}

int ReadNumberChoise(){
    int num;
    cout<<"Choose what do you want to do? [1 to 5] ? : ";cin>>num;
    
    while (num>5){
        
        cout<<"the number doesnt exist in Range ";
        cout<<"please Choose what do you want to do? [1 to 5] ? : ";
        cin>>num;
    }
    cout<<endl;
    
    return num;
}

bool FindUserByNameAndPassword(string Name,string Password,stClient &cls){
    
        if (CheckFindUser(Name,Password,cls)) {
        
        return 1;
    }
    
    return 0;
}


void Login(){
    
    char Reb='y';
    
    while (tolower(Reb)=='y') {
        
        string AccountNumber;
        stClient cls;
        string Password;
        HeaderForLogin();
        
        cout<<"Enter Account Number? ?  : ";cin>>AccountNumber;
        ;cout<<"Enter Pin ? : ";cin>>Password;
        
        
        while (!FindUserByNameAndPassword(AccountNumber, Password, cls)) {
            
            cout<<endl<<"Invlaid Username/Password! "<<endl;
            cout<<"Enter Account Number? ?  : ";cin>>AccountNumber;
            cout<<"Enter Pin ? : ";cin>>Password;

        }
        
        MenuScreen();
        int Number=ReadNumberChoise();
        
        while (Number<5){
            
            PrintAllMethods(Number,cls);
            MenuScreen();
            Number=ReadNumberChoise();
            
            
        }
        
        cout<<"If you Want to Complete ? y/n ";cin>>Reb;
        cout<<endl<<endl;
    }
    
}

int main(){
    
    Login();
    
    return 0;
}
