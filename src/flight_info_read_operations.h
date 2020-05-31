#ifndef _FLIGHT_INFO_READ_OPERATION_
#define _FLIGHT_INFO_READ_OPERATION_

#include <flight_database.h>

class FlightInfoReadOperation
{
public:
    explicit FlightInfoReadOperation(const std::shared_ptr<FlightDatabase> data_base);
    std::pair<FlightInfo,bool> GetFlightDetail(const FlightNumberType& flight_number);
    std::vector<FlightNumberType> GetListOfFlightFromTheCity(const std::string& source_city_name);
    std::vector<FlightNumberType> GetListOfFlightFromOperator(const std::string& operator_name);
    AirFareType AverageAirFare();
    AirFareType GetAirFare(const FlightNumberType& flight_number);
    void UpdateMaximumAirFareOperatorname(const OperatorNameUpdate operator_name);

    ~FlightInfoReadOperation()= default;
private:
std::shared_ptr<FlightDatabase> flight_data_base_;
};

#endif //_FLIGHT_INFO_READ_OPERATION_