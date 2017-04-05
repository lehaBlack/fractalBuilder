//
// Created by epicfail on 15.03.16.
//

#include <stdlib.h>
#include <string.h>
#include "Errors.h"

#define ENUM_TO_STR( err )      err

FILE * Error::log_file__ = NULL;

Error::Error (error_type err, const char * filename, int line, const char * pretty_function)
{
    log_file__ = fopen ("error_log.txt", "wb");
    if (!log_file__)
    {
        printf ("sorry, but I can't open log file in %s line: %d. Bye\n", __FILE__, __LINE__);
        exit (1);
    }

    if (!filename)
    {
        fprintf (log_file__, "!--FILENAME IS NULL\t%s\t%d\n", __FILE__, __LINE__);
        exit (1);
    }
    if (line <= 0)
    {
        fprintf (log_file__, "!--LINE <= 0\t%s\t%d\n", __FILE__, __LINE__);
        exit (1);
    }
    if (!pretty_function)
    {
        fprintf (log_file__, "!--PRETTY_FUNCTION IS NULL\t%s\t%d\n", __FILE__, __LINE__);
        exit (1);
    }
    fflush (log_file__);

    error_ = err;
    line_  = line;

    size_t filename_len = strlen (filename);
    if (filename_len < strlen (filename_))
        filename = &filename[filename_len - strlen (filename_)];
    strncpy (filename_, filename, filename_len);

    strncpy (function_, pretty_function, strlen (pretty_function));

    fprintf (log_file__, "error occured %u |\t%s |\t%d |\t%s\n", ENUM_TO_STR (error_), filename_, line_, function_);
    fflush (log_file__);

}

Error::~Error ()
{
    error_ = (error_type) 0xBADF00D;
    line_  = 0xBADF00D;
    for (size_t i = 0; i < strlen (filename_); i++)
        filename_[i] = '\0';
    for (size_t i = 0; i < strlen (function_); i++)
        function_[i] = '\0';

    fclose (log_file__);
}

Error::Error (const Error & that)
{
    if (!that.filename_)
    {
        fprintf (log_file__, "!--that.filename_ is NULL\t%s\t%d\t%s\n", filename_, line_, function_);
        exit(1);
    }
    if (!that.function_)
    {
        fprintf (log_file__, "!--that.function_ is NULL\t%s\t%d\t%s\n", filename_, line_, function_);
        exit (1);
    }
    if (that.line_ <= 0)
    {
        fprintf (log_file__, "!--that.line_ <= 0\t%s\t%d\t%s\n", filename_, line_, function_);
        exit (1);
    }
    fflush (log_file__);

    this->error_ = that.error_;
    this->line_  = that.line_;
    strncpy (this->function_, that.function_, strlen (that.function_));
    strncpy (this->filename_, that.filename_, strlen (that.filename_));
}

void Error::print_error ()
{
    printf ("error printing: %u |\t%s |\t%d |\t%s\n", ENUM_TO_STR (error_), filename_, line_, function_);
}

void Error::print_warning (error_type err, const char * filename, int line, const char * pretty_function)
{
    log_file__ = fopen ("error_log.txt", "wb");
    if (!log_file__)
    {
        printf ("sorry, but I can't open log file in %s line: %d. Bye\n", __FILE__, __LINE__);
        exit (1);
    }

    if (!filename)
    {
        fprintf (log_file__, "!--FILENAME IS NULL\t%s\t%d\n", __FILE__, __LINE__);
        exit (1);
    }
    if (line <= 0)
    {
        fprintf (log_file__, "!--LINE <= 0\t%s\t%d\n", __FILE__, __LINE__);
        exit (1);
    }
    /*if (!pretty_function)
    {
        fprintf (log_file__, "!--PRETTY_FUNCTION IS NULL\t%s\t%d\n", __FILE__, __LINE__);
        exit (1);
    }*/

    fprintf (log_file__, "warning occured %u |\t%s |\t%d |\t%s\n", ENUM_TO_STR (err), filename, line, pretty_function);
    fflush (log_file__);
    fclose (log_file__);
}
