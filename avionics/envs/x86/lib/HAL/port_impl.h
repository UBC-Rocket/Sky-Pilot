#ifndef HAL__PORT_IMPL_H_4670E21514FE46DE8214D2F192FBBD20
#define HAL__PORT_IMPL_H_4670E21514FE46DE8214D2F192FBBD20

#include "HAL/port.h"
#include "stdio_controller.hpp"
#include <cstring>

namespace Hal {

class Serial : public ISerial {
  private:
    typedef StdIoController StdIO;

  public:
    Serial(uint8_t id) : M_IO_ID(id) {}

    void begin(long baud) {}          // no-op for native
    bool available() { return true; } // std::cout always available
    int read() { return 0; } // TODO - make this read from multiplexed stdio
    void write(const uint8_t *buffer, std::size_t size) {
        StdIO::putPacket(M_IO_ID, buffer, size);
    };
    // TODO - make these actually do something
    void print(char *dat) {}
    void println(char *dat) {}

    operator bool() { return true; };

  private:
    uint8_t M_IO_ID;
};

} // namespace Hal
#endif
