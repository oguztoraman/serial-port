/* SPDX-FileCopyrightText: Copyright (c) 2022-2025 Oğuz Toraman <oguz.toraman@tutanota.com> */
/* SPDX-License-Identifier: BSL-1.0 */

#ifndef SERIAL_PORT_HPP
#define SERIAL_PORT_HPP

#include <boost/asio/serial_port.hpp>

static_assert(
    BOOST_VERSION >= 107600,
    "boost version must be at least 1.76.0!"
);

static_assert (
    __cplusplus >= 201402L,
    "minimum c++14 required!"
);

namespace ports {

class serial_port {
public:
    class serial_port_parameters {
    public:
        using port_t = boost::asio::serial_port_base;

        explicit serial_port_parameters(const std::string& port_name)
            : m_port_name{port_name}
        { }

        serial_port_parameters& baud_rate(unsigned int rate)
        {
            m_baud_rate = static_cast<port_t::baud_rate>(rate);
            return *this;
        }

        serial_port_parameters& flow_control_none()
        {
            m_flow_control = static_cast<port_t::flow_control>(
                port_t::flow_control::none
            );
            return *this;
        }

        serial_port_parameters& flow_control_software()
        {
            m_flow_control = static_cast<port_t::flow_control>(
                port_t::flow_control::software
            );
            return *this;
        }

        serial_port_parameters& flow_control_hardware()
        {
            m_flow_control = static_cast<port_t::flow_control>(
                port_t::flow_control::hardware
            );
            return *this;
        }

        serial_port_parameters& parity_none()
        {
            m_parity = static_cast<port_t::parity>(
                port_t::parity::none
            );
            return *this;
        }

        serial_port_parameters& parity_odd()
        {
            m_parity = static_cast<port_t::parity>(
                port_t::parity::odd
            );
            return *this;
        }

        serial_port_parameters& parity_even()
        {
            m_parity = static_cast<port_t::parity>(
                port_t::parity::even
            );
            return *this;
        }

        serial_port_parameters& stop_bits_one()
        {
            m_stop_bits = static_cast<port_t::stop_bits>(
                port_t::stop_bits::one
            );
            return *this;
        }

        serial_port_parameters& stop_bits_onepointfive()
        {
            m_stop_bits = static_cast<port_t::stop_bits>(
                port_t::stop_bits::onepointfive
            );
            return *this;
        }

        serial_port_parameters& stop_bits_two()
        {
            m_stop_bits = static_cast<port_t::stop_bits>(
                port_t::stop_bits::two
            );
            return *this;
        }

        serial_port_parameters& character_size(unsigned int size)
        {
            m_character_size = static_cast<port_t::character_size>(
                size
            );
            return *this;
        }

    private:
        friend serial_port;
        std::string m_port_name;
        port_t::baud_rate m_baud_rate{
            9'600
        };
        port_t::flow_control m_flow_control{
            port_t::flow_control::none
        };
        port_t::parity m_parity{
            port_t::parity::none
        };
        port_t::stop_bits m_stop_bits{
            port_t::stop_bits::one
        };
        port_t::character_size m_character_size{
            8
        };
    };

    static constexpr std::size_t error = 0;

    serial_port(const serial_port_parameters& parameters)
    try : m_serial_port{m_io, parameters.m_port_name}
    {
        m_serial_port.set_option(parameters.m_baud_rate);
        m_serial_port.set_option(parameters.m_flow_control);
        m_serial_port.set_option(parameters.m_character_size);
        m_serial_port.set_option(parameters.m_stop_bits);
        m_serial_port.set_option(parameters.m_parity);
    } catch (const boost::system::system_error& e) {
        throw std::runtime_error{
            std::string{"serial_port initialize error!\n"} + e.what()
        };
    }

    template <typename ...Args>
    std::size_t receive_to(Args&& ...args) const noexcept
    try {
        auto rx_buffer = boost::asio::buffer(std::forward<Args>(args)...);
        return m_serial_port.read_some(rx_buffer);
    } catch (const boost::system::system_error& e) {
        return error;
    }

    template <typename ...Args>
    std::size_t send(Args&& ...args) const noexcept
    try {
        auto tx_buffer = boost::asio::buffer(std::forward<Args>(args)...);
        return m_serial_port.write_some(tx_buffer);
    } catch (const boost::system::system_error& e) {
        return error;
    }

private:
    boost::asio::io_context m_io{};
    mutable boost::asio::serial_port m_serial_port;
};

namespace literals {
inline serial_port::serial_port_parameters
    operator""_p(const char* cstr_ptr, std::size_t n)
{
    return serial_port::serial_port_parameters{
        std::string(cstr_ptr, n)
    };
}
} /* namespace ports::literals */

} /* namespace ports */

#endif /* SERIAL_PORT_HPP */
