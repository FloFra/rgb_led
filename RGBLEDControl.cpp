#include <unistd.h>

#include <iostream>
#include <boost/asio.hpp>

class RGBLEDControl
{
public:
    /**
     * Constructor.
     * \param port device name, example "/dev/ttyUSB0" or "COM4"
     * \throws boost::system::system_error if cannot open the
     * serial device
     */
    RGBLEDControl(std::string port)
    : io_(), serial_(io_, port) {

	if( !serial_.is_open()) std::cout << "Port is NOT openend!" << std::endl;
        serial_.set_option(boost::asio::serial_port_base::baud_rate(4800));
	serial_.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
	serial_.set_option(boost::asio::serial_port_base::character_size(8));
	serial_.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
	serial_.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
    
}

    /**
     * Send new color value to an attached led.
     * \param s string to write
     * \throws boost::system::system_error on failure
     */
    void setColor(unsigned char red_value, unsigned char green_value, unsigned char blue_value) {
      
	unsigned char interrupter = 0;
	boost::asio::write(serial_, boost::asio::buffer( &interrupter, 1));
       
 	//usleep(10000);	
	
	//unsigned char quantifier[] = {'R', 'G', 'B'};
  	//boost::asio::write(serial_, boost::asio::buffer( &quantifier, 3));
        boost::asio::write(serial_, boost::asio::buffer( &red_value, 1));
        boost::asio::write(serial_, boost::asio::buffer( &green_value, 1));
        boost::asio::write(serial_, boost::asio::buffer( &blue_value, 1));
    
	std::cout << "Color was sent!" << std::endl;
    }

private:
    boost::asio::io_service io_;
    boost::asio::serial_port serial_;
};

int main(int argc, char* argv[])
{
    // Check if values for all colors where supplied
    if(argc != 4 and argc != 5) {
        std::cout << "Usage: " << argv[0] << " RED GREEN BLUE [PORT]" << std::endl
                  << std::endl
                  << "        RED, GREEN and BLUE must in the range of 0 to 255" << std::endl
                  << "        PORT is optional and defaults to /dev/ttyS0" << std::endl;
        
        return 1;
    } 

    // Parse input
    int red_value = atoi(argv[1]);
    int green_value = atoi(argv[2]);
    int blue_value = atoi(argv[3]);

    // Check if port was specified
    std::string port = (argc == 5 ? argv[4] : "/dev/ttyS0");

    // Check if input is valid
    if(red_value < 0 or red_value > 255 or green_value < 0 or green_value > 255 or blue_value < 0 or blue_value > 255) {
        std::cout << "Color values must be in the range of 0 to 255!";
        return 1;
    }

    // Send out serial command
    try {

        RGBLEDControl client(port);

        client.setColor((unsigned char) red_value, (unsigned char) green_value, (unsigned char) blue_value);

    } catch(boost::system::system_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
