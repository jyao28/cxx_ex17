#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <utility>
#include <array>
#include <iostream>

#include "Switchable.h"

constexpr bool dbg_func_trace {true};

namespace Home {


enum class HouseCode
{ 
  INVALID, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P
};

using House = HouseCode;

using UnitCode = std::uint8_t;

class Module : public Switchable
{
public:
  Module() = delete;

  Module(const Module& Module) = default;

  Module(HouseCode  hcode, UnitCode   ucode) :
    house_code {hcode},
    unit_code  {ucode}
  {
    
  }

  virtual ~Module();

  virtual std::string type() const { return "Module"; }

  bool is_valid() const 
  {
    return house_code != HouseCode::INVALID && unit_code != 0;
  }

  std::string module_name() const
  {
    return house_str() + ' ' + unit_str();
  }

  std::pair<HouseCode, UnitCode> id() const
  {
    return std::pair<HouseCode, UnitCode>(house_code, unit_code);
  }

  virtual void status() const;

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
