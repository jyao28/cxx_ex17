#include "ex.h"

#include <iostream>
#include "Lamp.h"
#include "Appliance.h"
#include "Room.h"
#include "Events.h"

using Home::Lamp;
using Home::NamedLamp;
using Home::Appliance;
using Timing::Instant;
using House = Home::HouseCode;

// Ex8 tests
void lamp_status(Lamp lamp)
{
  lamp.status();
}

void lamp_status_r(Lamp& lamp)
{
  lamp.status();
}

void lamp_status_r(const Lamp* lamp)
{
  lamp->status();
}

void lamp_status_cr(const Lamp& lamp)
{
  lamp.status();
}

void test_pass_by()
{
  std::cout << "Ex8 -- Compare pass by value, by reference and by pointer -----" << std::endl;
  {
    std::cout << "Ex8.1  ---------------------" << std::endl;
    Home::Lamp lamp = Home::Lamp::make_rand_lamp();
    lamp_status(lamp);
  }


  std::cout << "    Ex8.2  ---------------------" << std::endl;
  {
    Home::Lamp lampr = Home::Lamp::make_rand_lamp();
    lamp_status_r(&lampr);
  }

  std::cout << "    Ex8.3  ---------------------" << std::endl;
  {
    Home::Lamp lampr = Home::Lamp::make_rand_lamp();
    lamp_status_r(lampr);
  }

  std::cout << "    Ex8.4  ---------------------" << std::endl;
  {
    Home::Lamp lampr = Home::Lamp::make_rand_lamp();
    lamp_status_cr(lampr);
  }

}
////////////////////



// Ex10-a

void test_ex10()
{
  std::cout << "Ex10  ---- Connecting objects -----------------" << std::endl;

  Home::Lamp desk_lamp { Home::House::A, 2 };
  Home::NamedLamp standard_lamp { "Sofa Lamp", Home::House::A, 3 };
  Home::Appliance tv { "TV", Home::House::A, 4 };
  Home::Lamp bedside_lamp { Home::House::B, 1 };

  Home::Room lounge { "Lounge" };
  lounge.add(desk_lamp);
  lounge.add(standard_lamp);
  lounge.add(tv);

  Home::Room bedroom { "Bedroom" };
  bedroom.add(bedside_lamp);

  Timing::EventList events { };

  events.add_event(Timing::Instant { 0, 1 },
                   Timing::Instant { 0, 10 },
                   lounge);

  events.add_event(Timing::Instant { 0, 5 },
                   Timing::Instant { 0, 10 },
                   bedroom);

  lounge.status();
  bedroom.status();

  std::cout << std::endl;

  events.update_time(Timing::Instant { 0,  0 });  // Ignored.
  events.update_time(Timing::Instant { 0,  1 });  // Room A lights on.
  events.update_time(Timing::Instant { 0,  3 });  // Ignored.

  lounge.status();

  events.update_time(Timing::Instant { 0,  5 });  // Room B lights on.

  bedroom.status();
  events.update_time(Timing::Instant { 0, 10 });  // All lights off.

  lounge.status();
  bedroom.status();

  std::cout << std::endl;
}

// Ex11
void test_ex11()
{
  Lamp       lamp1 { House::B, 1 } ;
  NamedLamp  lamp2  { "Desk lamp", House::A, 1 } ;

  lamp1.on();  //  <= “ Lamp(B 1) has been turned on.”
  lamp2.on();  // <= “Desk lamp: Lamp(A1) has been turned on.”  
}