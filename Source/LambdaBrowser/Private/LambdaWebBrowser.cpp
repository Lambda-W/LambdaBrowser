// Copyright Lambda Works, Samuel Metters 2019. All rights reserved.
// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "LambdaWebBrowser.h"

#include "CoreMinimal.h"
#include "Async/Async.h"

#include "WebBrowserModule.h"
#include "IWebBrowserCookieManager.h"

#include "WebBrowser.h"
#include "SWebBrowser.h"

ULambdaWebBrowser::ULambdaWebBrowser(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsVariable = true;
}

void ULambdaWebBrowser::Previous()
{
	if (WebBrowserWidget)
	{
		if (WebBrowserWidget->CanGoBack())
		{
			WebBrowserWidget->GoBack();
		}
	}
}

void ULambdaWebBrowser::Next()
{
	if (WebBrowserWidget)
	{
		if (WebBrowserWidget->CanGoForward())
		{
			WebBrowserWidget->GoForward();
		}
	}
}

bool ULambdaWebBrowser::IsLoading()
{
	if (WebBrowserWidget)
	{
			return WebBrowserWidget->IsLoading();
	}

	return false;
}

void ULambdaWebBrowser::StopLoading()
{
	if (WebBrowserWidget)
	{
		return WebBrowserWidget->StopLoad();
	}
}

void ULambdaWebBrowser::Refresh()
{
	if (WebBrowserWidget)
	{
		return WebBrowserWidget->Reload();
	}
}

void ULambdaWebBrowser::ClearCache()
{
	IWebBrowserSingleton* WebBrowserSingleton = IWebBrowserModule::Get().GetSingleton();
	if (WebBrowserSingleton)
	{
		TSharedPtr<IWebBrowserCookieManager> CookieManager = WebBrowserSingleton->GetCookieManager();
		if (CookieManager.IsValid())
		{
			CookieManager->DeleteCookies();

			ClearHistory();
		}
	}
}

FString ULambdaWebBrowser::GetInitialURL()
{
	return InitialURL;
}

TArray<FLambdaURL> ULambdaWebBrowser::GetBrowserHistory()
{
	return BrowserHistory;
}

void ULambdaWebBrowser::GetSource(const FOnWebSourceRetrieved& Callback)
{
	FOnWebSourceRetrieved Delegate;
	Delegate = Callback;

	TFunction<void(const FString& content)>ProcessSource = [Delegate](const FString& content) {

		FString str(content);
		Delegate.ExecuteIfBound(str);
	};

	WebBrowserWidget->GetSource(ProcessSource);

}

void ULambdaWebBrowser::ClearHistory()
{
	BrowserHistory.Empty(0);
}

TSharedRef<SWidget> ULambdaWebBrowser::RebuildWidget()
{
	TSharedRef<SWidget> ReturnValue = Super::RebuildWidget();

	// Adds the current URL to history array everytime a new URL is loaded.
	OnUrlChanged.AddDynamic(this, &ULambdaWebBrowser::AddToBrowserHistory);

	return ReturnValue;
}

void ULambdaWebBrowser::AddToBrowserHistory(const FText& Text)
{
	// The idea here would have been to wait until the page is loaded to add the URL so we can get
	// the page title. However the OnLoadCompleted delegate was made private (why???). So we'll 
	// only pass in the URL with no title.

	FLambdaURL Item = FLambdaURL("", Text.ToString(), FDateTime::Now());
	BrowserHistory.AddUnique(Item);
}


