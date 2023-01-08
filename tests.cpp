#include <iostream>

#include <serial_port.hpp>

int main()
{
    try {
        using namespace ports::literals;
        ports::serial_port port{
            "/dev/ttyUSB0"_p
            .baud_rate(115'200)
            .character_size(8)
            .flow_control_none()
            .parity_none()
            .stop_bits_one()
        };
        std::cout << std::boolalpha;

        std::string tx_message{"test"};
        char rx_message[5]{};
        while(true){
            std::getchar();
            std::cout << (port.send(tx_message, tx_message.length()) != port.error ?
                "tx_message <" + tx_message + "> sent\n" :
                "tx_message <" + tx_message + "> could not be sent!\n");
            std::getchar();
            std::cout << (port.receive_to(rx_message, tx_message.length()) != port.error ?
                std::string{"rx_message <"} + rx_message + std::string{"> received\n"}:
                "rx_message could not be received!\n");
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}


