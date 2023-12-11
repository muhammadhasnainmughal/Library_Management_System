#include<iostream>
using namespace std;
int main()
{
	//interface
	cout << "\t\t\t\t\t-------------------------------" << endl;
	cout << "\t\t\t\t\t   Library Management System" << endl;
	cout << "\t\t\t\t\t-------------------------------" << endl;
	
	cout << "-----------------" << endl ;
	cout << "      Login!" << endl;
	cout << "-----------------" << endl;
	
	//make login system
	string username,password;
	
	cout << "Enter Username: ";
	cin >> username;
	
	cout << "Enter Password: ";
	cin >> password;

	if(username == "admin" && password == "admin")
	{
		cout << "Login Successfully..." << endl;
	}
	else
	{
		cout << "Invalid Username or Password Tryagain" << endl;
	}
	
        system("PAUSE");
		system("CLS");
	
	
	
	
	return 0;
}

