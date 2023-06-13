// Copyright Lambda Works, Samuel Metters 2019. All rights reserved.
// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WebBrowser.h"
#include "LambdaWebBrowser.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnWebSourceRetrieved, const FString, Source);

USTRUCT(BlueprintType)
struct LAMBDABROWSER_API FLambdaURL
{
	GENERATED_BODY()

	// The URL's web page title.
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Lambda Browser")
		FString Title;
	// The URL associated with this item.
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Lambda Browser")
		FString URL;
	// Time the URL was accessed.
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Lambda Browser")
		FDateTime Accessed;

	FLambdaURL()
	{
		Title = "Undefined";
		URL = "Undefined";
		Accessed = FDateTime::MinValue();
	}

	FLambdaURL(FString inTitle, FString inURL, FDateTime inAccessed)
	{
		Title = inTitle;
		URL = inURL;
		Accessed = inAccessed;
	}

	inline bool operator==(const FLambdaURL& other) const
	{
		return Title == other.Title && URL == other.URL;
	}
};

/* These will become the output pins for the GetSource latent action function. */
UENUM()
enum class EGetSourcePins : uint8
{
	Pending UMETA(DisplayName = "Pending"),
	OnComplete UMETA(DisplayName = "On Complete")
};


UCLASS(BlueprintType)
class LAMBDABROWSER_API ULambdaWebBrowser : public UWebBrowser
{
	GENERATED_UCLASS_BODY()



public: 
	// Loads the previous URL from the history.
	UFUNCTION(BlueprintCallable, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		void Previous();

	// Loads the next URL if any from the history.
	UFUNCTION(BlueprintCallable, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		void Next();

	// Returns whether the current URL is loading or not.
	UFUNCTION(BlueprintPure, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		bool IsLoading();

	// Stops loading the current URL.
	UFUNCTION(BlueprintCallable, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		void StopLoading();

	// Reloads the current URL.
	UFUNCTION(BlueprintCallable, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		void Refresh();

	// Clears webcache (cookies and history).
	UFUNCTION(BlueprintCallable, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		void ClearCache();

	// Returns the URL that was set as initial URL.
	UFUNCTION(BlueprintPure, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		FString GetInitialURL();

	// Returns the browser history for this session.
	UFUNCTION(BlueprintPure, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		TArray<FLambdaURL> GetBrowserHistory();

	// Returns the source code for this web page as a string.
	UFUNCTION(BlueprintCallable, meta = (Keywords = "Lambda Web Browser"), Category = "Lambda Browser")
		void GetSource(const FOnWebSourceRetrieved& Callback);

protected:

	// Overriding RebuildWidget to bind delegates.
	virtual TSharedRef<SWidget> RebuildWidget() override;

	// Clears the history array.
	UFUNCTION()
	void ClearHistory();

	// Adds an URL to the history array.
	UFUNCTION()
	void AddToBrowserHistory(const FText& Text);

	// History arry
	TArray<FLambdaURL> BrowserHistory;
};
