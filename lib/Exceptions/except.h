#ifndef HINPA_EXCEPT_H
#define HINPA_EXCEPT_H


#include <stdexcept>
#include <string>

#define VerboseNotImplemented NotImplemented(std::string() + "FUNCTION NOT IMPLEMENTED IN FILE: "  + __FILE__ + " IN FUNCTION: " + __func__ + " ON LINE: " + std::to_string(__LINE__));


class NotImplemented : public std::logic_error
{
public: 
    NotImplemented() : std::logic_error("Function has not been implemented yet") {} ;
    NotImplemented(std::string s) : std::logic_error(s) {} ;

};


#endif
