#include "domain.h"
#include <assert.h>

string Subject::get_name() const {
    return name;
}

int Subject::get_hours() const noexcept {
    return hours;
}

string Subject::get_type() const {
    return type;
}

string Subject::get_teacher() const {
    return teacher;
}
