#!/usr/bin/env -S tcc -run
//
// dumphex.c - C script to display hex output of binary file
//
//      usage: dumphex.c FILE [WORDSIZE] [ADDRESS]
//
// if ADDRESS is specified, that word will be highlighted on the display
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int32_t  main (int argc, char **argv)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare variables
    //
    FILE     *fptr                     = NULL;
    int32_t   byte                     = 0;
    uint32_t  flag                     = 0;
    uint32_t  offset                   = 0;
    uint32_t  match                    = -1;
    int32_t   wordsize                 = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Set matching address, if provided
    //
    if (argc                          >= 4)
    {
        match                          = strtol (argv[3], NULL, 16);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Determine wordsize
    //
    if (argc                          <  3)
    {
        wordsize                       = 1;
    }
    else
    {
        wordsize                       = atoi (argv[2]);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Determine FILE source (default to STDIN if no file specified)
    //
    if (argc                          == 1)
    {
        fprintf (stdout, "[dumphex] no arguments specified, defaulting to STDIN!\n");
        fptr                           = stdin;
    }
    else
    {
        fptr                           = fopen (argv[1], "r");
        if (fptr                      == NULL)
        {
            fprintf (stderr, "[error] could not open '%s' for reading!\n", argv[1]);
            exit (1);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Display offset header
    //
    fprintf (stdout, "               ");
    for (byte = 0; byte < wordsize; byte++)
    {
        fprintf (stdout, "   +%-6u   ", byte);
    }
    fprintf (stdout, "\n");

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Display initial offset
    //
    fprintf (stdout, "[0x%.8X]  ", offset / wordsize);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Continue until EOF or otherwise interrupted
    //
    byte                               = fgetc (fptr);
    offset                             = offset + 1;
    while (!feof (fptr))
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Display the byte
        //
        if (!feof (fptr))
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // If provided, highlight the matching word when we encounter it
            //
            if ((match                >= 0) &&
                (match                == ((offset - 1) / wordsize)))
            {
                fprintf (stdout, "\e[1;32m");
            }
            fprintf (stdout, "%.2X ", byte);

            ////////////////////////////////////////////////////////////////////////////
            //
            // Turn off highlighting once we are beyond the matching word
            //
            if ((match                >= 0) &&
                (match                == ((offset - 1) / wordsize)))
            {
                fprintf (stdout, "\e[m");
            }
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // If we are on a wordsize boundary, display an extra whitespace
        //
        if ((offset % wordsize)       == 0)
        {
            fprintf (stdout, " ");
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // If we are on a line boundary, display the current offset and generate a
        // newline (based on wordsize)
        //
        if ((offset % (wordsize * 4)) == 0)
        {
            fprintf (stdout, "[0x%.8X]\n", ((offset - 1)/ wordsize));
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Obtain the byte
        //
        byte                           = fgetc (fptr);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // If there is still more file to go
        //
        if (!feof (fptr))
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // If we are on a new line: display the current offset (based on wordsize)
            //
            if ((offset % (wordsize * 4)) == 0)
            {
                fprintf (stdout, "[0x%.8X]  ", (offset / wordsize));
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // Update the offset
            //
            offset                         = offset + 1;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Complete any incomplete last line
    //
    if ((offset % (wordsize * 4))         != 0)
    {
        flag                               = offset;
        while ((flag % (wordsize * 4))    != 0)
        {
            fprintf (stdout, "   ");
            if ((flag % wordsize)         == 0)
            {
                fprintf (stdout, " ");
            }
            flag                           = flag + 1;
        }

        fprintf (stdout, " [0x%.8X]\n", (offset / wordsize));
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Display offset footer
    //
    fprintf (stdout, "               ");
    for (byte = 0; byte < wordsize; byte++)
    {
        fprintf (stdout, "   +%-6u   ", byte);
    }
    fprintf (stdout, "\n");

    fclose (fptr);

    return (0);
}
