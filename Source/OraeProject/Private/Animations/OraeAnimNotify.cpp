// Fill out your copyright notice in the Description page of Project Settings.

#include "Animations/OraeAnimNotify.h"

void UOraeAnimNotify::Notify(
	USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	OnNotified.Broadcast(MeshComp);
}
