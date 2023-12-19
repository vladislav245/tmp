#include <locale>
#include "my_struct.cpp";
#include "Book.h";


bool operator > (const char* ptr, const AD_Magazine& obj1) {

	int step = 0;

	int size = strlen(ptr);
	while (step != 5 && size > 0) {

		if (ptr[size - 1] > obj1.ad_theme[step]) return 1;
		else if (ptr[size - 1] < obj1.ad_theme[step]) return 0;
		else {
			step++;
			size--;
		}
	}

	return 0;
}

void operator &= (char*& ptr, AD_Magazine& obj1) {

	if (ptr == nullptr || obj1.ad_theme == nullptr) return;

	int size = strlen(ptr);

	char* tmp;
	if (size <= 5) {
		delete[] ptr;
		ptr = new char[strlen(obj1.ad_theme) + 1];

		strcpy(ptr, obj1.ad_theme);
		return;
	}

	else {
		int s = (size - 5) + strlen(obj1.ad_theme) + 1;
		tmp = ptr;
		ptr = new char[s];

		strncpy(ptr, obj1.ad_theme, size - 5);
		ptr[size - 5] = '\0';
		strcat(ptr, obj1.ad_theme);
	}
}



int main()
{
	setlocale(LC_ALL, "RUS");

	factory->add<Book>("Book");
	factory->add<Scripture>("Scripture");
	factory->add<Magazine>("Magazine");
	factory->add<AD_Magazine>("AD_Magazine");
	factory->add<A>("A");

	Stack* a = new Stack;
	// // // //
	Book* obj1 = new Book("Vlad", "xz", "12", 22);
	Magazine* obj2 = new Magazine(43, "Anton", "policy", "ggwp", 99);
	Scripture* obj3 = new Scripture("xrist", "Oleg", "religion");
	Book* obj4 = new Book("Serg", "topic", "lol");
	Book* obj5 = new AD_Magazine("Serg2", 24, "topic2", "lol2");
	Book* obj6 = new Book("Serg3", "topic3", "lol3");
	Book* obj7 = new A(5);


	// // // //
	a->Push(obj1);
	a->Pop();
	a->Push(obj4);
	a->Push(obj5);
	a->Push(obj6);
	a->Push(obj7);

	a->Draw();

	a->Serialize("data.txt");

	delete a;

	a = new Stack;
	a->Deserialize("data.txt");
	a->Draw();

	return 0;
}