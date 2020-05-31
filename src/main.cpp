#include <iostream>
#include "flight_management.h"

int main() {
    int choice{};
    int fnumber;
    FlightInfo temp;

    std::vector<FlightInfo> flights;
    flights.emplace_back(10010, "Munich", "Berlin", "Lufthansa", 150.00);
    flights.emplace_back(10011, "Munich", "Prague", "Lufthansa", 100);
    flights.emplace_back(10012, "Munich", "Frankfurt", "Lufthansa", 180);
    flights.emplace_back(10013, "Barcelona", "Paris", "Swiss", 200);
    flights.emplace_back(10014, "Munich", "Zurich", "Lufthansa", 250);
    flights.emplace_back(10015, "Paris", "Lisbon", "Air France", 220);

    std::unique_ptr<FlightManagement> flight_management = std::make_unique<FlightManagement>();
    for(auto flight_info : flights)
    {
        flight_management->InsertFlightInformation(flight_info);
    }
    
    while(true)
    {
        std::cout << std::endl << "########################################" << std::endl;
        std::cout << "    FLIGHT MANAGEMENT SYSTEM   " << std::endl;
        std::cout << "(1) Insert Flight Information : " << std::endl;
        std::cout << "(2) Update Flight Information : " << std::endl;
        std::cout << "(3) Delete Flight Information : " << std::endl;
        std::cout << "(4) Display Flight Information : " << std::endl;
        std::cout << "(5) Check Price Information for Flight: " << std::endl;
        std::cout << "(6) Display Flight by Operator : " << std::endl;
        std::cout << "(7) Exit :" << std::endl;

        std::cout << std::endl << "Enter your Choice : " ;
        std::cin >> choice;
        switch(choice)
        {
            case 1:
                {
                    std::cout << "Please Enter flight details in below format:" << std::endl; 
                    std::cout << "[Flight number] [Origin] [Destination] [Operator] [AirFare]" << std::endl;
                    std::cin >> temp.flight_number >> temp.origin_city >> temp.destination_city >> temp.flight_operator >> temp.air_fare ;
                    flight_management->InsertFlightInformation(std::move(temp));
                    auto result = flight_management->GetFlightDetailForFlight(temp.flight_number);
                    std::cout << "Flight details inserted:" << std::endl;
                    std::cout << result.second.flight_number << " " << result.second.origin_city << " " << result.second.destination_city
                        << " " << result.second.flight_operator << " "<< result.second.air_fare << std::endl;
                }
                break;

            case 2:
                {
                    std::cout << "Please enter flight information to update : ";
                    std::cin >> temp.flight_number >> temp.origin_city >> temp.destination_city >> temp.flight_operator >> temp.air_fare ;
                    auto result = flight_management->UpdateFlightInformation(std::move(temp));
                }
                break;

            case 3:
                {
                    std::cout << "Please enter flight number to delete : ";
                    std::cin >> temp.flight_number;
                    auto result = flight_management->DeleteFlightInformation(temp.flight_number);
                }
                break;

            case 4:
            {
                std::cout << "Please Enter Flight number : " << std::endl;
                std::cin >> temp.flight_number;
                auto results = flight_management->GetFlightDetailForFlight(temp.flight_number);
                std::cout << "Flight details for " << results.second.flight_number << std::endl;
                std::cout << results.second.origin_city << " " << results.second.destination_city << " " << results.second.air_fare 
                    << " " << results.second.flight_operator << std::endl;
            }
                break;

            case 5:
            {
                std::cout << "Please Enter Flight number to get Fare details: " ;
                std::cin >> temp.flight_number;
                auto result = flight_management->GetAirFareForFlight(temp.flight_number);
                std::cout << "Air fare for flight " << temp.flight_number << "is : " << result << std::endl;
            }
                break;

            case 6:
            {
                FlightInfo temp;
                std::cout << "Enter Flight operator name : " ;
                std::cin >> temp.flight_operator;
                auto results = flight_management->GetFlightNumberForOperatorName(temp.flight_operator);
                std::cout << "Flight numbers for operator " << temp.flight_operator << " :" << std::endl;
                for(auto flight : results)
                {
                    std::cout << flight << std::endl;   
                }
            }
                break;

            case 7:
                std::cout << "Thank You for using Flight Management System " << std::endl;
                exit(1);
                break;

            default : 
                std::cout << "Please Enter correct input for FMS:" << std::endl;
                break;
        }
    }
    return 0;
}