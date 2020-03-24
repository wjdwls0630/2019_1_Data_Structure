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
		cout << "Polygon 생성자 호출" << endl;
	}
	~Polygon()
	{
		cout << "Polygon 소멸자 호출" << endl;
	}

	void setName()
	{
		cout << "도형 이름 : ";
		cin >> name;
	}

	string getName()
	{
		return name;
	}

	virtual void display() // pure virtual function 순수 가상함수
	{
		cout << "Polygon class입니다" << endl;
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
	string name; // 도형 이름
};


// Circle class
class Circle : public Polygon
{
public:
	Circle()
	{
		setName();
		cout << name << " Circle 생성자 호출" << endl;
	}
	~Circle()
	{
		cout << name << " Circle 소멸자 호출" << endl;
	}

	virtual void display()
	{
		cout << name << " Circle class입니다" << endl;
	}
};

// Polygon class
class Triangle : public Polygon
{
public:
	Triangle()
	{
		setName();
		cout << name << " Triangle 생성자 호출" << endl;
	}
	~Triangle()
	{
		cout << name << " Triangle 소멸자 호출" << endl;
	}

	virtual void display()
	{
		cout << name << " Triangle class입니다" << endl;
	}

};


// Rectangle class
class Rectangle : public Polygon
{
public:
	Rectangle()
	{
		setName();
		cout << name << " Rectangle 생성자 호출" << endl;
	}
	~Rectangle()
	{
		cout << name << " Rectangle 소멸자 호출" << endl;
	}

	virtual void display()
	{
		cout << name << " Rectangle class입니다" << endl;
	}
};

#endif