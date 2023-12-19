#include "Book.h"

static FooFactory* factory = new FooFactory;

//абстр фабрика
class Stack {

public:

	Stack() {
		HEAD = nullptr;
	}


	void Push(Interface* obj) {
		if (HEAD == nullptr) HEAD = new Store(obj);
		else {
			HEAD->Next = new Store(obj);
			HEAD->Next->Back = HEAD;
			HEAD = HEAD->Next;
		}
	}

	Interface* Pop() {

		if (HEAD == nullptr) return nullptr;

		Store* tmp = HEAD;
		HEAD = HEAD->Back;
		if (HEAD != nullptr) HEAD->Next = nullptr;
		delete tmp->obj;
	}

	void Serialize(const char* path) {

		std::fstream f(path, 'w');
		
		Store* tmp = HEAD;

		while (tmp != nullptr && tmp->Get_Back() != nullptr) {
			tmp = tmp->Get_Back();
		}

		while (1) {
			if (tmp == nullptr) break;

			std::string str = typeid(*tmp->Get_obj()).name();
			str.erase(0, 6);

			if (factory->find_id(str)) {
				
				f << str << '\n';
				tmp->Get_obj()->Serialize(f);
				tmp = tmp->Get_Next();
			}
		}
		

		f.close();
	}

	void Deserialize(const char* path) {

		std::fstream f(path);
		Interface* tmp;
		char buffer[256];
		
		while (!f.eof()) {

			f >> buffer;

			if (factory->find_id(buffer)) {
				tmp = factory->create(buffer);
				tmp->Deserialize(f);
				Push(tmp);
			}

		}
		f.close();
	}

	Interface* Get_First() {
		if (HEAD != nullptr) return HEAD->Get_obj();
		else return nullptr;
	}

	Interface* Get_Next(Interface* ptr) {
		for (Store* i = HEAD; i != nullptr; i = i->Get_Back()) {
			if (i->Get_obj() == ptr && i->Get_Back() != nullptr) return i->Get_Back()->Get_obj();
		}

		return nullptr;
	}

	void Draw() {

		Store* tmp = HEAD;

		while (tmp != nullptr) {
			tmp->Get_obj()->Output();
			tmp = tmp->Get_Back();
		}
	}

	~Stack() {

		Store* ptr = HEAD;
		while (ptr != nullptr) {
			ptr = HEAD->Get_Back();
			delete HEAD->Get_obj();
			HEAD = ptr;
		}
	}

private:

	class Store {
		Interface* obj; //указатель на объект
		Store* Next;   //указатель на след. элемент
		Store* Back;   //плаваюищй указатель на пред. элемент


	public:

		Store() {
			obj = nullptr;
			Next = nullptr;
			Back = nullptr;
		}

		Store(Interface* obj) {
			this->obj = obj;
			Next = nullptr;
			Back = nullptr;
		}


		Interface* Get_obj() { return obj; };
		Store* Get_Next() { return Next; };
		Store* Get_Back() { return Back; };


		friend Interface* Stack::Pop();
		friend void Stack::Push(Interface* obj);
	};

	Store* HEAD;
};
