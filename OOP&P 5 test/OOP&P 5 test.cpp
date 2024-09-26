#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <queue>
#include <list>
using namespace std;
#pragma warning(disable 2061)
fstream file;

class Date
{
protected:
	int day;
	int month;
	int year;

	friend ostream& operator<<(ostream& stream, Date& date2);
	friend istream& operator>>(istream& stream, Date& date1);
	//friend bool operator()(Date& t1, Date& t2);
public:
	Date() { day = 0; month = 0; year = 0; }
	Date(const Date& source)
	{
		this->day = source.day;
		this->month = source.month;
		this->year = source.year;
	}
	bool isDateOK()
	{
		while (true)
		{
			if (this->day > 31 || this->day < 1)
				break;
			if (this->month > 12 || this->month < 1)
				break;
			if (this->year > 2024)
			{
				cout << "how's it like in the future? \n";
				break;
			}
			if (this->year < 1900)
			{
				cout << "Hi, dinosaur!\n";
				break;
			}
			return true;
		}
		cout << "Incorrect date, try again.\n";
		return false;
	}
	void DateFileInput()
	{
		string date;
		string buf = ".";
		date = to_string(this->day) + buf + to_string(this->month) + buf + to_string(this->year);
		file.write(date.c_str(), strlen(date.c_str()));
	}
	//friend bool Compare_2(Date& t1, Date& t2);
};
/*
bool Compare_2(Date& t1, Date& t2)
{
	if (t1.day < t2.day) return true;
	if (t1.day == t2.day && t1.month < t2.month) return true;
	if (t1.day == t2.day && t1.month == t2.month && t1.year < t2.year) return true;
	return false;
}

class CompareDate : public Date
{
public:
	bool operator()(app& t1, app& t2) {

		return Compare_2(t1.date, t2.date);
	}
};*/

class app  //все сортируется по выручке
{
private:
	string name;
	int users;
	Date date;
	int revenue;

	friend ostream& operator<<(ostream& stream, app& app2);
	friend istream& operator>>(istream& stream, app& app1);
	friend bool operator>(const app& app1,const app& app2);
	friend bool operator<(app& app1, app& app2);

	void caseOutput(int num)
	{
		switch (num)
		{
		case 1:
		{
			cout << "date = " << this->date << endl;
			break;
		}
		case 2:
		{
			cout << "amount of users = " << this->users << endl;
			break;
		}
		case 3:
		{
			cout << "revenue = " << this->revenue << endl;
			break;
		}
		default:
		{
			break;
		}
		}
	}
public:
	app() { name = ""; users = 0; date; revenue = 0; }
	app(const app& source)
	{
		this->name = source.name;
		this->users = source.users;
		this->date = source.date;
		this->revenue = source.revenue;
	}
	void filteredView(int num)
	{
		cout << this->name << endl;
		cout << "**************************************\n";
		caseOutput(num / 100);
		caseOutput((num - (num / 100) * 100) / 10);
		caseOutput((num - (num / 100) * 100 - ((num - (num / 100) * 100) / 10) * 10));
		cout << "**************************************\n";
	}
	void fileInput()
	{
		string buff_2, buff = ":    ";
		buff_2 = this->name + buff;
		file.write(buff_2.c_str(), strlen(buff_2.c_str()));
		this->date.DateFileInput();
		buff = "\namount of users = ";
		buff_2 = buff + to_string(this->users);
		file.write(buff_2.c_str(), strlen(buff_2.c_str()));
		buff = "\nrevenue = ";
		buff_2 = buff + to_string(this->revenue);
		file.write(buff_2.c_str(), strlen(buff_2.c_str()));
		buff = "\n**************************************\n";
		file.write(buff.c_str(), sizeof(buff));
	}
	string GetName()
	{
		return this->name;
	}

	//friend class CompareDate;
};

bool operator>(app& app1, app& app2)
{
	return app1.revenue > app2.revenue;
}
bool operator<(app& app1, app& app2)
{
	return app1.revenue < app2.revenue;
}

ostream& operator<<(ostream& stream, Date& date2)
{
	stream << date2.day << "." << date2.month << "." << date2.year;
	return stream;
}
istream& operator>>(istream& stream, Date& date1)
{
	stream >> date1.day;
	cout << ".";
	stream >> date1.month;
	cout << ".";
	stream >> date1.year;
	return stream;
}
ostream& operator<<(ostream& stream, app& app1)
{
	stream << app1.name << ": ";
	//stream << app1.date << "\n";
	stream << "**************************************\n";
	stream << "amount of users: " << app1.users << "\n";
	stream << "revenue: " << app1.revenue << "\n";
	stream << "**************************************\n";
	return stream;
}
istream& operator>>(istream& stream, app& app1) // проверки в задании не требуются
{
	cout << "Enter the name of th app: ";
	stream.ignore();
	getline(stream, app1.name);
	cout << "Enter the date of launch: ";
	while (!app1.date.isDateOK())
	{
		stream >> app1.date;
	}
	cout << "Enter the amount of users: ";
	stream >> app1.users;
	cout << "Enter the revenue: ";
	stream >> app1.revenue;
	return stream;
}




priority_queue<app, deque<app>, less<vector<app>::value_type>> appQue;
//queue<app, vector<app>> appQue;
queue<app, deque<app>> buffQue;
