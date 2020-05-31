#ifndef _FLIGHT_MANAGEMENT_
#define _FLIGHT_MANAGEMENT_

#include <flight_info_read_operations.h>
#include <flight_info_write_operations.h>

enum class FlightEntryStatus
{
    insert_ok,
    update_ok,
    insert_nok,
    update_nok,
    deleted_nok,
    deleted_ok
};

class FlightManagement
{
public:
    FlightManagement();
    FlightManagement(const FlightManagement&)=delete;
    FlightManagement(FlightManagement&&)noexcept=delete;
    FlightManagement operator=(const FlightManagement&)=delete;
    FlightManagement operator=(FlightManagement&&)noexcept=delete;

    FlightEntryStatus InsertFlightInformation(const FlightInfo& flight_info);

    FlightEntryStatus UpdateFlightInformation(const FlightInfo& flight_info);

    FlightEntryStatus DeleteFlightInformation(const FlightNumberType& fight_number);

    AirFareType GetAirFareForFlight(const FlightNumberType& fight_number)const ;

    std::pair<FlightEntryStatus,FlightInfo> GetFlightDetailForFlight(const FlightNumberType& fight_number)const;

    FlightNumberListType GetFlightNumberDepartingFrom(const NameType& city_name)const;

    FlightNumberListType GetFlightNumberForOperatorName(const NameType& flight_operator);

    AirFareType GetAverageAirFareFromAllTrips()const;

    void MaximumAirFareForOperator(const OperatorNameUpdate operator_name_update);
    
private:
    std::shared_ptr<FlightDatabase> flight_database_;
    std::unique_ptr<FlightInfoReadOperation> flight_read_operations_;
    std::unique_ptr<FlightInfoWriteOperation> flight_write_operations_;
};

#endif //_FLIGHT_MANAGEMENT_
