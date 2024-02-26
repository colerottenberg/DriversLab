/* Class for the On board accelerometer */

class lis3dh {
private:
  /* data */
  float x, y, z;

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
  return true;
}

/* Setters and Getters for Registers */
uint8_t lis3dh::read_reg(uint8_t reg) {
  /* Reads and returns the byte at address reg on accelerometer */
  return 0;
}

void lis3dh::set_reg(uint8_t reg, uint8_t value) {
  /* Set a register on the LIS3D to a given value */
}

/* Update Functions */
void lis3dh::update() {
  /* Updates the class members x, y, z with current acceleration values */
}
