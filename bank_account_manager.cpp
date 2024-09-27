#include<iostream>
#include<fstream>
#include<sstream>
#include<windows.h>
#include<ctime>
#include<cstdlib>

using namespace std;



class Account{
private:
    int Balance;
    string AccountNo, Password;
public:
Account(): AccountNo(""), Password(""), Balance(0){}

void setAccountNo(string id){
    AccountNo = id;
}

void setPassword(string pwd){
    Password = pwd;
}

void setBalance(int bal){
    Balance = bal;
}


string getAccountNo(){
    return AccountNo;
}

string getPassword(){
    return Password;
}

int getBalance(){
    return Balance;
}

};

void openAccount(Account user){
    system("cls");
    string ID, Pwd;


    int input;
    cout<<"\t1.If you want to enter Account No. manually"<<endl;
    cout<<"\t2.Random Account No."<<endl;
    cout<<"\t  Enter your choice: ";
    cin>>input;


    // getting bank account 
    system("cls");

    if(input == 1){
        cout<<"\tEnter your Account No. of 5 digits: ";
        cin>>ID;
        if(ID.size() != 5){
            cout<<"\tPlease enter valid Account No:"<<endl;
            return;
        }

        user.setAccountNo(ID);

        ifstream infile(R"(D:\IIT H\placement\project\bank Account\accountdetails.txt)");
        if(!infile){
            cout<<"\tError: Couldn't open files.";
            return;
        }
        string line;
        while(getline(infile,line)){
            stringstream ss(line);

            string UserID, UserPwd;
            int userBalance;
            char delimiter;

            ss>>UserID>>delimiter>>UserPwd>>delimiter>>userBalance;
            if(UserID == ID){
                cout<<"\tAccount No. already exists."<<endl;
                return;
            }

        }
    infile.close();
    }

    if(input == 2){
        srand(time(0));
        int randomNumber = 10000 + rand() % 90000;
        ID = to_string(randomNumber);

        user.setAccountNo(ID);

        ifstream infile(R"(D:\IIT H\placement\project\bank Account\accountdetails.txt)");
        string line;
        while(getline(infile, line)){
            stringstream ss(line);
            string userID, userPwd;
            int userBalance;
            char delimiter;

            ss>>userID>>delimiter>>userPwd>>delimiter>>userBalance;

            if(userID == ID){
                cout<<"\tError in generating Account No."<<endl;
                cout<<"\tPlease try again.";
                return;
            }
        }
        infile.close();

        cout<<"\tYour Account No. is: "<<ID<<endl;
        infile.close();

    }



    //getiing Password
    cout<<"\tEnter strong Password: ";
    cin>>Pwd;
    user.setPassword(Pwd);

    // updating balance as 0
    user.setBalance(0);

    ofstream outfile(R"(D:\IIT H\placement\project\bank Account\accountdetails.txt)", ios::app);
    if(!outfile){
        cout<<"\tError: Couldn't open files.";
    }
    else{
        outfile<<"\t"<<user.getAccountNo()<<" : "<<user.getPassword()<<" : "<<user.getBalance()<<endl;
        cout<<"\tAccount created succesfully"<<endl;
    }

    outfile.close();

    Sleep(5000);
}

void DepositeCash(){
    system("cls");
    string ID, Pwd;
    cout<<"\tEnter your Account No: ";
    cin>>ID;
    cout<<"\tEnter Your Password: ";
    cin>>Pwd;

    ifstream infile(R"(D:\IIT H\placement\project\bank Account\accountdetails.txt)");
    ofstream outfile(R"(D:\IIT H\placement\project\bank Account\accountdetails temp.txt)");

    if(!infile || !outfile){
        cout<<"\tError: Couldn't open files."<<endl;
    }

    string line;
    bool found = false;

    while(getline(infile, line)){
        stringstream ss;
        ss<<line;
        string userID, userPwd;
        int userbalance;
        char delimiter;

        ss>>userID>>delimiter>>userPwd>>delimiter>>userbalance;
        if(userID == ID && userPwd == Pwd){
          found = true;

          int cash;
          cout<<"\tEnter Amount: ";
          cin>>cash;  

          int newBalance = userbalance + cash;
          userbalance = newBalance;

          outfile<<"\t"<<userID<<" : "<<userPwd<<" : "<<userbalance<<endl;
          cout<<"\tNew Balance is: "<<userbalance<<endl;
        }
        else{
            outfile<<line<<endl;
        }
    }
    if(!found){
        cout<<"\tEnter valid Account No: "<<endl;
    }
    outfile.close();
    infile.close();
    remove(R"(D:\IIT H\placement\project\bank Account\accountdetails.txt)");
    rename(R"(D:\IIT H\placement\project\bank Account\accountdetails temp.txt)", R"(D:\IIT H\placement\project\bank Account\accountdetails.txt)");
        
    Sleep(5000);
}

void withdrawCash(){
    system("cls");

    string ID, Pwd;
    cout<<"\tEnter Account No: ";
    cin>>ID;

    cout<<"\tEnter Password: ";
    cin>>Pwd;

    ifstream infile(R"(D:\IIT H\placement\project\bank Account\accountdetails.txt)");
    ofstream outfile(R"(D:\IIT H\placement\project\bank Account\accountdetails temp.txt)");


    if(!infile || !outfile){
        cout<<"\tError: Couldn't open files."<<endl;
        return;
    }

    string line;
    bool found = false;
    while(getline(infile,line)){
        stringstream ss(line);

        string userID, userPwd;
        int userBalance;
        char delimiter;

        ss>>userID>>delimiter>>userPwd>>delimiter>>userBalance;

        if(userID == ID && userPwd == Pwd){
            found = true;
            int amount;
            cout<<"\tEnter the amount to withdraw: ";
            cin>>amount;
            if(amount>userBalance){
                cout<<"\tInsufficient Balance"<<endl;
                outfile<<userID<<" : "<<userPwd<<" : "<<userBalance<<endl;
            }
            else{
                cout<<"\tRs "<<amount<<" has been withdrawal"<<endl;
                int newbalance = userBalance - amount;
                userBalance = newbalance;
                cout<<"\tNew Balance is: "<<userBalance<<endl;
                outfile<<userID<<" : "<<userPwd<<" : "<<userBalance<<endl;
            }
        }
        else{
            outfile<<line<<endl;
        }
    }

    if(!found){
        cout<<"\tEnter Correct Details.";
    }

    infile.close();
    outfile.close();
    remove(R"(D:\IIT H\placement\project\bank Account\accountdetails.txt)");
    rename(R"(D:\IIT H\placement\project\bank Account\accountdetails temp.txt)",R"(D:\IIT H\placement\project\bank Account\accountdetails.txt)");
 
    Sleep(5000);
}


void balance(){

    system("cls");

    string ID, Pwd;
    cout<<"\tEnter Account No: ";
    cin>>ID;

    cout<<"\tEnter Password: ";
    cin>>Pwd;


    ifstream infile(R"(D:\IIT H\placement\project\bank Account\accountdetails.txt)");

    if(!infile){
        cout<<"\tError: Couldn't open files.";
        return;
    }

    bool found = false;
    string line;

    while(getline(infile,line)){
        stringstream ss;
        ss<<line;

        string userID, userPwd;
        int userBalance;
        char delimeter;
        ss>>userID>>delimeter>>userPwd>>delimeter>>userBalance;

        if(userID == ID && userPwd == Pwd){
            found = true;
            cout<<"\tBank Balance: "<<userBalance<<endl;
        }
    }

    if(!found){
    cout<<"\tEnter Correct Details."<<endl;
    }
    infile.close();

    Sleep(5000);
}






int main(){
Account user;


bool exit = false;

while(exit == false){
    system("cls");


    int val;

    cout<<"\tWelcome to Bank Account Management System"<<endl;
    cout<<endl;
    cout<<"\t1.Create New Account"<<endl;
    cout<<"\t2.Deposite Cash"<<endl;
    cout<<"\t3.Withdraw Cash"<<endl;
    cout<<"\t4.Bank Balance"<<endl;
    cout<<"\t5.Exit"<<endl;
    cout<<"\t Enter Your Choice: ";
    cin>>val;

    if(val == 1){
        openAccount(user);
    }

    else if(val == 2){
        DepositeCash();
    }

    else if(val == 3){
        withdrawCash();
    }
    else if(val == 4){
        balance();
    }

    else if(val == 5){
        system("cls");
        cout<<"\tTHANK YOU"<<endl;
        return 0;
    }



    Sleep(3000);
}

}