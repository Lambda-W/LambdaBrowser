// Copyright Lambda Works, Samuel Metters 2019. All rights reserved.
// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LambdaBrowser_EditorCommands.h"

#define LOCTEXT_NAMESPACE "FLambdaBrowser_EditorModule"

void FLambdaBrowser_EditorCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Web browser", "Opens Lambda Web Browser in a editor tab.", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
