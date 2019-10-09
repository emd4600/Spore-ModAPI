/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/
#pragma once

/// @file Cheats.h
/// This file includes all the necessary headers to create new cheats and print strings to the cheat console.

///
/// @page cheats Cheats
///
/// This page has information about interacting with cheats and the cheat console in Spore. To use 
/// these things, you need to include the header Cheats.h
///
/// @tableofcontents
/// 
/// @section cheats_tutorial1 Tutorial: Print text to the cheat console
///
/// For debugging and testing reasons, it might be useful to print strings into the cheat console (you know, that thing you
/// open with Ctrl + Shift + C). You don't even have to follow any steps, since it's just one line of code. This assumes you
/// have included the Cheats.h header in your code.
///
/// To print text to the console, you need to use the ArgScript::PrintF() method. It works exactly the same way as the C++ function
/// 'printf' (more info here: http://www.cplusplus.com/reference/cstdio/printf/), excepts that it requires one argument more at the
/// beginning. That first argument is the ArgScript::FormatParser where the text will be printed, since the function is not only
/// for the cheat console. To get the cheat console stream, use the App::ICheatManager::GetConsoleStream() function. 
/// For example, to print "your score is: " and the value of the 'score' variable:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// int score = 10;
/// ArgScript::PrintF(App::ICheatManager::GetConsoleStream(), "your score is: %d", score);
/// // this prints 'your score is: 10'
/// ~~~~~~~~~~~~~~~~~
/// 
/// @section cheats_tutorial2 Tutorial: Add a new cheat
/// 
/// To add a new cheat to the cheat console, follow these steps. All files are assumed to include the Cheats.h header.
///
/// 1. Create a class that inherits from ICommand. The class must override the ArgScript::ICommand::ParseLine() and optionally, the 
/// ArgScript::ICommand::GetDescription() methods:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// class MyCheat : public ArgScript::ICommand
/// {
/// public:
/// virtual void ParseLine(const ArgScript::Line& line) override;
/// virtual const char* GetDescription(ArgScript::DescriptionMode mode) const override;
/// };
/// ~~~~~~~~~~~~~~~~~
///
/// You can use the "ModAPI Cheat" item template to create a basic ICommand class.
///
/// In the .cpp file, provide an implementation for these methods. The ArgScript::ICommand::ParseLine() method must do whatever
/// the cheat is meant to do when invoked. The ArgScript::ICommand::GetDescription() methods must return a text description of the cheat.
///
/// 2. Create an initialization function that adds the cheat, using the App::ICheatManager::AddCheat() method:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// bool CheatInitialization()
/// {
///		App::ICheatManager::Get()->AddCheat("pCheat", new MyCheat());
///		return true;
/// }
/// ~~~~~~~~~~~~~~~~~
///
/// 3. Add the initialization function in the DllMain function:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// /* inside the DllMain function */
/// // This line is always necessary
/// ModAPI::ModAPIUtils::InitModAPI();
/// 
/// ModAPI::ModAPIUtils::AddInitFunction(CheatInitialization);
/// ~~~~~~~~~~~~~~~~~
///
/// @section more_info More information:
/// - App::ICheatManager
/// - ArgScript::ICommand
/// - ArgScript
///

#include <Spore\App\ICheatManager.h>
#include <Spore\ArgScript\FormatParser.h>  // for the printf method
#include <Spore\ArgScript\ICommand.h>
