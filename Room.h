#pragma once

// #include "Switchable"
#include <string_view>
#include <array>


namespace Home
{

class Switchable;

class Room
{
public:
  Room() = delete;
  Room(const char* name) : name(name) {}
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
  static constexpr unsigned dsz {4};
  using DeviceList = std::array<Switchable*, dsz>;
  DeviceList devices;
  unsigned device_count {0};

};





}
