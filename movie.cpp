#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

const int ROWS = 5;
const int COLS = 10;

class Ticket {

    string movieName;
    char row;
    int col;
    double price;

public:

    Ticket(string movie, char r, int c, double p) {
        movieName = movie;
        row = r;
        col = c;
        price = p;
    }

    void saveToFile() {

        ofstream file("ticketbooked.txt");
        if (!file) {
            cout << "Error creating ticket file.\n";
            return;

        }

        time_t now = time(0);
        tm *ltm = localtime(&now);

        file << "----------------------------\n";
        file << "       🎬 PVR CINEMAS 🎬\n";
        file << "       TICKET CONFIRMED\n";
        file << "----------------------------\n";
        file << "Theatre       : PVR Kolhapur\n";
        file << "Movie         : " << movieName << "\n";
        file << "Seat Number   : " << row << col << "\n";
        file << "Booking ID    : " << now % 1000000 << "\n";
        file << "Status        : ✅Confirmed\n";
        file << "Date & Time   : "
             << (1900 + ltm->tm_year) << "-"
             << (1 + ltm->tm_mon) << "-"
             << ltm->tm_mday << " "
             << ltm->tm_hour << ":" << ltm->tm_min << "\n";
        file << "Price         : ₹" << price << "\n";
        file << "----------------------------\n";
        file << "   🍿 Enjoy your movie! 🍿\n";
        file << "----------------------------\n";

        file.close();
        cout << "Ticket saved as 'ticketbooked.txt'" <<  endl;
    }
};

class Movie {
    string name;
    bool seats[ROWS][COLS];

public:
    Movie(string movieName) {
        name = movieName;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                seats[i][j] = false;
            }
        }
    }

    string getName() {
        return name;
    }

    void displaySeats() {
        cout << "\nMovie: " << name << " (PVR Kolhapur)\n";
        cout << "Seats:\n   ";
        for (int i = 1; i <= COLS; i++) {
            cout << i << " ";
        }
        cout << "\n";

        for (int i = 0; i < ROWS; i++) {
            cout << (char)('A' + i) << ": ";
            for (int j = 0; j < COLS; j++) {
                if (seats[i][j]) {
                    cout << "X ";
                } else {
                    cout << "-";
                }
            }
            cout << "\n";
        }
    }

    void showSummary() {
        int reserved = 0, available = 0;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (seats[i][j]) {
                    reserved++;
                } else {
                    available++;
                }
            }
        }
        cout << "Reserved Seats: " << reserved << ", Available Seats: " << available << "\n";
    }

    void reserveSeat(char rowLetter, int col) {
        int rowIndex = toupper(rowLetter) - 'A';
        int colIndex = col - 1;

        if (seats[rowIndex][colIndex]) {
            cout << "Seat is already reserved.\n";
        } else {
            seats[rowIndex][colIndex] = true;
            double price = 250.0;
            cout << "Seat reserved successfully.\n";
            Ticket ticket(name, toupper(rowLetter), col, price);
            ticket.saveToFile();
        }
    }

    void cancelSeat(char rowLetter, int col) {
        int rowIndex = toupper(rowLetter) - 'A';
        int colIndex = col - 1;

        if (!seats[rowIndex][colIndex]) {
            cout << "Seat is not reserved.\n";
        } else {
            seats[rowIndex][colIndex] = false;
            cout << "Reservation cancelled.\n";
        }
    }
};

int main() {
    Movie movie1("Avengers");
    Movie movie2("Interstellar");
    Movie movie3("KGF 2");

    Movie* selectedMovie;
    int choice;

    cout << "Welcome to PVR Kolhapur Seat Booking System\n\n";
    cout << "Available Movies:\n";
    cout << "1. Avengers\n";
    cout << "2. Interstellar\n";
    cout << "3. KGF 2\n";
    cout << "Enter your choice (1-3): ";
    cin >> choice;

    if (choice == 1) {
        selectedMovie = &movie1;
    } else if (choice == 2) {
        selectedMovie = &movie2;
    } else if (choice == 3) {
        selectedMovie = &movie3;
    } else {
        cout << "Invalid choice.\n";
        return 0;
    }

    char row;
    int col, action;
    char again;

    do {
        selectedMovie->displaySeats();
        selectedMovie->showSummary();

        cout << "\nChoose Action:\n";
        cout << "1. Reserve Seat\n";
        cout << "2. Cancel Reservation\n";
        cout << "3. Exit\n";
        cout << "Enter action: ";
        cin >> action;

        if (action == 3) {
            break;
        }

        cout << "Enter Row (A-E): ";
        cin >> row;

        cout << "Enter Column (1-10): ";
        cin >> col;

        if (action == 1) {

            selectedMovie->reserveSeat(row, col);

        } else if (action == 2) {

            selectedMovie->cancelSeat(row, col);

        } else {

            cout << "Invalid action.\n";

        }

        cout << "\nDo you want to continue? (Y/N): ";
        cin >> again;

    } while (again == 'Y' || again == 'y');

    cout << "Thank you for using the system.\n";

    return 0;

}
