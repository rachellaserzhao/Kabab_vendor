// file:        interpreterprivate.h
// author:      Jack S-J, Geoff T
// date:        2017-10-11
// description: private methods for Interpreter
//              Declare and implement your private functions here.
//              Leave blank if you have no private functions to implement.
//              No includes or qualification necessary. Example below:

#ifndef _INTERPRETERPRIVATE_H_
#define _INTERPRETERPRIVATE_H_

#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

bool Operator(std::string item){
    
    return (item == "+" || item == "-" ||
            item == "*" || item == "/" ||
            item == "^" || item == "RQ"||
            item == "PRINT");
}



#endif