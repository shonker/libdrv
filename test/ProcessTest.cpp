#include "pch.h"
#include "ProcessTest.h"


//////////////////////////////////////////////////////////////////////////////////////////////////


NTSTATUS WINAPI HandleOneUserModule(_In_ PVOID DllBase, _In_ PUNICODE_STRING FullDllName, _In_opt_ PVOID Context)
{
    UNREFERENCED_PARAMETER(DllBase);
    UNREFERENCED_PARAMETER(FullDllName);
    UNREFERENCED_PARAMETER(Context);

    return STATUS_UNSUCCESSFUL;//����ö��
}


NTSTATUS HandleOneThread(_In_ PCLIENT_ID Cid, _In_opt_ PVOID Context)
{
    UNREFERENCED_PARAMETER(Cid);
    UNREFERENCED_PARAMETER(Context);

    return STATUS_UNSUCCESSFUL;//����ö��
}


NTSTATUS WINAPI HandleOneProcess(HANDLE UniqueProcessId, _In_opt_ PVOID Context)
/*
����������һ��ö�ٽ��̵Ļص�����������
*/
{
    UNREFERENCED_PARAMETER(Context);

    EnumThread(UniqueProcessId, HandleOneThread, NULL);
    EnumUserModule(UniqueProcessId, HandleOneUserModule, NULL);

    return STATUS_UNSUCCESSFUL;//����ö��
}


NTSTATUS EnumProcessTest(VOID)
/*
����������ö�ٽ��̵��÷���
*/
{
    return EnumProcess(HandleOneProcess, NULL);
}


//////////////////////////////////////////////////////////////////////////////////////////////////


NTSTATUS WINAPI HandleAllKernelModule(ULONG  numberOfModules, PAUX_MODULE_EXTENDED_INFO modules, _In_opt_ PVOID Context)
/*
ö���ں�ģ�飨EnumAllKernelModule����ʾ��������

ע�ͣ��˻ص�����ע��һ�Σ�����һ�Ρ�
*/
{
    UNREFERENCED_PARAMETER(Context);

    for (ULONG i = 0; i < numberOfModules; i++) {
        PUCHAR ModuleName = modules[i].FullPathName + modules[i].FileNameOffset;
        PVOID ImageBase = modules[i].BasicInfo.ImageBase;

    #if DBG 
        KdPrint(("ImageBase:%p, FullDllName:%s.\n", ImageBase, ModuleName));
    #else 
        DBG_UNREFERENCED_LOCAL_VARIABLE(ModuleName);
        DBG_UNREFERENCED_LOCAL_VARIABLE(ImageBase);
    #endif 
    }

    return STATUS_SUCCESS;
}


NTSTATUS PrintAllKernelModule()
/*
����һ��EnumAllKernelModule���÷������ӣ�ö���ں�ģ�顣
*/
{
    return EnumKernelModule(HandleAllKernelModule, NULL);
}


//////////////////////////////////////////////////////////////////////////////////////////////////