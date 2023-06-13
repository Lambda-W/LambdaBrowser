// Copyright Lambda Works, Samuel Metters 2019. All rights reserved.
// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "LambdaBrowser_EditorStyle.h"

class FLambdaBrowser_EditorCommands : public TCommands<FLambdaBrowser_EditorCommands>
{
public:

	FLambdaBrowser_EditorCommands()
		: TCommands<FLambdaBrowser_EditorCommands>(TEXT("LambdaBrowser_Editor"), NSLOCTEXT("Contexts", "LambdaBrowser_Editor", "LambdaBrowser_Editor Plugin"), NAME_None, FLambdaBrowser_EditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
