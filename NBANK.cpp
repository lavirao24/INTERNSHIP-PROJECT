#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<cctype>
#include<iomanip>
#include <cstdlib>
#include<process.h>
#include<stdio.h>
#include<string.h>
using namespace std;

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
	char password[20];
public:
	void create_account();
	void show_account() const;
	void modify();
	void dep(int);
	void draw(int);
	void report() const;
	int retacno() const;
	char* retpass();
	int retdeposit() const;
	char rettype() const;
};

void account::create_account()
{
	cout<<"\nEnter The account No. :";
	cin>>acno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	cout<<"CREATE PASSWORD :";
	cin.ignore();
	cin.getline(password,20);
	cout<<"\n\n\nAccount Created..";
}

void account::show_account() const
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}


void account::dep(int x)
{
	deposit+=x;
}

void account::draw(int x)
{
	deposit-=x;
}

void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<" "<<deposit<<endl;
}


int account::retacno() const
{
	return acno;
}
char* account::retpass()
{
    return password;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}

void write_account();
void login(int,char[]);
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);

void main1()
{
    char ch;
	int num;
	system ("COLOR 09");
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. DEPOSIT AMOUNT";
		cout<<"\n\n\t02. WITHDRAW AMOUNT";
		cout<<"\n\n\t03. BALANCE ENQUIRY";
		cout<<"\n\n\t04. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t05. CLOSE AN ACCOUNT";
		cout<<"\n\n\t06. MODIFY AN ACCOUNT";
		cout<<"\n\n\t07. EXIT";
		cout<<"\n\n\tSelect Your Option (1-7) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '4':
			display_all();
			break;
		case '5':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '7':
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='7');
}



int main()
{
	char ch;
	int num;
	char pass[20];
	do
	{
		system("cls");
		system ("COLOR 03");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. LOGIN";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tSelect Your Option (1-3) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			cout<<"\n\n\tENTER THE PASSRORD. :";
	        cin.ignore();
            cin.getline(pass,20);
			login(num,pass);
			break;
		 case '3':
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='3');
	return 0;
}


void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

void login(int n,char pass[])
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if((ac.retacno()==n)&&(strcmp(ac.retpass(),pass)==0))
		{
			flag=true;
			main1();
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nWRONG PASSWORD";
}



void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}



void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}


void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.       NAME           Type       Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}


void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}
