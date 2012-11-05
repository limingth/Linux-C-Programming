#ifndef _CONFIG_H_
#define _CONFIG_H_

/*config file for finc*/

/* using long double data type. 
 * If system does not support long double or don't want to support double data type in script,
 * please close it.
 */
#define USING_DOUBLE

/* using float data type. 
 * If system does not support float or don't want to support float data type in script,
 * please close it.
 */
#define USING_FLOAT

#define USING_LONG

/* using array data type */
#define USING_ARRAY
/* using dynamic array type*/
#define USING_DYNAMIC_ARRAY

/* using package */
/*#define USING_PACKAGE*/

/*using file script*/
#define USING_FILE

/* language API*/
/* using string API */
#define USING_STRING_API
/* using array API */
#define USING_ARRAY_API
/* using hash API */
// #define USING_HASH_API

#define USING_UTIL

/* using finc token debug */
/*#define FINC_TOKEN_DEBUG*/

#ifdef WIN32
#ifdef USING_PACKAGE
#undefine USING_PACKAGE
#endif
#endif

#ifndef __DOOLOO__
#define kprintf printf
#endif

#ifdef __VXWORKS__
#endif

#ifdef __LINUX__
#endif

#endif
