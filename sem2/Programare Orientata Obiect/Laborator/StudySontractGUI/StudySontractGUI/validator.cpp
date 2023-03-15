#include "validator.h"
#include <string>
#include <exception>
#include <assert.h>
using std::string;

void Validator::validate_subject(const string& name, const string& hours, const string& type, const string& teacher) {

	string msg;
	if (name.size() == 0) msg += "Invalid name!\n";
	if (hours[0] == '0' || hours[0] == '-' || hours.size() == 0) {
		msg += "Invalid number of hours!\n";
	}
	else {
		for (unsigned i = 0; i < hours.size(); i++) {
			if (isdigit(hours[i]) == false) {
				msg += "Invalid number of hours!\n";
				break;
			}
		}
	}
	if (type.size() == 0) msg += "Invalid type!\n";
	if (teacher.size() == 0) msg += "Invalid teacher!\n";
	if (msg.size() > 0)
		throw ValidateException(msg);

}

void Validator::validate_string(const string& str) {
	if (str.size() == 0) {
		throw ValidateException("Invalid name!\n");
	}
}
