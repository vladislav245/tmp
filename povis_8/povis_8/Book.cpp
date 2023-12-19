#include "Book.h"

#pragma warning(disable:4996)

void check_output() {
	if (!std::cin) {
		std::cin.clear();
		std::cin.ignore();
	}
}

char* Book::__new_char__() {

	std::cout << "Чтобы закончить нажмите /" << std::endl;

	char c = ' ';
	char* str = nullptr;
	int capacity = 1;
	int size = 0;
	while (true) {

		size++;

		if (size >= capacity) {
			capacity *= 2;

			if (str == nullptr) {
				str = new char[capacity];
			}
			else {
				char* tmp = str;
				tmp = str;
				tmp[size - 1] = '\0';
				str = new char[capacity];
				strcpy(str, tmp);

				delete[] tmp;
			}
		}

		c = std::cin.get();
		if (c == '/') break;

		if (std::cin.peek() == '\n') std::cin.get();


		str[size - 1] = c;
	}

	getchar();
	check_output();
	str[size - 1] = '\0';

	return str;
}

const char* Book::Get_private_data() const {
	return author;
}

const char* Book::Get_publ_office() const {
	return publ_office;
}
const char* Book::Get_topic() const {
	return topic;
}

Book::Book(const Book& tmp) {

	std::cout << "Конструктор копирования" << std::endl;

	if (this == &tmp) {
		std::cout << std::endl << "Нельзя копировать самого себя" << std::endl;
		return;
	}

	this->author = new char[strlen(tmp.author) + 1];
	strcpy(this->author, tmp.author);
	this->publ_office = new char[strlen(tmp.publ_office) + 1];
	strcpy(this->publ_office, tmp.publ_office);
	this->topic = new char[strlen(tmp.topic) + 1];
	strcpy(this->topic, tmp.topic);
	this->year_realease = tmp.year_realease;
}

void Book::Output() const {

	std::cout << std::endl;
	std::cout << "Автор: " << author << std::endl;
	std::cout << "издательство: " << publ_office << std::endl;
	std::cout << "тема: " << topic << std::endl;
	std::cout << "год издания: " << year_realease << std::endl;

}

void Book::Input() {

	std::cout << std::endl << "Введите автора" << std::endl;
	author = __new_char__();

	std::cout << "Введите издательство" << std::endl;
	publ_office = __new_char__();

	std::cout << "Введите жанр книги" << std::endl;
	topic = __new_char__();

	std::cout << "Введите год издания" << std::endl;
	std::cin >> year_realease;
	getchar();
	check_output();

	std::cout << std::endl << std::endl;
}

Book::Book(const char* author, const char* topic, const char* publ_office, int year_realease, bool flag) {

	if (flag == 0) {
		this->author = new char[strlen(author) + 1];
		strcpy(this->author, author);
		this->topic = new char[strlen(topic) + 1];
		strcpy(this->topic, topic);
		this->publ_office = new char[strlen(publ_office) + 1];
		strcpy(this->publ_office, publ_office);
	}
	else {
		this->author = const_cast<char*>(author);
		this->topic = const_cast<char*>(topic);
		this->publ_office = const_cast<char*>(publ_office);
	}

	this->year_realease = year_realease;
}


void Book::Serialize(std::fstream& f) {
	f << author << '\n';
	f << publ_office << '\n';
	f << topic << '\n';
	f << year_realease << '\n';
}

void Book::Deserialize(std::fstream& f) {

	char buffer[256];

	for (int i = 0; i < 4; i++) {
		f >> buffer;

		if (i == 0) {
			if (this->author != nullptr) delete[] author;
			this->author = new char[strlen(buffer) + 1];
			strcpy(this->author, buffer);
		}
		else if (i == 1) {
			if (this->publ_office != nullptr) delete[] publ_office;
			this->publ_office = new char[strlen(buffer) + 1];
			strcpy(this->publ_office, buffer);
		}
		else if (i == 2) {
			if (this->topic != nullptr) delete[] topic;
			this->topic = new char[strlen(buffer) + 1];
			strcpy(this->topic, buffer);
		}
		else if (i == 3) {
			this->year_realease = atoi(buffer);
		}
	}
}


Book::~Book() {
	if (author != nullptr) {
		delete author;
		author = nullptr;
	}
	if (topic != nullptr) {
		delete topic;
		topic = nullptr;
	}
	if (publ_office != nullptr) {
		delete publ_office;
		publ_office = nullptr;
	}
	year_realease = -1;

	std::cout << "object deleted" << std::endl;
}


Scripture::Scripture(const char* religion, const char* author, const char* topic, \
	const char* publ_office, int year_realease, bool flag) : Book(author, topic, publ_office, year_realease, flag) {

	if (flag == 0) {
		this->religion = new char[strlen(religion) + 1];
		strcpy(this->religion, religion);
	}
	else {
		this->religion = const_cast<char*>(religion);
	}
}

void Scripture::Output() const {
	Book::Output();
	std::cout << "Релилгия: " << religion << std::endl;
}

void Scripture::Input() {
	Book::Input();

	std::cout << "Введите религию" << std::endl;
	religion = __new_char__();
}


Scripture::Scripture(const Scripture& tmp) : Book(tmp) {

	std::cout << "Конструктор копирования" << std::endl;

	if (this == &tmp) {
		std::cout << std::endl << "Нельзя копировать самого себя" << std::endl;
		return;
	}

	this->religion = new char[strlen(tmp.religion) + 1];
	strcpy(this->religion, tmp.religion);
}

void Scripture::Serialize(std::fstream& f) {
	Book::Serialize(f);
	f << religion << '\n';
}

void Scripture::Deserialize(std::fstream& f) {

	Book::Deserialize(f);

	char buffer[64];
	f >> buffer;

	if (this->religion != nullptr) delete[] religion;
	this->religion = new char[strlen(buffer) + 1];
	strcpy(this->religion, buffer);
}

Scripture::~Scripture() {
	if (religion != nullptr) {
		delete religion;
		religion = nullptr;
	}
}



Magazine::Magazine(int size_news, const char* author, const char* topic, \
	const char* publ_office, int year_realease, bool flag) : Book(author, topic, publ_office, year_realease, flag) {

	this->size_news = size_news;
}

void Magazine::Output() const {
	Book::Output();
	std::cout << "Количество новостей:" << size_news << std::endl;
}

void Magazine::Input() {
	Book::Input();

	std::cout << "Введите кол-во новостей" << std::endl;
	std::cin >> size_news;
}


Magazine::Magazine(const Magazine& tmp) : Book(tmp) {

	std::cout << "Конструктор копирования" << std::endl;

	if (this == &tmp) {
		std::cout << std::endl << "Нельзя копировать самого себя" << std::endl;
		return;
	}

	this->size_news = tmp.size_news;
}


void Magazine::Serialize(std::fstream& f) {
	Book::Serialize(f);
	f << size_news << '\n';
}

void Magazine::Deserialize(std::fstream& f) {

	Book::Deserialize(f);

	char buffer[64];
	f >> buffer;

	this->size_news = atoi(buffer);
}


AD_Magazine::AD_Magazine(const char* ad_theme, int size_news, const char* author, const char* topic, \
	const char* publ_office, int year_realease, bool flag) : Magazine(size_news, author, topic, publ_office, year_realease, flag) {

	if (flag == 0) {
		this->ad_theme = new char[strlen(ad_theme) + 1];
		strcpy(this->ad_theme, ad_theme);
	}
	else {
		this->ad_theme = const_cast<char*>(ad_theme);
	}
}

void AD_Magazine::Output() const {
	Magazine::Output();
	std::cout << "Вид новостей: " << ad_theme << std::endl;
}

void AD_Magazine::Input() {
	Book::Input();

	std::cout << "Введите о чем новости" << std::endl;
	std::cin >> ad_theme;
}


AD_Magazine::AD_Magazine(const AD_Magazine& tmp) : Magazine(tmp) {

	std::cout << "Конструктор копирования" << std::endl;

	if (this == &tmp) {
		std::cout << std::endl << "Нельзя копировать самого себя" << std::endl;
		return;
	}

	this->ad_theme = new char[strlen(tmp.ad_theme) + 1];
	strcpy(this->ad_theme, tmp.ad_theme);
}


void AD_Magazine::Serialize(std::fstream& f) {
	Magazine::Serialize(f);
	f << ad_theme << '\n';
}

void AD_Magazine::Deserialize(std::fstream& f) {

	Magazine::Deserialize(f);

	char buffer[64];
	f >> buffer;

	if (this->ad_theme != nullptr) delete[] ad_theme;
	this->ad_theme = new char[strlen(buffer) + 1];
	strcpy(this->ad_theme, buffer);
}


AD_Magazine::~AD_Magazine() {
	if (ad_theme != nullptr) {
		delete[] ad_theme;
		ad_theme = nullptr;
	}
}


bool AD_Magazine::operator> (const char* ptr) {

	int step = 0;

	int size = strlen(ptr);
	while (step != 5 && size > 0) {

		if (ptr[size - 1] < ad_theme[step]) return 1;
		else if (ptr[size - 1] > ad_theme[step]) return 0;
		else {
			step++;
			size--;
		}
	}


	return 0;
}

void AD_Magazine::operator &= (const char* ptr) {

	if (ptr == nullptr || ad_theme == nullptr) return;

	int size = strlen(ad_theme);

	char* tmp;
	if (size <= 5) {
		if (ad_theme != nullptr) delete[] ad_theme;
		ad_theme = new char[strlen(ptr) + 1];

		strcpy(ad_theme, ptr);
		return;
	}

	else {
		int s = (size - 5) + strlen(ptr) + 1;
		tmp = ad_theme;
		ad_theme = new char[s];

		strncpy(ad_theme, tmp, size - 5);
		ad_theme[size - 5] = '\0';
		strcat(ad_theme, ptr);

		delete[] tmp;
	}
}
