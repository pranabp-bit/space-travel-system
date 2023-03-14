The Space travel has been implemented with various functionalities. As mentioned in the problem first a universe has been created with some planets, passengers, astronauts and commanders. This information is first printed on the screen to let the user know which planets, travellers already exist. Then the user can perform various functionalities like registering a passenger/astronaut/commander. After successful registration, user will receive an id which can then be used to book tickets. User can book, cancel and update tickets. Option to book return tickets has also been provided. When two tickets of same source destination date are booked, a spaceTravel object is created and an astronaut and commander is assigned ensuring there is no clash with their schedule. If no astronaut/commander is available, that too is informed. If a SpaceTravel has more  that 10 passengers, new passenger is not added to that travel. A list of travels is maintained for astronaut and commanders. A commander can list his travels by using the functionality of this app. Ticket Price system is implemented such that the price is inversely proportional to the number of days  to travel and directly proportional to the distance between the planets.All the functionalities have been implemented with proper error measures. Like while booking ticket the travel date should be valid, within the validity of a ticket and should be a date after the date of booking. Many more measures like valid passenger ID, Commander ID have also been implemented. The code has been properly commented for better understanding.

An example of interacting with the system after running the code-

New Planet Created
Planet: Earth
Coordinates: (0, 0, 0)
Radius: 10000
Mass: 13400
New Planet Created
Planet: Mars
Coordinates: (10, 20, 30)
Radius: 1293
Mass: 10290
New Planet Created
Planet: Jupiter
Coordinates: (-50, 100, -30)
Radius: 99912
Mass: 1220
New Planet Created
Planet: Saturn
Coordinates: (60, -200, 30)
Radius: 78912
Mass: 3220
New Passenger added
Passenger - Name: John ek, Id: 1
New Passenger added
Passenger - Name: John Do, Id: 2
New Passenger added
Passenger - Name: John teen, Id: 3
New Passenger added
Passenger - Name: John chaar, Id: 4
New Passenger added
Passenger - Name: John paanch, Id: 5
New Passenger added
Passenger - Name: John chhe, Id: 6
New Passenger added
Passenger - Name: John saat, Id: 7
New Passenger added
Passenger - Name: John aath, Id: 8
New Passenger added
Passenger - Name: John nau, Id: 9
New Passenger added
Passenger - Name: John das, Id: 10
New Passenger added
Passenger - Name: John gyara, Id: 11
New Astronaut added
Astronaut - Name: Buzz Aldrin, Id: 12, Experience: 20, License Id: ABC123
New Astronaut added
Astronaut - Name: Neil Armstrong, Id: 13, Experience: 15, License Id: DEF456
New Commander added
Commander - Name: Chris Hadfield, Id: 14, Authority: Mission Control
New Commander added
Commander - Name: Sunita Williams, Id: 15, Authority: International Space Station
Enter 0 to register a new Traveller ( Passenger/ Astronaut/ Commander )
Enter 1 to book/update/cancel ticket for a registered Passenger
Enter 2 to check travel details of a registered Commander
Enter 8 to clear previous commands
Enter 9 to terminate the program
1
Enter 1 to Book a ticket
Enter 2 to Cancel a ticket
Enter 3 to Update a ticket
Enter 4 to Book a return ticket
Enter 0 to return to main menu
Enter 8 to clear previous commands
1
Enter a valid Passenger ID
1
Enter Travel date in DDMMYYYY format
10032026
Enter the name of the source Planet
Earth
Enter the name of the destination Planet
Mars
The price for your ticket is 34.2329
Enter 1 to continue, anything else to abort
1
Ticket booked! But Astronaut and Commander have not been assigned yet, since only one ticket along the desired source-destination on given travel date.

Ticket ID: 1
Passenger ID: 1
Source: Earth
Destination: Mars
Date of Booking: 14032023
Date of Travel: 10032026
Price: 34.2329
Validity(in years): 10

Enter 1 to Book a ticket
Enter 2 to Cancel a ticket
Enter 3 to Update a ticket
Enter 4 to Book a return ticket
Enter 0 to return to main menu
Enter 8 to clear previous commands
1
Enter a valid Passenger ID
2
Enter Travel date in DDMMYYYY format
10032026
Enter the name of the source Planet
Earth
Enter the name of the destination Planet
Mars
The price for your ticket is 34.2329
Enter 1 to continue, anything else to abort
1
Ticket booked! Space Travel confirmed!

Travel ID: 2
Source: Earth
Destination: Mars
Date: 10032026
Astronaut: Buzz Aldrin
commander: Chris Hadfield

Ticket ID: 2
Passenger ID: 2
Source: Earth
Destination: Mars
Date of Booking: 14032023
Date of Travel: 10032026
Price: 34.2329
Validity(in years): 10

Enter 1 to Book a ticket
Enter 2 to Cancel a ticket
Enter 3 to Update a ticket
Enter 4 to Book a return ticket
Enter 0 to return to main menu
Enter 8 to clear previous commands
4
Enter valid ticket ID
2
Enter Travel date in DDMMYYYY format
10032024
Return date is before the Travel date, try again
Enter Travel date in DDMMYYYY format
10022027
The price for your return ticket is 34.2329
Enter 1 to continue, anything else to abort
1
Return Ticket booked! But Astronaut and Commander have not been assigned yet, since only one ticket along the desired source-destination on given travel date.

Ticket ID: 3
Passenger ID: 2
Source: Mars
Destination: Earth
Date of Booking: 14032023
Date of Travel: 10022027
Price: 26.1654
Validity(in years): 10

Enter 1 to Book a ticket
Enter 2 to Cancel a ticket
Enter 3 to Update a ticket
Enter 4 to Book a return ticket
Enter 0 to return to main menu
Enter 8 to clear previous commands
0
Enter 0 to register a new Traveller ( Passenger/ Astronaut/ Commander )
Enter 1 to book/update/cancel ticket for a registered Passenger
Enter 2 to check travel details of a registered Commander
Enter 8 to clear previous commands
Enter 9 to terminate the program
2
Enter a valid Commander ID
12
Invalid input(not Registered Commander), try again
Enter a valid Commander ID
14
Following are the details of your Space Travels:

Travel ID: 2
Source: Earth
Destination: Mars
Date: 10032026
Astronaut: Buzz Aldrin
commander: Chris Hadfield

Enter 0 to register a new Traveller ( Passenger/ Astronaut/ Commander )
Enter 1 to book/update/cancel ticket for a registered Passenger
Enter 2 to check travel details of a registered Commander
Enter 8 to clear previous commands
Enter 9 to terminate the program
9
