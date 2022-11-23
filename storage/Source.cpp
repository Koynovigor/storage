#include <iostream>
#include <string>

using namespace std;

class Storage
{
	string address;
};

class Area
{

};

class Date
{
	int m_day;
	int m_month;
	int m_year;
public:
	Date(int day = 1, int month = 1, int year = 2000) {
		if ((day * month * year) == 0) {
			printf("Date is not valid! /set defolt/\n");
			day = 1; month = 1; year = 2000;
		}
		m_day = day; m_month = month; m_year = year;
	};

	string get_date() {
		return (string)(to_string(m_day) + "." + to_string(m_month) + "." + to_string(m_year));
	};

	void set_date(int day, int month, int year) {
		if ((day * month * year) == 0) {
			printf("Date is not valid! /set defolt/\n");
			day = 1; month = 1; year = 2000;
		}
		m_day = day;
		m_month = month;
		m_year = year;
	};

	int get_day() { return m_day; };
	int get_month() { return m_month; };
	int get_year() { return m_year; };
	void set_day(int day) { if (day > 0) m_day = day; };
	void set_month(int month) { if (month > 0) m_month = month; };
	void set_year(int year) { if (year > 0) m_year = year; };
};

class Report
{
	Date delivery_date;
	Date ship_date;
	int count_in_area;
public:
	Report(int day = 1, int month = 1, int year = 2000, int count = 1) {
		delivery_date.set_date(day, month, year);
		ship_date.set_date(day, month, year + 20);
		count_in_area = count;
	};

	void set_delivery_date(int day, int month, int year) {
		delivery_date.set_date(day, month, year);
	};
	string get_delivery_date() {
		return delivery_date.get_date();
	}

	void set_ship_date(int day, int month, int year) {
		ship_date.set_date(day, month, year);
	};
	string get_ship_date() {
		return ship_date.get_date();
	}

	void set_count(int count) {
		if (count < 0) {
			printf("Count is not valid! /set 0/\n");
			count = 0;
		}
		count_in_area = count;
	};

	int get_count() { return count_in_area; };
};

class Product : public Report
{
	string name;
	int type;
public:
	Product(string name_product = "prod", int type_product = 1, int count_product = 1) {
		name = name_product;
		type = type_product;
		set_count(count_product);
	};

	Product add_prod(int count) {
		if (count < 0) {
			return sub_prod(-count);
		}
		set_count(count + get_count());
		return *this;
	}

	Product sub_prod(int count) {
		if (count < 0) {
			return add_prod(-count);
		}
		if (count > get_count()) {
			printf("Запрос на изъятие %d продуктов исправлен на %d продуктов (максимальное количество)", count, get_count());
			set_count(0);
			return *this;
		}
		set_count(get_count() - count);
		return *this;
	}
};

int main()
{
	Product a;
	a.set_delivery_date(3, 6, 2022);
	a.set_count(100);
	a.add_prod(100);
	cout << a.get_count() << "\n";
	cout << a.get_delivery_date() << "\n";
}