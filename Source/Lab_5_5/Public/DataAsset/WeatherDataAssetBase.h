// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeatherDataAssetBase.generated.h"

USTRUCT(BlueprintType)
struct FDirectionalLightSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float Intensity;

	UPROPERTY(EditDefaultsOnly)
	float SourceAngle;

	UPROPERTY(EditDefaultsOnly)
	float Temperature;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor LightColor;
};

USTRUCT(BlueprintType)
struct FSkyLightSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float IntensityScale;
};

USTRUCT(BlueprintType)
struct FSkyAtmosphereSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float MultiScattering;

	UPROPERTY(EditDefaultsOnly)
	float MieScatteringScale;

	UPROPERTY(EditDefaultsOnly)
	float MieAbsorptionScale;

	UPROPERTY(EditDefaultsOnly)
	float MieAnisotropy;
	
	UPROPERTY(EditDefaultsOnly)
	float AerialPerspectiveViewDistanceScale;
	
	UPROPERTY(EditDefaultsOnly)
	FLinearColor RayleighScattering;
};

USTRUCT(BlueprintType)
struct FExponentialHeightFogSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float ExtinctionScale;
	
	UPROPERTY(EditDefaultsOnly)
	FLinearColor EmissiveColor;
};

/**
 * 
 */
UCLASS()
class LAB_5_5_API UWeatherDataAssetBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FDirectionalLightSettings DirectionalLightSettings;

	UPROPERTY(EditDefaultsOnly)
	FSkyLightSettings SkyLightSettings;

	UPROPERTY(EditDefaultsOnly)
	FSkyAtmosphereSettings SkyAtmosphereSettings;
	
	UPROPERTY(EditDefaultsOnly)
	FExponentialHeightFogSettings ExponentialHeightFogSettings;
};
