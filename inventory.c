#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a book
struct Book {
    int id;
    char title[100];
    char author[100];
    float price;
    int quantity;
    struct Book* next;
};

// Function to create a new book node
struct Book* createBook(int id, char title[], char author[], float price, int quantity) {
    struct Book* newBook = (struct Book*)malloc(sizeof(struct Book));
    newBook->id = id;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->price = price;
    newBook->quantity = quantity;
    newBook->next = NULL;
    return newBook;
}

// Function to insert a book into the inventory
void insertBook(struct Book** head, struct Book* newBook) {
    newBook->next = *head;
    *head = newBook;
}

// Function to display the inventory
void displayInventory(struct Book* head) {
    struct Book* current = head;
    while (current != NULL) {
        printf("ID: %d\nTitle: %s\nAuthor: %s\nPrice: $%.2f\nQuantity: %d\n\n",
            current->id, current->title, current->author, current->price, current->quantity);
        current = current->next;
    }
}

// Function to search for a book by ID
struct Book* searchBookByID(struct Book* head, int id) {
    struct Book* current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to update the information of a book
void updateBook(struct Book* book, char title[], char author[], float price, int quantity) {
    strcpy(book->title, title);
    strcpy(book->author, author);
    book->price = price;
    book->quantity = quantity;
}

// Function to remove a book from the inventory by ID
void removeBook(struct Book** head, int id) {
    struct Book* current = *head;
    struct Book* prev = NULL;
    if (current != NULL && current->id == id) {
        *head = current->next;
        free(current);
        return;
    }
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Book with ID %d not found.\n", id);
        return;
    }
    prev->next = current->next;
    free(current);
}

// Function to add a new book to the inventory
void addNewBook(struct Book** head) {
    int id;
    char title[100];
    char author[100];
    float price;
    int quantity;

    // Get book details from the user
    printf("Enter the new Book ID: ");
    scanf("%d", &id);
    printf("Enter the title: ");
    scanf("%s", title);
    printf("Enter the author: ");
    scanf("%s", author);
    printf("Enter the price: ");
    scanf("%f", &price);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    // Create a new book and insert it into the inventory
    insertBook(head, createBook(id, title, author, price, quantity));

    printf("New book added to the inventory.\n");
}

// Function to calculate the total value of the inventory
float calculateTotalValue(struct Book* head) {
    float totalValue = 0;
    struct Book* current = head;

    while (current != NULL) {
        totalValue += current->price * current->quantity;
        current = current->next;
    }

    return totalValue;
}

int main() {
    struct Book* inventory = NULL;

    // Adding books to the inventory
    insertBook(&inventory, createBook(1, "C Programming", "Dennis Ritchie", 19.99, 50));
    insertBook(&inventory, createBook(2, "Python", "Guido van Rossum", 14.99, 30));
    insertBook(&inventory, createBook(3, "Design Patterns: Elements of Reusable Object-Oriented Software", "Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides", 29.99, 20));
    insertBook(&inventory, createBook(4, "Code: The Hidden Language of Computer Hardware and Software","Charles Petzold", 49.99, 25));
    insertBook(&inventory, createBook(5, "Programming Pearls", "Jon Bentley", 35.00, 15));

    // Display the inventory
    printf("Initial Inventory:\n");
    displayInventory(inventory);

    int choice;
    do {
        printf("\nAdditional Functions:\n");
        printf("1. Search for a Book by ID\n");
        printf("2. Update Book Information\n");
        printf("3. Remove a Book by ID\n");
        printf("4. Display the Inventory\n");
        printf("5. Add a New Book\n");
        printf("6. Calculate Total Value\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int id;
                printf("Enter the Book ID to search for: ");
                scanf("%d", &id);
                struct Book* foundBook = searchBookByID(inventory, id);
                if (foundBook != NULL) {
                    printf("Book found:\n");
                    printf("ID: %d\nTitle: %s\nAuthor: %s\nPrice: $%.2f\nQuantity: %d\n",
                        foundBook->id, foundBook->title, foundBook->author, foundBook->price,
                        foundBook->quantity);
                } else {
                    printf("Book with ID %d not found.\n", id);
                }
                break;
            }
            case 2: {
                int id;
                printf("Enter the Book ID to update: ");
                scanf("%d", &id);
                struct Book* foundBook = searchBookByID(inventory, id);
                if (foundBook != NULL) {
                    char newTitle[100];
                    char newAuthor[100];
                    float newPrice;
                    int newQuantity;
                    printf("Enter the new title: ");
                    scanf("%s", newTitle);
                    printf("Enter the new author: ");
                    scanf("%s", newAuthor);
                    printf("Enter the new price: ");
                    scanf("%f", &newPrice);
                    printf("Enter the new quantity: ");
                    scanf("%d", &newQuantity);
                    updateBook(foundBook, newTitle, newAuthor, newPrice, newQuantity);
                    printf("Book information updated.\n");
                } else {
                    printf("Book with ID %d not found.\n", id);
                }
                break;
            }
            case 3: {
                int id;
                printf("Enter the Book ID to remove: ");
                scanf("%d", &id);
                removeBook(&inventory, id);
                printf("Book with ID %d removed from the inventory.\n", id);
                break;
            }
            case 4:
                printf("Current Inventory:\n");
                displayInventory(inventory);
                break;
            case 5:
                addNewBook(&inventory);
                break;
            case 6:
                printf("Total value of the inventory: $%.2f\n", calculateTotalValue(inventory));
                break;
            case 7:
                printf("Exiting the program.\n");
                printf("Thank You!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    // Free allocated memory before exiting
    struct Book* current = inventory;
    while (current != NULL) {
        struct Book* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}