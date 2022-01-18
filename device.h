#pragma once
#include <cstdint>
#include <string>
#include <utility>

namespace Home {


enum class HouseCode
{ 
  INVALID, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P
};

using UnitCode = std::uint8_t;

class Device
{
public:
  Device() = default;

  Device(const Device& device) = default;

  Device(HouseCode  hcode, UnitCode   ucode) :
    house_code {hcode},
    unit_code  {ucode}
  {
    
  }

  char houseName() {
    if (house_code == HouseCode::INVALID) return '-';

    return static_cast<int>(house_code) - static_cast<int>(HouseCode::A) + 'A';
  };

  std::string device_name()
  {
    std::string house_name { houseName() };
    std::string unit_code_str = 
      (unit_code >= 1 && unit_code <= 16) ?
        std::to_string(unit_code) :
        "-";

    return house_name + unit_code_str;
  }

  std::pair<HouseCode, UnitCode> id()
  {
    return std::pair<HouseCode, UnitCode>(house_code, unit_code);
  }

  void set_id(const std::pair<HouseCode, UnitCode>& id);
  void set_id(HouseCode house_code, UnitCode unit_code);

  virtual void status();

private:
  HouseCode  house_code {HouseCode::INVALID};
  UnitCode   unit_code {0};

};

class Lamp : public Device
{
public:
  Lamp() = default;

  Lamp(const Lamp&) = default;

  Lamp(const Device& device, bool s) :
    Device {device},
    state {s}
  {

  }


  //static std::unique_ptr<Lamp> create();
  static Lamp make_rand_lamp();

  bool      is_on() const { return state; }
  void      on();
  void      off();

  void      status() override;

private:
  bool      state {false};

};

}
