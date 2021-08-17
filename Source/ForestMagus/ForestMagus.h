#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(ForestMagus, Log, All);

#define FM_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

#define FM_S(Verbosity) UE_LOG(ForestMagus, Verbosity, TEXT("%s"), *FM_CALLINFO)

#define FMLOG(Verbosity,Format, ...) UE_LOG(ForestMagus, Verbosity, TEXT("%s %s"), *FM_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

// ��ũ�θ� �߰� : ���ǽ��� �ƴ� ��쿡 ���� �α� �Ѹ��� �Լ� ��ȯ
#define FMCHECK(Expr, ...){if(!(Expr)) {FMLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}
