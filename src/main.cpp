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

// Issue and return information
struct Borrowing
{
    int issueId;
    int bookId;
    int memberId;
    string issueDate;
    string returnDate;
    bool returned;
};

vector<Book> books;
vector<Member> members;
vector<Borrowing> borrowings;

// Valid number input
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

        cout << RED;
        cout << "Please enter a valid number.\n";
        cout << RESET;
    }
}

// Valid text input
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

        cout << RED;
        cout << "This field cannot be empty.\n";
        cout << RESET;
    }
}

// Find book using Book ID
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

// Find member using Member ID
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

// Save books
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

// Load books
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
                // Ignore damaged data
            }
        }
    }
}

// Save members
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

// Load members
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
                // Ignore damaged data
            }
        }
    }
}

// Save issue and return information
void saveBorrowings()
{
    ofstream file("borrowings.txt");

    for (const Borrowing &borrowing : borrowings)
    {
        file << borrowing.issueId << '|'
             << borrowing.bookId << '|'
             << borrowing.memberId << '|'
             << borrowing.issueDate << '|'
             << borrowing.returnDate << '|'
             << borrowing.returned << '\n';
    }
}

// Load issue and return information
void loadBorrowings()
{
    borrowings.clear();

    ifstream file("borrowings.txt");
    string line;

    while (getline(file, line))
    {
        string issueIdText;
        string bookIdText;
        string memberIdText;
        string issueDate;
        string returnDate;
        string returnedText;

        stringstream ss(line);

        if (getline(ss, issueIdText, '|') &&
            getline(ss, bookIdText, '|') &&
            getline(ss, memberIdText, '|') &&
            getline(ss, issueDate, '|') &&
            getline(ss, returnDate, '|') &&
            getline(ss, returnedText))
        {
            try
            {
                Borrowing borrowing;

                borrowing.issueId = stoi(issueIdText);
                borrowing.bookId = stoi(bookIdText);
                borrowing.memberId = stoi(memberIdText);
                borrowing.issueDate = issueDate;
                borrowing.returnDate = returnDate;
                borrowing.returned = stoi(returnedText) != 0;

                borrowings.push_back(borrowing);
            }
            catch (...)
            {
                // Ignore damaged data
            }
        }
    }
}

// Create automatic Issue ID
int createIssueId()
{
    int largestId = 0;

    for (const Borrowing &borrowing : borrowings)
    {
        if (borrowing.issueId > largestId)
        {
            largestId = borrowing.issueId;
        }
    }

    return largestId + 1;
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

// View all books
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

    // Issued book cannot be deleted
    for (const Borrowing &borrowing : borrowings)
    {
        if (borrowing.bookId == id && !borrowing.returned)
        {
            cout << RED;
            cout << "This book is currently issued and cannot be deleted.\n";
            cout << RESET;

            return;
        }
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

// Book Management
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

// View all members
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

    // Member with an issued book cannot be deleted
    for (const Borrowing &borrowing : borrowings)
    {
        if (borrowing.memberId == id && !borrowing.returned)
        {
            cout << RED;
            cout << "This member has an issued book and cannot be deleted.\n";
            cout << RESET;

            return;
        }
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

// Member Management
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

// Issue Book
void issueBook()
{
    cout << BLUE;
    cout << "\n     ISSUE BOOK\n";
    cout << "     ----------\n\n";
    cout << RESET;

    if (books.empty())
    {
        cout << RED;
        cout << "No books are available. Add a book first.\n";
        cout << RESET;

        return;
    }

    if (members.empty())
    {
        cout << RED;
        cout << "No members are available. Add a member first.\n";
        cout << RESET;

        return;
    }

    int bookId = readInt("Enter Book ID: ");
    int bookIndex = findBookIndex(bookId);

    if (bookIndex == -1)
    {
        cout << RED;
        cout << "Book not found.\n";
        cout << RESET;

        return;
    }

    if (books[bookIndex].quantity <= 0)
    {
        cout << RED;
        cout << "This book is currently unavailable.\n";
        cout << RESET;

        return;
    }

    int memberId = readInt("Enter Member ID: ");
    int memberIndex = findMemberIndex(memberId);

    if (memberIndex == -1)
    {
        cout << RED;
        cout << "Member not found.\n";
        cout << RESET;

        return;
    }

    // Prevent issuing the same book twice to the same member
    for (const Borrowing &borrowing : borrowings)
    {
        if (borrowing.bookId == bookId &&
            borrowing.memberId == memberId &&
            !borrowing.returned)
        {
            cout << RED;
            cout << "This member has already borrowed this book.\n";
            cout << RESET;

            return;
        }
    }

    string issueDate = readText("Issue date (DD-MM-YYYY): ");
    string answer = readText("Confirm issue? (y/n): ");

    if (answer != "y" && answer != "Y")
    {
        cout << YELLOW;
        cout << "Book issue cancelled.\n";
        cout << RESET;

        return;
    }

    Borrowing borrowing;

    borrowing.issueId = createIssueId();
    borrowing.bookId = bookId;
    borrowing.memberId = memberId;
    borrowing.issueDate = issueDate;
    borrowing.returnDate = "Not returned";
    borrowing.returned = false;

    borrowings.push_back(borrowing);

    // Reduce available quantity
    books[bookIndex].quantity--;

    saveBooks();
    saveBorrowings();

    cout << GREEN;
    cout << "\nBook issued successfully.\n";
    cout << RESET;

    cout << "Issue ID    : " << borrowing.issueId << '\n';
    cout << "Book title  : " << books[bookIndex].title << '\n';
    cout << "Member name : " << members[memberIndex].name << '\n';
    cout << "Issue date  : " << borrowing.issueDate << '\n';
    cout << "Available   : " << books[bookIndex].quantity << '\n';
}

// Return Book
void returnBook()
{
    cout << BLUE;
    cout << "\n     RETURN BOOK\n";
    cout << "     -----------\n\n";
    cout << RESET;

    bool activeBorrowingFound = false;

    cout << CYAN;
    cout << "CURRENTLY ISSUED BOOKS\n";
    cout << RESET;

    // Show books that are not returned yet
    for (const Borrowing &borrowing : borrowings)
    {
        if (!borrowing.returned)
        {
            activeBorrowingFound = true;

            int bookIndex = findBookIndex(borrowing.bookId);
            int memberIndex = findMemberIndex(borrowing.memberId);

            cout << "Issue ID    : " << borrowing.issueId << '\n';
            cout << "Book ID     : " << borrowing.bookId << '\n';
            cout << "Book title  : ";

            if (bookIndex != -1)
            {
                cout << books[bookIndex].title << '\n';
            }
            else
            {
                cout << "Unknown book\n";
            }

            cout << "Member ID   : " << borrowing.memberId << '\n';
            cout << "Member name : ";

            if (memberIndex != -1)
            {
                cout << members[memberIndex].name << '\n';
            }
            else
            {
                cout << "Unknown member\n";
            }

            cout << "Issue date  : " << borrowing.issueDate << '\n';
            cout << "------------------------------\n";
        }
    }

    if (!activeBorrowingFound)
    {
        cout << RED;
        cout << "No issued book is waiting to be returned.\n";
        cout << RESET;

        return;
    }

    int issueId = readInt("Enter Issue ID: ");
    int borrowingIndex = -1;

    for (int i = 0; i < static_cast<int>(borrowings.size()); i++)
    {
        if (borrowings[i].issueId == issueId)
        {
            borrowingIndex = i;
            break;
        }
    }

    if (borrowingIndex == -1)
    {
        cout << RED;
        cout << "Issue ID not found.\n";
        cout << RESET;

        return;
    }

    if (borrowings[borrowingIndex].returned)
    {
        cout << RED;
        cout << "This book has already been returned.\n";
        cout << RESET;

        return;
    }

    int bookIndex =
        findBookIndex(borrowings[borrowingIndex].bookId);

    if (bookIndex == -1)
    {
        cout << RED;
        cout << "Book information not found. Return cannot be completed.\n";
        cout << RESET;

        return;
    }

    string returnDate =
        readText("Return date (DD-MM-YYYY): ");

    string answer =
        readText("Confirm return? (y/n): ");

    if (answer != "y" && answer != "Y")
    {
        cout << YELLOW;
        cout << "Book return cancelled.\n";
        cout << RESET;

        return;
    }

    borrowings[borrowingIndex].returned = true;
    borrowings[borrowingIndex].returnDate = returnDate;

    // Increase available quantity
    books[bookIndex].quantity++;

    saveBorrowings();
    saveBooks();

    cout << GREEN;
    cout << "\nBook returned successfully.\n";
    cout << RESET;

    cout << "Issue ID    : "
         << borrowings[borrowingIndex].issueId << '\n';

    cout << "Book title  : "
         << books[bookIndex].title << '\n';

    cout << "Return date : "
         << borrowings[borrowingIndex].returnDate << '\n';

    cout << "Available   : "
         << books[bookIndex].quantity << '\n';
}

// Program starts here
int main()
{
    loadBooks();
    loadMembers();
    loadBorrowings();

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
                issueBook();
                break;

            case 4:
                returnBook();
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
