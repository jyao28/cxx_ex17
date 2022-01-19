#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <utility>
#include <array>

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
  Device() = default;

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

  void set_id(const std::pair<HouseCode, UnitCode>& id);
  void set_id(HouseCode house_code, UnitCode unit_code);

  virtual void status() const;

  virtual std::string status_str() const;

private:

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

  HouseCode  house_code {HouseCode::INVALID};
  UnitCode   unit_code {0};

};

class Lamp : public Device
{
public:
  Lamp() = default;

  Lamp(const Lamp&) = default;

  explicit Lamp(bool s) :
    state(s)
  {
    
  }

  Lamp(const Device& device, bool s) :
    Device {device},
    state {s}
  {

  }

  Lamp(HouseCode  hcode, UnitCode   ucode) :
    Device {hcode, ucode},
    state {false}
  {

  }

  std::string type() const override { return "Lamp"; }

  //static std::unique_ptr<Lamp> create();
  static Lamp make_rand_lamp();

  bool      is_on() const { return state; }
  void      on();
  void      off();

  void      status() const override;
  std::string status_str() const override;

  ~Lamp();

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
  void set_name(const char* name);
  void status();

private:
  std::string_view name;
  static constexpr unsigned dsz {4};
  using DeviceList = std::array<Device*, dsz>;
  DeviceList devices;
  unsigned device_count {0};

};



}
