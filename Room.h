#pragma once

// #include "Switchable"
#include <string_view>
//#include <array>
#include <vector>


namespace Home
{

class Switchable;

class Room
{
public:
  Room() = delete;
  Room(const char* name) : name(name) { devices.reserve(4); }
  Room(const Room&) = delete;

  bool add(Switchable& switchable);
  void all_off();
  void all_on();

  //void set_name(const char* name)
  //{
  //  this->name = name;
  //}
  void status();

private:
  const std::string_view name;
  using DeviceList = std::vector<Switchable*>;
  DeviceList devices;

};





}
