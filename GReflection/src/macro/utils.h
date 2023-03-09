#pragma once

//#define MM_CONCAT__( a, b )     a ## b
//#define MM_CONCAT_( a, b )      MM_CONCAT__( a, b )
//#define MM_CONCAT( a, b )       MM_CONCAT_( a, b )
//
//#define MM_INVOKE( macro, args ) macro args
//#define MM_INVOKE_B( macro, args ) macro args
//
//#define MM_APPLY_1( macroname, content, a1 ) \
//    MM_INVOKE_B( macroname, (content, a1) )
//
//#define MM_APPLY_2( macroname, content, a1, a2 ) \
//    MM_INVOKE_B( macroname, (content, a1) ) \
//    MM_APPLY_1( macroname, content, a2 )
//
//#define MM_APPLY_3( macroname, content, a1, a2, a3 ) \
//    MM_INVOKE_B( macroname, (content, a1) ) \
//    MM_APPLY_2( macroname, content, a2, a3 )
//
//#define MM_APPLY_4( macroname, content, a1, a2, a3, a4 ) \
//    MM_INVOKE_B( macroname, (content, a1) ) \
//    MM_APPLY_3( macroname, content, a2, a3, a4 )
//
//#define MM_APPLY_5( macroname, content, a1, a2, a3, a4, a5 ) \
//    MM_INVOKE_B( macroname, (content, a1) ) \
//    MM_APPLY_4( macroname, content, a2, a3, a4, a5 )
//
//#define MM_APPLY_6( macroname, content, a1, a2, a3, a4, a5, a6 ) \
//    MM_INVOKE_B( macroname, (content, a1) ) \
//    MM_APPLY_5( macroname, content, a2, a3, a4, a5, a6 )
//
//#define MM_APPLY_7( macroname, content, a1, a2, a3, a4, a5, a6, a7 ) \
//    MM_INVOKE_B( macroname, (content, a1) ) \
//    MM_APPLY_6( macroname, content, a2, a3, a4, a5, a6, a7 )
//
//#define MM_APPLY_8( macroname, content, a1, a2, a3, a4, a5, a6, a7, a8 ) \
//    MM_INVOKE_B( macroname, (content, a1) ) \
//    MM_APPLY_7( macroname, content, a2, a3, a4, a5, a6, a7, a8 )
//
//#define MM_APPLY_9( macroname, content, a1, a2, a3, a4, a5, a6, a7, a8, a9 ) \
//    MM_INVOKE_B( macroname, (content, a1) ) \
//    MM_APPLY_8( macroname, content, a2, a3, a4, a5, a6, a7, a8, a9 )
//
//#define MM_APPLY_10( macroname, content, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10 ) \
//    MM_INVOKE_B( macroname, (content, a1) ) \
//    MM_APPLY_9( macroname, content, a2, a3, a4, a5, a6, a7, a8, a9, a10 )
//
//#define EXPAND( x ) x
//#define PP_NARG(...) EXPAND(PP_ARG_N(__VA_ARGS__,\
//	63, 62, 61, 60,                                   \
//	59, 58, 57, 56, 55, 54, 53, 52, 51, 50,           \
//	49, 48, 47, 46, 45, 44, 43, 42, 41, 40,           \
//	39, 38, 37, 36, 35, 34, 33, 32, 31, 30,           \
//	29, 28, 27, 26, 25, 24, 23, 22, 21, 20,           \
//	19, 18, 17, 16, 15, 14, 13, 12, 11, 10,           \
//	9,  8,  7,  6,  5,  4,  3,  2,  1, 0))
//#define PP_ARG_N( \
//	_1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, _10,  \
//	_11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
//	_21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
//	_31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
//	_41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
//	_51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
//	_61, _62, _63, N, ...) N
//
//#define MM_APPLY( macroname, content, ... ) \
//    MM_INVOKE( \
//        MM_CONCAT( MM_APPLY_, PP_NARG( __VA_ARGS__ ) ), \
//        ( macroname, content, __VA_ARGS__ ) \
//        )
//
//#define MM_REMOVE_LAST_COMMA_1( end )
//#define MM_REMOVE_LAST_COMMA_2( a1, end ) a1
//#define MM_REMOVE_LAST_COMMA_3( a1, a2, end ) a1 , a2
//#define MM_REMOVE_LAST_COMMA_4( a1, a2, a3, end ) a1, a2, a3
//#define MM_REMOVE_LAST_COMMA_5( a1, a2, a3, a4, end ) a1, a2, a3, a4
//#define MM_REMOVE_LAST_COMMA_6( a1, a2, a3, a4, a5, end ) a1, a2, a3, a4, a5  
//#define MM_REMOVE_LAST_COMMA_7( a1, a2, a3, a4, a5, a6, end ) a1, a2, a3, a4, a5, a6
//#define MM_REMOVE_LAST_COMMA_8( a1, a2, a3, a4, a5, a6, a7, end ) a1, a2, a3, a4, a5, a6, a7
//#define MM_REMOVE_LAST_COMMA_9( a1, a2, a3, a4, a5, a6, a7, a8, end ) a1, a2, a3, a4, a5, a6, a7, a8
//#define MM_REMOVE_LAST_COMMA_10( a1, a2, a3, a4, a5, a6, a7, a8, a9, end ) a1, a2, a3, a4, a5, a6, a7, a8, a9
//#define MM_REMOVE_LAST_COMMA_11( a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, end ) a1, a2, a3, a4, a5, a6, a7, a8, a9, a10

//#define PP_NARG(...) \
//	PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
//
//#define PP_NARG_(...) \
//	PP_ARG_N(__VA_ARGS__)
//
//#define PP_ARG_N( \
//_1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
//_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
//_21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
//_31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
//_41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
//_51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
//_61,_62,_63, N, ...) N
//
//#define PP_RSEQ_N() \
//63,62,61,60, \
//59,58,57,56,55,54,53,52,51,50, \
//49,48,47,46,45,44,43,42,41,40, \
//39,38,37,36,35,34,33,32,31,30, \
//29,28,27,26,25,24,23,22,21,20, \
//19,18,17,16,15,14,13,12,11,10, \
//9,8,7,6,5,4,3,2,1,0

#define PARENS ()

#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define FOR_EACH(macro, content, ...) \
  __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, content, __VA_ARGS__)) )

#define FOR_EACH_HELPER(macro, content, a1, ...) \
  macro(content, a1) __VA_OPT__(,) \
  __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, content, __VA_ARGS__))

#define FOR_EACH_AGAIN() FOR_EACH_HELPER
