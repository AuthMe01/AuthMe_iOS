/* Copyright (c) OASIS Open 2016. All Rights Reserved./
 * /Distributed under the terms of the OASIS IPR Policy,
 * [http://www.oasis-open.org/policies-guidelines/ipr], AS-IS, WITHOUT ANY
 * IMPLIED OR EXPRESS WARRANTY; there is no warranty of MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE or NONINFRINGEMENT of the rights of others.
 */
        
/* Latest version of the specification:
 * http://docs.oasis-open.org/pkcs11/pkcs11-base/v2.40/pkcs11-base-v2.40.html
 */

/* See top of pkcs11.h for information about the macros that
 * must be defined and the structure-packing conventions that
 * must be set before including this file.
 */

#ifndef _PKCS11T_H_
#define _PKCS11T_H_ 1
#define CKR_OK                                0x00000000UL
#define CKR_CANCEL                            0x00000001UL
#define CKR_HOST_MEMORY                       0x00000002UL
#define CKR_SLOT_ID_INVALID                   0x00000003UL

#define CKR_GENERAL_ERROR                     0x00000005UL
#define CKR_FUNCTION_FAILED                   0x00000006UL

#define CKR_ARGUMENTS_BAD                     0x00000007UL
#define CKR_NO_EVENT                          0x00000008UL
#define CKR_NEED_TO_CREATE_THREADS            0x00000009UL
#define CKR_CANT_LOCK                         0x0000000AUL

#define CKR_ATTRIBUTE_READ_ONLY               0x00000010UL
#define CKR_ATTRIBUTE_SENSITIVE               0x00000011UL
#define CKR_ATTRIBUTE_TYPE_INVALID            0x00000012UL
#define CKR_ATTRIBUTE_VALUE_INVALID           0x00000013UL

#define CKR_ACTION_PROHIBITED                 0x0000001BUL

#define CKR_DATA_INVALID                      0x00000020UL
#define CKR_DATA_LEN_RANGE                    0x00000021UL
#define CKR_DEVICE_ERROR                      0x00000030UL
#define CKR_DEVICE_MEMORY                     0x00000031UL
#define CKR_DEVICE_REMOVED                    0x00000032UL
#define CKR_ENCRYPTED_DATA_INVALID            0x00000040UL
#define CKR_ENCRYPTED_DATA_LEN_RANGE          0x00000041UL
#define CKR_FUNCTION_CANCELED                 0x00000050UL
#define CKR_FUNCTION_NOT_PARALLEL             0x00000051UL

#define CKR_FUNCTION_NOT_SUPPORTED            0x00000054UL

#define CKR_KEY_HANDLE_INVALID                0x00000060UL

#define CKR_KEY_SIZE_RANGE                    0x00000062UL
#define CKR_KEY_TYPE_INCONSISTENT             0x00000063UL

#define CKR_KEY_NOT_NEEDED                    0x00000064UL
#define CKR_KEY_CHANGED                       0x00000065UL
#define CKR_KEY_NEEDED                        0x00000066UL
#define CKR_KEY_INDIGESTIBLE                  0x00000067UL
#define CKR_KEY_FUNCTION_NOT_PERMITTED        0x00000068UL
#define CKR_KEY_NOT_WRAPPABLE                 0x00000069UL
#define CKR_KEY_UNEXTRACTABLE                 0x0000006AUL

#define CKR_MECHANISM_INVALID                 0x00000070UL
#define CKR_MECHANISM_PARAM_INVALID           0x00000071UL

#define CKR_OBJECT_HANDLE_INVALID             0x00000082UL
#define CKR_OPERATION_ACTIVE                  0x00000090UL
#define CKR_OPERATION_NOT_INITIALIZED         0x00000091UL
#define CKR_PIN_INCORRECT                     0x000000A0UL
#define CKR_PIN_INVALID                       0x000000A1UL
#define CKR_PIN_LEN_RANGE                     0x000000A2UL

#define CKR_PIN_EXPIRED                       0x000000A3UL
#define CKR_PIN_LOCKED                        0x000000A4UL

#define CKR_SESSION_CLOSED                    0x000000B0UL
#define CKR_SESSION_COUNT                     0x000000B1UL
#define CKR_SESSION_HANDLE_INVALID            0x000000B3UL
#define CKR_SESSION_PARALLEL_NOT_SUPPORTED    0x000000B4UL
#define CKR_SESSION_READ_ONLY                 0x000000B5UL
#define CKR_SESSION_EXISTS                    0x000000B6UL

#define CKR_SESSION_READ_ONLY_EXISTS          0x000000B7UL
#define CKR_SESSION_READ_WRITE_SO_EXISTS      0x000000B8UL

#define CKR_SIGNATURE_INVALID                 0x000000C0UL
#define CKR_SIGNATURE_LEN_RANGE               0x000000C1UL
#define CKR_TEMPLATE_INCOMPLETE               0x000000D0UL
#define CKR_TEMPLATE_INCONSISTENT             0x000000D1UL
#define CKR_TOKEN_NOT_PRESENT                 0x000000E0UL
#define CKR_TOKEN_NOT_RECOGNIZED              0x000000E1UL
#define CKR_TOKEN_WRITE_PROTECTED             0x000000E2UL
#define CKR_UNWRAPPING_KEY_HANDLE_INVALID     0x000000F0UL
#define CKR_UNWRAPPING_KEY_SIZE_RANGE         0x000000F1UL
#define CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT  0x000000F2UL
#define CKR_USER_ALREADY_LOGGED_IN            0x00000100UL
#define CKR_USER_NOT_LOGGED_IN                0x00000101UL
#define CKR_USER_PIN_NOT_INITIALIZED          0x00000102UL
#define CKR_USER_TYPE_INVALID                 0x00000103UL

#define CKR_USER_ANOTHER_ALREADY_LOGGED_IN    0x00000104UL
#define CKR_USER_TOO_MANY_TYPES               0x00000105UL

#define CKR_WRAPPED_KEY_INVALID               0x00000110UL
#define CKR_WRAPPED_KEY_LEN_RANGE             0x00000112UL
#define CKR_WRAPPING_KEY_HANDLE_INVALID       0x00000113UL
#define CKR_WRAPPING_KEY_SIZE_RANGE           0x00000114UL
#define CKR_WRAPPING_KEY_TYPE_INCONSISTENT    0x00000115UL
#define CKR_RANDOM_SEED_NOT_SUPPORTED         0x00000120UL

#define CKR_RANDOM_NO_RNG                     0x00000121UL

#define CKR_DOMAIN_PARAMS_INVALID             0x00000130UL

#define CKR_CURVE_NOT_SUPPORTED               0x00000140UL

#define CKR_BUFFER_TOO_SMALL                  0x00000150UL
#define CKR_SAVED_STATE_INVALID               0x00000160UL
#define CKR_INFORMATION_SENSITIVE             0x00000170UL
#define CKR_STATE_UNSAVEABLE                  0x00000180UL

#define CKR_CRYPTOKI_NOT_INITIALIZED          0x00000190UL
#define CKR_CRYPTOKI_ALREADY_INITIALIZED      0x00000191UL
#define CKR_MUTEX_BAD                         0x000001A0UL
#define CKR_MUTEX_NOT_LOCKED                  0x000001A1UL

#define CKR_NEW_PIN_MODE                      0x000001B0UL
#define CKR_NEXT_OTP                          0x000001B1UL

#define CKR_EXCEEDED_MAX_ITERATIONS           0x000001B5UL
#define CKR_FIPS_SELF_TEST_FAILED             0x000001B6UL
#define CKR_LIBRARY_LOAD_FAILED               0x000001B7UL
#define CKR_PIN_TOO_WEAK                      0x000001B8UL
#define CKR_PUBLIC_KEY_INVALID                0x000001B9UL

#define CKR_FUNCTION_REJECTED                 0x00000200UL

#define CKR_VENDOR_DEFINED                    0x80000000UL


#endif /* _PKCS11T_H_ */
