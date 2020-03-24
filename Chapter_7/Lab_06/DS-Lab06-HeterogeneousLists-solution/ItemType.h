#ifndef _ITEMTYPE_H
#define _ITEMTYPE_H

#include <iostream>
#include <string>
using namespace std;


class Polygon
{
public:
	Polygon()
	{
		cout << "Polygon ������ ȣ��" << endl;
	}
	~Polygon()
	{
		cout << "Polygon �Ҹ��� ȣ��" << endl;
	}

	void setName()
	{
		cout << "���� �̸� : ";
		cin >> name;
	}

	string getName()
	{
		return name;
	}

	virtual void display() // pure virtual function ���� �����Լ�
	{
		cout << "Polygon class�Դϴ�" << endl;
	}


	bool operator<(Polygon& data)
	{
		if (this->name < data.name)
			return true;
		else
			return false;
	}

	bool operator>(Polygon& data)
	{
		if (this->name > data.name)
			return true;
		else
			return false;
	}

	bool operator==(Polygon& data)
	{
		if (this->name.compare(data.name))
			return true;
		else
			return false;
	}

	Polygon operator=(Polygon& data)
	{
		this->name = data.name;
		return *this;
	}

protected:
	string name; // ���� �̸�
};


// Circle class
class Circle : public Polygon
{
public:
	Circle()
	{
		setName();
		cout << name << " Circle ������ ȣ��" << endl;
	}
	~Circle()
	{
		cout << name << " Circle �Ҹ��� ȣ��" << endl;
	}

	virtual void display()
	{
		cout << name << " Circle class�Դϴ�" << endl;
	}
};

// Polygon class
class Triangle : public Polygon
{
public:
	Triangle()
	{
		setName();
		cout << name << " Triangle ������ ȣ��" << endl;
	}
	~Triangle()
	{
		cout << name << " Triangle �Ҹ��� ȣ��" << endl;
	}

	virtual void display()
	{
		cout << name << " Triangle class�Դϴ�" << endl;
	}

};


// Rectangle class
class Rectangle : public Polygon
{
public:
	Rectangle()
	{
		setName();
		cout << name << " Rectangle ������ ȣ��" << endl;
	}
	~Rectangle()
	{
		cout << name << " Rectangle �Ҹ��� ȣ��" << endl;
	}

	virtual void display()
	{
		cout << name << " Rectangle class�Դϴ�" << endl;
	}
};

#endif