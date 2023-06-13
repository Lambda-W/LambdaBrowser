// Copyright Lambda Works, Samuel Metters 2019. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LambdaBrowser/Public/LambdaWebBrowser.h"
#include "LambdaBrowser_EditorLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LAMBDABROWSER_EDITOR_API ULambdaBrowser_EditorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintPure, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		static FString GetHomeURLFromSettings();

	UFUNCTION(BlueprintPure, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		static TArray<FLambdaURL> GetFavouritesFromSettings();

	UFUNCTION(BlueprintCallable, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		static void AddFavouritesToSettings(FLambdaURL Favourite);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		static void RemoveFavouritesFromSettigs(FLambdaURL Favourite);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		static void ClearFavouritesSettings();


};
