// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DynamicSky.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/SkyLightComponent.h"

ADynamicSky::ADynamicSky()
{
	PrimaryActorTick.bCanEverTick = false;
	
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}
	
	SunDirectionalLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("SunDirectionalLight"));
	SunDirectionalLight->SetForwardShadingPriority(1);
	SunDirectionalLight->SetupAttachment(RootComponent);

	MoonDirectionalLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("MoonDirectionalLight"));
	MoonDirectionalLight->SetIntensity(0.1f);
	MoonDirectionalLight->SetupAttachment(RootComponent);
	
	SkyAtmosphere = CreateDefaultSubobject<USkyAtmosphereComponent>(TEXT("SkyAtmosphere"));
	SkyAtmosphere->SetupAttachment(RootComponent);

	SkyLight = CreateDefaultSubobject<USkyLightComponent>(TEXT("SkyLight"));
	SkyLight->SetupAttachment(RootComponent);

	/**
	 * TODO (rubenmontes): Para mejorar rendimiento desactivarlo, usar un Recapture Scene para recalcular manualmente iluminacion cuando cambie la fase del dia. De momento dejarlo asi.
	 */
	SkyLight->SetRealTimeCapture(true);
}

void ADynamicSky::OnConstruction(const FTransform& Transform)
{
	HandleSunRotation();
	HandleMoonRotation();
	HandleSunMoonVisibility();
}

void ADynamicSky::BeginPlay()
{
	Super::BeginPlay();
}

void ADynamicSky::HandleSunRotation()
{
	float SunRotationPitch = MapRangeUnclamped(TimeOfDay, DawnTime, DuskTime);
	FRotator SunRotation = FRotator(SunRotationPitch, 0.f, 0.f);
	SunDirectionalLight->SetWorldRotation(SunRotation);
}

void ADynamicSky::HandleMoonRotation()
{
	// Rotation before dusk
	float MoonRotationPitch = MapRangeUnclamped(TimeOfDay, DuskTime + MoonLightOffsetTime, 24.0f, -180.f, -90.f);
	FRotator MoonRotation = FRotator(MoonRotationPitch, 0.f, 0.f);
	MoonDirectionalLight->SetWorldRotation(MoonRotation);

	//Rotation before dawn
	MoonRotationPitch = MapRangeUnclamped(TimeOfDay, 0.f, DawnTime - MoonLightOffsetTime, -90.f, 0.f);
	MoonRotation = FRotator(MoonRotationPitch, 0.f, 0.f);
	MoonDirectionalLight->SetWorldRotation(MoonRotation);
}

void ADynamicSky::HandleSunMoonVisibility()
{
	const bool bIsDayTime = IsDayTime();
	SunDirectionalLight->SetVisibility(bIsDayTime);
	MoonDirectionalLight->SetVisibility(!bIsDayTime);
}

bool ADynamicSky::IsDayTime()
{
	return TimeOfDay > (DawnTime - MoonLightOffsetTime) && TimeOfDay < (DuskTime + MoonLightOffsetTime); 
}

float ADynamicSky::MapRangeUnclamped(float Value, float InMin, float InMax, float OutMin, float OutMax)
{
	return OutMin +  (Value - InMin) / (InMax - InMin) * (OutMax - OutMin);
}


