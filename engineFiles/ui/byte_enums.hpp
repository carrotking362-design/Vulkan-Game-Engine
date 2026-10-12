#pragma once

#include <cstdint>

namespace error {
enum : uint8_t { 
    null = 0x00, 
    header = 0x01, 
    command = 0x02, 
    other = 0x03,
    error = 0xFF
};
}

namespace h {
enum : uint8_t { 
    null = 0x00, 
    engine = 0x01, 
    renderer = 0x02, 
    scene = 0x03, 
    error = 0xFF 
};
}

namespace ecode {
enum : uint8_t { 
    null = 0x00, 
    
    setfps = 0x01, 
    getfps = 0x02,

    play = 0x03,
    pause = 0x04,
    
    error = 0xFF 
};
}

namespace rcode {
enum : uint8_t { 
    null = 0x00, 
    error = 0xFF 
};
}

namespace scode {
enum : uint8_t { 
    null = 0x00, 
    load = 0x01, 
    save = 0x02, 
    clear = 0x03, 
    error = 0xFF 
};
}
