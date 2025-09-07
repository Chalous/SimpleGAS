// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_StartUpData.generated.h"

class USimpleASC;
class USimpleGameplayAbility;

USTRUCT(BlueprintType)
struct FSimpleAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"), Category = "InputAbility")
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputAbility")
	TSubclassOf<USimpleGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};

UCLASS()
class SIMPLEGAS_API UDataAsset_StartUpData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveToASC(USimpleASC* InASCToGive, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf <USimpleGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf <USimpleGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FSimpleAbilitySet> SimpleStartUpAbilitySets;

	void GrantAbilites(const TArray<TSubclassOf <USimpleGameplayAbility>>& InAbilitesToGive, USimpleASC* InASCToGive, int32 ApplyLevel = 1);

};
