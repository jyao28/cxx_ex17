#include <cstdint>

enum class HouseCode
{ 
  INVALID, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P
};

using UnitCode = std::uint8_t;

class Device
{
public:
  char houseName() {
    if (house_code == HouseCode::INVALID) return '-';

    return static_cast<int>(house_code) - static_cast<int>(HouseCode::A) + 'A';
  };

  virtual void dump();

protected:
  HouseCode  house_code {HouseCode::INVALID};
  UnitCode   unit_code {0};
  
};

class Lamp : public Device
{
public:
  bool      state {false};

  //static std::unique_ptr<Lamp> create();
  static Lamp make_lamp();

  void      on();
  void      off();

  void dump() override;
};

