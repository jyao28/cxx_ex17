#pragma once

#include <iostream>
#include <memory>
//#include <array>
#include <vector>

namespace Home {
  class Room;
}

namespace Timing {

class Instant
{
public:
  Instant() = default;
  Instant(const Instant&) = default;
  Instant(unsigned hour, unsigned minute);
  Instant& operator=(const Instant&) = default;

  bool is_equal(const Instant& inst) const;

  friend std::ostream& operator<< (std::ostream& cout, const Instant& inst);
  friend bool operator==(const Instant& inst1, const Instant& inst2);
private:
  unsigned hour   {0};
  unsigned minute {0};
};

class Event
{
public:
  Event() = default;
  Event(const Event&) = default;
  Event(const Instant& inst_on, const Instant& inst_off, Home::Room& room);

  void do_action(const Instant& inst);
  void update(const Instant& time);

private:
  Instant on  {};
  Instant off {};
  Home::Room*  room {};
};

class EventList
{
public:
  EventList()
  {
    events.reserve(6);
  }
  
  bool add_event(const Instant& on, const Instant& off, Home::Room& room);
  void update_time(const Instant& time);

private:
  using EventArray = std::vector<std::unique_ptr<Event>>;
  EventArray events; 
  
};

}
