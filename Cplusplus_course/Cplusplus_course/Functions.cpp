#include "Functions.h"


void startMenu(Facebook& facebook)
{
	string userInput, nameInput, nameInput2, statusInput,mediaFile;
	Page* page;
	Member* member1, * member2;
	bool isValid;
	cout << "Welcome to the amazing Facebook!" << endl << endl;
	MENU_OPTIONS  choice = MENU_OPTIONS::START_MENU;
	readValidChoice(userInput, choice, facebook);

	while (choice != MENU_OPTIONS::EXIT_MENU)
	{
		isValid = false;
		switch (choice)
		{
		case MENU_OPTIONS::ADD_MEMBER:
			facebook.addMember();
			break;

		case MENU_OPTIONS::ADD_FAN_PAGE:
			facebook.addPage();
			break;

		case MENU_OPTIONS::ADD_MEMBER_STATUS:
			readMemberName(facebook, nameInput);
			cout << "Please enter a status: ";
			statusInput = readInputString();
			if (getMedia(mediaFile))
				facebook.getMemberByName(nameInput)->addMediaStatus(statusInput,mediaFile);
			else
				facebook.getMemberByName(nameInput)->addStatus(statusInput);
			break;

		case MENU_OPTIONS::ADD_PAGE_STATUS:
			readPageName(facebook, nameInput);
			cout << "Please enter a status: ";
			statusInput = readInputString();
			if (getMedia(mediaFile))
				facebook.getPageByName(nameInput)->addMediaStatus(statusInput, mediaFile);
			else
				facebook.getPageByName(nameInput)->addStatus(statusInput);
			break;

		case MENU_OPTIONS::PRINT_MEMBER_STATUS:
			readMemberName(facebook, nameInput);
			facebook.getMemberByName(nameInput)->printAllStatus();
			break;

		case MENU_OPTIONS::PRINT_PAGE_STATUS:
			readPageName(facebook, nameInput);
			facebook.getPageByName(nameInput)->printAllStatus();
			break;

		case MENU_OPTIONS::PRINT_RECENT_FRIENDS_STATUS:
			readMemberName(facebook, nameInput);
			facebook.getMemberByName(nameInput)->printLatestStatusesOfFriends();
			break;

		case MENU_OPTIONS::CONNECT_MEMBERS:
			readMemberName(facebook, nameInput);
			member1 = facebook.getMemberByName(nameInput);
				if (member1->getFriendsSize() == (facebook.getMembersList().size()-1) )
					cout << "No members available to add as friends to this user" << endl;
				else
				{
					while (!isValid)
					{
						facebook.printAvailableFriends(nameInput);
						cout << "Choose the second member from the above by typing his name: ";
						nameInput2 = readInputString();
						try
						{
							isBlank(nameInput2);
							facebook.isNotMember(nameInput2);
							member1->isMe(nameInput2);
							member2 = facebook.getMemberByName(nameInput2);
							member1->checkFollowship(nameInput2);
							isValid = true;
						}
						catch (FacebookExceptions& e)
						{
							cout << e.what() << endl;
						}
					}
					member2 = facebook.getMemberByName(nameInput2);
					*member1 += *member2;
				}
			break;

		case MENU_OPTIONS::DISCONNECT_MEMBERS:
			readMemberName(facebook, nameInput);
			member1 = facebook.getMemberByName(nameInput);
			if (member1->getFriendsSize() == 0)
				cout << "No members available to remove from this user" << endl;
			else
			{
				while (!isValid)
				{
					facebook.printFriendListOfMember(nameInput);
					cout << "Please choose a friend to delete from the list above: ";
					nameInput2 = readInputString();
					try
					{
						isBlank(nameInput2);
						facebook.isNotMember(nameInput2);
						member1->isMe(nameInput2);
						member2 = facebook.getMemberByName(nameInput2);
						member1->checkNotFollowship(nameInput2);
						isValid = true;
					}
					catch (FacebookExceptions& e)
					{
						cout << e.what() << endl;
					}
				}
				member1->removeMutualFollow(nameInput2);
			}
			break;

		case MENU_OPTIONS::ADD_FAN_TO_PAGE:
			readPageName(facebook, nameInput);
			page = facebook.getPageByName(nameInput);
			if (page->getFollowersList().size() == (facebook.getMembersList().size() - 1))
				cout << "No members available to add as fans to this page" << endl;
			else
			{
				while (!isValid)
				{
					facebook.printAvailableFans(page);
					cout << "Please enter the member's name from the list above: ";
					nameInput2 = readInputString();
					try
					{
						isBlank(nameInput2);
						facebook.isNotMember(nameInput2);
						page->checkFollowship(nameInput2);
						isValid = true;
					}
					catch (FacebookExceptions& e)
					{
						cout << e.what() << endl;
					}
				}
				member1 = facebook.getMemberByName(nameInput2);
				*page += *member1;
			}
			break;

		case MENU_OPTIONS::REMOVE_FAN_FROM_PAGE:
			readPageName(facebook, nameInput);
			page = facebook.getPageByName(nameInput);
			if (page->getFollowersList().size() == 0)
				cout << "No members available to remove from this page fan list" << endl;
			else
			{
				while (!isValid)
				{
					cout << "Fans available to delete:" << endl;
					page->printAllFollowerMembers();
					cout << "Please enter the member's name from the list above: ";
					nameInput2 = readInputString();
					try
					{
						isBlank(nameInput2);
						facebook.isNotMember(nameInput2);
						page->checkNotFollowship(nameInput2);
						isValid = true;
					}
					catch (FacebookExceptions& e)
					{
						cout << e.what() << endl;
					}
				}
				page->removeMutualFollow(nameInput2);
			}
			break;

		case MENU_OPTIONS::PRINT_ALL_ENTITIES:
			facebook.printAllEntities();
			break;

		case MENU_OPTIONS::PRINT_MEMBER_FRIENDS:
			readMemberName(facebook, nameInput);
			facebook.getMemberByName(nameInput)->printAllMyFriends();
			break;

		case MENU_OPTIONS::PRINT_PAGE_FANS:
			readPageName(facebook, nameInput);
			facebook.getPageByName(nameInput)->printAllFollowerMembers();
			break;

		case MENU_OPTIONS::EXIT_MENU:
			break;
		default:
			cout << "Invalid option" << endl;
			break;
		}

		if (choice != MENU_OPTIONS::EXIT_MENU)
		{
			cout << "-------------------------" << endl;
			readValidChoice(userInput, choice, facebook);
		}


	}

}

void newTerminate()
{
	cout << "A problem has occured" << endl;
	exit(1);
}


void readValidChoice(string& userInput, MENU_OPTIONS& choice,Facebook& facebook)
{
	bool isValid = false;
	while (!isValid)
	{
		printMenu();
		userInput = readInputString();
		try
		{
			isBlank(userInput);
			facebook.isNumber(userInput);
			choice = (MENU_OPTIONS)stoi(userInput);
			isValid = true;
		}
		catch (FacebookExceptions& e)
		{
			cout << e.what() << endl;
		}

	}

}

void printMenu()
{
	cout << "Please enter desired action by number:" << endl;
	for (int i = 0; i < enumStringSize; i++)
	{
		cout << i + 1 << ". " << enumStrings[i] << endl;
	}
	cout << "Your choice: ";
}

void readMemberName(Facebook& facebook, string& nameInput)
{
	bool isValid = false;
	while (!isValid)
	{
		facebook.printAllMembers();
		cout << "Choose 1 member of the above by typing his name: ";
		nameInput = readInputString();
		try
		{
			isBlank(nameInput);
			facebook.isNotMember(nameInput);
			isValid = true;
			
		}
		//isMember function throws an exception if and only if the member exists
		catch (FacebookExceptions& e)
		{
			cout << e.what() << endl;
		}
	}
}

void readPageName(Facebook& facebook, string& nameInput)
{
	bool isValid = false;
	while (!isValid)
	{
		facebook.printAllPages();
		cout << "Choose 1 page of the above by typing his name: ";
		nameInput = readInputString();
		try
		{
			isBlank(nameInput);
			facebook.isNotPage(nameInput);
			isValid = true;
		}
		//isPage function throws an exception if and only if the page exists
		catch (FacebookExceptions& e)
		{
			cout << e.what() << endl;
		}
	}
}

string readInputString()
{
	string input;
	getline(cin, input);

	return input;
}



void isBlank(const string& input) throw(BlankException)
{
	if (input.size() == 0)
		throw BlankException();
}

bool getMedia(string& mediaFile)
{
	bool isValid = false;
	string userAnswer;

	while (!isValid)
	{
		cout << "Do you want to add a media file (image/video)? y/n" << endl;
		userAnswer = readInputString();
		if (userAnswer == "y")
		{
			cout << "Please type the file name with extension: " << endl;
			mediaFile = readInputString();
			try
			{
				isBlank(mediaFile);
			}
			catch (FacebookExceptions& e)
			{
				cout << e.what() << endl;
			}
			isValid = true;
			return true;
		}
		else if (userAnswer == "n")
			return false;
		else 
			cout << "Wrong input!";
		
	}	
	return isValid;
}

void saveData(Facebook& facebook)
{
	ofstream outFile("database.txt",ios::out);
	outFile << facebook;
	outFile.close();
}

void getData(Facebook& facebook)
{
	ifstream inFile("database.txt");
	inFile >> facebook;
	inFile.close();

}