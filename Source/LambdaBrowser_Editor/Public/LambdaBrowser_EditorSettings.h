// Copyright Lambda Works, Samuel Metters 2019. All rights reserved.
// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LambdaBrowser/Public/LambdaWebBrowser.h"
#include "LambdaBrowser_EditorSettings.generated.h"

/**
 * 
 */
UCLASS(config = LambdaBrowser, defaultconfig)
class LAMBDABROWSER_EDITOR_API ULambdaBrowser_EditorSettings : public UObject
{
	GENERATED_UCLASS_BODY()

		/* The URL to load when first opening the browser or when pressing "Home". */
		UPROPERTY(EditAnywhere, config, Category = General)
		FString HomeURL;

	/* The list of saved URL. This only concerns the editor browser. Runtime browser favourites aren't saved here. */
	UPROPERTY(EditAnywhere, config, Category = General)
		TArray<FLambdaURL> Favourites;

	/* Wether or not to show the Web Browser button in the toolbar. (Require a restart). */
	UPROPERTY(EditAnywhere, config, Category = General)
		bool ShowToolbarButton;
	
};
