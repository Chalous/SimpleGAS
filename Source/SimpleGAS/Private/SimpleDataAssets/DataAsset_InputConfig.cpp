// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleDataAssets/DataAsset_InputConfig.h"
//#include "DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	// 遍历类默认值NativeInputActions中的所有input tag action
	for (const FSimpleGASInputActionConfig& InputActionConfig : NativeInputActions)
	{
		// 如果遍历到的tag==目标tag，并且tag不为空，就返回目标tag
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}
	return nullptr;
}
