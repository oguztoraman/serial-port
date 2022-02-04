#include <iostream>

#include <serial_port.hpp>

int main()
{
    try {
        using namespace project::literals;
        project::serial_port port{
            "/dev/ttyUSB0"_p
            .baud_rate(115'200)
            .character_size(8)
            .flow_control_none()
            .parity_none()
            .stop_bits_one()
        };
        std::cout << std::boolalpha;
        std::cout << (port.send("test") ? "message sent!\n" : "message could not be sent!\n");
        char rx[9]{};
        while(true){
            std::cout << port.receive_to(rx) << " " << rx << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
