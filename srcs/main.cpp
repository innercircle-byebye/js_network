#include "Cycle.hpp"
#include "HttpConfig.hpp"
#include <map>

int main(int argc, char *argv[])
{
	if (argc <= 2)
	{
		std::string		config_file_name;
		config_file_name = ((argc == 1) ? "sample.conf" : argv[1]);

		try {
			HttpConfig *httpconfig = new HttpConfig(config_file_name);
			Cycle cycle(httpconfig);

			cycle.webservCycle();
			delete httpconfig;
		}
		catch(std::exception &e) {
			std::cerr << e.what() << std::endl;
			return (-1);
		}
	}
	return (0);
}
