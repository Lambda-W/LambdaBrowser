// Copyright Lambda Works, Samuel Metters 2019. All rights reserved.
// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LambdaBrowser_Editor.h"
#include "LambdaBrowser_EditorStyle.h"
#include "LambdaBrowser_EditorCommands.h"
#include "LambdaBrowser_EditorSettings.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "ISettingsModule.h"

#include "LevelEditor.h"
#include "Editor/Blutility/Classes/EditorUtilityWidgetBlueprint.h"
#include "EditorUtilitySubsystem.h"

#include "LevelEditor.h"

static const FName LambdaBrowser_EditorTabName("LambdaBrowser_Editor");

#define LOCTEXT_NAMESPACE "FLambdaBrowser_EditorModule"
DEFINE_LOG_CATEGORY(LambdaBrowser);

void FLambdaBrowser_EditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FLambdaBrowser_EditorStyle::Initialize();
	FLambdaBrowser_EditorStyle::ReloadTextures();

	FLambdaBrowser_EditorCommands::Register();
	
	RegisterSettings();


	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FLambdaBrowser_EditorCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FLambdaBrowser_EditorModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("LevelEditor", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FLambdaBrowser_EditorModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Content", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FLambdaBrowser_EditorModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FLambdaBrowser_EditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FLambdaBrowser_EditorStyle::Shutdown();

	FLambdaBrowser_EditorCommands::Unregister();
}

void FLambdaBrowser_EditorModule::PluginButtonClicked()
{
	UE_LOG(LambdaBrowser, Display, TEXT("LambdaBrowser editor tab opening."));

	FString PathToWidget = FString("EditorUtilityWidgetBlueprint'/LambdaBrowser/WebBrowser.WebBrowser'");

	UObject* WidgetReference = LoadObject<UObject>(nullptr, *PathToWidget);
	UEditorUtilityWidgetBlueprint* Widget = (UEditorUtilityWidgetBlueprint*)WidgetReference;
	if (!WidgetReference) {
		UE_LOG(LambdaBrowser, Error, TEXT("Could not find the LambdaBrowser widget. Make sure there is a EditorUtilityWidget called 'WebBrowser' in LambdaBrowser/"));
		return;
	}
	if (!WidgetReference) {
		UE_LOG(LambdaBrowser, Error, TEXT("Failed to cast to the LambdaBrowser EditorUtilityWidget."));
		return;
	}

	UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
	EditorUtilitySubsystem->SpawnAndRegisterTab(Widget);
}

void FLambdaBrowser_EditorModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.BeginSection("CustomMenu", TAttribute<FText>(FText::FromString("Lambda Web Browser")));

	Builder.AddMenuEntry(FLambdaBrowser_EditorCommands::Get().PluginAction);

	Builder.EndSection();
}

void FLambdaBrowser_EditorModule::RegisterSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "Lambda Browser",
			LOCTEXT("RuntimeSettingsName", "Lambda Browser"),
			LOCTEXT("RuntimeSettingsDescription", "Configure Lambda Browser settings"),
			GetMutableDefault<ULambdaBrowser_EditorSettings>());
	}
}

void FLambdaBrowser_EditorModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	ULambdaBrowser_EditorSettings* LambdaBrowser_Settings = GetMutableDefault<ULambdaBrowser_EditorSettings>();
	if (LambdaBrowser_Settings->ShowToolbarButton)
	{
		Builder.AddToolBarButton(FLambdaBrowser_EditorCommands::Get().PluginAction);
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLambdaBrowser_EditorModule, LambdaBrowser_Editor)