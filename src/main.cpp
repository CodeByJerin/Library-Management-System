#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Color codes
const string BLUE = "\033[1;34m";
const string CYAN = "\033[1;36m";
const string GREEN = "\033[1;32m";
const string RED = "\033[1;31m";
const string YELLOW = "\033[1;33m";
const string RESET = "\033[0m";

// Book information
struct Book
{
    int id;
    string title;
    string author;
    int quantity;
};

// Member information
struct Member
{
    int id;
    string name;
    string phone;
};

vector<Book> books;
vector<Member> members;

// সঠিক number নেওয়ার function
int readInt(const string &message)
{
    while (true)
    {
        cout << YELLOW << message << RESET;

        string input;
        getline(cin, input);

        stringstream ss(input);
        int value;
        char extra;

        if (ss >> value && !(ss >> extra))
        {
            return value;
        }

        cout << RED << "Please enter a valid number.\n" << RESET;
    }
}

// খালি নয় এমন text নেওয়ার function
string readText(const string &message)
{
    while (true)
    {
        cout << YELLOW << message << RESET;

        string value;
        getline(cin, value);

        if (!value.empty())
        {
            return value;
        }

        cout << RED << "This field cannot be empty.\n" << RESET;
    }
}

// ID দিয়ে Book খোঁজা
int findBookIndex(int id)
{
    for (int i = 0; i < static_cast<int>(books.size()); i++)
    {
        if (books[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

// ID দিয়ে Member খোঁজা
int findMemberIndex(int id)
{
    for (int i = 0; i < static_cast<int>(members.size()); i++)
    {
        if (members[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

// Book file-এ save করা
void saveBooks()
{
    ofstream file("books.txt");

    for (const Book &book : books)
    {
        file << book.id << '|'
             << book.title << '|'
             << book.author << '|'
             << book.quantity << '\n';
    }
}

// Book file থেকে load করা
void loadBooks()
{
    books.clear();

    ifstream file("books.txt");
    string line;

    while (getline(file, line))
    {
        string idText;
        string title;
        string author;
        string quantityText;

        stringstream ss(line);

        if (getline(ss, idText, '|') &&
            getline(ss, title, '|') &&
            getline(ss, author, '|') &&
            getline(ss, quantityText))
        {
            try
            {
                Book book;

                book.id = stoi(idText);
                book.title = title;
                book.author = author;
                book.quantity = stoi(quantityText);

                books.push_back(book);
            }
            catch (...)
            {
                // ভুল line থাকলে বাদ যাবে
            }
        }
    }
}

// Member file-এ save করা
void saveMembers()
{
    ofstream file("members.txt");

    for (const Member &member : members)
    {
        file << member.id << '|'
             << member.name << '|'
             << member.phone << '\n';
    }
}

// Member file থেকে load করা
void loadMembers()
{
    members.clear();

    ifstream file("members.txt");
    string line;

    while (getline(file, line))
    {
        string idText;
        string name;
        string phone;

        stringstream ss(line);

        if (getline(ss, idText, '|') &&
            getline(ss, name, '|') &&
            getline(ss, phone))
        {
            try
            {
                Member member;

                member.id = stoi(idText);
                member.name = name;
                member.phone = phone;

                members.push_back(member);
            }
            catch (...)
            {
                // ভুল line থাকলে বাদ যাবে
            }
        }
    }
}

// Main Menu
void showMainMenu()
{
    cout << BLUE;
    cout << "\n     LIBRARY MANAGEMENT SYSTEM\n";
    cout << "     -------------------------\n\n";
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
}

// Book Management Menu
void showBookMenu()
{
    cout << BLUE;
    cout << "\n     BOOK MANAGEMENT\n";
    cout << "     ---------------\n\n";
    cout << RESET;

    cout << CYAN;
    cout << "1. Add Book\n";
    cout << "2. View All Books\n";
    cout << "3. Search Book\n";
    cout << "4. Update Book\n";
    cout << "5. Delete Book\n";
    cout << "6. Back to Main Menu\n\n";
    cout << RESET;
}

// Add Book
void addBook()
{
    cout << CYAN;
    cout << "\nADD BOOK\n";
    cout << "--------\n";
    cout << RESET;

    int id = readInt("Book ID: ");

    if (findBookIndex(id) != -1)
    {
        cout << RED;
        cout << "A book with this ID already exists.\n";
        cout << RESET;
        return;
    }

    Book book;

    book.id = id;
    book.title = readText("Book title: ");
    book.author = readText("Author name: ");

    do
    {
        book.quantity = readInt("Quantity: ");

        if (book.quantity < 0)
        {
            cout << RED;
            cout << "Quantity cannot be negative.\n";
            cout << RESET;
        }

    } while (book.quantity < 0);

    books.push_back(book);
    saveBooks();

    cout << GREEN;
    cout << "Book added successfully.\n";
    cout << RESET;
}

// View All Books
void viewAllBooks()
{
    cout << CYAN;
    cout << "\nALL BOOKS\n";
    cout << "---------\n";
    cout << RESET;

    if (books.empty())
    {
        cout << RED;
        cout << "No books found.\n";
        cout << RESET;
        return;
    }

    for (const Book &book : books)
    {
        cout << "Book ID  : " << book.id << '\n';
        cout << "Title    : " << book.title << '\n';
        cout << "Author   : " << book.author << '\n';
        cout << "Quantity : " << book.quantity << '\n';
        cout << "------------------------------\n";
    }
}

// Search Book
void searchBook()
{
    cout << CYAN;
    cout << "\nSEARCH BOOK\n";
    cout << "-----------\n";
    cout << RESET;

    int id = readInt("Enter Book ID: ");
    int index = findBookIndex(id);

    if (index == -1)
    {
        cout << RED;
        cout << "Book not found.\n";
        cout << RESET;
        return;
    }

    const Book &book = books[index];

    cout << GREEN;
    cout << "Book found.\n";
    cout << RESET;

    cout << "Book ID  : " << book.id << '\n';
    cout << "Title    : " << book.title << '\n';
    cout << "Author   : " << book.author << '\n';
    cout << "Quantity : " << book.quantity << '\n';
}

// Update Book
void updateBook()
{
    cout << CYAN;
    cout << "\nUPDATE BOOK\n";
    cout << "-----------\n";
    cout << RESET;

    int id = readInt("Enter Book ID: ");
    int index = findBookIndex(id);

    if (index == -1)
    {
        cout << RED;
        cout << "Book not found.\n";
        cout << RESET;
        return;
    }

    books[index].title = readText("New title: ");
    books[index].author = readText("New author name: ");

    do
    {
        books[index].quantity = readInt("New quantity: ");

        if (books[index].quantity < 0)
        {
            cout << RED;
            cout << "Quantity cannot be negative.\n";
            cout << RESET;
        }

    } while (books[index].quantity < 0);

    saveBooks();

    cout << GREEN;
    cout << "Book updated successfully.\n";
    cout << RESET;
}

// Delete Book
void deleteBook()
{
    cout << CYAN;
    cout << "\nDELETE BOOK\n";
    cout << "-----------\n";
    cout << RESET;

    int id = readInt("Enter Book ID: ");
    int index = findBookIndex(id);

    if (index == -1)
    {
        cout << RED;
        cout << "Book not found.\n";
        cout << RESET;
        return;
    }

    string answer = readText("Delete this book? (y/n): ");

    if (answer == "y" || answer == "Y")
    {
        books.erase(books.begin() + index);
        saveBooks();

        cout << GREEN;
        cout << "Book deleted successfully.\n";
        cout << RESET;
    }
    else
    {
        cout << YELLOW;
        cout << "Delete cancelled.\n";
        cout << RESET;
    }
}

// Book Management চালানো
void bookManagement()
{
    int choice;

    do
    {
        showBookMenu();
        choice = readInt("Enter your choice: ");

        switch (choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                viewAllBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                updateBook();
                break;

            case 5:
                deleteBook();
                break;

            case 6:
                cout << YELLOW;
                cout << "Returning to Main Menu...\n";
                cout << RESET;
                break;

            default:
                cout << RED;
                cout << "Invalid choice. Please try again.\n";
                cout << RESET;
        }

    } while (choice != 6);
}

// Member Management Menu
void showMemberMenu()
{
    cout << BLUE;
    cout << "\n     MEMBER MANAGEMENT\n";
    cout << "     -----------------\n\n";
    cout << RESET;

    cout << CYAN;
    cout << "1. Add Member\n";
    cout << "2. View All Members\n";
    cout << "3. Search Member\n";
    cout << "4. Update Member\n";
    cout << "5. Delete Member\n";
    cout << "6. Back to Main Menu\n\n";
    cout << RESET;
}

// Add Member
void addMember()
{
    cout << CYAN;
    cout << "\nADD MEMBER\n";
    cout << "----------\n";
    cout << RESET;

    int id = readInt("Member ID: ");

    if (findMemberIndex(id) != -1)
    {
        cout << RED;
        cout << "A member with this ID already exists.\n";
        cout << RESET;
        return;
    }

    Member member;

    member.id = id;
    member.name = readText("Member name: ");
    member.phone = readText("Phone number: ");

    members.push_back(member);
    saveMembers();

    cout << GREEN;
    cout << "Member added successfully.\n";
    cout << RESET;
}

// View All Members
void viewAllMembers()
{
    cout << CYAN;
    cout << "\nALL MEMBERS\n";
    cout << "-----------\n";
    cout << RESET;

    if (members.empty())
    {
        cout << RED;
        cout << "No members found.\n";
        cout << RESET;
        return;
    }

    for (const Member &member : members)
    {
        cout << "Member ID : " << member.id << '\n';
        cout << "Name      : " << member.name << '\n';
        cout << "Phone     : " << member.phone << '\n';
        cout << "------------------------------\n";
    }
}

// Search Member
void searchMember()
{
    cout << CYAN;
    cout << "\nSEARCH MEMBER\n";
    cout << "-------------\n";
    cout << RESET;

    int id = readInt("Enter Member ID: ");
    int index = findMemberIndex(id);

    if (index == -1)
    {
        cout << RED;
        cout << "Member not found.\n";
        cout << RESET;
        return;
    }

    const Member &member = members[index];

    cout << GREEN;
    cout << "Member found.\n";
    cout << RESET;

    cout << "Member ID : " << member.id << '\n';
    cout << "Name      : " << member.name << '\n';
    cout << "Phone     : " << member.phone << '\n';
}

// Update Member
void updateMember()
{
    cout << CYAN;
    cout << "\nUPDATE MEMBER\n";
    cout << "-------------\n";
    cout << RESET;

    int id = readInt("Enter Member ID: ");
    int index = findMemberIndex(id);

    if (index == -1)
    {
        cout << RED;
        cout << "Member not found.\n";
        cout << RESET;
        return;
    }

    members[index].name = readText("New member name: ");
    members[index].phone = readText("New phone number: ");

    saveMembers();

    cout << GREEN;
    cout << "Member updated successfully.\n";
    cout << RESET;
}

// Delete Member
void deleteMember()
{
    cout << CYAN;
    cout << "\nDELETE MEMBER\n";
    cout << "-------------\n";
    cout << RESET;

    int id = readInt("Enter Member ID: ");
    int index = findMemberIndex(id);

    if (index == -1)
    {
        cout << RED;
        cout << "Member not found.\n";
        cout << RESET;
        return;
    }

    string answer = readText("Delete this member? (y/n): ");

    if (answer == "y" || answer == "Y")
    {
        members.erase(members.begin() + index);
        saveMembers();

        cout << GREEN;
        cout << "Member deleted successfully.\n";
        cout << RESET;
    }
    else
    {
        cout << YELLOW;
        cout << "Delete cancelled.\n";
        cout << RESET;
    }
}

// Member Management চালানো
void memberManagement()
{
    int choice;

    do
    {
        showMemberMenu();
        choice = readInt("Enter your choice: ");

        switch (choice)
        {
            case 1:
                addMember();
                break;

            case 2:
                viewAllMembers();
                break;

            case 3:
                searchMember();
                break;

            case 4:
                updateMember();
                break;

            case 5:
                deleteMember();
                break;

            case 6:
                cout << YELLOW;
                cout << "Returning to Main Menu...\n";
                cout << RESET;
                break;

            default:
                cout << RED;
                cout << "Invalid choice. Please try again.\n";
                cout << RESET;
        }

    } while (choice != 6);
}

// Program এখান থেকে শুরু
int main()
{
    loadBooks();
    loadMembers();

    int choice;

    do
    {
        showMainMenu();
        choice = readInt("Enter your choice: ");

        switch (choice)
        {
            case 1:
                bookManagement();
                break;

            case 2:
                memberManagement();
                break;

            case 3:
                cout << YELLOW;
                cout << "Issue Book will be added later.\n";
                cout << RESET;
                break;

            case 4:
                cout << YELLOW;
                cout << "Return Book will be added later.\n";
                cout << RESET;
                break;

            case 5:
                cout << YELLOW;
                cout << "Borrowing History will be added later.\n";
                cout << RESET;
                break;

            case 6:
                cout << YELLOW;
                cout << "Library Summary will be added later.\n";
                cout << RESET;
                break;

            case 7:
                cout << YELLOW;
                cout << "Exiting the program...\n";
                cout << RESET;
                break;

            default:
                cout << RED;
                cout << "Invalid choice. Please try again.\n";
                cout << RESET;
        }

    } while (choice != 7);

    return 0;
}
