/**
 * @file ntfuncs.h
 * @author dragonero2704
 * @brief
 * @version 0.1
 * @date 2023-11-10
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <Windows.h>
#include <winternl.h>
#include <ntdef.h>

typedef CLIENT_ID* PCLIENT_ID;
// NtOpenProcess
typedef NTSTATUS(NTAPI *NtOpenProcess)(
    OUT PHANDLE ProcessHandle,
    IN ACCESS_MASK AccessMask,
    IN POBJECT_ATTRIBUTES ObjectAttributes,
    IN PCLIENT_ID ClientId);

typedef NTSTATUS(NTAPI *NtCreateProcess)(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ParentProcess,
    _In_ BOOLEAN InheritObjectTable,
    _In_opt_ HANDLE SectionHandle,
    _In_opt_ HANDLE DebugPort,
    _In_opt_ HANDLE TokenHandle);