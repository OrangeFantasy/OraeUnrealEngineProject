// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class AnimUtils
{
public:
	template <typename NotifyType>
	static NotifyType* FindNotifyByClass(UAnimMontage* Animation)
	{
		if (Animation)
		{
			const TArray<FAnimNotifyEvent>& NotifyEvents = Animation->Notifies;
			for (const FAnimNotifyEvent& NotifyEvent : NotifyEvents)
			{
				NotifyType* AnimNotify = Cast<NotifyType>(NotifyEvent.Notify);
				if (AnimNotify)
				{
					return AnimNotify;
				}
			}
		}

		return nullptr;
	}
};
