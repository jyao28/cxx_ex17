#pragma once

#include <iostream>
#include <array>
#include <memory>

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
  bool add_event(const Instant& on, const Instant& off, Home::Room& room);
  void update_time(const Instant& time);

private:
  static constexpr unsigned sz {16};
  using EventArray = std::array<std::unique_ptr<Event>, sz>;
  EventArray events; 
  unsigned events_count {0};
  
};

}
