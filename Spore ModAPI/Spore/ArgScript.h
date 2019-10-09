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

/// @file ArgScript.h
/// This file has all the includes necessary to work with ArgScript.

#include <Spore\ArgScript\IParser.h>
#include <Spore\ArgScript\IBlock.h>
#include <Spore\ArgScript\ICommand.h>
#include <Spore\ArgScript\ISpecialBlock.h>
#include <Spore\ArgScript\IFunction.h>
#include <Spore\ArgScript\FormatParser.h>
#include <Spore\ArgScript\Lexer.h>
#include <Spore\ArgScript\Line.h>

///
/// @namespace ArgScript
/// ArgScript is a scripting language largely used in Spore. Although it can be used for scripts, it is mostly used as a file format,
/// as a way to store information about multiple objects (for example, effects, property definitions, cinematics, etc). 
/// ArgScript can be considered similar to XML: ArgScript is the format, but the interpretation depends on the program.
/// To create a parser for ArgScript, use the ArgScript::FormatParser class.
/// Below is a  detailed description of all the components in the language:
///
/// ## Commands
/// Commands are the basic element in ArgScript. A command is a single line of words, separated by whitespaces. The first word
/// is the **keyword**, which determines how the command is processed and executed. The rest of words are the **arguments**.
///
/// Words prefixed with '-', like '-scale', are called **options**, which are not required (that is, they are optional).
/// Options can have arguments as well; when they don't, they are called **flags**.
///
/// For example, consider this line:
/// ~~~~~~~~~~~~~
/// model MyCube 3 -scale 2.0 -rigid
/// ~~~~~~~~~~~~~
/// This command line is formed by:
/// - Keyword *model*.
/// - 2 arguments: *MyCube* and *3*.
/// - 1 option called *scale*, with 1 argument: *2.0*.
/// - 1 option called (something).
/// - 1 flag (option without arguments) called.
///
/// To process commands, the ICommand class is used. On its main method, ICommand::ParseLine(), an instance of the class 
/// ArgScript::Line is received; the Line class contains all the arguments and options, and it has functions to get them
/// ensuring the format is correct. Finally, using the FormatParser::AddParser() method, an ICommand can be assigned to a keyword.
///
/// The cheat console uses commands to process cheats. For more information, check the App::ICheatManager class.
///
/// ## Blocks
/// Blocks are groups of commands. A block starts with a command, and ends when a line with the keyword 'end' is reached.
/// Usually, blocks represent groups of data, for example, a scene in a cinematic; commands inside it represent its properties,
/// for example the camera movement. A block can have its own parsers, allowing to have specific blocks and commands that only
/// work on certain blocks.
///
/// For example:
/// ~~~~~~~~~~~~~
/// effect fire_special_fx  # a block is assigned to the keyword 'effect'
///		particles FireParticles  # a command inside a block, it does not work outside the block
///		sound fire_sound  # indentation is not necessary, but it makes it look more organised
/// end  # this is the end of the 'effect' block
/// ~~~~~~~~~~~~~
///
/// To process blocks, the IBlock class is used. The IBlock::ParseLine() method reads the first line of the block:
/// on this function, the FormatParser::AddBlock() method should be called to notify the parser a block has been found.
/// The IBlock::OnBlockEnd() method is called when the 'end' keyword is reached; the block will close automatically.
/// Additionally, there is the IBlock::SetData() method, which is called when the FormatParser::AddParser() or IBlock::AddParser()
/// method is called; in this function, the block should add to itself any parsers it requires.
/// Finally, a block is assigned to a keyword using the FormatParser::AddParser() method, just like commands.
/// 
/// ## Literals and parenthesis
/// All the words in a line are separated when whitespaces are found. Sometimes, however, one might be interested in having an argument
/// that has whitespaces inside; in that case, string literals surrounded by "" can be used. For example:
/// ~~~~~~~~~~~~~
/// text "Problem solved!"
/// ~~~~~~~~~~~~~
/// In that example, *Problem solved!* will be a single argument.
///
/// Parenthesis have the same effect as string literals; for convention, string literals are only used for things that are actually
/// text; for everything else, parenthesis are preferred. For example:
/// ~~~~~~~~~~~~~
/// model MyCube -color (0.2, 0, 1.0)
/// ~~~~~~~~~~~~~
/// In that example *0.2, 0, 1.0* will be a single argument.
///
/// ## Mathematical and logical expressions
/// ArgScript has support for mathematical and logical expressions. For example, imagine there is a command with keyword *angle*
/// and an argument which is meant to be the angle we want. We can put a mathematical expression there surrounded by parenthesis, 
/// like '(3 + 0.2^3 * sqrt(0.2))', '(sind(50) * datan(30))', etc. Check the FormatParser::ParseFloat() method for more information.
/// 
/// Logical expressions are also supported. They accept the operators 'not', 'or', 'and'; check the FormatParser::ParseBool() for more
/// information.
///
/// ## Functions
/// As seen in the mathematical example before, ArgScript has support for functions. Functions cannot be declared in the script file
/// (like one would expect in a programming language); they can only be declared in the code. Functions can take any number of parameters
/// and return a bool, int or float value. 
///
/// Functions are processed using the IFunction class. To add a function, the Lexer::AddFunction() method must be used (to get the
/// lexer of the parser, use FormatParser::GetLexer()).
///
/// ## Variables
/// ArgScript has support for variables. Variables are assigned using the 'set...' commands. To get the value of a variable, 
/// it must be prefixed with $. For example:
/// ~~~~~~~~~~~~~
/// setf kMaxScale 10.0  # set a float variable with value 10.0 
///
/// model MyCube -scale $kMaxScale
/// ~~~~~~~~~~~~~
/// It is also possible to use variables inside other names or variables, using ${var_name}. For example:
/// ~~~~~~~~~~~~~
/// set quality low
/// model MyCube_${low}_quality
/// ~~~~~~~~~~~~~
///
/// These are the commands for settings variables:
/// - **set VariableName Value**: strings. For example *set name "My name"*
/// - **setb VariableName Value**: booleans. For example *setb render false*
/// - **seti VariableName Value**: integers. For exmaple *seti kMaxInt (2^31)*
/// - **setf VariableName Value**: floats. For example *setf kMaxScale 10.0*
/// - **setc VariableName Value**: colors. For example *setc red (1.0, 0, 0)*
/// - **setv2 VariableName Value**: vector2. For example *setv2 UV_offset (0.5, -0.5)*
/// - **setv3 VariableName Value**: vector3. For example *setv3 offset (0.5, -0.5, 3.0)*
/// - **setv4 VariableName Value**: vector4. For example *setv4 randomv4 (0.5, -0.5, 3.0, 0.2)*
/// - **sete VariableName Value Enumeration**: special case, the value is restricted to an enumeration of values. For example,
/// *sete mode Wireframe (Wireframe Normal)*, the value can only be 'Wireframe' or 'Normal'.
///
/// Variables can also be set and used using the FormatParser::SetVariable() and FormatParser::GetVariable() methods.
///
/// ## Namespaces
/// Namespaces are special blocks that restrict the scope (that is, where it can be used) of a variable. When a variable is assigned,
/// it is automatically assigned in the namespace scope, and therefore it can't be used outside of that scope. Namespace variables
/// can be accessed prefixing the variable name with the namespace name and a ':' sign. For example:
/// ~~~~~~~~~~~~~
/// namespace ParticleEffects
///		set EffectTag "particles"
///		# the variable can be used here because we are in the same scope
///		effect ${EffectTag}_01  # this will be 'particles_01'
///			# insert any code here
///		end
/// end
///
/// namespace SoundEffects
///		set EffectTag "sound"
///		# the variable can be used here because we are in the same scope
///		effect ${EffectTag}_01  # this will be 'sound_01'
///			# insert any code here
///		end
/// end
///
/// # if we try to use $EffectTag here, it will throw an exception, because EffecTag is not defined in this scope.
/// # however, we can do this:
/// setEffect ${ParticleEffects:EffectTag}_01
/// ~~~~~~~~~~~~~
///
/// Via code, global variables can be set; those can be accessed prefixing the name with ':'. For example, if you set a global variable
/// (using the FormatParser::SetGlobalVariable() method) called 'CurrentEditor', you can access it using ':CurrentEditor'
///
/// ## Conditionals
/// Conditions are also supported in ArgScript. Conditional blocks only get executed if a condition is met.
/// To create a conditional block, use the command '**if (condition...)**'; to end the conditional block, use the command '**endif**'.
/// To define what must be excuted if the condition is NOT met, use the '**else**' keyword. To define another condition when the 
/// first one is not met, use the command '**elseif (condition..)**'. The conditions are logical expressions, like the ones that have
/// been described above.
///
/// For example:
/// ~~~~~~~~~~~~~
/// seti kQuality 0
/// if ($kQuality < 0)
///		# do something that is only executed if kQuality is less than 0
/// else if ($kQuality > 3)
///		# do something that is only executed if kQuality is greater than 3
/// else
///		# do something that is only executed if kQuality is not less than 0 and not greater than 3.
/// endif  # end conditional block
///
/// # let 'IsInEditor' and 'CinematicSupported' be bool variables set via code
/// if (IsInEditor and CinematicSupported)
///		# do something
/// endif
/// ~~~~~~~~~~~~~
///
/// ## Definitions
/// ArgScript has support for definitions, which are blocks of data that can be created multiple times, changing certain parameters.
/// To create a definition, use the '**define DefinitionName(arguments...)**' command; to end the conditional block, use the command
/// '**enddef**'. When inside the definition, the arguments can be used like variables. For example:
/// ~~~~~~~~~~~~~
///	define EDT_currency_materials_MACRO( CURRENCY )
///		material EDT_currency_&{ CURRENCY }_mtl
///			shader planetLitIcon_material
///			texture sampler0 UI_currency_coin_&{ CURRENCY }_diffuse
///			texture sampler1 UI_currency_coin_&{ CURRENCY }_specBump
///		end
/// enddef
/// ~~~~~~~~~~~~~
/// 
/// Now, there are three commands that can be used to create instances of that definition:
/// - **create**: Instatiate the given definition; an exception is thrown if the definition does not exist. 
/// For example: '*create EDT_currency_materials_MACRO( DNA )*'.
/// - **screate**: Instatiate the given definition, without throwing an error if it does not exist. For example:
/// '*screate EDT_currency_materials_MACRO( DNA )*'.
/// - **arrayCreate**: Instatiate the given definition a certain number of times. The definition will receive two parameters:
/// the current index and the number of times to instatiate. For example: '*arrayCreate defined_macro 10*'.
///
/// The command **undefine** can be used to remove a definition, for example, '*undefine EDT_currency_materials_MACRO*'.
///
/// ## Other commands and functions
/// Here is a list of other commands supported by default in ArgScript:
/// - **include FileName**: Includes the given file, throwing an exception if it does not exist. The path uses the format required
/// by http://www.cplusplus.com/reference/cstdio/fopen/
/// - **sinclude FileName**: Includes the given file, with no error if the file does not exist. The path uses the format required
/// by http://www.cplusplus.com/reference/cstdio/fopen/
/// - **help [Pattern] [-full] [-html]**: Shows the description of commands and blocks. Optionally, a pattern (that allows * and ?) that the keywords
/// must follow can be specified; otherwise, all descriptions will be printed. There are two options: '-full' prints a detailed description,
/// and '-html' prints an html description (rarely supported).
/// - **eval Command**: Parse the given argument as a command.
/// - **purge Scope**: Purge variable definitions from the given namespace scope. Scope must finish in ':'.
/// - **showArguments ...**: Output the arguments of this command.
/// - **version Number**: Set the version of this script. Using the FormatParser::SetVersionRange() method, the supported version range of the
/// script can be set; when the command 'version' is found with an unsupported version, an exception is thrown.
/// - **trace "Text"**: Prints the given text to the output stream.
///
/// Here is a list of other functions supported by default in ArgScript:
/// - **varExists(name)**: Returns true if the given variable exists (has a value).
/// - **commandExists(name)**: Returns true if the given command exists.
/// - **defExists(name)**: Returns true if the given definition exists.
/// - **eq(string1, string2)**: Compares two strings.
/// - **match(string, pattern)**: Returns true if the string matches the wildcard pattern (which supports special characters * and ?).
/// - **minVersion()**: Returns minimum accepted script version.
/// - **maxVersion()**: Returns maximum accepted script version.
///
/// # Parsing files with ArgScript.
/// To parse files with ArgScript, first you must get a FormatParser instance using the ArgScript::CreateStream() method.
/// After that, you must use the FormatParser::Initialize() method, to ensure all the default features are added.
/// Using the FormatParser::AddParser() method, add any parsers your format requires.
/// Finally, use the FormatParser::ProcessFile() methods (or their safe methods) to process files. Mind you, the variables of processed files
/// are stored; if you want to avoid that, you have to create a new FormatParser for each file you process.
///
