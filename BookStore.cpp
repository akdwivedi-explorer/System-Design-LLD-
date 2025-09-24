// Q - Design a Bookstore system
// Requirements
// 1. Multiple books
// 2. users can search by title/author/ISBN
// 3. buy/sell books

// Data Structures Used
// 1. Array
// 2. Pair<Book, int>

// Code
#include <bits/stdc++.h>
using namespace std;

class Book {
private:
    string title;
    string ISBN;
    string author;
    int pages;
    double price;
    int stock;

public:
    Book(string t, string isbn, string a, int p, double pr, int st)
        : title(t), ISBN(isbn), author(a), pages(p), price(pr), stock(st) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return ISBN; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    void addStock(int qty) { stock += qty; }

    bool reduceStock(int qty) {
        if (stock >= qty) {
            stock -= qty;
            return true;
        }
        return false;
    }

    int countWordOccurrence(const string& content, const string& word) const {
        int count = 0;
        size_t pos = content.find(word, 0);
        while (pos != string::npos) {
            count++;
            pos = content.find(word, pos + word.length());
        }
        return count;
    }

    bool operator==(const Book& other) const {
        return ISBN == other.ISBN;
    }
};

class User {
private:
    string userID;
    string name;
    string email;

public:
    User(string id, string n, string e) : userID(id), name(n), email(e) {}
    string getUserID() const { return userID; }
    string getName() const { return name; }
};

class Cart {
private:
    vector<pair<Book, int>> items;

public:
    void addBook(Book& book, int qty) { items.push_back({book, qty}); }

    void removeBook(const string& ISBN) {
        items.erase(remove_if(items.begin(), items.end(),
                              [&](pair<Book, int>& item) {
                                  return item.first.getISBN() == ISBN;
                              }),
                    items.end());
    }

    vector<pair<Book, int>> getBooks() { return items; }
};

class Order {
private:
    string orderID;
    User u;
    vector<pair<Book, int>> items;
    double totalAmount;
    string status;

public:
    Order(string id, User u, vector<pair<Book, int>> items, double total,
          string st)
        : orderID(id), u(u), items(items), totalAmount(total), status(st) {}

    double getTotalAmount() const { return totalAmount; }
    string getStatus() const { return status; }
    void updateStatus(string s) { status = s; }
};

class Bookstore {
private:
    vector<Book> inventory;

public:
    void addBook(Book book) { inventory.push_back(book); }

    vector<Book> searchByTitle(const string& title) {
        vector<Book> result;
        for (auto& b : inventory) {
            if (b.getTitle() == title) result.push_back(b);
        }
        return result;
    }

    vector<Book> searchByAuthor(const string& author) {
        vector<Book> result;
        for (auto& b : inventory) {
            if (b.getAuthor() == author) result.push_back(b);
        }
        return result;
    }

    Book* searchByIsbn(const string& isbn) {
        for (auto& b : inventory) {
            if (b.getISBN() == isbn) return &b;
        }
        return nullptr;
    }

    bool buyBook(const string& isbn, int qty) {
        Book* book = searchByIsbn(isbn);
        if (book && book->reduceStock(qty)) return true;
        return false;
    }

    void sellBook(const string& isbn, int qty) {
        Book* book = searchByIsbn(isbn);
        if (book) book->addStock(qty);
    }
};

int main() {
    Bookstore store;

    Book b1("Atomic Habits", "B001", "James Clear", 180, 150.0, 5);
    Book b2("Do Epic Shit", "B002", "Ankur Warikoo", 200, 120.0, 3);

    store.addBook(b1);
    store.addBook(b2);

    auto results = store.searchByAuthor("James Clear");
    for (auto& book : results) {
        cout << "Found: " << book.getTitle() << endl;
    }

    if (store.buyBook("B001", 1))
        cout << "Purchase successful\n";
    else
        cout << "Out of stock\n";

    string content =
        "James is a character. James does great things. James!";
    cout << "Word 'James' appears "
         << b1.countWordOccurrence(content, "James") << " times\n";

    return 0;
}
