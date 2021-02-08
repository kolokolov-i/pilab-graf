#pragma once

#include <string>

namespace IPF
{
    // Exception
    struct Invalid_Parameter
    {
        std::string message;
        Invalid_Parameter(std::string msg)
        {
            message = msg;
        }
    };
    
    // Exception
    struct Image_File_Error
    {
        std::string message;
        Image_File_Error(std::string msg)
        {
            message = msg;
        }
    };
}