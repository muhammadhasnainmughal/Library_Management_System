#include<iostream>
#include <iomanip>
#include <cstring>
#include <ctime>

using namespace std;

const int MAX_BOOKS = 100;
const int MAX_COPIES = 15;  // Maximum number of copies per book
const int PENALTY_AMOUNT = 200;

struct Student {
    int studentID;
    char studentName[50];
    char studentClass[20];
    int penalty;
};

struct IssuedBook {
    int bookID;
    time_t issueDate;
    time_t returnDate;
    Student borrower;
};

struct Book {
    int id;
    char bookName[50];
    char authorName[50];
    int quantity;  // Added quantity field
    int issuedCount;  // Number of issued copies
    IssuedBook issuedCopies[MAX_COPIES];  // Store information about each issued copy
};

// Function to parse a date string into a tm structure
void parseDate(const string& dateStr, tm& date) {
    if (sscanf(dateStr.c_str(), "%d-%d-%d", &date.tm_year, &date.tm_mon, &date.tm_mday) != 3) {
        cerr << "Error parsing date\n";
    }
    date.tm_year -= 1900;  // Adjust year
    date.tm_mon--;         // Adjust month
}

void addBook(Book library[], int& count) {
    if (count >= MAX_BOOKS) {
    	cout << "\n-------------------------------------------\n";
        cout << "    Library is full. Cannot add more books.";
        cout << "\n-------------------------------------------\n";
        return;
    }

    Book newBook;
    cout << "\n------------------------------\n";
    cout << "    <== Enter Book Details ==>";
    cout << "\n------------------------------\n";
    cout << "ID: ";
    cin >> newBook.id;
    cin.ignore();

    cout << "Book Name: ";
    cin.getline(newBook.bookName, 50);

    cout << "Author Name: ";
    cin.getline(newBook.authorName, 50);

    cout << "Quantity: ";
    cin >> newBook.quantity;

    newBook.issuedCount = 0;

    library[count++] = newBook;
    
    cout << "\n---------------------------\n";
    cout << "    Book Added Successfully";
    cout << "\n---------------------------\n";
}

void printBooks(const Book library[], int count) {
    if (count == 0) {
    	cout << "\n----------------------------\n";
        cout << "    No books in the library.";
        cout << "\n----------------------------\n";
        return;
    }
	cout << "\n---------------------\n";
    cout << "    <== All Books ==>";
    cout << "\n---------------------\n";
    cout << setw(5) << "ID" << setw(20) << "Book Name" << setw(20) << "Author Name" << setw(15) << "Quantity" << endl;

    for (int i = 0; i < count; ++i) {
        cout << setw(5) << library[i].id << setw(20) << library[i].bookName << setw(20) << library[i].authorName << setw(15) << library[i].quantity;
        cout << "\n";
    }
}

void issueBook(Book library[], int count) {
    int bookID;
    cout << "Enter the ID of the book to issue: ";
    cin >> bookID;

    for (int i = 0; i < count; ++i) {
        if (library[i].id == bookID) {
            if (library[i].quantity > 1 && library[i].issuedCount < MAX_COPIES) {
                IssuedBook& issuedCopy = library[i].issuedCopies[library[i].issuedCount];
                issuedCopy.bookID = bookID;

                // ... (populate issuedCopy with relevant information)

                library[i].quantity--;
                library[i].issuedCount++;

                cout << "Enter Student CMS-ID: ";
                cin >> issuedCopy.borrower.studentID;
                cin.ignore();

                cout << "Enter Student Name: ";
                cin.getline(issuedCopy.borrower.studentName, 50);

                cout << "Enter Student Section: ";
                cin.getline(issuedCopy.borrower.studentClass, 20);

                // Manually enter the issue date
                string issueDateStr;
                cout << "Enter Issue Date (YYYY-MM-DD): ";
                cin >> issueDateStr;

                tm issueDate = {};
                parseDate(issueDateStr, issueDate);
                issuedCopy.issueDate = mktime(&issueDate);

				cout << "\n----------------------------\n";
                cout << "    Book Issued Successfully";
                cout << "\n----------------------------\n";
                
            } else if(library[i].quantity == 1) {
            	
            	cout << "\n----------------------\n";
                cout << "    No Last Copy Issue";
                cout << "\n----------------------\n";
            }
			else {
				cout << "\n--------------------------------------------\n";
                cout << "    No available copies of the book to issue";
                cout << "\n--------------------------------------------\n";
            }
            return;
        }
    }
	
	cout << "\n-------------------\n";
    cout << "    Book not found.";
    cout << "\n-------------------\n";
}

void returnBook(Book library[], int count) {
    int bookID, studentID;

    cout << "Enter the ID of the book to return: ";
    cin >> bookID;

    cout << "Enter your Student CMS-ID: ";
    cin >> studentID;

    for (int i = 0; i < count; ++i) {
        if (library[i].id == bookID) {
            for (int j = 0; j < library[i].issuedCount; ++j) {
                if (library[i].issuedCopies[j].borrower.studentID == studentID) {
                    library[i].quantity++;
                    IssuedBook& issuedCopy = library[i].issuedCopies[j];

                    // Manually enter the return date
                    string returnDateStr;
                    cout << "Enter Return Date (YYYY-MM-DD): ";
                    cin >> returnDateStr;

                    tm returnDate = {};
                    parseDate(returnDateStr, returnDate);
                    issuedCopy.returnDate = mktime(&returnDate);

                    // Check if the book is returned after 7 days (604800 seconds)
                    if (difftime(issuedCopy.returnDate, issuedCopy.issueDate) > 604800) {
                        // Apply penalty
                        cout << "\n-------------------------------------------------------\n";
                        cout << "    Book Returned After 7 Days. Penalty Applied: Rs." << PENALTY_AMOUNT;
                        cout << "\n-------------------------------------------------------\n";

                        // Assuming there is a balance or penalty field for the student
                        issuedCopy.borrower.penalty += PENALTY_AMOUNT;
                    }

                    // Remove the returned copy from the issuedCopies array
                    for (int k = j; k < library[i].issuedCount - 1; ++k) {
                        library[i].issuedCopies[k] = library[i].issuedCopies[k + 1];
                    }

                    library[i].issuedCount--;
					
					cout << "\n------------------------------\n";
                    cout << "    Book Returned Successfully";
                    cout << "\n------------------------------\n";
                    return;
                }
            }
			cout << "\n-----------------------------------------------------\n";
            cout << "    No issued copies found for the specified student.";
            cout << "\n-----------------------------------------------------\n";
            return;
        }
    }
	cout << "\n-------------------\n";
    cout << "    Book not found.";
    cout << "\n-------------------\n";
}



void removeBook(Book library[], int& count) {
    int bookID;
    cout << "Enter the ID of the book to remove: ";
    cin >> bookID;

    for (int i = 0; i < count; ++i) {
        if (library[i].id == bookID) {
            for (int j = i; j < count - 1; ++j) {
                library[j] = library[j + 1];
            }

            --count;
            cout << "\n-----------------------------\n";
            cout << "    Book Removed Successfully";
            cout << "\n-----------------------------\n";
            return;
        }
    }
	cout << "\n-------------------\n";
    cout << "    Book not found.";
    cout << "\n-------------------\n";
}

void viewIssuedBooks(const Book library[], int count) {
    bool issuedBooksExist = false;
	
	cout << "\n------------------------\n";
    cout << "    <== Issued Books ==>";
    cout << "\n------------------------\n";
    cout << setw(5) << "ID" << setw(10) << "Book Name" << setw(15) << "Book Author" << setw(20) << "Student CMS-ID" << setw(15) << "Student Name" << setw(20) << "Student Class" << endl;

    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < library[i].issuedCount; ++j) {
            issuedBooksExist = true;

            cout << setw(5) << library[i].id << setw(10) << library[i].bookName << setw(15) << library[i].authorName
                 << setw(15) << library[i].issuedCopies[j].borrower.studentID << setw(15) << library[i].issuedCopies[j].borrower.studentName
                 << setw(20) << library[i].issuedCopies[j].borrower.studentClass << endl;
        }
    }

    if (!issuedBooksExist) {
    	cout << "\n----------------------------------\n";
        cout << "    No books are currently issued.";
        cout << "\n----------------------------------\n";
    }
}

int main()
{
	//interface
	cout << "\t\t\t\t\t*******************************" << endl;
	cout << "\t\t\t\t\t   LIBRARY MANAGNEMNT SYSTEM" << endl;
	cout << "\t\t\t\t\t*******************************" << endl;
	cout << "\t\t\t*****************************************************************\n";
    cout << "\t\t\t   DEVELOPED BY: M HASNAIN MUGHAL / SHEHROZ ALI / KHALIL AREJO\n";
    cout << "\t\t\t*****************************************************************\n\n";
	
	cout << "----------" << endl ;
	cout << "  Login!" << endl;
	cout << "----------" << endl;
	
	//make login system
	string username,password;
	
	cout << "Enter Username: ";
	cin >> username;
	
	cout << "Enter Password: ";
	cin >> password;

	if(username == "admin" && password == "admin")
	{
		cout << "-----------------------------" << endl;
		cout << "    Login Successfully..." << endl;
		cout << "-----------------------------" << endl;
		
		system("PAUSE");
		system("CLS");
		
	//chosse the option
	cout << "\t\t\t\t\t*******************************" << endl;
	cout << "\t\t\t\t\t   LIBRARY MANAGNEMNT SYSTEM" << endl;
	cout << "\t\t\t\t\t*******************************" << endl;
	cout << "\t\t\t*****************************************************************\n";
    cout << "\t\t\t   DEVELOPED BY: M HASNAIN MUGHAL / SHEHROZ ALI / KHALIL AREJO\n";
    cout << "\t\t\t*****************************************************************\n\n";
	
	Book library[MAX_BOOKS];
    int bookCount = 0;
    int choice;

    while (true) {
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Remove Book\n";
        cout << "6. View Issued Books\n";
        cout << "7. Exit\n\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library, bookCount);
                break;

            case 2:
                printBooks(library, bookCount);
                break;

            case 3:
                issueBook(library, bookCount);
                break;

            case 4:
                returnBook(library, bookCount);
                break;

            case 5:
                removeBook(library, bookCount);
                break;

            case 6:
                viewIssuedBooks(library, bookCount);
                break;

            case 7:
        		cout << "\n------------------------------------------------------\n";
        		cout << "    Thank you for using the Library Management System!\n";
        		cout << "------------------------------------------------------\n";
                return 0;

            default:
            	cout << "\n-----------------\n";
                cout << "   Invalid Choice\n";
                cout << "\n-----------------\n";
        }
		

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        system("CLS");
        
    	cout << "\t\t\t\t\t*******************************" << endl;
		cout << "\t\t\t\t\t   LIBRARY MANAGNEMNT SYSTEM" << endl;
		cout << "\t\t\t\t\t*******************************" << endl;
		cout << "\t\t\t*****************************************************************\n";
    	cout << "\t\t\t   DEVELOPED BY: M HASNAIN MUGHAL / SHEHROZ ALI / KHALIL AREJO\n";
    	cout << "\t\t\t*****************************************************************\n\n";
        
    }	
	}
	else
	{
		cout << "----------------------------------------------" << endl;
		cout << "   Invalid Username or Password Tryagain..." << endl;
		cout << "----------------------------------------------" << endl;
	}
		
	return 0;
}

