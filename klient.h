#pragma once
#include <iostream>
#include <conio.h>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <string>

using namespace std;

class klient
{
public:
	klient()
	{
		cout << "Witamy w systemie cateringowym do skladania zamowien" << endl;
	}
};

class Kompilowanie
{
public:
	Kompilowanie(double initial_balance)
	{
		balance = initial_balance;
	}
	double GetBalance();
	double Deposit(double Amount);
	double Withdraw(double Amount);
protected:
	double balance;
};

inline double Kompilowanie::GetBalance()
{
	return balance;
}

inline double Kompilowanie::Deposit(double Amount)
{
	return (balance += Amount);
}

inline double Kompilowanie::Withdraw(double Amount)
{
	return (balance -= Amount);
}
