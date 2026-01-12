#!/usr/bin/env -S tcc -run
//
// dumphex.c - C script to display hex output of binary file
//
//      usage: dumphex.c FILE WORDSIZE
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
    FILE     *fptr         = NULL;
    int32_t   byte         = 0;
    uint32_t  offset       = 0;
    int32_t   wordsize     = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Determine wordsize
    //
    if (argc              <  3)
    {
        wordsize           = 1;
    }
    else
    {
        wordsize           = atoi (argv[2]);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Determine FILE source (default to STDIN if no file specified)
    //
    if (argc              == 1)
    {
        fprintf (stdout, "[dumphex] no arguments specified, defaulting to STDIN!\n");
        fptr               = stdin;
    }
    else
    {
        fptr               = fopen (argv[1], "r");
        if (fptr          == NULL)
        {
            fprintf (stderr, "[error] could not open '%s' for reading!\n", argv[1]);
            exit (1);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Display initial offset
    //
    fprintf (stdout, "[0x%.8X]  ", offset / wordsize);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Continue until EOF or otherwise interrupted
    //
    while (!feof (fptr))
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Obtain the byte, update the offset
        //
        byte               = fgetc (fptr);
        offset             = offset + 1;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Display the byte
        //
        fprintf (stdout, "%.2X ", byte);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // If we are on a wordsize boundary, display an extra whitespace
        //
        if ((offset % wordsize)  == 0)
        {
            fprintf (stdout, " ");
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // If we are on a line boundary, generate a newline and display the current
        // offset (based on wordsize)
        //
        if ((offset % (wordsize * 4)) == 0)
        {
			fprintf (stdout, "[0x%.8X]  ", ((offset - 1)/ wordsize));
            fprintf (stdout, "\n");
            if (byte      != -1)
            {
                fprintf (stdout, "[0x%.8X]  ", (offset / wordsize));
            }
        }
    }

    fclose (fptr);

    return (0);
}
