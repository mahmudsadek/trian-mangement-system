#include<bits/stdc++.h>
#include<iomanip>

using namespace std;

void menu()
{
    cout << "==========================================================" << endl;
    cout << "           Welcome To Our Mangement System" << endl;
    cout << "----------------------------------------------------------" << endl << endl;;
    cout << "               please select an option" << endl << endl;
    cout << "1-Reserve a ticket.\n\n";
	cout << "2-Cancel the reservation.\n\n";
	cout << "3-Check whether a specific car has available seat or not.\n\n";
	cout << "4-Check whether a specific seat is available or not.\n\n";
	cout << "5-Get the number of the available seats in a specific car.\n\n";
	cout << "6-Show all the seats status of a specific car.\n\n";
	cout << "7-Exit\n\n";
    cout << "\n=========================================================" << endl;
    cout << "\nEnter Your Choice : ";
}


struct Car
{
    int seats[40] = {};
    int carID;
};

void addDataToFile(Car c[])
{
    ofstream data1;
    data1.open("car.txt",ios::app);
    for (int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 40; j++)
        {
            data1 << c[i].seats[j] << " ";
        }
        data1 << endl;
    }
    data1.close();
}

void reserve(Car c[])
{
    cout << "\n\n-----------------------------------------------------------------\n\n";
    cout << "Enter Car Number (1-10) : ";
    int carNumber;      cin >> carNumber;
    cout << "\nEnter Seat Number (1-40) : ";
    int seatNumber;     cin >> seatNumber;
    if(c[carNumber].seats[seatNumber-1] == 1)
    {
        cout << "\n\n\nSorry this seat is not avilable.\n";
    }
    else
    {
        c[carNumber].seats[seatNumber-1] = 1;
        time_t now = time(0);
        char* dt = ctime(&now);
        cout << "\n\n\nThe operation was completed successfully.\n";
        cout << "\n========================= Your Ticket ===================================\n\n";
        cout << "Date : " << dt << endl;
        cout << "Car Number : " << carNumber << "                   " <<"seat Number : " << seatNumber << endl;
        cout << "\n=========================================================================\n\n";
    }
    remove("car.txt");
    addDataToFile(c);
}

void canselResevation(Car c[])
{
    cout << "\n\n-----------------------------------------------------------------\n\n";
    cout << "Enter Car Number (1-10) : ";
    int carNumber;      cin >> carNumber;
    cout << "\nEnter Seat Number (1-40) : ";
    int seatNumber;     cin >> seatNumber;
    if(c[carNumber].seats[seatNumber-1] == 1)
    {
        c[carNumber].seats[seatNumber-1] = 0;
        cout << "\nThe reservation has been successfully cancelled\n\n";
        cout << "\n\n-----------------------------------------------------------------\n\n";
    }
    else
    {
        cout << "\nThis seat is not reserved from the beginning,\npress 1 to reserve it or 0 to return to the main menu : ";
        int ch;  cin >> ch;
        if(ch == 1)
        {
            c[carNumber].seats[seatNumber-1] = 1;
            time_t now = time(0);
            char* dt = ctime(&now);
            cout << "\n\n\nThe operation was completed successfully.\n";
            cout << "\n========================= Your Ticket ===================================\n\n";
            cout << "Date : " << dt << endl;
            cout << "Car Number : " << carNumber << "                   " <<"seat Number : " << seatNumber << endl;
            cout << "\n=========================================================================\n\n";
        }
    }
    remove("car.txt");
    addDataToFile(c);
}

void seatStatus (Car c[])
{
    cout << "\n\n-----------------------------------------------------------------\n\n";
    cout << "Enter the Number of the Car you want to Check (1-10) : ";
    int carNumber;      cin >> carNumber;
    cout << "\n\n-----------------------------------------------------------------\n\n";
    for (int i = 1; i <= 40; i++)
    {
        if(i < 10) { cout << 0;}
        if(c[carNumber-1].seats[i-1] == 1)
            cout << i << " : Not Avilable" << "       ";
        else
            cout << i << " : Avilable    " << "       ";

        if(i % 4 == 0 && i != 0)
            cout << "\n";
    }
    cout << "\n=========================================================================\n\n";
    
}

bool carAvilablety(Car c[])
{
    cout << "\n=========================================================================\n\n";
    cout << "Enter Car Number (1-10) : ";
    int carNumber; cin >> carNumber;
    for (int i = 0; i < 40; i++)
    {
        if(c[carNumber].seats[i] == 0)
            return true;
    }
    return false;
}

bool seatAvilabelety(Car c[])
{
    cout << "\n=========================================================================\n\n";
    cout << "Enter Car Number (1-10) : ";
    int carNumber;      cin >> carNumber;
    cout << "\nEnter Seat Number (1-40) : ";
    int seatNumber;     cin >> seatNumber;

    if(c[carNumber].seats[seatNumber-1] == 0)
        return true;
    return false;
}

int numberOfAvilableSeats(Car c[], int carNumber)
{
    int count = 0;
    for (int i = 0; i < 40 ; i++)
    {
        if(c[carNumber].seats[i] == 0)
            count++;
    }
    return count;
}

int main()
{
    Car car[10];
    for (int i = 0; i < 10; i++)
    {
        car[i].carID = i+1;
    }
    ifstream data1;
    data1.open("car.txt",ios::app);
    for (int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 40; j++)
        {
            data1 >> car[i].seats[j];
        }
    }
    data1.close();
    
    bool exit = false;
    while (1)
    {
        menu();
        int choice;     cin >> choice;
        switch (choice)
        {
        case 1:
            reserve(car);
            break;
        case 2:
            canselResevation(car);
            break;
        case 3:
            if(carAvilablety(car))
                cout << "\n\nThis Car has available seats.\n\n";
            else
                cout << "\n\nSorry, This Car has no available seats.\n\n";
            break;
        case 4:
            if(seatAvilabelety(car))
                cout << "\n\nThis Seat is available.\n\n";
            else
                cout << "\n\nSorry, This Seat is not available.\n\n";
            break;
        case 5:
            cout << "Enter Car Number (1-10) : ";
            int carNumber;      cin >> carNumber;
            numberOfAvilableSeats(car, carNumber);
            cout << "\n\n There is " << numberOfAvilableSeats(car, carNumber) << " avilable Seat in this Car.\n\n";
            break;
        case 6:
            seatStatus(car);
            break;
        case 7:
            exit = true;
            cout << "\nExiting ..\n";
            break;
        default:
            cout << "\nWrong choice, please try againn\n\n";
            break;
        }
        if(exit)
            break;
    }
}