#include <iostream>
#include <iomanip>
#include <cstring>
#include <windows.h>
#include <ctime>	// for use time functions
#include <unistd.h> // for use sleep function

using namespace std;

const int MAX_BOOKS = 100;
const int MAX_COPIES = 100;  // Maximum number of copies per book
const int PENALTY_AMOUNT = 200;

//add student data
struct Student {
    int studentID;
    char studentName[50];
    char studentClass[20];
    int penalty;
};

//add single copy book data
struct IssuedBook {
    int bookID;
    time_t issueDate;
    time_t returnDate;
    Student borrower;
};

//add book data
struct Book {
    int id;
    char bookName[50];
    char authorName[50];
    int quantity;  // Added quantity field
    int issuedCount;  // Number of issued copies
    IssuedBook issuedCopies[MAX_COPIES];  // Store information about each issued copy
};

void maincolor()
{
	HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 3);
}

void welcomescreencolor()
{
	HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 11);
}

void successcolor()
{
	HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 2);
}

void faildcolor()
{
	HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
}


// Function to display the splash screen
void displaySplashScreen() {
    cout << "\n\n\n\n\n";
    welcomescreencolor();
    cout << "\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    cout << "\t\t\t\t\t           WELCOME TO" << endl;
	cout << "\t\t\t\t\t   LIBRARY MANAGNEMNT SYSTEM" << endl;
	cout << "\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	cout << "\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    cout << "\t\t\t   DEVELOPED BY: M HASNAIN MUGHAL|SHEHROZ ALI|KHALIL AREJO\n";
    cout << "\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
    cout << "\t\t\t\t\t          Loading";
}

// Function to loading with a delay
void loading() {
    for(int i = 6;i >= 1;i--)
	{	
		cout << ".";
		cout.flush();
		sleep(1);
	}
	system("CLS");
}

// Function to display the header
void header(){
	maincolor();
	cout << "\t\t\t\t\t*******************************" << endl;
	cout << "\t\t\t\t\t   LIBRARY MANAGNEMNT SYSTEM" << endl;
	cout << "\t\t\t\t\t*******************************" << endl;
	cout << "\t\t\t*************************************************************\n";
    cout << "\t\t\t   DEVELOPED BY: M HASNAIN MUGHAL|SHEHROZ ALI|KHALIL AREJO\n";
    cout << "\t\t\t*************************************************************\n\n";
}


// Function to parse a date string into a tm structure
void parseDate(const string& dateStr, tm& date) {
    if (sscanf(dateStr.c_str(), "%d-%d-%d", &date.tm_year, &date.tm_mon, &date.tm_mday) != 3) {
        cerr << "Error parsing date\n";
    }
    date.tm_year -= 1900;  // Adjust year
    date.tm_mon--;         // Adjust month
}

// Function to addbook
void addBook(Book library[], int& count) {
    if (count >= MAX_BOOKS) {
    	cout << "\n-------------------------------------------\n";
    	faildcolor();
        cout << "  Library is full. Cannot add more books.";
		maincolor();
        cout << "\n-------------------------------------------\n";
        return;
    }

    Book newBook;
    cout << "\n------------------------------\n";
    cout << "  <== Enter Book Details ==>";
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
	successcolor();
    cout << "  Book Added Successfully";
    maincolor();
    cout << "\n---------------------------\n";
}

// Function to print All Books

void printBooks(const Book library[], int count) {
    if (count == 0) {
    	cout << "\n----------------------------\n";
		faildcolor();
        cout << "  No books in the library.";
        maincolor();
        cout << "\n----------------------------\n";
        return;
    }
	cout << "\n---------------------\n";
    cout << "  <== All Books ==>";
    cout << "\n---------------------\n";
    cout << setw(5) << "ID" << setw(20) << "Book Name" << setw(20) << "Author Name" << setw(15) << "Quantity" << endl;

    for (int i = 0; i < count; ++i) {
        cout << setw(5) << library[i].id << setw(20) << library[i].bookName << setw(20) << library[i].authorName << setw(15) << library[i].quantity;
        cout << "\n";
    }
}

// Function to Issue Book

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

                // Automatically set the issue date to the current date
                time_t currentTime = time(0);
                tm* issueDate = localtime(&currentTime);
                issuedCopy.issueDate = mktime(issueDate);

                // Automatically set the return date to 7 days later
                tm* returnDate = localtime(&currentTime);
                returnDate->tm_sec += 7 * 24 * 60 * 60; // 7 days in seconds
                issuedCopy.returnDate = mktime(returnDate);

                cout << "\n--------------------------------------------\n";
				successcolor();
                cout << "  Book Issued Successfully" << endl;
                cout << "  Return Date: " << asctime(returnDate);
                maincolor();
                cout << "----------------------------------------------\n";

            } else if(library[i].quantity == 1) {

                cout << "\n----------------------\n";
				faildcolor();
                cout << "  No Last Copy Issue";
                maincolor();
                cout << "\n----------------------\n";
            }
            else {
                cout << "\n--------------------------------------------\n";
				faildcolor();
                cout << "  No available copies of the book to issue";
                maincolor();
                cout << "\n--------------------------------------------\n";
            }
            return;
        }
    }

    cout << "\n-------------------\n";
    faildcolor();
    cout << "  Book not found.";
    maincolor();
    cout << "\n-------------------\n";
}

// Function to renew the return date for a book
void renewBook(Book library[], int count) {
    int bookID, studentID;

    cout << "Enter the ID of the book to renew: ";
    cin >> bookID;

    cout << "Enter your Student CMS-ID: ";
    cin >> studentID;

    for (int i = 0; i < count; ++i) {
        if (library[i].id == bookID) {
            for (int j = 0; j < library[i].issuedCount; ++j) {
                if (library[i].issuedCopies[j].borrower.studentID == studentID) {
                    IssuedBook& issuedCopy = library[i].issuedCopies[j];

                    // Automatically renew the return date to 7 days later
                    issuedCopy.returnDate += 7 * 24 * 60 * 60; // 7 days in seconds

                    // Format renewed return date
                    tm* localReturnDate = localtime(&issuedCopy.returnDate);
                    char returnDateStr[20];
                    strftime(returnDateStr, sizeof(returnDateStr), "%Y-%m-%d", localReturnDate);

                    cout << "\n-------------------------------------\n";
                    faildcolor();
                    cout << "  Book Renewed Successfully" << endl;
                    cout << "  Renewed Return Date: " << returnDateStr << "\n";
                    maincolor();
                    cout << "---------------------------------------\n";

                    return;
                }
            }
            cout << "\n-----------------------------------------------------\n";
            faildcolor();
            cout << "  No issued copies found for the specified student.";
            maincolor();
            cout << "\n-----------------------------------------------------\n";
            return;
        }
    }
    cout << "\n-------------------\n";
    faildcolor();
    cout << "  Book not found.";
    maincolor();
    cout << "\n-------------------\n";
}

// Function to Return the Book

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

                    // Get old return date as a string in the format "YYYY-MM-DD"
                    char oldReturnDateStr[20];
                    strftime(oldReturnDateStr, sizeof(oldReturnDateStr), "%Y-%m-%d", localtime(&issuedCopy.returnDate));

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
                        cout << "\n----------------------------------------------------------\n";
                        faildcolor();
                        cout << "  Book Returned After Return Date. Penalty Applied: Rs." << PENALTY_AMOUNT;
                        maincolor();
                        cout << "\n----------------------------------------------------------\n";

                        // Assuming there is a balance or penalty field for the student
                        issuedCopy.borrower.penalty += PENALTY_AMOUNT;
                    }
                    else{
                    	cout << "\n-----------------------------------\n";
                    	successcolor();
                        cout << "  Book Returned Before Return Date.";
                        maincolor();
                        cout << "\n-----------------------------------\n";
					}

                    // Check if the book is returned before, on, or after the expected return date
                    if (difftime(issuedCopy.returnDate, issuedCopy.issueDate) <= 0) {
                        cout << "\n-----------------------------------\n";
                        faildcolor();
                        cout << "  Last Return Date: " << oldReturnDateStr;
                        maincolor();
                        cout << "\n-----------------------------------\n";
                    } else {
                        // Book returned after the expected return date
                        cout << "\n-----------------------------------\n";
                        faildcolor();
                        cout << "  Last Return Date: " << oldReturnDateStr;
                        maincolor();
                        cout << "\n-----------------------------------\n";
                    }

                    // Remove the returned copy from the issuedCopies array
                    for (int k = j; k < library[i].issuedCount - 1; ++k) {
                        library[i].issuedCopies[k] = library[i].issuedCopies[k + 1];
                    }

                    library[i].issuedCount--;

                    cout << "\n------------------------------\n";
                    successcolor();
                    cout << "  Book Returned Successfully";
                    maincolor();
                    cout << "\n------------------------------\n";
                    return;
                }
            }
            cout << "\n-----------------------------------------------------\n";
            faildcolor();
            cout << "  No issued copies found for the specified student.";
            maincolor();
            cout << "\n-----------------------------------------------------\n";
            return;
        }
    }
    cout << "\n-------------------\n";
    faildcolor();
    cout << "  Book not found.";
    maincolor();
    cout << "\n-------------------\n";
}

// Function to Remove the Book

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
            successcolor();
            cout << "  Book Removed Successfully";
            maincolor();
            cout << "\n-----------------------------\n";
            return;
        }
    }
	cout << "\n-------------------\n";
	faildcolor();
    cout << "  Book not found.";
    maincolor();
    cout << "\n-------------------\n";
}

// Function to View Issued Books

void viewIssuedBooks(const Book library[], int count) {
    bool issuedBooksExist = false;

    cout << "\n------------------------\n";
    cout << "  <== Issued Books ==>";
    cout << "\n------------------------\n";
    cout << setw(5) << "ID" << setw(20) << "Book Name" << setw(20) << "Book Author" << setw(18) << "Student CMS-ID"
         << setw(20) << "Student Name" << setw(15) << "Student Class" << setw(15) << "Issue Date" << setw(15) << "Return Date" << "\n";

    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < library[i].issuedCount; ++j) {
            issuedBooksExist = true;

            cout << setw(5) << library[i].id << setw(20) << library[i].bookName << setw(20) << library[i].authorName
                 << setw(18) << library[i].issuedCopies[j].borrower.studentID << setw(20) << library[i].issuedCopies[j].borrower.studentName
                 << setw(15) << library[i].issuedCopies[j].borrower.studentClass;

            // Format issue date
            char issueDateStr[20];
            strftime(issueDateStr, sizeof(issueDateStr), "%Y-%m-%d", localtime(&library[i].issuedCopies[j].issueDate));
            cout << setw(15) << issueDateStr;

            // Format return date
            char returnDateStr[20];
            strftime(returnDateStr, sizeof(returnDateStr), "%Y-%m-%d", localtime(&library[i].issuedCopies[j].returnDate));
            cout << setw(15) << returnDateStr << "\n";
        }
    }

    if (!issuedBooksExist) {
        cout << "\n----------------------------------\n";
        faildcolor();
        cout << "  No books are currently issued.";
        maincolor();
        cout << "\n----------------------------------\n";
    }
}

//Main Body

int main()
{
	//splash screen
	displaySplashScreen();
    loading();
    
	
	//header
	header();
	
	cout << "----------" << endl ;
	cout << "  Login!" << endl;
	cout << "----------" << endl;
	
	//login system
	string username,password;
	
	cout << "Enter Username: ";
	cin >> username;
	
	cout << "Enter Password: ";
	cin >> password;

	if(username == "admin" && password == "admin")
	{
		cout << "-----------------------------" << endl;
		successcolor();
		cout << "    Login Successfully..." << endl;
		maincolor();
		cout << "-----------------------------" << endl;
		
		system("PAUSE");
		system("CLS");
		
	//header and choose the option
	header();
	
	Book library[MAX_BOOKS];
    int bookCount = 0;
    int choice;
    while (true) {
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Renew Book\n"; 
        cout << "6. Remove Book\n";
        cout << "7. View Issued Books\n";
        cout << "8. Exit\n\n";
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
                renewBook(library, bookCount);
                break;

            case 6:
                removeBook(library, bookCount);
                break;

            case 7:
                viewIssuedBooks(library, bookCount);
                break;

            case 8:
        		cout << "\n------------------------------------------------------\n";
        		successcolor();
        		cout << "    Thank you for using the Library Management System!\n";
        		maincolor();
        		cout << "------------------------------------------------------\n";
                return 0;

            default:
            	cout << "\n-----------------\n";
            	faildcolor();
                cout << "  Invalid Choice\n";
                maincolor();
                cout << "\n-----------------\n";
        }
		

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        system("CLS"); //clear screen
        
        //after clear screen display the header
    	header();
    }	
	}
	else
	{
		cout << "----------------------------------------------" << endl;
		faildcolor();
		cout << "   Invalid Username or Password Tryagain..." << endl;
		maincolor();
		cout << "----------------------------------------------" << endl;
	}
		
	return 0;
}
