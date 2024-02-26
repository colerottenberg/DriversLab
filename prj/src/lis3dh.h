/* Class for the On board accelerometer */

#include "lis3dh_i2c.c"

class lis3dh {
private:
  /* data */
  float x, y, z;
  uint8_t address, ctrl_reg1, ctrl_reg4, temp_cfg_reg;

public:
  lis3dh(/* args */);
  ~lis3dh();
  bool init();
  // Register Setters and Getters
  void set_reg(uint8_t reg, uint8_t value);
  uint8_t read_reg(uint8_t reg);
  void update();
};

lis3dh::lis3dh(/* args */) {}

lis3dh::~lis3dh() {}

/* Init */
bool lis3dh::init() {
  /* Initializes the accelerometer */
  lis3dh_i2c::lis3dh_init();
  return true;
}

/* Setters and Getters for Registers */
uint8_t lis3dh::read_reg(uint8_t reg) {
  /* Reads and returns the byte at address reg on accelerometer */
  float data; // pass pointer to data for reading
  lis3dh_i2c::lis3dh_read_data(reg, &data, true); // 1 for bool isAccel = true
  return uint8_t(data);
}

void lis3dh::set_reg(uint8_t reg, uint8_t value) {
  /* Set a register on the LIS3D to a given value */
}

/* Update Functions */
void lis3dh::update() {
  /* Updates the class members x, y, z with current acceleration values */
  float _x, _y, _z;
  // Read raw data from accelerometer and store through pointers
  lis3dh_i2c::lis3dh_read_data(0x28, &_x, true);
  lis3dh_i2c::lis3dh_read_data(0x2A, &_y, true);
  lis3dh_i2c::lis3dh_read_data(0x2C, &_z, true);

  // Convert raw data to g's and store in class members
  lis3dh_i2c::lis3dh_calc_value(_x, &this->x, true);
  lis3dh_i2c::lis3dh_calc_value(_y, &this->y, true);
  lis3dh_i2c::lis3dh_calc_value(_z, &this->z, true);
}
