#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"

void PromptForAddress(tutorial::Person *person)
{
	std::cout << "enter person ID " << std::endl;
	int id;
	std::cin >> id;
	person->set_id(id);
	std::cin.ignore(256, '\n');

	std::cout << "Enter name: " << std::endl;
	getline(std::cin, *person->mutable_name());

	std::cout << "Enter email address (blank for none): " << std::endl;
	std::string email;

	std::cin >> email;
	if (!email.empty())
	{
		person->set_email(email);
	}

	while(true)
	{
		std::cout << "Enter a phone Number (or leave blank to finish): " << std::endl;
		std::string number;
		std::cin >> number;
		if (number == "quit")
		{
			break;
		}

		tutorial::Person::PhoneNumber *phone_number = person->add_phone();
		phone_number->set_number(number);
		std::cout << "Is this a mobile, home, or work phone" << std::endl;
		std::string type;
		std::cin >> type;
		if ("mobile" == type)
		{
			phone_number->set_type(tutorial::Person::MOBILE);
		}
		else if ("home" == type)
		{
			phone_number->set_type(tutorial::Person::HOME);
		}
		else if ("work" == type)
		{
			phone_number->set_type(tutorial::Person::WORK);
		}
		else 
		{
			std::cout << "UnKnown phne type, Using Defaule." << std::endl; 
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
		std::fstream input(argv[1], std::ios::in | std::ios::binary);
		if (!input)
		{
			std::cout << argv[1] << ": File not found. Creating a new file. " << std::endl;
		}
		else if (!address_book.ParseFromIstream(&input))
		{
			std::cout << "Failed to parse address book." << std::endl;
			return -1;
		}
	}
	
	// Add an address
	PromptForAddress(address_book.add_person());
	{
		// Write the new address book back to disk
		std::fstream output(argv[1], std::ios::out | std::ios::trunc | std::ios::binary);
		if (!address_book.SerializeToOstream(&output))
		{
			std::cerr << "Failed to write address book." << std::endl;
			return -1;
		}
	}

	// Optional: Delete all global objects allocated by libprotobuf
	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}
