#include <iostream>
using namespace std;

// Color codes
const string BLUE = "\033[1;34m";
const string CYAN = "\033[1;36m";
const string GREEN = "\033[1;32m";
const string RED = "\033[1;31m";
const string YELLOW = "\033[1;33m";
const string RESET = "\033[0m";

// Main menu দেখানোর function
void showMainMenu()
{
    cout << BLUE;
    cout << "\n     LIBRARY MANAGEMENT SYSTEM\n\n";
    cout << RESET;

    cout << CYAN;
    cout << "1. Book Management\n";
    cout << "2. Member Management\n";
    cout << "3. Issue Book\n";
    cout << "4. Return Book\n";
    cout << "5. Borrowing History\n";
    cout << "6. Library Summary\n";
    cout << "7. Exit\n\n";
    cout << RESET;

    cout << YELLOW << "Enter your choice: " << RESET;
}

int main()
{
    int choice;

    do
    {
        showMainMenu();
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << GREEN << "Book Management selected.\n" << RESET;
                break;

            case 2:
                cout << GREEN << "Member Management selected.\n" << RESET;
                break;

            case 3:
                cout << GREEN << "Issue Book selected.\n" << RESET;
                break;

            case 4:
                cout << GREEN << "Return Book selected.\n" << RESET;
                break;

            case 5:
                cout << GREEN << "Borrowing History selected.\n" << RESET;
                break;

            case 6:
                cout << GREEN << "Library Summary selected.\n" << RESET;
                break;

            case 7:
                cout << YELLOW << "Exiting the program...\n" << RESET;
                break;

            default:
                cout << RED << "Invalid choice. Please try again.\n" << RESET;
        }

    } while (choice != 7);

    return 0;
}
