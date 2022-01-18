#pragma once
#include <cstdint>
#include <string>

enum class HouseCode
{ 
  INVALID, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P
};

using UnitCode = std::uint8_t;

class Device
{
public:
  Device() {}

  Device(const Device& device) :
    house_code(device.house_code),
    unit_code(device.unit_code)
  {
    
  }

  Device(HouseCode  hcode, UnitCode   ucode) :
    house_code(hcode),
    unit_code(ucode)
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

  virtual void dump();

protected:
  HouseCode  house_code {HouseCode::INVALID};
  UnitCode   unit_code {0};

};

class Lamp : public Device
{
public:
  Lamp() {}
  Lamp(const Device& device, bool s) :
    Device(device),
    state(s)
  {

  }


  //static std::unique_ptr<Lamp> create();
  static Lamp make_lamp();

  void      on();
  void      off();

  void dump() override;

private:
  bool      state {false};

};

