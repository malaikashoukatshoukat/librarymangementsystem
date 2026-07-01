#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>


using namespace std;

class Book
{
private:
    int bookID;
    string title;
    string author;
    string category;
    bool available;

public:
    Book();
    Book(int id, string t, string a, string c, bool avail);
    void input();
    void display();
    int getID();
    string toFile();
    string getTitle();
    string getAuthor();
    void setTitle(string t);
    void setAuthor(string a);
    void setCategory(string c);
    bool isAvailable();
    void setAvailability(bool status);
};

class Member
{
private:
    int memberID;
    string name;
    string contact;
    int borrowCount;

public:
    Member();
    void input();
    void display();
    void increaseBorrow();
    void decreaseBorrow();
    int getID();
    Member(int id, string n, string c, int borrow);
    string toFile();
};

class Transaction
{
private:
    int memberID;
    int bookID;
    string issueDate;
    string returnDate;

public:
    Transaction();
    Transaction(int mID, int bID, string iDate, string rDate);
    void display();
    int getBookID();
    int getMemberID();
    string getReturnDate();
    void setReturnDate(string date);
    string toFile();
};

class Library
{
private:
    vector<Book> books;
    vector<Member> members;
    vector<Transaction> transactions;

public:
    void addBook();
    void updateBook();
    void deleteBook();
    void viewBooks();
    void addMember();
    void viewMembers();
    void issueBook();
    void returnBook();
    void searchByID();
    void searchByTitle();
    void searchByAuthor();
    void issuedBooks();
    void overdueBooks();
    void viewTransactions();
    void loadData();
    void saveData();
    void loadMembers();
    void saveMembers();
    void saveTransactions();
    void loadTransactions();
    void memberHistory();
    void mostBorrowedBooks();
};

Book::Book() { bookID = 0; title = ""; author = ""; category = ""; available = true; }
Book::Book(int id, string t, string a, string c, bool avail) { bookID = id; title = t; author = a; category = c; available = avail; }
void Book::input()
{
    cout << "Enter Book ID: ";
    cin >> bookID;
    cin.ignore();
    cout << "Enter Title: ";
    getline(cin, title);
    cout << "Enter Author: ";
    getline(cin, author);
    cout << "Enter Category: ";
    getline(cin, category);
    available = true;
}
void Book::display()
{
    cout << "\nBook ID: " << bookID << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Category: " << category << endl;
    cout << "Availability: " << (available ? "Available" : "Issued") << endl;
}
int Book::getID() { return bookID; }
string Book::getTitle() { return title; }
string Book::getAuthor() { return author; }
bool Book::isAvailable() { return available; }
void Book::setAvailability(bool status) { available = status; }
void Book::setTitle(string t) { title = t; }
void Book::setAuthor(string a) { author = a; }
void Book::setCategory(string c) { category = c; }
string Book::toFile()
{
    stringstream ss;
    ss << bookID << "|" << title << "|" << author << "|" << category << "|" << available;
    return ss.str();
}

Member::Member() { memberID = 0; name = ""; contact = ""; borrowCount = 0; }
Member::Member(int id, string n, string c, int borrow) { memberID = id; name = n; contact = c; borrowCount = borrow; }
void Member::input()
{
    cout << "Enter Member ID: ";
    cin >> memberID;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Contact: ";
    getline(cin, contact);
    borrowCount = 0;
}
void Member::display()
{
    cout << "\nMember ID: " << memberID << endl;
    cout << "Name: " << name << endl;
    cout << "Contact: " << contact << endl;
    cout << "Borrow Count: " << borrowCount << endl;
}
int Member::getID() { return memberID; }
void Member::increaseBorrow() { borrowCount++; }
void Member::decreaseBorrow() { if (borrowCount > 0) borrowCount--; }
string Member::toFile()
{
    stringstream ss;
    ss << memberID << "|" << name << "|" << contact << "|" << borrowCount;
    return ss.str();
}

Transaction::Transaction() { memberID = 0; bookID = 0; issueDate = ""; returnDate = ""; }
Transaction::Transaction(int mID, int bID, string iDate, string rDate) { memberID = mID; bookID = bID; issueDate = iDate; returnDate = rDate; }
void Transaction::display()
{
    cout << "\nMember ID: " << memberID;
    cout << "\nBook ID: " << bookID;
    cout << "\nIssue Date: " << issueDate;
    cout << "\nReturn Date: " << returnDate << endl;
}
int Transaction::getBookID() { return bookID; }
int Transaction::getMemberID() { return memberID; }
string Transaction::getReturnDate() { return returnDate; }
void Transaction::setReturnDate(string date) { returnDate = date; }
string Transaction::toFile()
{
    stringstream ss;
    ss << memberID << "|" << bookID << "|" << issueDate << "|" << returnDate;
    return ss.str();
}

void Library::addBook()
{
    Book b;
    b.input();
    for (Book &book : books)
    {
        if (book.getID() == b.getID())
        {
            cout << "\nBook ID already exists!\n";
            return;
        }
    }
    books.push_back(b);
    saveData();
    cout << "\nBook Added Successfully.\n";
}
void Library::addMember()
{
    Member m;
    m.input();
    for (Member &member : members)
    {
        if (member.getID() == m.getID())
        {
            cout << "\nMember ID already exists.\n";
            return;
        }
    }
    members.push_back(m);
    saveMembers();
    cout << "\nMember Added Successfully.\n";
}
void Library::viewMembers()
{
    if (members.empty()) { cout << "\nNo members available.\n"; return; }
    cout << "\n========== Member List ==========\n";
    for (Member &m : members) { m.display(); cout << "------------------------------\n"; }
}
void Library::viewBooks()
{
    if (books.empty()) { cout << "\nNo books available.\n"; return; }
    cout << "\n========== Book List ==========\n";
    for (Book &b : books) { b.display(); cout << "------------------------------\n"; }
}
void Library::saveData()
{
    ofstream fout("books.txt");
    if (!fout) { cout << "File could not be opened.\n"; return; }
    for (Book &b : books) fout << b.toFile() << endl;
    fout.close();
}
void Library::loadData()
{
    books.clear();
    ifstream fin("books.txt");
    if (!fin) return;
    string line;
    while (getline(fin, line))
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, title, author, category, available;
        getline(ss, id, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, category, '|');
        getline(ss, available);
        if (id.empty() || available.empty()) continue;
        books.push_back(Book(stoi(id), title, author, category, stoi(available)));
    }
    fin.close();
}
void Library::updateBook()
{
    int id;
    cout << "Enter Book ID to update: ";
    cin >> id;
    cin.ignore();
    bool found = false;
    for (Book &b : books)
    {
        if (b.getID() == id)
        {
            string title, author, category;
            cout << "Enter New Title: ";
            getline(cin, title);
            cout << "Enter New Author: ";
            getline(cin, author);
            cout << "Enter New Category: ";
            getline(cin, category);
            b.setTitle(title);
            b.setAuthor(author);
            b.setCategory(category);
            saveData();
            cout << "\nBook Updated Successfully.\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "\nBook not found.\n";
}
void Library::deleteBook()
{
    int id;
    cout << "Enter Book ID to delete: ";
    cin >> id;
    auto it = remove_if(books.begin(), books.end(), [id](Book &b) { return b.getID() == id; });
    if (it != books.end()) { books.erase(it, books.end()); saveData(); cout << "\nBook Deleted Successfully.\n"; }
    else cout << "\nBook not found.\n";
}
void Library::searchByID()
{
    int id;
    cout << "Enter Book ID to search: ";
    cin >> id;
    bool found = false;
    for (Book &b : books)
    {
        if (b.getID() == id) { cout << "\nBook Found:\n"; b.display(); found = true; break; }
    }
    if (!found) cout << "\nBook not found.\n";
}
void Library::searchByTitle()
{
    cin.ignore();
    string title;
    cout << "Enter Book Title: ";
    getline(cin, title);
    bool found = false;
    for (Book &b : books) { if (b.getTitle() == title) { b.display(); found = true; } }
    if (!found) cout << "\nBook not found.\n";
}
void Library::searchByAuthor()
{
    cin.ignore();
    string author;
    cout << "Enter Author Name: ";
    getline(cin, author);
    bool found = false;
    for (Book &b : books) { if (b.getAuthor() == author) { b.display(); found = true; } }
    if (!found) cout << "\nNo books found for this author.\n";
}
void Library::saveMembers()
{
    ofstream fout("members.txt");
    if (!fout) { cout << "Unable to open members file.\n"; return; }
    for (Member &m : members) fout << m.toFile() << endl;
    fout.close();
}
void Library::loadMembers()
{
    members.clear();
    ifstream fin("members.txt");
    if (!fin) return;
    string line;
    while (getline(fin, line))
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name, contact, borrow;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, contact, '|');
        getline(ss, borrow);
        if (id.empty() || borrow.empty()) continue;
        members.push_back(Member(stoi(id), name, contact, stoi(borrow)));
    }
    fin.close();
}
void Library::loadTransactions()
{
    transactions.clear();
    ifstream fin("transactions.txt");
    if (!fin) return;
    string line;
    while (getline(fin, line))
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string memberID, bookID, issueDate, returnDate;
        getline(ss, memberID, '|');
        getline(ss, bookID, '|');
        getline(ss, issueDate, '|');
        getline(ss, returnDate);
        if (memberID.empty() || bookID.empty()) continue;
        transactions.push_back(Transaction(stoi(memberID), stoi(bookID), issueDate, returnDate));
    }
    fin.close();
}
void Library::saveTransactions()
{
    ofstream fout("transactions.txt");
    if (!fout) { cout << "Unable to open transactions file.\n"; return; }
    for (Transaction &t : transactions) fout << t.toFile() << endl;
    fout.close();
}
void Library::issueBook()
{
    int bookID, memberID;
    cout << "Enter Book ID: ";
    cin >> bookID;
    cout << "Enter Member ID: ";
    cin >> memberID;
    Book *book = nullptr;
    Member *member = nullptr;
    for (Book &b : books) { if (b.getID() == bookID) { book = &b; break; } }
    if (book == nullptr) { cout << "\nBook not found.\n"; return; }
    for (Member &m : members) { if (m.getID() == memberID) { member = &m; break; } }
    if (member == nullptr) { cout << "\nMember not found.\n"; return; }
    if (!book->isAvailable()) { cout << "\nBook is already issued.\n"; return; }
    book->setAvailability(false);
    member->increaseBorrow();
    transactions.push_back(Transaction(memberID, bookID, "30-06-2026", "Not Returned"));
    saveData();
    saveMembers();
    saveTransactions();
    cout << "\nBook Issued Successfully.\n";
}
void Library::returnBook()
{
    int bookID;
    cout << "Enter Book ID: ";
    cin >> bookID;
    Book *book = nullptr;
    for (Book &b : books) { if (b.getID() == bookID) { book = &b; break; } }
    if (book == nullptr) { cout << "\nBook not found.\n"; return; }
    if (book->isAvailable()) { cout << "\nThis book is already available.\n"; return; }
    for (Transaction &t : transactions)
    {
        if (t.getBookID() == bookID && t.getReturnDate() == "Not Returned")
        {
            t.setReturnDate("30-06-2026");
            for (Member &m : members) { if (m.getID() == t.getMemberID()) { m.decreaseBorrow(); break; } }
            break;
        }
    }
    book->setAvailability(true);
    saveData();
    saveMembers();
    saveTransactions();
    cout << "\nBook Returned Successfully.\n";
}
void Library::viewTransactions()
{
    if (transactions.empty()) { cout << "\nNo transactions available.\n"; return; }
    cout << "\n========== Transaction History ==========\n";
    for (Transaction &t : transactions) { t.display(); cout << "----------------------------\n"; }
}
void Library::memberHistory()
{
    int memberID;
    cout << "Enter Member ID: ";
    cin >> memberID;
    bool found = false;
    cout << "\n===== Borrowing History =====\n";
    for (Transaction &t : transactions)
    {
        if (t.getMemberID() == memberID) { t.display(); cout << "-------------------------\n"; found = true; }
    }
    if (!found) cout << "No borrowing history found.\n";
}
void Library::issuedBooks()
{
    bool found = false;
    cout << "\n===== Currently Issued Books =====\n";
    for (Transaction &t : transactions)
    {
        if (t.getReturnDate() == "Not Returned") { t.display(); cout << "-------------------------\n"; found = true; }
    }
    if (!found) cout << "No books are currently issued.\n";
}
void Library::overdueBooks()
{
    bool found = false;
    cout << "\n===== Overdue Books =====\n";
    for (Transaction &t : transactions)
    {
        if (t.getReturnDate() == "Not Returned")
        {
            t.display();
            cout << "Status : Possibly Overdue\n";
            cout << "-------------------------\n";
            found = true;
        }
    }
    if (!found) cout << "No overdue books.\n";
}
void Library::mostBorrowedBooks()
{
    if (transactions.empty()) { cout << "No transaction history available.\n"; return; }
    cout << "\n===== Most Borrowed Books =====\n";
    for (Book &b : books)
    {
        int count = 0;
        for (Transaction &t : transactions) { if (t.getBookID() == b.getID()) count++; }
        cout << "Book ID: " << b.getID() << "  Borrowed " << count << " time(s)\n";
    }
}

int main()
{
    Library lib;
    lib.loadData();
    lib.loadMembers();
    lib.loadTransactions();
    int choice;
    do
    {
        cout << "\n========== Library Management System==========\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Update Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Search by ID\n";
        cout << "6. Search by Title\n";
        cout << "7. Search by Author\n";
        cout << "8. Add Member\n";
        cout << "9. View Members\n";
        cout << "10. Issue Book\n";
        cout << "11. Return Book\n";
        cout << "12. View Transactions\n";
        cout << "13. Member Borrowing History\n";
        cout << "14. Currently Issued Books\n";
        cout << "15. Most Borrowed Books\n";
        cout << "16. Overdue Books\n";
        cout << "17. Exit\n";
        cout << "----------------------------------------\n";
        cout << "Enter Choice: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!\n";
            continue;
        }
        switch (choice)
        {
        case 1: lib.addBook(); break;
        case 2: lib.viewBooks(); break;
        case 3: lib.updateBook(); break;
        case 4: lib.deleteBook(); break;
        case 5: lib.searchByID(); break;
        case 6: lib.searchByTitle(); break;
        case 7: lib.searchByAuthor(); break;
        case 8: lib.addMember(); break;
        case 9: lib.viewMembers(); break;
        case 10: lib.issueBook(); break;
        case 11: lib.returnBook(); break;
        case 12: lib.viewTransactions(); break;
        case 13: lib.memberHistory(); break;
        case 14: lib.issuedBooks(); break;
        case 15: lib.mostBorrowedBooks(); break;
        case 16: lib.overdueBooks(); break;
        case 17: cout << "\nThank you for using the Library Management System.\n"; break;
        default: cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 17);
    return 0;
}
