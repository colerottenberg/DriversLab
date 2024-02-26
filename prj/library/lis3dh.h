/* Class for the On board accelerometer */

/* 
 * Keep in mind that on the Adafruit Feather RP2040, the I2C pins are 4 and 5.
 * That truly means the SDA and SCL pins are 4 and 5 respectively.
 */

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
  // Getters for acceleration values
  float get_x() { return this->x; }
  float get_y() { return this->y; }
  float get_z() { return this->z; }
};

lis3dh::lis3dh(/* args */) {}

lis3dh::~lis3dh() {}

/* Init */
bool lis3dh::init() {
  /* Initializes the accelerometer */
  i2c_init(i2c_default, 400 * 1000);
  gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
  gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
  // Make the I2C pins available to picotool
  bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

  lis3dh_init();
  return true;
}

/* Setters and Getters for Registers */
uint8_t lis3dh::read_reg(uint8_t reg) {
  /* Reads and returns the byte at address reg on accelerometer */
  float data; // pass pointer to data for reading
  lis3dh_read_data(reg, &data, true); // 1 for bool isAccel = true
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

  lis3dh_read_data(0x28, &_x, true);
  lis3dh_read_data(0x2A, &_y, true);
  lis3dh_read_data(0x2C, &_z, true);


  float x, y, z;
  // Convert raw data to g's and store in class members
  lis3dh_calc_value(_x, &x, false);
  lis3dh_calc_value(_y, &y, false);
  lis3dh_calc_value(_z, &z, false);
  this->x = x;
  this->y = y;
  this->z = z;
}
