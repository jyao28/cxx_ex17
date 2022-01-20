#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <utility>
#include <array>
#include <iostream>

constexpr bool dbg_func_trace {true};

namespace Home {


enum class HouseCode
{ 
  INVALID, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P
};

using House = HouseCode;

using UnitCode = std::uint8_t;

class Device
{
public:
  Device() = delete;

  Device(const Device& device) = default;

  Device(HouseCode  hcode, UnitCode   ucode) :
    house_code {hcode},
    unit_code  {ucode}
  {
    
  }

  virtual std::string type() const { return "Device"; }

  bool is_valid() const 
  {
    return house_code != HouseCode::INVALID && unit_code != 0;
  }

  std::string device_name() const
  {
    return house_str() + unit_str();
  }

  std::pair<HouseCode, UnitCode> id() const
  {
    return std::pair<HouseCode, UnitCode>(house_code, unit_code);
  }

  void status() const;

  //void set_id(const std::pair<HouseCode, UnitCode>& id);
  //void set_id(HouseCode house_code, UnitCode unit_code);

protected:
  virtual std::string status_str() const;

  std::string house_str() const
  {
    if (house_code == HouseCode::INVALID) return "-";

    char c = static_cast<int>('A') + static_cast<int>(house_code) - static_cast<int>(HouseCode::A);
    return { c };
  }

  std::string unit_str() const
  {
     return (unit_code >= 1 && unit_code <= 16) ?
        std::to_string(unit_code) :
        "-";
  }

private:
  HouseCode  house_code {HouseCode::INVALID};
  UnitCode   unit_code {0};

};

class Lamp : public Device
{
public:
  Lamp() = delete;
  Lamp(const Lamp& lamp)
    : Device(*(static_cast<const Device*>(&lamp))),
      state(lamp.state)
  {
    if (dbg_func_trace)
    {
      std::cout << "Lamp::Lamp(const Lamp& <"
                  << device_name() << ", " 
                  << (state ? "true" : "false") 
                << ">)" << std::endl;
    }
  }

  Lamp(const Device& device, bool s) :
    Device {device},
    state {s}
  {
    if (dbg_func_trace)
    {
      std::cout << "Lamp::Lamp("
                  << device_name() << ", " 
                  << (s ? "true" : "false") 
                << ")" << std::endl;
    }

  }

  Lamp(HouseCode  hcode, UnitCode ucode, bool s=false) :
    Device {hcode, ucode},
    state {s}
  {
    if (dbg_func_trace)
    {
      std::cout << "Lamp::Lamp(" 
                  << house_str() << ", " 
                  << unit_str() << ", "
                  << (s ? "true" : "false") 
                << ")" << std::endl;
    }

  }

  std::string type() const override { return "Lamp"; }

  //static std::unique_ptr<Lamp> create();
  static Lamp make_rand_lamp();

  bool      is_on() const { return state; }
  void      on();
  void      off();

  ~Lamp();

protected:
  std::string status_str() const override;

private:
  bool      state {false};

};


class Room
{
public:
  Room() = delete;
  Room(const char* name) : name(name) {}
  Room(const Room&) = delete;

  bool add(Device& device);
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
  using DeviceList = std::array<Device*, dsz>;
  DeviceList devices;
  unsigned device_count {0};

};



}
