#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Vehicle class
class Vehicle
{
protected:
    string route;   // Route name
    int capacity;   // Maximum passengers
    int passengers; // Current passengers

public:
    // Constructor
    Vehicle(string r, int cap)
    {
        route = r;
        capacity = cap;
        passengers = 0;
        cout << "Created vehicle for route " << route << endl;
    }

    virtual ~Vehicle() {}

    // Calculate travel time
    virtual double calculateTravelTime(double distance)
    {
        return distance / 50.0; // 50 km/h
    }

    // Book a ticket
    bool bookTicket()
    {
        if (passengers < capacity)
        {
            passengers++;
            cout << "Booking successful! Current: " << passengers << "/" << capacity << " passengers" << endl;
            return true;
        }
        cout << "Cannot book - vehicle is full!" << endl;
        return false;
    }

    // Cancel a ticket
    bool cancelTicket()
    {
        if (passengers > 0)
        {
            passengers--;
            cout << "Cancellation successful! Current: " << passengers << "/" << capacity << " passengers" << endl;
            return true;
        }
        return false;
    }

    // Display vehicle information
    virtual void displayInfo()
    {
        cout << "=== VEHICLE INFO ===" << endl;
        cout << "Route: " << route << endl;
        cout << "Capacity: " << capacity << " people" << endl;
        cout << "Current passengers: " << passengers << " people" << endl;
    }

    // Getters
    string getRoute() { return route; }
    int getCapacity() { return capacity; }
    int getPassengers() { return passengers; }
};

// ExpressBus class inheriting from Vehicle
class ExpressBus : public Vehicle
{
private:
    double expressSpeed;

public:
    // Constructor
    ExpressBus(string r, int cap, double speed = 80.0) : Vehicle(r, cap)
    {
        expressSpeed = speed;
        cout << "This is an express bus!" << endl;
    }

    // Destructor
    ~ExpressBus() {}

    double calculateTravelTime(double distance) override
    {
        return distance / expressSpeed;
    }
    
    void displayInfo() override
    {
        cout << "=== EXPRESS BUS ===" << endl;
        cout << "Route: " << route << endl;
        cout << "Capacity: " << capacity << " people" << endl;
        cout << "Current passengers: " << passengers << " people" << endl;
        cout << "Express speed: " << expressSpeed << " km/h" << endl;
    }
};

// Station class
class Station
{
private:
    string name;
    string location;
    vector<string> schedules; // Maximum 10 schedules

public:
    // Constructor
    Station(string stationName, string stationLocation)
    {
        name = stationName;
        location = stationLocation;
        cout << "Created station " << name << endl;
    }

    // Destructor
    ~Station() {}

    // Add schedule
    void addSchedule(string schedule)
    {
        if (schedules.size() < 10)
        { // Maximum 10 schedules
            schedules.push_back(schedule);
            cout << "Added schedule: " << schedule << endl;
        }
        else
        {
            cout << "Cannot add - already have 10 schedules!" << endl;
        }
    }

    // Display station information
    void displayInfo()
    {
        cout << "\n=== STATION INFO ===" << endl;
        cout << "Station name: " << name << endl;
        cout << "Location: " << location << endl;
        cout << "Number of schedules: " << schedules.size() << "/10" << endl;
        cout << "Schedules:" << endl;
        for (int i = 0; i < schedules.size(); i++)
        {
            cout << "  " << (i + 1) << ". " << schedules[i] << endl;
        }
    }
};

// Passenger class
class Passenger
{
private:
    string name;
    string id;
    vector<string> bookedTickets;

public:
    // Constructor
    Passenger(string passengerName, string passId)
    {
        name = passengerName;
        id = passId;
        cout << "Passenger " << name << " joined the system" << endl;
    }

    // Destructor
    ~Passenger() {}

    // Book a ticket
    bool bookTicket(Vehicle *vehicle, string ticketInfo)
    {
        if (vehicle->bookTicket())
        {
            bookedTickets.push_back(ticketInfo);
            cout << name << " booked ticket: " << ticketInfo << endl;
            return true;
        }
        else
        {
            cout << name << " cannot book ticket for: " << ticketInfo << endl;
            return false;
        }
    }

    // Display passenger information
    void displayInfo()
    {
        cout << "\n=== PASSENGER INFO ===" << endl;
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Number of tickets booked: " << bookedTickets.size() << endl;
        for (int i = 0; i < bookedTickets.size(); i++)
        {
            cout << "  Ticket " << (i + 1) << ": " << bookedTickets[i] << endl;
        }
    }
};

// Main
int main()
{
    cout << "=== PUBLIC TRANSPORTATION MANAGEMENT SYSTEM ===" << endl;
    cout << endl;

    // Create stations
    Station centralStation("Ben Thanh Station", "Ben Thanh");
    Station busTerminal("Thu Duc Station", "Thu Duc");

    // Create vehicles
    Vehicle *regularBus = new Vehicle("Route 01", 40);
    ExpressBus *expressBus = new ExpressBus("Express Route 02", 50, 80);

    cout << endl;

    // Travel times
    cout << "=== TRAVEL TIME COMPARISON ===" << endl;
    double distance = 100; // 100km
    cout << "Distance: " << distance << " km" << endl;
    cout << "Regular bus travel time: " << regularBus->calculateTravelTime(distance) << " hours" << endl;
    cout << "Express bus travel time: " << expressBus->calculateTravelTime(distance) << " hours" << endl;
    cout << endl;

    // Display vehicle information
    regularBus->displayInfo();
    cout << endl;
    expressBus->displayInfo();
    cout << endl;

    // Add schedules to station
    centralStation.addSchedule("08:00 - Route 01 departure");
    centralStation.addSchedule("08:15 - Express Route 02 departure");
    centralStation.addSchedule("09:30 - Route 01 arrival");

    // Display station information
    centralStation.displayInfo();

    // Create passengers
    Passenger passenger1("Vo Hoang Tung", "P001");
    Passenger passenger2("Nguyen Van A", "P002");
    cout << endl;

    // Booking system
    cout << "=== BOOKING SYSTEM ===" << endl;
    passenger1.bookTicket(regularBus, "Route 01 - 08:00");
    passenger2.bookTicket(expressBus, "Express Route 02 - 08:15");
    cout << endl;

    // Test capacity limits
    cout << "=== CAPACITY LIMIT TEST ===" << endl;
    cout << "Trying to book many tickets for regular bus (capacity 40)..." << endl;
    for (int i = 0; i < 42; i++)
    { // Try to book 42 tickets for bus with capacity 40
        if (!regularBus->bookTicket())
        {
            cout << "Bus is full after " << regularBus->getPassengers() << " tickets!" << endl;
            break;
        }
    }
    cout << endl;

    // Display passenger information
    passenger1.displayInfo();
    passenger2.displayInfo();

    // Test schedule limit
    cout << "\n=== SCHEDULE LIMIT TEST ===" << endl;
    for (int i = 4; i <= 12; i++)
    {
        string schedule = "Schedule number " + to_string(i);
        centralStation.addSchedule(schedule);
    }

    // Display final status
    cout << "\n=== FINAL SYSTEM STATUS ===" << endl;
    cout << "Regular bus: " << regularBus->getPassengers()
         << "/" << regularBus->getCapacity() << " passengers" << endl;
    cout << "Express bus: " << expressBus->getPassengers()
         << "/" << expressBus->getCapacity() << " passengers" << endl;

    return 0;  
}