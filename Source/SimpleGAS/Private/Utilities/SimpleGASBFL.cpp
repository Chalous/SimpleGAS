// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/SimpleGASBFL.h"
#include "ScalableFloat.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "SimpleComponents/SimpleASC.h"

USimpleASC* USimpleGASBFL::NativeGetSimpleASCFromActor(AActor* InActor)
{
	check(InActor);
	return CastChecked<USimpleASC>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

bool USimpleGASBFL::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	USimpleASC* ASC = NativeGetSimpleASCFromActor(InActor);
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

float USimpleGASBFL::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

void USimpleGASBFL::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	USimpleASC* ASC = NativeGetSimpleASCFromActor(InActor);
	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void USimpleGASBFL::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	USimpleASC* ASC = NativeGetSimpleASCFromActor(InActor);
	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

void USimpleGASBFL::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ESimpleConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? ESimpleConfirmType::Yes : ESimpleConfirmType::No;
}
