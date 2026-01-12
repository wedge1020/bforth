#!/usr/bin/env bash
### 
### bforth.sh - BASH-based FORTH interpreter
### 
########################################################################################

########################################################################################
##
## Declare variables
##
QUIT="false"
SYSTEM="system"
SYSTEM_TYPE="vircon32"
CONFIG="conf"
MEMORY="${SYSTEM}/memory"
REGISTERS="${SYSTEM}/registers"
DICTIONARY="${MEMORY}/dictionary"
RETURNSTACK="${MEMORY}/return_stack"
PARAMETERSTACK="${MEMORY}/parameter_stack"

########################################################################################
##
## Load configuration
##
if [ -r "${CONFIG}/${SYSTEM_TYPE}.conf" ]; then
    source ${CONFIG}/${SYSTEM_TYPE}.conf
else
    echo "[ERROR] Could not read ${CONFIG}/${SYSTEM_TYPE}.conf" 1>&2
fi

########################################################################################
##
## init() - initialize FORTH system resources
##
function init()
{
    rm    -rf      ${SYSTEM}     ${REGISTERS}
    mkdir -p       ${SYSTEM}     ${MEMORY}    ${RETURNSTACK} ${PARAMETERSTACK}
    mkdir -p       ${DICTIONARY} ${REGISTERS}
    chmod -R  0700 ${SYSTEM}
}

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
    STACKTYPE="${1}"

    if [ "${STACKTYPE}" = "RETURN" ]; then
        rm -f ${RETURNSTACK}/*
        echo "${RETURNSTACKBASE}"                                   >  ${REGISTERS}/BP
        echo "${RETURNSTACKBASE}"                                   >  ${REGISTERS}/SP
        base=$(echo  "${RETURNSTACKBASE}"           | cut -d'x' -f2)
        base=$(echo  "obase=10; ibase=16; ${base}"  | bc -q)
        bound=$(echo "${RETURNSTACKBOUND}"          | cut -d'x' -f2)
        bound=$(echo "obase=10; ibase=16; ${bound}" | bc -q)

        for ((index=${bound}; index<${base}; index++)); do
            addr=$(echo "obase=16; ibase=10; ${index}" | bc -q)
            addr=$(printf "%.8X\n" "0x${addr}")
            ADDR="${RETURNSTACK}/${addr}"
            echo "00 00 00 00"                                      >  ${ADDR}
        done
        chmod -R 0600 ${RETURNSTACK}/*
    fi
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
init
while [ "${QUIT}" = "false" ]; do
    clearstack RETURN
    processinput
    interpret
    [ "${QUIT}" = "false" ] && echo "ok"
done

exit 0
