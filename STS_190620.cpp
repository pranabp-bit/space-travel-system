// Below is the Command line app implementation of the Space Travel System
// Check the readme file of this repo for detailed explanation- 
// https://github.com/pranabp-bit/space-travel-system
// Code is commented for better understanding

#include <iostream>
#include <bits/stdc++.h>
#include <cmath>
#include <ctime>

#define clrscr system("clear");
using namespace std;

//Declarations
class Planet;
class Traveller;
class Ticket;
class SpaceTravel;

// Planet class
class Planet {
public:
    string name;
    double x, y, z; // Coordinates
    // Optional attributes:
    double radius;
    double mass;
    Planet(string n, double xx, double yy, double zz, double r = 0, double m = 0) {
        name = n;
        x = xx;
        y = yy;
        z = zz;
        // Default value of r, m is 0
        radius = r;
        mass = m;
        cout << "New Planet Created\n";
        printInfo();
    }
    void setRadius(double r) {
        radius = r;
    }
    void setMass(double m) {
        mass = m;
    }
    string getName() {
        return name;
    }
    vector<double> getCoordinates() {
        vector<double> coords = {x, y, z};
        return coords;
    }
    double getX(){
        return x;
    }
    double getY(){
        return y;
    }
    double getZ(){
        return z;
    }
    void printInfo() {
        cout << "Planet: " << name << endl;
        cout << "Coordinates: (" << x << ", " << y << ", " << z << ")" << endl;
        cout << "Radius: " << radius << endl;
        cout << "Mass: " << mass << endl;
    }
};

// Traveller class (abstract class)
class Traveller {
protected:
    string name;
    int id;

    // static variable to keep track of the last Id assigned
    static int last_id;
public:
    Traveller(string n) {
        name = n;

        // generate a unique Id for the traveller
        id = last_id++;
    }
    ~Traveller() {}
    virtual string getType() = 0; // Pure virtual function
    void setName(string n) {
        name = n;
    }
    void setId(int i) {
        id = i;
    }
    string getName() {
        return name;
    }
    int getId() {
        return id;
    }
};

// initialize the static variable to 1
int Traveller::last_id = 1;

// Astronaut class
class Astronaut : public Traveller {
private:
    int experience;
    string licenseId;
    vector<SpaceTravel*> listOfTravels;
public:
    Astronaut(string n, int exp, string licId) : Traveller(n) {
        experience = exp;
        licenseId = licId;
        cout << "New Astronaut added\n";
        printInfo();
    }
    string getType() {
        return "Astronaut";
    }
    int getExperience() {
        return experience;
    }
    string getLicenseId() {
        return licenseId;
    }
    void setExperience(int exp) {
        experience = exp;
    }
    void setLicenseId(string licId) {
        licenseId = licId;
    }
    void printInfo() {
        cout << getType() << " - Name: " << name << ", Id: " << id << ", Experience: " << experience << ", License Id: " << licenseId << endl;
    }
    void addTravel(SpaceTravel* travel){
        listOfTravels.push_back(travel);
    }
    vector<SpaceTravel*> getAlltravels(){
        return listOfTravels;
    }
};

// Commander class
class Commander : public Traveller {
private:
    vector<SpaceTravel*> listOfTravels;
    string authority;
public:
    Commander(string n, string auth = "CommanderInCharge") : Traveller(n) {
        authority = auth;
        cout << "New Commander added\n";
        printInfo();
    }
    string getType() {
        return "Commander";
    }
    string getAuthority() {
        return authority;
    }
    void setAuthority(string auth) {
        authority = auth;
    }
    void printInfo() {
        cout << getType() << " - Name: " << name << ", Id: " << id << ", Authority: " << authority << endl;
    }
    void addTravel(SpaceTravel* travel){
        listOfTravels.push_back(travel);
    }
    vector<SpaceTravel*> getAlltravels(){
        return listOfTravels;
    }
};

// Passenger class
class Passenger : public Traveller {
public:
    Passenger(string n) : Traveller(n) {
        cout << "New Passenger added\n";
        printInfo();
    }
    string getType() {
        return "Passenger";
    }
    void printInfo() {
        cout << getType() << " - Name: " << name << ", Id: " << id << endl;
    }
};


//Function which returns today's date in DDMMYYYY format using system date
string getTodaysDate(){
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string year = to_string(1900 + ltm->tm_year);
    string month = to_string(1 + ltm->tm_mon);
    string day = to_string(ltm->tm_mday);

    if(month.size()==1)month="0"+month;
    if(day.size()==1)day="0"+day;

    return day+month+year;
}

// Make a tm structure representing a date
// Useful in the next getTimeDiff function
tm make_tm(int year, int month, int day)
{
    std::tm tm = {0};
    tm.tm_year = year - 1900; // years count from 1900
    tm.tm_mon = month - 1;    // months count from January=0
    tm.tm_mday = day;         // days count from 1
    return tm;
}

// Function returning difference in "number of days" between two dates
double getTimeDiff(string dateOfBooking, string dateOfTravel){

    int year1 = stoi(dateOfBooking.substr(4));
    int year2 = stoi(dateOfTravel.substr(4));

    int month1 = stoi(dateOfBooking.substr(2,2));
    int month2 = stoi(dateOfTravel.substr(2,2));

    int day1 = stoi(dateOfBooking.substr(0,2));
    int day2 = stoi(dateOfTravel.substr(0,2));

    // Structures representing the two dates
    tm tm1 = make_tm(year1, month1, day1); //date of booking
    tm tm2 = make_tm(year2,month2,day2); //date of travel

    // Arithmetic time values.
    // On a posix system, these are seconds since 1970-01-01 00:00:00 UTC
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);

    // Divide by the number of seconds in a day
    const int seconds_per_day = 60*60*24;
    double difference = std::difftime(time2, time1) / seconds_per_day;
    return difference;
}

class Ticket {
private:
    int passengerId;
    Planet* sourcePlanet;
    Planet* destinationPlanet;

    // All dates in DDMMYYYY format
    string dateOfBooking;
    string dateOfTravel;

    double price;
    int validity;
    int ticketId;

    // static variable to keep track of the last Id assigned
    static int last_id;
public:
    Ticket(int passengerId, Planet* sourcePlanet, Planet* destinationPlanet, string dateOfTravel) {
        this->passengerId = passengerId;
        this->sourcePlanet = sourcePlanet;
        this->destinationPlanet = destinationPlanet;
        this->dateOfTravel = dateOfTravel;
        this->dateOfBooking = getTodaysDate();

        // Calculate the distance between the source and destination planets using the Euclidean distance formula
        double distance = std::sqrt(std::pow((destinationPlanet->getX() - sourcePlanet->getX()), 2) + std::pow((destinationPlanet->getY() - sourcePlanet->getY()), 2) + std::pow((destinationPlanet->getZ() - sourcePlanet->getZ()), 2));

        // Calculate the price of the ticket based on the distance and date of travel
        double daysUntilTravel = getTimeDiff(dateOfBooking, dateOfTravel);
        double priceConstant = 1000; // This can be any constant value
        this->price = (priceConstant*distance)/(daysUntilTravel+1);

        this->validity = 10; // Set the validity period to 10 years by default

        // generate a unique Id for the ticket
        this->ticketId = last_id++;

    }

    int getPassengerId() {
        return passengerId;
    }

    Planet* getSourcePlanet() {
        return sourcePlanet;
    }

    Planet* getDestinationPlanet() {
        return destinationPlanet;
    }

    int getTicketId(){
        return ticketId;
    }

    std::string getDateOfTravel() {
        return dateOfTravel;
    }
    
    std::string getDateOfBooking() {
        return dateOfBooking;
    }

    double getPrice() {
        return price;
    }

    int getValidity() {
        return validity;
    }

    void setPassengerId(int passengerId) {
        this->passengerId = passengerId;
    }

    void setSourcePlanet(Planet* sourcePlanet) {
        this->sourcePlanet = sourcePlanet;
    }

    void setDestinationPlanet(Planet* destinationPlanet) {
        this->destinationPlanet = destinationPlanet;
    }

    void setDateOfTravel(std::string dateOfTravel) {
        this->dateOfTravel = dateOfTravel;
    }

    void setPrice(double price){
        this->price = price;
    }

    void printTicketDetails(){
        cout<<"Ticket ID: "<<ticketId<<endl;
        cout<<"Passenger ID: "<<passengerId<<endl;
        cout<<"Source: "<<sourcePlanet->getName()<<endl;
        cout<<"Destination: "<<destinationPlanet->getName()<<endl;
        cout<<"Date of Booking: "<<dateOfBooking<<endl;
        cout<<"Date of Travel: "<<dateOfTravel<<endl;
        cout<<"Price: "<<price<<endl;
        cout<<"Validity(in years): "<<validity<<endl;
    }
};
// initialize the static variable to 1
int Ticket::last_id = 1;

class SpaceTravel {
    private:
        vector<Passenger*> passengers;
        Astronaut* astronaut;
        Commander* commander;
        int travelId;
        Planet* source;
        Planet* destination;
        string date; // date in DDMMYYYY format

        // static variable to keep track of the last Id assigned
        static int last_id;
    public:
        SpaceTravel(Planet* src, Planet* dest, string dt) {
            source = src;
            destination = dest;
            date = dt;
            astronaut = nullptr;
            commander = nullptr;

            // generate a unique Id for the travel
            travelId = last_id++;
        }

        bool addPassenger(Passenger* passenger) { //return true if limit of 10 is not crossed, else false
            if(getTravellersCount()==10)
                return false;
            else{
                passengers.push_back(passenger);
                return true;
            }
        }
        
        void removePassenger(Passenger* passenger) { //remove passenger already in listAllPassengers
            for(int i=0;i<passengers.size();i++){
                if(passenger->getId() == passengers[i]->getId()){
                    passengers.erase(passengers.begin()+i);
                    break;
                }
            }
        }

        void listAllPassengers() {
            for (Passenger* passenger : passengers){
                cout << passenger->getName() << endl;
            }
        }

        void setAstronaut(Astronaut* astro) {
            astronaut = astro;
        }

        void setCommander(Commander* cmdr) {
            commander = cmdr;
        }

        void updateAstronaut(Astronaut* newAstro) {
            astronaut = newAstro;
        }

        void updateCommander(Commander* newCmdr) {
            commander = newCmdr;
        }

        int getTravelId() {
            return travelId;
        }

        Planet* getSource() {
            return source;
        }

        Planet* getDestination() {
            return destination;
        }

        string getDate() {
            return date;
        }

        Astronaut* getAstronaut() {
            return astronaut;
        }

        Commander* getCommander() {
            return commander;
        }

        int getTravellersCount(){
            int size = (int)passengers.size();

            //add count for astronaut and commander
            if(astronaut != nullptr) size++;
            if(commander != nullptr) size++;
            return size;
        }
        
        void printTravelDetails(){
            cout<<"Travel ID: "<<travelId<<endl;
            cout<<"Source: "<<source->getName()<<endl;
            cout<<"Destination: "<<destination->getName()<<endl;
            cout<<"Date: "<<date<<endl;
            cout<<"Astronaut: "<<astronaut->getName()<<endl;
            cout<<"commander: "<<commander->getName()<<endl;
        }
};
// initialize the static variable to 1
int SpaceTravel::last_id = 1;

//check if given date is valid
bool isValidDate(int dd, int mm, int yyyy){
    if(mm==1 || mm==3 || mm==5|| mm==7|| mm==8||mm==10||mm==12 && dd>0 && dd<=31)
        return true;
    else if(mm==4 || mm==6 || mm==9|| mm==11 && dd>0 && dd<=30)
        return true;
    else if(mm==2){
        if((yyyy%400==0 || (yyyy%100!=0 && yyyy%4==0)) && dd>0 && dd<=29)
            return true;
        else if(dd>0 && dd<=28)
            return true;
        else
            return false;
    }
    return false;
}

//return pointer to passenger object given a valid Passenger id, by referng the list of allPassengers
Passenger* getPassengerById(int id, vector<Passenger*> &allPassengers){
    for(auto passenger:allPassengers){
        if(passenger->getId() == id){
            return passenger;
        }
    }
    return nullptr;
}

int main() {
  // Create the universe with at least 3 planets
  Planet* earth = new Planet("Earth", 0, 0, 0, 10000, 13400);
  Planet* mars = new Planet("Mars", 10, 20, 30, 1293, 10290);
  Planet* jupiter = new Planet("Jupiter", -50, 100, -30, 99912, 1220);
  Planet* saturn = new Planet("Saturn", 60, -200, 30, 78912, 3220);

  //Maintain list of all Planets
  vector<Planet*> allPlanets;
  allPlanets.push_back(earth);
  allPlanets.push_back(mars);
  allPlanets.push_back(jupiter);
  allPlanets.push_back(saturn);

  //Create some passengers, astronauts, and commanders
  Passenger* p1 = new Passenger("John ek");
  Passenger* p2 = new Passenger("John Do");
  Passenger* p3 = new Passenger("John teen");
  Passenger* p4 = new Passenger("John chaar");
  Passenger* p5 = new Passenger("John paanch");
  Passenger* p6 = new Passenger("John chhe");
  Passenger* p7 = new Passenger("John saat");
  Passenger* p8 = new Passenger("John aath");
  Passenger* p9 = new Passenger("John nau");
  Passenger* p10 = new Passenger("John das");
  Passenger* p11 = new Passenger("John gyara");
  Astronaut* a1 = new Astronaut("Buzz Aldrin", 20, "ABC123");
  Astronaut* a2 = new Astronaut("Neil Armstrong", 15, "DEF456");
  Commander* c1 = new Commander("Chris Hadfield", "Mission Control");
  Commander* c2 = new Commander("Sunita Williams", "International Space Station");

  // Maintain list of all passengers, astronauts and commanders
  vector<Passenger*> allPassengers;
  vector<Astronaut*> allAstronauts;
  vector<Commander*> allCommanders;
  
  allPassengers.push_back(p1);
  allPassengers.push_back(p2);
  allPassengers.push_back(p3);
  allPassengers.push_back(p4);
  allPassengers.push_back(p5);
  allPassengers.push_back(p6);
  allPassengers.push_back(p7);
  allPassengers.push_back(p8);
  allPassengers.push_back(p9);
  allPassengers.push_back(p10);
  allPassengers.push_back(p11);
  allAstronauts.push_back(a1);
  allAstronauts.push_back(a2);
  allCommanders.push_back(c1);
  allCommanders.push_back(c2);

  //Create a SpaceTravel class from earth to mars on 10th March 2025
  SpaceTravel* st = new SpaceTravel(earth, mars, "10032025");

  // Add passengers to the travel
  st->addPassenger(p1);
  st->addPassenger(p2);

  // Set the astronaut and commander Ids
  st->setAstronaut(a1);
  st->setCommander(c1);

  // Update the astronaut and commander Ids
  st->updateAstronaut(a2);
  a2->addTravel(st); //add travel to astronaut's listOfTravels
  st->updateCommander(c2);
  c2->addTravel(st); //add travel to commander's listOfTravels
  
  //Maintain list of all travels
  vector<SpaceTravel*>allTravels;
  allTravels.push_back(st);

  //Store the index of the last assigned astronaut and commander to ensure 
  //that all astronauts and commanders are being evenly assigned, avoiding overassignment
  int lastAssignedAstro = 1;
  int lastAssignedComm = 1;
  //In case of a very advanced system, assignment of astro/commander could be done based on the information that
  //on which planet would a particular astraunaut/commander be according to the current Space Travels

  //map storing all tickets of a particular space travel(source+destination+travelDate)
  //used to create SpaceTravel class when >1 tickets from source to dest is booked some date
  map<string,vector<Ticket*>>tickets;

  //map from ticketID to ticket, useful for updation
  map<int, Ticket*> tickets_by_id;

  //map from ticketID to SpaceTravel, easier to update SpaceTravel objects
  map<Ticket*, SpaceTravel*> ticket_to_travel;
  
  

  //Provide commandline functionalities
  while(1){
    cout << "Enter 0 to register a new Traveller ( Passenger/ Astronaut/ Commander )\n";
    cout << "Enter 1 to book/update/cancel ticket for a registered Passenger\n";
    cout << "Enter 2 to check travel details of a registered Commander\n";
    cout << "Enter 8 to clear previous commands\n";
    //know all planets k liye kuchh dabayein
    cout << "Enter 9 to terminate the program\n";
    int input;
    cin >> input;
    if(input==0){
        while(1){
            cout << "Enter 1 to register a Passenger\n";
            cout << "Enter 2 to register a Astronaut\n";
            cout << "Enter 3 to register a Commander\n";
            cout << "Enter 0 to return to main menu\n";
            cout << "Enter 8 to clear previous commands\n";

            int inp;
            cin >> inp;

            if(inp==1){
                while(1){
                    cout << "Enter the name of the Passenger to be registered\n";
                    string name;
                    cin >> name;
                    if(name==""){
                        cout << "Invalid input(empty), try again\n";
                        continue;
                    }
                    Passenger* p_temp = new Passenger(name);
                    allPassengers.push_back(p_temp);
                    cout<<endl;
                    break;
                }
            }
            else if(inp==2){
                while(1){
                    cout << "Enter the name of the Astronaut to be registered\n";
                    string name;
                    cin >> name;
                    if(name==""){
                        cout << "Invalid input(empty), try again\n";
                        continue;
                    }

                    cout << "Enter the experience of the Astronaut rounded of to nearest integer(in years)\n";
                    string in;
                    cin >> in;
                    bool invalid = false;
                    for(char a:in){
                        if(!isdigit(a)){ 
                            invalid = true;
                            break;
                        }
                    }
                    if(invalid){
                        cout << "Invalid input(not Integer), try again\n";
                        continue;
                    }
                    int exp = stoi(in);

                    cout << "Enter the LicenceID of the Astronaut\n";
                    cin >> in;

                    Astronaut* a_temp = new Astronaut(name, exp, in);
                    allAstronauts.push_back(a_temp);
                    cout<<endl;
                    break;
                }
            }
            else if(inp==3){
                while(1){
                    cout << "Enter the name of the Commander to be registered\n";
                    string name;
                    cin >> name;
                    if(name==""){
                        cout << "Invalid input(empty), try again\n";
                        continue;
                    }
                    Commander* c_temp = new Commander(name);
                    allCommanders.push_back(c_temp);
                    cout<<endl;
                    break;
                }
            }
            else if(inp==0){
                break;
            }
            else if(inp==8){
                clrscr;
            }
            else{
                cout << "Invalid input, Try again\n" ;
            }
        }
    }
    else if(input==1){
        while(1){
            cout << "Enter 1 to Book a ticket\n";
            cout << "Enter 2 to Cancel a ticket\n";
            cout << "Enter 3 to Update a ticket\n";
            cout << "Enter 4 to Book a return ticket\n";
            cout << "Enter 0 to return to main menu\n";
            cout << "Enter 8 to clear previous commands\n";

            int inp;
            cin >> inp;

            bool return_to_menu = false;
            if(inp==1){
                while(1){
                    cout << "Enter a valid Passenger ID\n";
                    Passenger* currPassenger;
                    string in;
                    cin >> in;
                    bool invalid = false;
                    for(char a:in){
                        if(!isdigit(a)){ 
                            invalid = true;
                            break;
                        }
                    }
                    if(invalid){
                        cout << "Invalid input(not Integer), try again\n";
                        continue;
                    }
                    int id = stoi(in);

                    invalid=true;
                    for(auto passenger:allPassengers){
                        if(passenger->getId() == id){
                            currPassenger=passenger;
                            invalid=false;
                            break;
                        }
                    }
                    if(invalid){
                        cout << "Invalid input(not Registered Passenger), try again\n";
                        continue;
                    }

                    while(1){
                        cout << "Enter Travel date in DDMMYYYY format\n";
                        string dt;
                        cin>>dt;
                        if(dt.size()!=8){
                            cout << "Invalid date input, try again\n";
                            continue;
                        }
                        bool inv=false;
                        for(char a:dt){
                            if(!isdigit(a)){ 
                                inv = true;
                                break;
                            }
                        }
                        if(inv){
                            cout << "Invalid date input(not Integer), try again\n";
                            continue;
                        }
                        int day=stoi(dt.substr(0,2)), month=stoi(dt.substr(2,2)), year=stoi(dt.substr(4));
                        if(!isValidDate(day, month, year)){
                            cout << "Invalid date input, try again\n";
                            continue;
                        }

                        string today = getTodaysDate();
                        double df=getTimeDiff(today, dt);
                        if(df > 3652){ //travel date is after 10 years of booking date
                            cout << "Ticket will become invalid until day of travel, change date and try again\n";
                            continue;
                        }
                        else if(df<0){ //travel date is before booking date
                            cout<<"Travel date is in the past, try again\n";
                            continue;
                        }

                        while(1){
                            cout << "Enter the name of the source Planet\n";
                            string pl;
                            cin>>pl;
                            bool iv=true;
                            Planet* source;
                            for(auto planet:allPlanets){
                                if(planet->getName()==pl){
                                    source = planet;
                                    iv=false;
                                    break;
                                }
                            }
                            if(iv){
                                cout << "Invalid input(entered Source Planet does not exist), try again\n";
                                continue;
                            }

                            while(1){
                                cout << "Enter the name of the destination Planet\n";
                                string pl;
                                cin>>pl;
                                iv = true;
                                Planet* destination;
                                for(auto planet:allPlanets){
                                    if(planet->getName()==pl){
                                        destination = planet;
                                        iv=false;
                                        break;
                                    }
                                }
                                if(iv){
                                    cout << "Invalid input(entered Destination Planet does not exist), try again\n";
                                    continue;
                                }

                                Ticket* ticket = new Ticket(id, source, destination, dt);
                                double price = ticket->getPrice();
                                cout << "The price for your ticket is " << price << "\nEnter 1 to continue, anything else to abort\n";
                                string cont;
                                cin>>cont;
                                if(cont!="1"){
                                    delete ticket;
                                    return_to_menu = true;
                                    break;
                                }
                                tickets[source->getName() + destination->getName() + dt].push_back(ticket);
                                tickets_by_id[ticket->getTicketId()] = ticket;
                                
                                int len = (int)tickets[source->getName() + destination->getName() + dt].size();
                                
                                //Warn the passenger if only 1 ticket for this date
                                if(len==1){
                                    cout<<"Ticket booked! But Astronaut and Commander have not been assigned yet, ";
                                    cout<<"since only one ticket along the desired source-destination on given travel date.\n";
                                    cout<<endl;
                                    ticket->printTicketDetails();
                                    cout<<endl;
                                }
                                //Create SpaceTravel object when 2 tickets from same source-same destination on same day.
                                if(len==2){
                                    int currAstro=lastAssignedAstro, currComm=lastAssignedComm;
                                    bool flag=false;
                                    while(1){
                                        vector<SpaceTravel*>v = allAstronauts[lastAssignedAstro]->getAlltravels();
                                        lastAssignedAstro++;
                                        lastAssignedAstro%=(allAstronauts.size());
                                        bool clash=false;
                                        for(SpaceTravel* t:v){
                                            if(t->getDate()==dt){
                                                clash=true;
                                                break;
                                            }
                                        }
                                        if(!clash){
                                            break;
                                        }
                                        if(currAstro==lastAssignedAstro){
                                            cout<<"Booking failed, No astronaut available for this date\n";
                                            flag=true;
                                            break;
                                        }
                                    }
                                    while(1){
                                        vector<SpaceTravel*>v = allCommanders[lastAssignedComm]->getAlltravels();
                                        lastAssignedComm++;
                                        lastAssignedComm%=(allCommanders.size());
                                        bool clash=false;
                                        for(SpaceTravel* t:v){
                                            if(t->getDate()==dt){
                                                clash=true;
                                                break;
                                            }
                                        }
                                        if(!clash){
                                            break;
                                        }
                                        if(currAstro==lastAssignedAstro){
                                            cout<<"Booking failed, No commander available for this date\n";
                                            flag=true;
                                            break;
                                        }
                                    }
                                    if(flag){
                                        tickets[source->getName() + destination->getName() + dt].pop_back();
                                        tickets_by_id.erase(ticket->getTicketId());
                                        delete ticket;
                                        return_to_menu = true;
                                        break;
                                    }
                                    else{
                                        cout << "Ticket booked! Space Travel confirmed!\n";
                                        SpaceTravel* tmp= new SpaceTravel(source, destination, dt);

                                        // Add passengers to the travel
                                        tmp->addPassenger(getPassengerById(tickets[source->getName() + destination->getName() + dt][0]->getPassengerId(), allPassengers));
                                        tmp->addPassenger(getPassengerById(tickets[source->getName() + destination->getName() + dt][1]->getPassengerId(), allPassengers));
                                    
                                        // Set the astronaut and commander Ids
                                        tmp->setAstronaut(allAstronauts[lastAssignedAstro]);
                                        allAstronauts[lastAssignedAstro++]->addTravel(tmp); //add travel to astronaut's listOfTravels
                                        
                                        tmp->setCommander(allCommanders[lastAssignedComm]);
                                        allCommanders[lastAssignedComm++]->addTravel(tmp); //add travel to commander's listOfTravels
                                        
                                        cout<<endl;
                                        tmp->printTravelDetails();
                                        cout<<endl;
                                        ticket->printTicketDetails();
                                        cout<<endl;
                                        
                                        allTravels.push_back(tmp);
                                        ticket_to_travel[tickets[source->getName() + destination->getName() + dt][0]]=tmp;
                                        ticket_to_travel[tickets[source->getName() + destination->getName() + dt][1]]=tmp;
                                        
                                    }
                                }
                                else if(len>2){
                                    cout << "Ticket booked! Space Travel confirmed!\n";
                                    SpaceTravel* tmp = ticket_to_travel[tickets[source->getName() + destination->getName() + dt][0]];
                                    tmp->addPassenger(getPassengerById(tickets[source->getName() + destination->getName() + dt][len-1]->getPassengerId(), allPassengers));
                                    cout<<endl;
                                    tmp->printTravelDetails();
                                    cout<<endl;
                                    ticket->printTicketDetails();
                                    cout<<endl;
                                }
                                return_to_menu = true;
                                break;
                            }
                            if(return_to_menu) break;
                        }
                        if(return_to_menu) break;
                    }
                    if(return_to_menu) break;
                }
            }
            else if(inp==2){
                while(1){
                    cout<<"Enter valid ticket ID\n";
                    string in;
                    cin >> in;
                    bool invalid = false;
                    for(char a:in){
                        if(!isdigit(a)){ 
                            invalid = true;
                            break;
                        }
                    }
                    if(invalid){
                        cout << "Invalid input(not Integer), try again\n";
                        continue;
                    }
                    int id = stoi(in);

                    if(tickets_by_id.find(id)==tickets_by_id.end()){
                        cout << "Invalid ticket ID input, try again\n";
                        continue;
                    }
                    
                    Ticket* ticket = tickets_by_id[id];
                    
                    //Remove passenger from Space Trave if Space Travel object has been created
                    if(ticket_to_travel.find(ticket)!=ticket_to_travel.end()){
                        ticket_to_travel[ticket]->removePassenger(getPassengerById(ticket->getPassengerId(), allPassengers));
                    }
                    tickets_by_id.erase(id);
                    
                    cout<<"Ticket Cancelled Successfully!\n";
                    break;
                    
                }
            }
            else if(inp==3){
                while(1){
                    cout<<"Enter valid ticket ID\n";
                    string in;
                    cin >> in;
                    bool invalid = false;
                    for(char a:in){
                        if(!isdigit(a)){ 
                            invalid = true;
                            break;
                        }
                    }
                    if(invalid){
                        cout << "Invalid input(not Integer), try again\n";
                        continue;
                    }
                    int id = stoi(in);

                    if(tickets_by_id.find(id)==tickets_by_id.end()){
                        cout << "Invalid ticket ID input, try again\n";
                        continue;
                    }
                    
                    Ticket* ticket = tickets_by_id[id];
                    
                    //Remove passenger from Space Trave if Space Travel object has been created
                    if(ticket_to_travel.find(ticket)!=ticket_to_travel.end()){
                        ticket_to_travel[ticket]->removePassenger(getPassengerById(ticket->getPassengerId(), allPassengers));
                    }
                    
                    while(1){
                        cout << "Enter Travel date in DDMMYYYY format\n";
                        string dt;
                        cin>>dt;
                        if(dt.size()!=8){
                            cout << "Invalid date input, try again\n";
                            continue;
                        }
                        bool inv=false;
                        for(char a:dt){
                            if(!isdigit(a)){ 
                                inv = true;
                                break;
                            }
                        }
                        if(inv){
                            cout << "Invalid date input(not Integer), try again\n";
                            continue;
                        }
                        int day=stoi(dt.substr(0,2)), month=stoi(dt.substr(2,2)), year=stoi(dt.substr(4));
                        if(!isValidDate(day, month, year)){
                            cout << "Invalid date input, try again\n";
                            continue;
                        }

                        string today = getTodaysDate();
                        double df=getTimeDiff(today, dt);
                        if(df > 3652){ //travel date is after 10 years of booking date
                            cout << "Ticket will become invalid until day of travel, change date and try again\n";
                            continue;
                        }
                        else if(df<0){
                            cout<<"Travel date is in the past, try again\n";
                            continue;
                        }

                        while(1){
                            cout << "Enter the name of the source Planet\n";
                            string pl;
                            cin>>pl;
                            bool iv=true;
                            Planet* source;
                            for(auto planet:allPlanets){
                                if(planet->getName()==pl){
                                    source = planet;
                                    iv=false;
                                    break;
                                }
                            }
                            if(iv){
                                cout << "Invalid input(entered Source Planet does not exist), try again\n";
                                continue;
                            }

                            while(1){
                                cout << "Enter the name of the destination Planet\n";
                                string pl;
                                cin>>pl;
                                iv = true;
                                Planet* destination;
                                for(auto planet:allPlanets){
                                    if(planet->getName()==pl){
                                        destination = planet;
                                        iv=false;
                                        break;
                                    }
                                }
                                if(iv){
                                    cout << "Invalid input(entered Destination Planet does not exist), try again\n";
                                    continue;
                                }
                                
                                Ticket* dummyTicket = new Ticket(id, source, destination, dt);
                                double price = dummyTicket->getPrice();
                                delete dummyTicket;
                                cout << "The price for your new ticket is " << price<<endl;
                                
                                ticket->setSourcePlanet(source);
                                ticket->setDestinationPlanet(destination);
                                ticket->setPrice(price);
                                ticket->setDateOfTravel(dt);
                                
                                tickets[source->getName() + destination->getName() + dt].push_back(ticket);
                                int len = (int)tickets[source->getName() + destination->getName() + dt].size();
                                
                                //Warn the passenger if only 1 ticket for this date
                                if(len==1){
                                    cout<<"Ticket booked! But Astronaut and Commander have not been assigned yet, ";
                                    cout<<"since only one ticket along the desired source-destination on given travel date.\n";
                                    cout<<endl;
                                    ticket->printTicketDetails();
                                    cout<<endl;
                                }
                                //Create SpaceTravel object when 2 tickets from same source-same destination on same day.
                                if(len==2){
                                    int currAstro=lastAssignedAstro, currComm=lastAssignedComm;
                                    bool flag=false;
                                    while(1){
                                        vector<SpaceTravel*>v = allAstronauts[lastAssignedAstro]->getAlltravels();
                                        lastAssignedAstro++;
                                        lastAssignedAstro%=(allAstronauts.size());
                                        bool clash=false;
                                        for(SpaceTravel* t:v){
                                            if(t->getDate()==dt){
                                                clash=true;
                                                break;
                                            }
                                        }
                                        if(!clash){
                                            break;
                                        }
                                        if(currAstro==lastAssignedAstro){
                                            cout<<"Booking failed, No astronaut available for this date\n";
                                            flag=true;
                                            break;
                                        }
                                    }
                                    while(1){
                                        vector<SpaceTravel*>v = allCommanders[lastAssignedComm]->getAlltravels();
                                        lastAssignedComm++;
                                        lastAssignedComm%=(allCommanders.size());
                                        bool clash=false;
                                        for(SpaceTravel* t:v){
                                            if(t->getDate()==dt){
                                                clash=true;
                                                break;
                                            }
                                        }
                                        if(!clash){
                                            break;
                                        }
                                        if(currAstro==lastAssignedAstro){
                                            cout<<"Booking failed, No commander available for this date\n";
                                            flag=true;
                                            break;
                                        }
                                    }
                                    if(flag){
                                        tickets[source->getName() + destination->getName() + dt].pop_back();
                                        tickets_by_id.erase(ticket->getTicketId());
                                        delete ticket;
                                        return_to_menu = true;
                                        break;
                                    }
                                    else{
                                        cout << "Ticket updated! Space Travel confirmed!\n";
                                        SpaceTravel* tmp= new SpaceTravel(source, destination, dt);

                                        // Add passengers to the travel
                                        tmp->addPassenger(getPassengerById(tickets[source->getName() + destination->getName() + dt][0]->getPassengerId(), allPassengers));
                                        tmp->addPassenger(getPassengerById(tickets[source->getName() + destination->getName() + dt][1]->getPassengerId(), allPassengers));
                                    
                                        // Set the astronaut and commander Ids
                                        tmp->setAstronaut(allAstronauts[lastAssignedAstro]);
                                        allAstronauts[lastAssignedAstro++]->addTravel(tmp); //add travel to astronaut's listOfTravels
                                        
                                        tmp->setCommander(allCommanders[lastAssignedComm]);
                                        allCommanders[lastAssignedComm++]->addTravel(tmp); //add travel to commander's listOfTravels
                                        
                                        cout<<endl;
                                        tmp->printTravelDetails();
                                        cout<<endl;
                                        ticket->printTicketDetails();
                                        cout<<endl;
                                        
                                        allTravels.push_back(tmp);
                                        ticket_to_travel[tickets[source->getName() + destination->getName() + dt][0]]=tmp;
                                        ticket_to_travel[tickets[source->getName() + destination->getName() + dt][1]]=tmp;
                                        
                                    }
                                }
                                else if(len>2){
                                    cout << "Ticket updated! Space Travel confirmed!\n";
                                    SpaceTravel* tmp = ticket_to_travel[tickets[source->getName() + destination->getName() + dt][0]];
                                    tmp->addPassenger(getPassengerById(tickets[source->getName() + destination->getName() + dt][len-1]->getPassengerId(), allPassengers));
                                    cout<<endl;
                                    tmp->printTravelDetails();
                                    cout<<endl;
                                    ticket->printTicketDetails();
                                    cout<<endl;
                                }
                                return_to_menu = true;
                                break;
                            }
                            if(return_to_menu) break;
                        }
                        if(return_to_menu) break;
                    }
                    if(return_to_menu) break;
                }
            }
            else if(inp==4){
                while(1){
                    cout<<"Enter valid ticket ID\n";
                    string in;
                    cin >> in;
                    bool invalid = false;
                    for(char a:in){
                        if(!isdigit(a)){ 
                            invalid = true;
                            break;
                        }
                    }
                    if(invalid){
                        cout << "Invalid input(not Integer), try again\n";
                        continue;
                    }
                    int id = stoi(in);

                    if(tickets_by_id.find(id)==tickets_by_id.end()){
                        cout << "Invalid ticket ID input, try again\n";
                        continue;
                    }
                    
                    Ticket* ticket = tickets_by_id[id];
                    
                    while(1){
                        cout << "Enter Travel date in DDMMYYYY format\n";
                        string dt;
                        cin>>dt;
                        if(dt.size()!=8){
                            cout << "Invalid date input, try again\n";
                            continue;
                        }
                        bool inv=false;
                        for(char a:dt){
                            if(!isdigit(a)){ 
                                inv = true;
                                break;
                            }
                        }
                        if(inv){
                            cout << "Invalid date input(not Integer), try again\n";
                            continue;
                        }
                        int day=stoi(dt.substr(0,2)), month=stoi(dt.substr(2,2)), year=stoi(dt.substr(4));
                        if(!isValidDate(day, month, year)){
                            cout << "Invalid date input, try again\n";
                            continue;
                        }

                        string today = getTodaysDate();
                        double df=getTimeDiff(today, dt);
                        double df_from_travel=getTimeDiff(ticket->getDateOfTravel(), dt);
                        if(df > 3652){ //travel date is after 10 years of booking date
                            cout << "Ticket will become invalid until day of travel, change date and try again\n";
                            continue;
                        }
                        else if(df<0){
                            cout<<"Travel date is in the past, try again\n";
                            continue;
                        }
                        else if(df_from_travel<0){
                            cout<<"Return date is before the Travel date, try again\n";
                            continue;
                        }

                        // no need to take source and destination planets as input
                        Planet* source = ticket->getDestinationPlanet();
                        Planet* destination = ticket->getSourcePlanet();
                                
                        Ticket* returnTicket = new Ticket(id, source, destination, dt);
                        double price = ticket->getPrice();
                        cout << "The price for your return ticket is " << price << "\nEnter 1 to continue, anything else to abort\n";
                        string cont;
                        cin>>cont;
                        if(cont!="1"){
                            delete ticket;
                            return_to_menu = true;
                            break;
                        }
                        tickets[source->getName() + destination->getName() + dt].push_back(returnTicket);
                        tickets_by_id[returnTicket->getTicketId()] = returnTicket;
                                
                        int len = (int)tickets[source->getName() + destination->getName() + dt].size();
                                
                        //Warn the passenger if only 1 ticket for this date
                        if(len==1){
                            cout<<"Return Ticket booked! But Astronaut and Commander have not been assigned yet, ";
                            cout<<"since only one ticket along the desired source-destination on given travel date.\n";
                            cout<<endl;
                            returnTicket->printTicketDetails();
                            cout<<endl;
                        }
                        //Create SpaceTravel object when 2 tickets from same source-same destination on same day.
                        if(len==2){
                            int currAstro=lastAssignedAstro, currComm=lastAssignedComm;
                            bool flag=false;
                            while(1){
                                vector<SpaceTravel*>v = allAstronauts[lastAssignedAstro]->getAlltravels();
                                lastAssignedAstro++;
                                lastAssignedAstro%=(allAstronauts.size());
                                bool clash=false;
                                for(SpaceTravel* t:v){
                                    if(t->getDate()==dt){
                                        clash=true;
                                        break;
                                    }
                                }
                                if(!clash){
                                    break;
                                }
                                if(currAstro==lastAssignedAstro){
                                    cout<<"Booking failed, No astronaut available for this date\n";
                                    flag=true;
                                    break;
                                }
                            }
                            while(1){
                                vector<SpaceTravel*>v = allCommanders[lastAssignedComm]->getAlltravels();
                                lastAssignedComm++;
                                lastAssignedComm%=(allCommanders.size());
                                bool clash=false;
                                for(SpaceTravel* t:v){
                                    if(t->getDate()==dt){
                                        clash=true;
                                        break;
                                    }
                                }
                                if(!clash){
                                    break;
                                }
                                if(currAstro==lastAssignedAstro){
                                    cout<<"Booking failed, No commander available for this date\n";
                                    flag=true;
                                    break;
                                }
                            }
                            if(flag){
                                tickets[source->getName() + destination->getName() + dt].pop_back();
                                tickets_by_id.erase(returnTicket->getTicketId());
                                delete returnTicket;
                                return_to_menu = true;
                                break;
                            }
                            else{
                                cout << "Return Ticket booked! Space Travel confirmed!\n";
                                SpaceTravel* tmp= new SpaceTravel(source, destination, dt);

                                // Add passengers to the travel
                                tmp->addPassenger(getPassengerById(tickets[source->getName() + destination->getName() + dt][0]->getPassengerId(), allPassengers));
                                tmp->addPassenger(getPassengerById(tickets[source->getName() + destination->getName() + dt][1]->getPassengerId(), allPassengers));
                            
                                // Set the astronaut and commander Ids
                                tmp->setAstronaut(allAstronauts[lastAssignedAstro]);
                                allAstronauts[lastAssignedAstro++]->addTravel(tmp); //add travel to astronaut's listOfTravels
                                
                                tmp->setCommander(allCommanders[lastAssignedComm]);
                                allCommanders[lastAssignedComm++]->addTravel(tmp); //add travel to commander's listOfTravels
                                
                                cout<<endl;
                                tmp->printTravelDetails();
                                cout<<endl;
                                returnTicket->printTicketDetails();
                                cout<<endl;
                                
                                allTravels.push_back(tmp);
                                ticket_to_travel[tickets[source->getName() + destination->getName() + dt][0]]=tmp;
                                ticket_to_travel[tickets[source->getName() + destination->getName() + dt][1]]=tmp;
                                
                            }
                        }
                        else if(len>2){
                            cout << "Return Ticket booked! Space Travel confirmed!\n";
                            SpaceTravel* tmp = ticket_to_travel[tickets[source->getName() + destination->getName() + dt][0]];
                            tmp->addPassenger(getPassengerById(tickets[source->getName() + destination->getName() + dt][len-1]->getPassengerId(), allPassengers));
                            cout<<endl;
                            tmp->printTravelDetails();
                            cout<<endl;
                            returnTicket->printTicketDetails();
                            cout<<endl;
                        }
                        return_to_menu = true;
                        break;
                    }
                    if(return_to_menu) break;
                }
            }
            else if(inp==0){
                break;
            }
            else if(inp==8){
                clrscr;
            }
            else{
                cout << "Invalid input, Try again\n" ;
            }
        }
    }
    else if(input==2){
        while(1){
            cout << "Enter a valid Commander ID\n";
            Commander* currComm;
            string in;
            cin >> in;
            bool invalid = false;
            for(char a:in){
                if(!isdigit(a)){ 
                    invalid = true;
                    break;
                }
            }
            if(invalid){
                cout << "Invalid input(not Integer), try again\n";
                continue;
            }
            int id = stoi(in);

            invalid=true;
            for(auto commander:allCommanders){
                if(commander->getId() == id){
                    currComm=commander;
                    invalid=false;
                    break;
                }
            }
            if(invalid){
                cout << "Invalid input(not Registered Commander), try again\n";
                continue;
            }
            cout<<"Following are the details of your Space Travels:\n";
            
            vector<SpaceTravel*>v=currComm->getAlltravels();
            
            for(auto travel:v){
                cout<<"\n";
                travel->printTravelDetails();
                cout<<"\n";
            }
            break;
        }
    }
    else if(input==9){
        break;
    }
    else if(input==8){
        clrscr;
    }
    else{
        cout << "Invalid input, Try again\n" ;
    }
  }

  return 0;
}