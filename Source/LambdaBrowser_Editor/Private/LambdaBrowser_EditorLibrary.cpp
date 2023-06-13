// Copyright Lambda Works, Samuel Metters 2019. All rights reserved.


#include "LambdaBrowser_EditorLibrary.h"
#include "LambdaBrowser_EditorSettings.h"
#include "LambdaBrowser/Public/LambdaWebBrowser.h"

#include "ISettingsModule.h"


FString ULambdaBrowser_EditorLibrary::GetHomeURLFromSettings()
{
	return GetDefault<ULambdaBrowser_EditorSettings>()->HomeURL;
}

TArray<FLambdaURL> ULambdaBrowser_EditorLibrary::GetFavouritesFromSettings()
{
	return GetDefault<ULambdaBrowser_EditorSettings>()->Favourites;
}

void ULambdaBrowser_EditorLibrary::AddFavouritesToSettings(FLambdaURL Favourite)
{
	ULambdaBrowser_EditorSettings* LambdaBrowser_Settings = GetMutableDefault<ULambdaBrowser_EditorSettings>();
	LambdaBrowser_Settings->Favourites.Add(Favourite);
	LambdaBrowser_Settings->SaveConfig();
	return;
}

void ULambdaBrowser_EditorLibrary::RemoveFavouritesFromSettigs(FLambdaURL Favourite)
{
	ULambdaBrowser_EditorSettings* LambdaBrowser_Settings = GetMutableDefault<ULambdaBrowser_EditorSettings>();
	LambdaBrowser_Settings->Favourites.Remove(Favourite);
	LambdaBrowser_Settings->SaveConfig();
	return;
}

void ULambdaBrowser_EditorLibrary::ClearFavouritesSettings()
{
	ULambdaBrowser_EditorSettings* LambdaBrowser_Settings = GetMutableDefault<ULambdaBrowser_EditorSettings>();
	LambdaBrowser_Settings->Favourites.Empty(0);
	LambdaBrowser_Settings->SaveConfig();
	return;
}
