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

	int operator ==(Product& prod) {
		if (name == prod.name) return 1;
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
		max_count_prod = max;
		Product prod;
		product.push_back(prod);
		quantity_prod_now = 0;
	}

	int get_type() { return type; }
	void set_type(int new_type) { type = new_type; }

	int get_max_count_prod() { return max_count_prod; }
	void set_max_count_prod(int new_max_count_prod) { max_count_prod = new_max_count_prod; }

	int get_quantity_prod_now() { return quantity_prod_now; };

	void add_products(Product& prod) {
		int i = 0;
		for (; i < product.size(); i++) {
			if (product[i] == prod) {
				if ((prod.get_count() + quantity_prod_now) > max_count_prod) {
					printf("Added only %d products! Storage is full!", max_count_prod - quantity_prod_now);
					quantity_prod_now = max_count_prod;
					product[i].add_prod(max_count_prod - quantity_prod_now);
					return;
				}
				quantity_prod_now += prod.get_count();
				product[i].add_prod(prod.get_count());
				return;
			}
		}
		if (i == product.size()) {
			if ((prod.get_count() + quantity_prod_now) > max_count_prod) {
				printf("Added only %d products! Storage is full!", max_count_prod - quantity_prod_now);
				quantity_prod_now = max_count_prod;
				product.push_back(prod);
			}
			quantity_prod_now += prod.get_count();
			product.push_back(prod);
		}
	};

	void sub_products(Product& prod) {
		int i = 0;
		for (; i < product.size(); i++) {
			if (product[i] == prod) {
				if (prod.get_count() > product[i].get_count()) {
					printf("Subed only %d products! Storage is empty!", product[i].get_count());
					product[i].set_count(0);
					if (prod.get_count() > quantity_prod_now) {
						quantity_prod_now = 0;
						return;
					}
					quantity_prod_now -= prod.get_count();
					return;
				}
				quantity_prod_now -= prod.get_count();
				product[i].sub_prod(prod.get_count());
				return;
			}
		}
		if (i == product.size()) {
			cout << "Product " << prod.get_name() << " not found\n";
		}
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

};


class Storage
{
	string address;
	vector<Area> area;
public:
	Storage(string address_of_storage, int count_of_area) {
		address = address_of_storage;
		for (int i = 1; i <= count_of_area; i++)
		{
			Area new_area(i, 999);
			area.push_back(new_area);
		}
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
		int i = 0;
		for (; i < area.size(); i++) {
			if (area[i].get_type() == type) {
				return area[i].set_max_count_prod(new_max_count);
			}
		}
		if (i == area.size()) {
			printf("This type '%d' is not found!", type);
		}
	}


};


int main()
{
	Area area;

	Product a;
	a.set_delivery_date(3, 6, 2022);
	a.set_count(100);
	a.add_prod(100);

	Product b;
	b.set_name("jkl");

	area.add_products(a);
	cout << area.get_quantity_prod_now() << "\n";

	area.sub_products(b);

}