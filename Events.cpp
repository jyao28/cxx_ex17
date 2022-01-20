
#include "Events.h"
#include "Module.h"
#include "Room.h"


using Home::Room;

namespace Timing {

Instant::Instant(unsigned hour, unsigned minute)
{
  unsigned extra_hour = minute / 60;
  this->minute = minute % 60;

  this->hour = (hour + extra_hour) % 24;
}

bool Instant::is_equal(const Instant& inst) const
{
  return (hour == inst.hour &&
          minute == inst.minute);
}

bool operator==(const Instant& inst1, const Instant& inst2)
{
  return inst1.is_equal(inst2);
}

std::ostream& operator<< (std::ostream& cout, const Instant& inst)
{
  cout << inst.hour << ":" << inst.minute;
  return cout;
}


/////////

void Event::do_action(const Instant& inst)
{
  if (on == inst)
  {
    std::cout << "inst matches 'on' time" << std::endl;
  }

  if (off == inst)
  {
    std::cout << "inst matches 'off' time" << std::endl;
  }
}

Event::Event(const Instant& inst_on, const Instant& inst_off, Room& room)
  : on(inst_on), off(inst_off), room(&room)
{

}

void Event::update(const Instant& time)
{
  if (room)
  {
    if (time == on)
    {
      room->all_on();
    }
    if (time == off)
    {
      room->all_off();
    }
  }
}

bool EventList::add_event(const Instant& on, const Instant& off, Home::Room& room)
{
  if (events_count < events.size())
  {
    events[events_count] = Event{on, off, room};
    ++events_count;
    return true;
  }

  return false;
}

void EventList::update_time(const Instant& time)
{
  unsigned int i;
  EventArray::iterator iter;
  for ( i=0, iter = events.begin(); 
        i<events_count;
        ++i, ++iter)
  {
    iter->update(time);
  }
}


}
