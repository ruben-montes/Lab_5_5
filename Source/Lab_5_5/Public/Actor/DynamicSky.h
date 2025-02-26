// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicSky.generated.h"

UCLASS()
class LAB_5_5_API ADynamicSky : public AActor
{
	GENERATED_BODY()

public:	
	ADynamicSky();

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	void HandleSunRotation();
	void HandleMoonRotation();
	void HandleSunMoonVisibility();
	bool IsDayTime();
	
	//  Offset time before dusk and after dawn that moon is providing still light
	const float MoonLightOffsetTime = 0.3f; 
	
	// Maps a Value in a float range (InMin, InMax) to degrees within a degrees range
	float MapRangeUnclamped(float Value, const float InMin, const float InMax, const float OutMin = 0.f, const float OutMax = -180.f);
	
	UPROPERTY(VisibleAnywhere)
	UDirectionalLightComponent* SunDirectionalLight;
	
	UPROPERTY(VisibleAnywhere)
    UDirectionalLightComponent* MoonDirectionalLight;

	UPROPERTY(VisibleAnywhere)
	USkyAtmosphereComponent* SkyAtmosphere;

	UPROPERTY(VisibleAnywhere)
	USkyLightComponent* SkyLight;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "24.0", UIMin = "0.0", UIMax = "24.0"), Category = "Time")
	float TimeOfDay = 9.f;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "5.0", ClampMax = "8.0", UIMin = "5.0", UIMax = "8.0"), Category = "Time")
	float DawnTime = 6.f;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "16.0", ClampMax = "20.0", UIMin = "16.0", UIMax = "20.0"), Category = "Time")
	float DuskTime = 18.f;



};
