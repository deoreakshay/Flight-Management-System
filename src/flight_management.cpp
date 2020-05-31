#include <flight_management.h>

FlightManagement::FlightManagement():flight_database_{std::make_shared<FlightDatabase>()},
                                     flight_read_operations_{std::make_unique<FlightInfoReadOperation>(flight_database_)},
                                     flight_write_operations_{std::make_unique<FlightInfoWriteOperation>(flight_database_)}
{

}

FlightEntryStatus FlightManagement::InsertFlightInformation(const FlightInfo& flight_info)
{
    FlightEntryStatus status= FlightEntryStatus::insert_nok;
    if(flight_write_operations_->AddTrip(flight_info))
    {
        status = FlightEntryStatus::insert_ok;
    }
    return status;
}

FlightEntryStatus FlightManagement::UpdateFlightInformation(const FlightInfo& flight_info)
{
    FlightEntryStatus status= FlightEntryStatus::update_nok;
    if(flight_write_operations_->UpdateTrip(flight_info))
    {
        status = FlightEntryStatus::update_ok;
    }
    return status;
}

FlightEntryStatus FlightManagement::DeleteFlightInformation(const FlightNumberType& fight_number)
{
    FlightEntryStatus status= FlightEntryStatus::deleted_nok;
    if(flight_write_operations_->RemoveTrip(fight_number))
    {
        status = FlightEntryStatus::deleted_ok;
    }
    return status;
}

AirFareType FlightManagement::GetAirFareForFlight(const FlightNumberType& fight_number)const
{
    return flight_read_operations_->GetAirFare(fight_number);
}

std::pair<FlightEntryStatus,FlightInfo> FlightManagement::GetFlightDetailForFlight(const FlightNumberType& fight_number)const
{
    std::pair<FlightEntryStatus,FlightInfo> flight_info;

    auto find_index = flight_read_operations_->GetFlightDetail(fight_number);
    if(find_index.second)
    {
        flight_info = std::make_pair(FlightEntryStatus::update_ok,find_index.first);
    }
    return flight_info;
}

FlightNumberListType FlightManagement::GetFlightNumberDepartingFrom(const NameType& city_name)const
{
    return flight_read_operations_->GetListOfFlightFromTheCity(city_name);
}

FlightNumberListType FlightManagement::GetFlightNumberForOperatorName(const NameType& flight_operator)
{
    return flight_read_operations_->GetListOfFlightFromOperator(flight_operator);
}

AirFareType FlightManagement::GetAverageAirFareFromAllTrips()const
{
    return flight_read_operations_->AverageAirFare();
}

void FlightManagement::MaximumAirFareForOperator(const OperatorNameUpdate operator_name_update)
{
    flight_read_operations_->UpdateMaximumAirFareOperatorname(operator_name_update);
}