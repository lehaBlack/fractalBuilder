//
// Created by epicfail on 03.03.16.
//

#ifndef GLLIB_ERRORS_H
#define GLLIB_ERRORS_H

#include <stdio.h>

//! @brief use in other files there are we throw something
#define THROW( type_error )     {\
                                    Error oh_now_I_have_an_error (type_error, __FILE__, __LINE__, "");\
                                    throw oh_now_I_have_an_error;\
                                }
#define WPRINT( type_error )    Error::print_warning (type_error, __FILE__, __LINE__, "");

//{-------------------------------------------------------------------
//! @brief enum with all errors
//!
//! @warning suffix W if warning
//}-------------------------------------------------------------------
enum error_type
{
    NULL_FILENAME,              //!<char * filename is NULL
    NULL_FILE,                  //!<file pointer is NULL
    NO_MEMORY_FOR_ALL_FILE,     //!<can't malloc memory for file
    NO_ALL_FILE_WAS_READ,       //!<file size != fread size
    NO_MODEL_IN_FILE,           //!<strtok can't find "\n"
    TOO_HIGH_VERT_INDEX,        //!<file doesn't contain verts
    TOO_HIGH_FACE_INDEX,        //!<file doesn't contain faces
    NO_VERTS_IN_FILE,           //!<index is more than number of verts in array
    NO_FACES_IN_FILE,           //!<index is more than number of faces in array
    NEGATIVE_COORDINATE,        //!<coordinate is less than zero
    TOO_BIG_COORDINATE,         //!<coordinate is bigger than image width or height
    INDEX_OUT_OF_BOUNDS,        //!<array index out of bounds
    ZERO_SIZE,                  //!<used a number which meaning is zero, but it's invalid value
    WZERO_COORDINATE,           //!<algorithm can work incorrectly
    ZERO_POINTER,               //!<pointer is zero
    WBIG_SIZE                   //!<extremely big size
};

//! @brief class to work with errors
class Error
{
public:

    //{-------------------------------------------------------------------
    //! @brief use it, when you are throwing an error
    //!
    //! @param err              some enum "error_type" meaning
    //! @param filename         name of the file where error occured
    //! @param line             line in the file where error occured
    //! @param pretty_function  name of the function where error occured
    //!
    //! @warning function write info into log_file__. If constructor can't open log_file__ all program aborting!
    //! @warning if !filename, line <= 0 or !pretty_function constructor write it in log_file__ and abort program
    //}-------------------------------------------------------------------
    Error (error_type err, const char * filename, int line, const char * pretty_function);

    ~Error ();

    //{-------------------------------------------------------------------
    //! @brief used when we catch error
    //!
    //! @param object of class Error
    //!
    //! @warning if !filename, line <= 0 or !pretty_function constructor write it in log_file__ and abort program
    //}-------------------------------------------------------------------
    Error (const Error & that);

    //{-------------------------------------------------------------------
    //! @brief print last error into log_file__
    //}-------------------------------------------------------------------
    void print_error ();

    //{-------------------------------------------------------------------
    //! @brief global function which print warnings in file
    //!
    //! @param err              error from enum error_type which can be regarded as a warning
    //! @param filename         name of the file where error occured
    //! @param line             line in the file where error occured
    //! @param pretty_function  name of the function where error occured
    //!
    //! @warning function write info into log_file__. If it can't open log_file__ all program aborting!
    //! @warning if !filename, line <= 0 or !pretty_function function write it in log_file__ and abort program
    //}-------------------------------------------------------------------
    static void print_warning (error_type err, const char * filename, int line, const char * pretty_function);

private:

    //{-------------------------------------------------------------------
    //! @brief file where the error occured
    //!
    //! @warning I'm so sorry, but I must use const size, because otherwise there is a cycle:(
    //}-------------------------------------------------------------------
    char filename_[256];

    //! @brief line where the error occured
    int line_;

    //{-------------------------------------------------------------------
    //! @brief function where the error occured
    //!
    //! @warning I'm so sorry, but I must use const size, because otherwise there is a cycle:(
    //}-------------------------------------------------------------------
    char function_[256];

    //! @brief number of error
    error_type error_;

    //{-------------------------------------------------------------------
    //! @brief class Error writing all in this file
    //!
    //! @warning log_file__ updates every session
    //}-------------------------------------------------------------------
    static FILE * log_file__;
};

#endif //GLLIB_ERRORS_H