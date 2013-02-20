#include "python_confor.h"

void thing::set(const std::string &msg) {
    this->msg = msg;
}

std::string thing::getMsg() {
    return this->msg;
}
