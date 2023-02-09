// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/OraeGameHUD.h"

#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void AOraeGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AOraeGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerHUDWidgetClass)
	{
		UUserWidget* PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
		if (PlayerHUDWidget)
		{
			PlayerHUDWidget->AddToViewport();
		}
	}
}