// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "SimpleGASBFL.generated.h"

struct FScalableFloat;
class USimpleASC;

UENUM()
enum class ESimpleConfirmType : uint8
{
	Yes,
	No
};

UCLASS()
class SIMPLEGAS_API USimpleGASBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static USimpleASC* NativeGetSimpleASCFromActor(AActor* InActor);
	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintPure, Category = "SimpleGASPlugin|FunctionLibrary", meta = (CompactNodeTitle = "Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.f);

	UFUNCTION(BlueprintCallable, Category = "SimpleGASPlugin|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "SimpleGASPlugin|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	UFUNCTION(BlueprintCallable, Category = "SimpleGASPlugin|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ESimpleConfirmType& OutConfirmType);
	
};
