#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Date
{
	int m_day;
	int m_month;
	int m_year;
public:
	Date(int day = 1, int month = 1, int year = 2000) {
		if ((day <= 0) || (month <= 0) || (year <= 0)) {
			printf("Date is not valid! /set defolt/\n");
			day = 1; month = 1; year = 2000;
		}
		m_day = day; m_month = month; m_year = year;
	};

	string get_date() {
		return (string)(to_string(m_day) + "." + to_string(m_month) + "." + to_string(m_year));
	};
	void set_date(int day, int month, int year) {
		if ((day <= 0) || (month <= 0) || (year <= 0)) {
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
	string name_of_product;
	Date delivery_date;
	Date send_date;
	int count;
	int type_of_report;
public:
	Report(string name = "prod", int count_of_prod = 1, int type_of_rep = 0, int day = 1, int month = 1, int year = 2000) {
		name_of_product = name;
		type_of_report = type_of_rep;
		delivery_date.set_date(day, month, year);
		send_date.set_date(day, month, year);
		count = count_of_prod;
	};

	void set_delivery_date(int day, int month, int year) {
		delivery_date.set_date(day, month, year);
	};
	string get_delivery_date() {
		return delivery_date.get_date();
	}

	void set_send_date(int day, int month, int year) {
		send_date.set_date(day, month, year);
	};
	string get_send_date() {
		return send_date.get_date();
	}

	void set_count(int count_of_prod) {
		if (count_of_prod < 0) {
			printf("Count is not valid! /set 0/\n");
			count_of_prod = 0;
		}
		count = count_of_prod;
	};
	int get_count() { return count; };

	int get_type() { return type_of_report; }

	friend ostream& operator<<(ostream& r, Report& report)
	{
		if (&report == NULL) return r;
		if (report.get_type() == 1) r << "\n" << "send\t" << report.name_of_product << "\t" << report.get_count() << "\t" << report.get_send_date();
		else r << "\n" << "delivery\t" << report.name_of_product << "\t" << report.get_count() << "\t" << report.get_send_date();
		return r;
	}
};

class Product
{
	string name;
	int type;
	int count;
public:
	Product(string name_product = "prod", int type_product = 1, int count_product = 1) {
		name = name_product;
		type = type_product;
		if (count_product < 0) {
			printf("Count is not valid! /set 0/\n");
			count = 0;
		}
		else count = count_product;
	};

	void set_name(string name_of_product) {
		name = name_of_product;
	}

	string get_name() {
		return name;
	}

	void set_type(int type_of_product) {
		type = type_of_product;
	}

	int get_type() {
		return type;
	}

	void set_count(int count_of_prod) {
		if (count_of_prod < 0) {
			printf("Count is not valid! /set 0/\n");
			count = 0;
		}
		else count = count_of_prod;
	}

	int get_count() { return count; }

	Product add_prod(int count_of_product) {
		if (count_of_product < 0) {
			return sub_prod(-count_of_product);
		}
		count += count_of_product;
		return *this;
	}

	Product sub_prod(int count_of_product) {
		if (count_of_product < 0) {
			return add_prod(-count_of_product);
		}
		if (count_of_product > count) {
			printf("Запрос на изъятие %d продуктов исправлен на %d продуктов (максимальное количество)", count_of_product, count);
			count = 0;
			return *this;
		}
		count -= count_of_product;
		return *this;
	}

	int operator ==(Product& prod) {
		if ((name == prod.name) || (this == &prod)) return 1;
		return 0;
	};

};

class Area
{
	int type;
	vector<Product> product;
	int quantity_prod_now;
	int max_count_prod;
public:
	Area(int type_prod = 1, int max = 999) {
		type = type_prod;
		if (max < 0) {
			printf("MAX count is not valid! /set 999/\n");
			max_count_prod = 999;
		}
		else max_count_prod = max;
		Product prod;
		product.push_back(prod);
		quantity_prod_now = 0;
	}

	int get_type() { return type; }

	void set_type(int new_type) { type = new_type; }

	int get_max_count_prod() { return max_count_prod; }

	void set_max_count_prod(int new_max_count_prod) {
		if (new_max_count_prod < 0) {
			printf("MAX count is not valid! /set 999/\n");
			max_count_prod = 999;
		}
		else max_count_prod = new_max_count_prod;
	}

	int get_quantity_prod_now() { return quantity_prod_now; };

	int add_products(Product& prod) {
		int i = 0;
		for (; i < product.size(); i++) {
			if (product[i] == prod) {
				if ((prod.get_count() + quantity_prod_now) > max_count_prod) {
					printf("Added only %d products! Storage is full!", max_count_prod - quantity_prod_now);
					quantity_prod_now = max_count_prod;
					product[i].add_prod(max_count_prod - quantity_prod_now);
					return max_count_prod - quantity_prod_now;
				}
				quantity_prod_now += prod.get_count();
				product[i].add_prod(prod.get_count());
				return quantity_prod_now;
			}
		}
		if (i == product.size()) {
			if ((prod.get_count() + quantity_prod_now) > max_count_prod) {
				printf("Added only %d products! Storage is full!", max_count_prod - quantity_prod_now);
				quantity_prod_now = max_count_prod;
				product.push_back(prod);
				return max_count_prod - quantity_prod_now;
			}
			quantity_prod_now += prod.get_count();
			product.push_back(prod);
		}
		return quantity_prod_now;
	};

	int sub_products(Product& prod) {
		int i = 0;
		for (; i < product.size(); i++) {
			if (product[i] == prod) {
				if (prod.get_count() > product[i].get_count()) {
					printf("Subed only %d products! Storage is empty!", product[i].get_count());
					product[i].set_count(0);
					if (prod.get_count() > quantity_prod_now) {
						quantity_prod_now = 0;
						return 0;
					}
					quantity_prod_now -= prod.get_count();
					return quantity_prod_now;
				}
				quantity_prod_now -= prod.get_count();
				product[i].sub_prod(prod.get_count());
				return quantity_prod_now;
			}
		}
		if (i == product.size()) {
			cout << "Product " << prod.get_name() << " not found\n";
		}
		return 0;
	};

	int get_count_of_prod(Product prod) {
		int i = 0;
		for (; i < product.size(); i++) {
			if (product[i] == prod) {
				return product[i].get_count();
			}
		}
		if (i == product.size()) {
			cout << "Product " << prod.get_name() << " not found\n";
			return 0;
		}
		return 0;
	}

	int operator ==(Area& _area) {
		if (type == _area.get_type()) return 1;
		else return 0;
	}

	Product* find_product(string _name) {
		int i = 0;
		for (; i < product.size(); i++) {
			if (product[i].get_name() == _name) {
				return &product[i];
			}
		}
		if (i == product.size()) {
			return NULL;
		}
	}

};


class Storage
{
	string address;
	vector<Area> area;
	vector<Report> report;
public:
	Storage(string address_of_storage = "defolt", int count_of_area = 1, int max_count_of_prod = 999) {
		address = address_of_storage;

		int new_max_count_of_prod = 0;
		if (max_count_of_prod < 0) {
			printf("MAX count of product in area is not valid! /set 999/\n");
			new_max_count_of_prod = 999;
		}
		else new_max_count_of_prod = max_count_of_prod;

		int new_count_of_area = 0;
		if (count_of_area <= 0) {
			printf("Count of area is not valid! /set 1/\n");
			new_count_of_area = 1;
		}
		else new_count_of_area = count_of_area;

		for (int i = 1; i <= new_count_of_area; i++)
		{
			Area new_area(i, new_max_count_of_prod);
			area.push_back(new_area);
		}
		Report rep;
		report.push_back(rep);
	}

	void change_type_area(int old_type, int new_type) {
		int i = 0;
		for (; i < area.size(); i++) {
			if (area[i].get_type() == old_type) {
				return area[i].set_type(new_type);
			}
		}
		if (i == area.size()) {
			printf("This type '%d' is not found!", old_type);
		}
	}

	void change_max_count_prod_of_area(int type, int new_max_count) {

		int _new_max_count = 0;
		if (new_max_count < 0) {
			printf("New MAX count of product in area is not valid! /set 999/\n");
			_new_max_count = 999;
		}
		else _new_max_count = new_max_count;

		int i = 0;
		for (; i < area.size(); i++) {
			if (area[i].get_type() == type) {
				return area[i].set_max_count_prod(_new_max_count);
			}
		}
		if (i == area.size()) {
			printf("This type '%d' is not found!", type);
		}
	}

	void add_products(string name_of_product, int type_of_product, int count_of_product, Date date) {
		if (count_of_product < 0) return sub_products(name_of_product, type_of_product, -count_of_product, date);

		int i = 0;
		for (; i < area.size(); i++) {
			if (area[i].get_type() == type_of_product) {
				Product new_prod(name_of_product, type_of_product, count_of_product);
				int new_count = area[i].add_products(new_prod);
				Report new_report(name_of_product, new_count, 0, date.get_day(), date.get_month(), date.get_year());
				report.push_back(new_report);
				return;
			}
		}
		if (i == area.size()) {
			printf("This type '%d' is not found!", type_of_product);
		}
	}

	void sub_products(string name_of_product, int type_of_product, int count_of_product, Date date) {
		if (count_of_product < 0) return add_products(name_of_product, type_of_product, -count_of_product, date);

		int i = 0;
		for (; i < area.size(); i++) {
			if (area[i].get_type() == type_of_product) {
				Product new_prod(name_of_product, type_of_product, count_of_product);
				int new_count = area[i].sub_products(new_prod);
				Report new_report(name_of_product, new_count, 1, date.get_day(), date.get_month(), date.get_year());
				report.push_back(new_report);
				return;
			}
		}
		if (i == area.size()) {
			printf("This type '%d' is not found!", type_of_product);
		}
	}

	vector<Report> get_all_rep() { return report; }

	Product* find_prod(string _name, int _type) {
		int i = 0;
		for (; i < area.size(); i++) {
			if (area[i].get_type() == _type) {
				return area[i].find_product(_name);
			}
		}
		if (i == area.size()) {
			printf("This type '%d' is not found!", _type);
		}
	}

	Product* find_prod(string _name) {
		int i = 0;
		for (; i < area.size(); i++) {
			Product* find;
			find = area[i].find_product(_name);
			if (find != NULL) {
				return area[i].find_product(_name);
			}
		}
		if (i == area.size()) {
			cout << "Product " << _name << " not found\n";
		}
	}
};


int main()
{
	Storage storage("Tosmk", 3);
	Date today(24, 11, 2022);
	Date tomorrow(25, 11, 2022);

	storage.add_products("table", 1, 17, today);
	storage.add_products("fork", 2, 789, today);

	storage.sub_products("table", 1, 10, tomorrow);

	for (int i = 1; i < storage.get_all_rep().size(); i++)
	{
		cout << storage.get_all_rep()[i];
	}

	return 0;
}