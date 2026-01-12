#!/usr/bin/env bash
### 
### bforth.sh - BASH-based FORTH interpreter
### 
########################################################################################

QUIT="false"

########################################################################################
##
## clearstack() - clear and initialize indicated stack
##
##         usage: clearstack STACKTYPE
##
## ... where `STACKTYPE` is one of "PARAMETER" or "RETURN"
##
function clearstack()
{
    echo -n
}

########################################################################################
##
## processinput() - obtain input and tokenize
##
function processinput()
{
    read input
}

########################################################################################
##
## interpret() - FORTH interpreter for current line of input
##
function interpret()
{
    echo "input: ${input}"
    qchk=$(echo "${input}" | grep -qio '^[Bb][Yy][Ee]$' && echo "true" || echo "false")
    if [ "${qchk}" = "true" ]; then
        QUIT="true"
    fi
}

########################################################################################
##
## The core
##
## : QUIT  BEGIN
##      CLEAR_RETURN_STACK
##      PROCESS_INPUT
##      INTERPRET
##      ." ok " CR
## AGAIN ;
##
input=
while [ "${QUIT}" = "false" ]; do
    clearstack RETURN
    processinput
    interpret
    [ "${QUIT}" = "false" ] && echo "ok"
done

exit 0
