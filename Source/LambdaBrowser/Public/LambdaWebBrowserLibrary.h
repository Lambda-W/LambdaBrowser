// Copyright Lambda Works, Samuel Metters 2019. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LambdaWebBrowserLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LAMBDABROWSER_API ULambdaWebBrowserLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

	// Returns a percent-encoded version of the passed in string compatible in web URLs.
	UFUNCTION(BlueprintPure, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		static FString EncodeStringToURL(FString URL);

	// Returns a decoded version of the percent-encoded passed in string.
	UFUNCTION(BlueprintPure, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		static FString DecodeURLToString(FString URL);

	// Checks whether or not the input string is an URL based on whether it contains specific url substring (ie: http, https, www).
	UFUNCTION(BlueprintPure, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		static bool isValidURL(FString URL);

	/* This function save the input content to a file. Each array element will be written as new line. Don't forget to add a file extension to the path (ex: ".txt" or ".html").
@param PathToFile	PathToFile	Path to the file to create (including the extension).
@param FileContent	FileContent	The file's content.
*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Save String Array To File", Keywords = "Lambda Browser"), Category = "Lambda Browser")
		static bool SaveStringArrayToFile(FString PathToFile, TArray<FString> FileContent);

	/* This function save the input content to a file. Don't forget to add a file extension to the path (ex: ".txt" or ".html").
@param PathToFile	PathToFile	Path to the file to create (including the extension).
@param FileContent	FileContent	The file's content.
*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Save String To File", Keywords = "Lambda Browser"), Category = "Lambda Browser")
		static bool SaveStringToFile(FString PathToFile, FString FileContent);
};
