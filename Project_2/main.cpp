/**
*	@mainpage	HeteroGeneousList.
*				This is a simple example of Lab06 on data structures course.<br>
*
*	@date	2019.05.18
*	@author	ParkJungJin
*/

#include "BaseApplication.hpp"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

/* uncomment for applications that use vectors */
/*#include <vector>*/

#include "/usr/local/mysql-connector-c++-8.0/include/

#include <driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#define EXAMPLE_HOST "localhost"
#define EXAMPLE_USER "worlduser"
#define EXAMPLE_PASS "worldpass"
#define EXAMPLE_DB "world"
using namespace std;

/**
*	program main function for data structures course.
*/
int main(int argc, const char **argv)
{
    string url(argc >= 2 ? argv[1] : EXAMPLE_HOST);
    const string user(argc >= 3 ? argv[2] : EXAMPLE_USER);
    const string pass(argc >= 4 ? argv[3] : EXAMPLE_PASS);
    const string database(argc >= 5 ? argv[4] : EXAMPLE_DB);

    cout << "Connector/C++ tutorial framework..." << endl;
    cout << endl;

    try {

        /* INSERT TUTORIAL CODE HERE! */

    } catch (sql::SQLException &e) {
        /*
          MySQL Connector/C++ throws three different exceptions:

          - sql::MethodNotImplementedException (derived from sql::SQLException)
          - sql::InvalidArgumentException (derived from sql::SQLException)
          - sql::SQLException (derived from std::runtime_error)
        */
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        /* what() (derived from std::runtime_error) fetches error message */
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;

        return EXIT_FAILURE;
    }

    cout << "Done." << endl;
    return EXIT_SUCCESS;

	BaseApplication app;	// Program application
	app.Run();			// run program

	return 0;
}