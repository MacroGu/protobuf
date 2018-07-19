#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"

// Iterator thougn all people in the AddressBook and prints info about them.
void ListPeople(const tutorial::AddressBook &address_book)
{
	for (int i = 0; i < address_book.person_size(); i++)
	{
		const tutorial::Person &person = address_book.person(i);
		std::cout << "Person ID" << person.id() << std::endl;
		std::cout << "Name: " << person.name() << std::endl;
		if (person.has_email())
		{
			std::cout << "E-mail address: " << person.email() << std::endl;
		}

		for (int j = 0; j < person.phone_size(); j++)
		{
			const tutorial::Person::PhoneNumber &phone_number = person.phone(j);
			switch(phone_number.type())
			{
				case tutorial::Person::MOBILE:
					std::cout << "Mobile phone #: " << std::endl;
					break;
				case tutorial::Person::HOME:
					std::cout << "Home Phone #: " << std::endl;
					break;
				case tutorial::Person::WORK:
					std::cout <<  " Work phone #: " << std::endl;
					break;
			}
			std::cout << phone_number.number() << std::endl;
		}
	}
}



int main(int argc, char* argv[])
{

	GOOGLE_PROTOBUF_VERIFY_VERSION;
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << "ADDRESS_BOOK_FILE" << std::endl;
		return -1;
	}

	tutorial::AddressBook address_book;
	{
		// Read the existing address book.
		std::fstream input(argv[1], std::ios::in | std::ios::binary);
		if (!address_book.ParseFromIstream(&input))
		{
			std::cerr << "Failed to parse address book. " << std::endl;
			return -1;
		}
	}

	// Optional: Delete All global objects allocated by libprotobuf
	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}


