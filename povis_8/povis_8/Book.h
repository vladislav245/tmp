#pragma once

#include <iostream>
#include <fstream>
#include <map>

#pragma warning(disable:4996)

void check_output();

class Interface {

public:
	virtual void Output() const = 0;
	virtual void Input() = 0;
	virtual void Serialize(std::fstream& f) = 0;
	virtual void Deserialize(std::fstream& f) = 0;
	virtual const char* Name() = 0;
	virtual ~Interface() { };
};

class Book : public Interface {

	char* author;  //автор

	const char* Get_private_data() const;

protected:
	char* __new_char__();

	char* publ_office; // издательство
	char* topic;   //тема

	const char* Get_publ_office() const;

	const char* Get_topic() const;

public:

	int year_realease; // год издания

	Book(const Book& tmp);

	virtual void Output() const;

	virtual void Input();

	Book(const char* author = "None", const char* topic = "None", const char* publ_office = "None", int year_realease = 40, bool flag = 0);

	virtual const char* Name() { return "Book"; };

	virtual void Serialize(std::fstream& f);

	virtual void Deserialize(std::fstream& f);

	virtual ~Book();
};

//священная книга
class Scripture : public Book {

	char* religion;

public:

	Scripture(const char* religion = "None", const char* author = "None", const char* topic = "None",
		const char* publ_office = "None", int year_realease = 40, bool flag = 0);

	Scripture(const Scripture& tmp);

	virtual void Output() const;

	virtual void Input();

	virtual const char* Name() { return "Scripture"; };

	virtual void Serialize(std::fstream& f);

	virtual void Deserialize(std::fstream& f);

	virtual ~Scripture();

};

class Magazine : public Book {

	int size_news;

public:

	Magazine(int size_news = 0, const char* author = "None", const char* topic = "None",
		const char* publ_office = "None", int year_realease = 40, bool flag = 0);

	Magazine(const Magazine& tmp);

	virtual void Output() const;

	virtual void Input();

	virtual const char* Name() { return "Magazine"; };

	virtual void Serialize(std::fstream& f);

	virtual void Deserialize(std::fstream& f);

	virtual ~Magazine() { };

};

//рекламный журнал
class AD_Magazine : public Magazine {

	char* ad_theme;

public:

	AD_Magazine(const char* ad_theme = "None", int size_news = 0, const char* author = "None", const char* topic = "None",
		const char* publ_office = "None", int year_realease = 40, bool flag = 0);

	AD_Magazine(const AD_Magazine& tmp);

	bool operator > (const char* ptr);

	void operator &= (const char* ptr);

	virtual void Output() const;

	virtual void Input();

	friend bool operator > (const char* ptr, const AD_Magazine& obj1);
	friend void operator &= (char*& ptr, AD_Magazine& obj1);

	virtual const char* Name() { return "AD_Magazine"; };

	virtual void Serialize(std::fstream& f);

	virtual void Deserialize(std::fstream& f);

	virtual ~AD_Magazine();
};


class A : public Book {


public:

	int a;

	A(int a = 1) : Book() { this->a = a; };

	virtual void Serialize(std::fstream& f) {
		Book::Serialize(f);
		f << a << std::endl;
	}

	virtual void Deserialize(std::fstream& f) {
		Book::Deserialize(f);

		char buffer[64];
		f >> buffer;

		this->year_realease = atoi(buffer);
	}

	virtual void Output() { Book::Output(); };
	virtual void Input() { Book::Input(); };
	virtual const char* Name() { return "A"; };


};


class abstractFooCreator
{
public:
	virtual Interface* create() const = 0;
};


template <class C>
class fooCreator : public abstractFooCreator
{
public:
	virtual Interface* create() const { return new C(); }
};


class FooFactory
{
protected:
	typedef std::map<std::string, abstractFooCreator*> FactoryMap;
	FactoryMap _factory;


public:

	FooFactory() { };

	virtual ~FooFactory() { };


	template <class C>
	void add(const std::string& id)
	{
		typename FactoryMap::iterator it = _factory.find(id);
		
		if (it == _factory.end())
			_factory[id] = new fooCreator<C>();
	}


	Interface* create(const std::string& id)
	{

		typename FactoryMap::iterator it = _factory.find(id);

		if (it != _factory.end())
			return it->second->create();

		return 0;
	}

	bool find_id(const std::string& id) {

		typename FactoryMap::iterator it = _factory.find(id);

		if (it != _factory.end())
			return 1;

		return 0;
	}
};