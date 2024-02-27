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

lis3dh::lis3dh(/* args */) {
  /* Constructor */

  // Set the address and control registers
  this->address = 0x18;
  this->ctrl_reg1 = 0x20;
  this->ctrl_reg4 = 0x23;
  this->temp_cfg_reg = 0xC0;

  // Initialize the acceleration values
  this->x = 0;
  this->y = 0;
  this->z = 0;
}

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
  uint8_t data; // pass pointer to data for reading
  i2c_write_blocking(i2c_default, this->address, &reg, 1, true);
  i2c_read_blocking(i2c_default, this->address, &data, 1, false);
  return data;
}

void lis3dh::set_reg(uint8_t reg, uint8_t value) {
  /* Set a register on the LIS3D to a given value */
  uint8_t data[2] = {reg, value};
  i2c_write_blocking(i2c_default, this->address, data, 2, false);
  return;
}

/* Update Functions */
void lis3dh::update() {
  /* Updates the class members x, y, z with current acceleration values */
  float sensitivity = 0.004f; // Sensitivity of the accelerometer
  float scaling = 64 / sensitivity; // Scaling factor for the accelerometer

  // Read raw data from accelerometer and store through pointers
  uint8_t x_l, x_h, y_l, y_h, z_l, z_h;
  x_l = read_reg(0x28);
  x_h = read_reg(0x29);

  y_l = read_reg(0x2A);
  y_h = read_reg(0x2B);

  z_l = read_reg(0x2C);
  z_h = read_reg(0x2D);

  // Combine the high and low bytes to get the raw data
  int16_t x_raw = (x_h << 8) | x_l;
  int16_t y_raw = (y_h << 8) | y_l;
  int16_t z_raw = (z_h << 8) | z_l;

  // Convert the raw data to acceleration

  this->x = (float) ((int16_t) x_raw) / scaling;
  this->y = (float) ((int16_t) y_raw) / scaling;
  this->z = (float) ((int16_t) z_raw) / scaling;

  // Return the acceleration values
  return;
}
