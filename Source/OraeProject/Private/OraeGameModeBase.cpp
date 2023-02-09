// Fill out your copyright notice in the Description page of Project Settings.

#include "OraeGameModeBase.h"
#include "Characters/OraeBaseCharacter.h"
#include "Characters/OraePlayerController.h"
#include "UI/OraeGameHUD.h"

AOraeGameModeBase::AOraeGameModeBase()
{
	DefaultPawnClass = AOraeBaseCharacter::StaticClass();
	PlayerControllerClass = AOraePlayerController::StaticClass();
	HUDClass = AOraeGameHUD::StaticClass();
}
