/*
 * File:   util.h
 * Author: Russell Lewis
 *
 * Purpose: Declarations for the functions implemented in util.c
 */


#ifndef _UTIL_H__INCLUDED_
#define _UTIL_H__INCLUDED_


char **extendArray(char **oldArray, int oldLen, int newLen);
void   sortArray  (char **array,    int len);


#endif
