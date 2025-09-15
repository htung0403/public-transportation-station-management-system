#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Schedule class
class Schedule {
private:
    string time;      
    string action; // "departure" or "arrival"
    string route; 
public:
    Schedule(string t, string a, string r) : time(t), action(a), route(r) {}

    string getTime() const { return time; }
    string getAction() const { return action; }
    string getRoute() const { return route; }

    void displayInfo() const {
        cout << time << " - " << route << " " << action << endl;
    }
};

// Vehicle class
class Vehicle
{
protected:
    string route;                    // Route name
    int capacity;                    // Maximum passengers
    int passengers;                  // Current passengers
    vector<string> assignedStations; // List of assigned stations
    vector<Schedule> vehicleSchedules; // Vehicle's schedule

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

    // Assign vehicle to a station
    void assignToStation(const string &stationName)
    {
        assignedStations.push_back(stationName);
        cout << "Vehicle " << route << " assigned to station: " << stationName << endl;
    }

    // Add schedule to vehicle
    void addSchedule(Schedule schedule)
    {
        vehicleSchedules.push_back(schedule);
        cout << "Added schedule to vehicle " << route << ": ";
        schedule.displayInfo();
    }

    // Book a seat
    bool bookSeat()
    {
        if (passengers < capacity)
        {
            passengers++;
            return true;
        }
        return false;
    }

    // Cancel a seat
    bool cancelSeat()
    {
        if (passengers > 0)
        {
            passengers--;
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
        cout << "Stations assigned: ";
        if (assignedStations.empty())
            cout << "None";
        else
        {
            for (size_t i = 0; i < assignedStations.size(); i++)
            {
                cout << assignedStations[i];
                if (i < assignedStations.size() - 1)
                    cout << ", ";
            }
        }
        cout << endl;
        cout << "Vehicle schedules: " << vehicleSchedules.size() << endl;
        for (size_t i = 0; i < vehicleSchedules.size(); i++)
        {
            cout << "  ";
            vehicleSchedules[i].displayInfo();
        }
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
        cout << "Capacity: " << capacity << endl;
        cout << "Passengers: " << passengers << endl;
        cout << "Express speed: " << expressSpeed << " km/h" << endl;
        cout << "Stations assigned: ";
        if (assignedStations.empty())
            cout << "None";
        else
        {
            for (size_t i = 0; i < assignedStations.size(); i++)
            {
                cout << assignedStations[i];
                if (i < assignedStations.size() - 1)
                    cout << ", ";
            }
        }
        cout << endl;
        cout << "Vehicle schedules: " << vehicleSchedules.size() << endl;
        for (size_t i = 0; i < vehicleSchedules.size(); i++)
        {
            cout << "  ";
            vehicleSchedules[i].displayInfo();
        }
    }
};

// Station class
class Station
{
private:
    string name;
    string location;
    vector<Schedule> schedules; // Maximum 10 schedules

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
    void addSchedule(Schedule schedule)
    {
        if (schedules.size() < 10)
        { // Maximum 10 schedules
            schedules.push_back(schedule);
            cout << "Added schedule: ";
            schedule.displayInfo();
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
            cout << "  " << (i + 1) << ". ";
            schedules[i].displayInfo();
        }
    }

    // Getters
    string getName() { return name; }
    string getLocation() { return location; }
    vector<Schedule> getSchedules() { return schedules; }
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
    }

    // Destructor
    ~Passenger() {}

    // Book a ticket
    bool bookTicket(Vehicle *vehicle, const string &ticketInfo)
    {
        if (vehicle->bookSeat())
        {
            bookedTickets.push_back(ticketInfo);
            cout << name << " booked: " << ticketInfo << endl;
            return true;
        }
        cout << name << " failed to book: vehicle full!" << endl;
        return false;
    }

    // Cancel a ticket
    bool cancelTicket(Vehicle *vehicle, const string &ticketInfo)
    {
        for (size_t i = 0; i < bookedTickets.size(); i++)
        {
            if (bookedTickets[i] == ticketInfo)
            {
                if (vehicle->cancelSeat())
                {
                    bookedTickets.erase(bookedTickets.begin() + i);
                    cout << name << " cancelled: " << ticketInfo << endl;
                    return true;
                }
            }
        }
        cout << name << " does not have ticket: " << ticketInfo << endl;
        return false;
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
    Station benThanhStation("Ben Thanh Station", "Ben Thanh");
    Station thuDucStation("Thu Duc Station", "Thu Duc");

    // Create vehicles
    Vehicle *bus = new Vehicle("Route 01", 40);
    ExpressBus *expressBus = new ExpressBus("Express Route 02", 50, 60);

    cout << endl;

    // Assign vehicles to stations
    bus->assignToStation(benThanhStation.getName());
    expressBus->assignToStation(thuDucStation.getName());

    // Add schedules to vehicles
    bus->addSchedule(Schedule("08:00", "departure", "Route 01"));
    bus->addSchedule(Schedule("09:30", "arrival", "Route 01"));
    expressBus->addSchedule(Schedule("08:15", "departure", "Express Route 02"));

    // Travel times
    cout << "=== TRAVEL TIME COMPARISON ===" << endl;
    double distance = 100; // 100km
    cout << "Distance: " << distance << " km" << endl;
    cout << "Bus travel time: " << bus->calculateTravelTime(distance) << " hours" << endl;
    cout << "Express bus travel time: " << expressBus->calculateTravelTime(distance) << " hours" << endl;
    cout << endl;

    // Display vehicle & station information
    bus->displayInfo();
    cout << endl;
    expressBus->displayInfo();
    cout << endl;

    // Add schedules to station
    benThanhStation.addSchedule(Schedule("08:00", "departure", "Route 01"));
    benThanhStation.addSchedule(Schedule("08:15", "departure", "Express Route 02"));
    benThanhStation.addSchedule(Schedule("09:30", "arrival", "Route 01"));

    benThanhStation.displayInfo();
    thuDucStation.displayInfo();

    // Create passengers
    Passenger passenger1("Vo Hoang Tung", "P001");
    Passenger passenger2("Nguyen Van A", "P002");
    cout << endl;

    // Booking system
    cout << "=== BOOKING SYSTEM ===" << endl;
    passenger1.bookTicket(bus, "Route 01 - 08:00");
    passenger2.bookTicket(expressBus, "Express Route 02 - 08:15");
    cout << endl;

    // Test capacity limit
    cout << "=== CAPACITY LIMIT TEST ===" << endl;
    cout << "Trying to book many tickets for bus (capacity 40)..." << endl;
    for (int i = 0; i < 42; i++)
    { // Try to book 42 tickets for bus with capacity 40
        if (!passenger2.bookTicket(bus, "Route 01 - 08:00"))
        {
            cout << "Bus is full after " << bus->getPassengers() << " tickets!" << endl;
            break;
        }
    }
    cout << endl;

    // Cancel a ticket
    cout << "=== CANCEL TICKET TEST ===" << endl;
    passenger2.cancelTicket(bus, "Route 01 - 08:00");
    passenger1.cancelTicket(expressBus, "Express Route 02 - 08:15");

    // Display passenger information
    passenger1.displayInfo();
    passenger2.displayInfo();

    // Test schedule limit
    cout << "\n=== SCHEDULE LIMIT TEST ===" << endl;
    for (int i = 4; i <= 12; i++)
    {
        string scheduleTime = "10:" + (i < 10 ? string("0") : string("")) + to_string(i);
        Schedule newSchedule(scheduleTime, "departure", "Route " + to_string(i));
        benThanhStation.addSchedule(newSchedule);
    }

    benThanhStation.displayInfo();
    
    // Final status
    cout << "\n=== FINAL SYSTEM STATUS ===" << endl;
    cout << "Bus: " << bus->getPassengers() << "/" << bus->getCapacity() << " passengers" << endl;
    cout << "Express bus: " << expressBus->getPassengers() << "/" << expressBus->getCapacity() << " passengers" << endl;

    // Cleanup
    delete bus;
    delete expressBus;

    return 0;
}