#include <iostream>
#include <string>
using namespace std;

// Linked List node for Book
struct Book {
    int id;
    string title;
    string author;
    int quantity;
    Book* next;
};

// Stack node for recent purchases
struct Purchase {
    int bookId;
    string title;
    Purchase* next;
};

// Global heads
Book* head = nullptr;          // Head of book list
Purchase* top = nullptr;       // Top of purchase stack

// Add Book to Linked List (sorted by ID)
void addBook(int id, string title, string author, int quantity) {
    Book* newBook = new Book{id, title, author, quantity, nullptr};

    if (head == nullptr || id < head->id) {
        newBook->next = head;
        head = newBook;
    } else {
        Book* current = head;
        while (current->next != nullptr && current->next->id < id) {
            current = current->next;
        }
        newBook->next = current->next;
        current->next = newBook;
    }
    cout << "\n? Book added successfully!\n";
}

// Display all books
void displayBooks() {
    if (head == nullptr) {
        cout << "\n?? No books available.\n";
        return;
    }

    Book* current = head;
    cout << "\n?? Book List:\n";
    while (current != nullptr) {
        cout << "ID: " << current->id
             << " | Title: " << current->title
             << " | Author: " << current->author
             << " | Quantity: " << current->quantity << "\n";
        current = current->next;
    }
}

// Search book by ID
Book* searchBook(int id) {
    Book* current = head;
    while (current != nullptr) {
        if (current->id == id)
            return current;
        current = current->next;
    }
    return nullptr;
}

// Purchase a book and push to stack
void purchaseBook(int id) {
    Book* book = searchBook(id);
    if (book == nullptr) {
        cout << "? Book not found.\n";
        return;
    }
    if (book->quantity <= 0) {
        cout << "?? Out of stock.\n";
        return;
    }

    book->quantity--;
    Purchase* newPurchase = new Purchase{id, book->title, top};
    top = newPurchase;
    cout << "? Book purchased: " << book->title << "\n";
}

// Show recent purchases from stack
void showRecentPurchases() {
    if (top == nullptr) {
        cout << "\n?? No recent purchases.\n";
        return;
    }

    Purchase* current = top;
    cout << "\n?? Recent Purchases:\n";
    while (current != nullptr) {
        cout << "Book ID: " << current->bookId
             << " | Title: " << current->title << "\n";
        current = current->next;
    }
}

// Delete a book by ID
void deleteBook(int id) {
    if (head == nullptr) {
        cout << "? No books available to delete.\n";
        return;
    }

    if (head->id == id) {
        Book* temp = head;
        head = head->next;
        delete temp;
        cout << "??? Book deleted successfully.\n";
        return;
    }

    Book* current = head;
    while (current->next != nullptr && current->next->id != id) {
        current = current->next;
    }

    if (current->next == nullptr) {
        cout << "? Book not found.\n";
    } else {
        Book* temp = current->next;
        current->next = temp->next;
        delete temp;
        cout << "??? Book deleted successfully.\n";
    }
}

// Main menu
int main() {
    int choice, id, quantity;
    string title, author;

    do {
        cout << "\n?? Bookstore Management System\n";
        cout << "--------------------------------\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Purchase Book\n";
        cout << "5. Show Recent Purchases\n";
        cout << "6. Delete Book\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Title: ";
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            cout << "Enter Quantity: ";
            cin >> quantity;
            addBook(id, title, author, quantity);
            break;

        case 2:
            displayBooks();
            break;

        case 3:
            cout << "Enter Book ID to search: ";
            cin >> id;
            {
                Book* found = searchBook(id);
                if (found) {
                    cout << "?? Book Found: " << found->title << " by " << found->author
                         << " | Quantity: " << found->quantity << "\n";
                } else {
                    cout << "? Book not found.\n";
                }
            }
            break;

        case 4:
            cout << "Enter Book ID to purchase: ";
            cin >> id;
            purchaseBook(id);
            break;

        case 5:
            showRecentPurchases();
            break;

        case 6:
            cout << "Enter Book ID to delete: ";
            cin >> id;
            deleteBook(id);
            break;

        case 0:
            cout << "?? Exiting the system. Goodbye!\n";
            break;

        default:
            cout << "? Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
