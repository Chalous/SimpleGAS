// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleDataAssets/DataAsset_InputConfig.h"
//#include "DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	// ������Ĭ��ֵNativeInputActions�е�����input tag action
	for (const FSimpleGASInputActionConfig& InputActionConfig : NativeInputActions)
	{
		// �����������tag==Ŀ��tag������tag��Ϊ�գ��ͷ���Ŀ��tag
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}
	return nullptr;
}
