#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

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
    string category;
    int totalQuantity;
    int availableQuantity;
};

vector<Book> books;

// Take a valid number from the user
int readNumber(string message)
{
    int number;

    while (true)
    {
        cout << YELLOW << message << RESET;

        if (cin >> number)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return number;
        }

        cout << RED << "Please enter a valid number.\n" << RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Take non-empty text from the user
string readText(string message)
{
    string text;

    do
    {
        cout << YELLOW << message << RESET;
        getline(cin, text);

        if (text.empty())
        {
            cout << RED << "This field cannot be empty.\n" << RESET;
        }
    }
    while (text.empty());

    return text;
}

// Find a book using its ID
Book* findBook(int id)
{
    for (Book& book : books)
    {
        if (book.id == id)
        {
            return &book;
        }
    }

    return nullptr;
}

// Save book data in books.txt
void saveBooks()
{
    ofstream file("books.txt");

    for (Book book : books)
    {
        file << book.id << "\n";
        file << book.title << "\n";
        file << book.author << "\n";
        file << book.category << "\n";
        file << book.totalQuantity << "\n";
        file << book.availableQuantity << "\n";
    }
}

// Load book data when the program starts
void loadBooks()
{
    ifstream file("books.txt");
    Book book;

    while (file >> book.id)
    {
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        getline(file, book.title);
        getline(file, book.author);
        getline(file, book.category);

        file >> book.totalQuantity;
        file >> book.availableQuantity;
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        books.push_back(book);
    }
}

// Add a new book
void addBook()
{
    cout << BLUE << "\nADD BOOK\n--------\n" << RESET;

    Book book;
    book.id = readNumber("Book ID: ");

    if (book.id <= 0)
    {
        cout << RED << "Book ID must be greater than zero.\n" << RESET;
        return;
    }

    if (findBook(book.id) != nullptr)
    {
        cout << RED << "This Book ID already exists.\n" << RESET;
        return;
    }

    book.title = readText("Book title: ");
    book.author = readText("Author name: ");
    book.category = readText("Category: ");
    book.totalQuantity = readNumber("Total quantity: ");

    if (book.totalQuantity <= 0)
    {
        cout << RED << "Quantity must be greater than zero.\n" << RESET;
        return;
    }

    book.availableQuantity = book.totalQuantity;
    books.push_back(book);
    saveBooks();

    cout << GREEN << "Book added successfully.\n" << RESET;
}

// View all saved books
void viewAllBooks()
{
    cout << BLUE << "\nALL BOOKS\n---------\n" << RESET;

    if (books.empty())
    {
        cout << RED << "No books found.\n" << RESET;
        return;
    }

    for (Book book : books)
    {
        cout << "Book ID   : " << book.id << "\n";
        cout << "Title     : " << book.title << "\n";
        cout << "Author    : " << book.author << "\n";
        cout << "Category  : " << book.category << "\n";
        cout << "Total     : " << book.totalQuantity << "\n";
        cout << "Available : " << book.availableQuantity << "\n";
        cout << "-------------------------\n";
    }
}

// Search a book by ID
void searchBook()
{
    cout << BLUE << "\nSEARCH BOOK\n-----------\n" << RESET;

    int id = readNumber("Enter Book ID: ");
    Book* book = findBook(id);

    if (book == nullptr)
    {
        cout << RED << "Book not found.\n" << RESET;
        return;
    }

    cout << GREEN << "Book found successfully.\n" << RESET;
    cout << "Book ID   : " << book->id << "\n";
    cout << "Title     : " << book->title << "\n";
    cout << "Author    : " << book->author << "\n";
    cout << "Category  : " << book->category << "\n";
    cout << "Total     : " << book->totalQuantity << "\n";
    cout << "Available : " << book->availableQuantity << "\n";
}

// Update a book
void updateBook()
{
    cout << BLUE << "\nUPDATE BOOK\n-----------\n" << RESET;

    int id = readNumber("Enter Book ID to update: ");
    Book* book = findBook(id);

    if (book == nullptr)
    {
        cout << RED << "Book not found.\n" << RESET;
        return;
    }

    int issuedQuantity =
        book->totalQuantity - book->availableQuantity;

    book->title = readText("New title: ");
    book->author = readText("New author: ");
    book->category = readText("New category: ");

    int newQuantity = readNumber("New total quantity: ");

    if (newQuantity <= 0 || newQuantity < issuedQuantity)
    {
        cout << RED << "Invalid quantity. Update cancelled.\n" << RESET;
        return;
    }

    book->totalQuantity = newQuantity;
    book->availableQuantity = newQuantity - issuedQuantity;
    saveBooks();

    cout << GREEN << "Book updated successfully.\n" << RESET;
}

// Delete a book
void deleteBook()
{
    cout << BLUE << "\nDELETE BOOK\n-----------\n" << RESET;

    int id = readNumber("Enter Book ID to delete: ");

    for (size_t i = 0; i < books.size(); i++)
    {
        if (books[i].id == id)
        {
            if (books[i].availableQuantity < books[i].totalQuantity)
            {
                cout << RED;
                cout << "Issued book cannot be deleted.\n";
                cout << RESET;
                return;
            }

            books.erase(books.begin() + i);
            saveBooks();

            cout << GREEN << "Book deleted successfully.\n" << RESET;
            return;
        }
    }

    cout << RED << "Book not found.\n" << RESET;
}

// Book Management menu
void bookManagement()
{
    int choice;

    do
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

        choice = readNumber("Enter your choice: ");

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
                cout << YELLOW << "Returning to Main Menu...\n" << RESET;
                break;

            default:
                cout << RED << "Invalid choice. Please try again.\n" << RESET;
        }
    }
    while (choice != 6);
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

int main()
{
    loadBooks();

    int choice;

    do
    {
        showMainMenu();
        choice = readNumber("Enter your choice: ");

        switch (choice)
        {
            case 1:
                bookManagement();
                break;

            case 2:
                cout << YELLOW
                     << "Member Management will be added next.\n"
                     << RESET;
                break;

            case 3:
                cout << YELLOW
                     << "Issue Book will be added later.\n"
                     << RESET;
                break;

            case 4:
                cout << YELLOW
                     << "Return Book will be added later.\n"
                     << RESET;
                break;

            case 5:
                cout << YELLOW
                     << "Borrowing History will be added later.\n"
                     << RESET;
                break;

            case 6:
                cout << YELLOW
                     << "Library Summary will be added later.\n"
                     << RESET;
                break;

            case 7:
                cout << YELLOW
                     << "Exiting the program...\n"
                     << RESET;
                break;

            default:
                cout << RED
                     << "Invalid choice. Please try again.\n"
                     << RESET;
        }
    }
    while (choice != 7);

    return 0;
}
