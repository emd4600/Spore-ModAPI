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

#include <Spore\App\DirectPropertyList.h>

/// AppProperties is a kind of PropertyList containing globally-accessible properties that control
/// the running of the app as a whole.
///
/// Use AppProperties to get the property list and access global properties, for example:
/// ~~~~~~~~~~~~~~~{.cpp}
/// if (AppProperties.GetDirectBool(SPPropertyIDs::kRenderEffects)) ...
/// ~~~~~~~~~~~~~~~
#define AppProperties (*App::GetAppProperties())

namespace Addresses(App)
{
	DeclareAddress(AppProperties_ptr);
}

namespace App
{
#ifndef SDK_TO_GHIDRA
	/// AppProperties is a kind of PropertyList containing globally-accessible properties that control
	/// the running of the app as a whole.
	///
	/// Use AppProperties to get the property list and access global properties, for example:
	/// ~~~~~~~~~~~~~~~{.cpp}
	/// if (AppProperties.GetDirectBool(SPPropertyIDs::kRenderEffects)) ...
	/// ~~~~~~~~~~~~~~~
	inline DirectPropertyList* GetAppProperties()
	{
		return *(DirectPropertyList**)(GetAddress(App, AppProperties_ptr));
	}
#else
	DirectPropertyList* sAppProperties;
#endif

	/// 
	/// This namespace only contains property IDs to be used in the AppProperties module. These properties define
	/// basic configurations that should be fast and accessible in all the app. They were taken from the AppProperties.txt file.
	///
	namespace SPPropertyIDs
	{
		enum Properties
		{
			kShowFPS = 1,
			kRenderUI = 2,

			kRenderEffects = 3,
			kRenderTerrain = 4,
			kRenderModels = 5,
			krenderDebugDraw = 6,

			kShowProfiler = 9,  /// 0=hide, 1=self 2=hier
			kShowProfilerGraph = 10,

			kCullingLevel = 11,  /// 0=none, 1=flat 2=hier, 3=occluders

			kShowCulling = 12,
			kShowBBoxes = 13,
			kShowPicking = 14,
			kShowHulls = 15,
			kShowGrid = 16,
		
			kTextureStats = 17,
			kModelStats = 18,
			kRenderStats = 19,
			kEffectStats = 20,

			kShowPropEditor = 21,

			kDisableSkinning = 22,

			kProfilerReportLength = 23,  /// 0 - short, 1 - medium, 2 - long
			kProfilerLogFactor = 24,  /// if non-zero, a frame that takes this times more time than average will generate a profile dump. E.g., 2
			kProfilerLogTime = 25,  /// if non-zero, a frame that takes longer than this (in seconds) will generate a profile dump. E.g., 0.1

			kMemoryProfilerMore = 26,
			kMemoryProfilerSort = 27,
			kMemoryProfilerLogSize = 28,  /// if non-zero, absolute size (KB) of allocations size spike to log a frame. E.g., 2000
			kMemoryProfilerLogFactor = 29,  /// if non-zero, spike factor over average allocation size to log a frame
			kMemoryProfilerWatchLines = 30,  /// number of watch window lines to use >=1 and <= 20
			kMemoryProfilesSmoothing = 31,  /// (from  [0, 1] - 1 is the smoothest)
			kMemoryProfilesBySystem = 32,  /// whether to show a detailed memory-usage breakdown by system

			kTerrainLODThreshold = 33,  /// LOD threshold
			kTerrainLODMorphDistance = 34,  /// How rapidly we morph between LODs after a change
			kTerrainLODAspect = 35,  /// how much to weigh horizontal distance over vertical

			kDisableLogging = 36,  /// disables all logging when set (including asserts)

			kSubstituteMissingResources = 37,  /// whether to substitute a dummy resource for missing models, textures, etc.

			kFlushGPU = 38,  /// Force synchronization with the GPU after drawing, for better profiling of render costs
			kModelLODDistanceScale = 39,  /// scale on model manager LOD values

			kAppModeControlsCamera = 40,

			kMRT = 41,  /// Does your graphics card support Multiple Render Targers (GeForce FX 5900 Ultra does not)

			kDumpMemoryLeaks = 42,  /// Dump memory leaks on shutdown (overridden to false by default for non-Debug builds)

			kSoftwareCursor = 43,  /// On some builds, enable software cursor

			kFrameLimitMS = 44,  /// if non-zero, the main game loop will always take at least this long, i.e., frame rate will be constant apart from long frames
			kMemoryLimit = 45,  /// if non-zero, we will report out-of-memory and do a memory dump when we hit this many MB

			kUIScissor = 46,  /// if true, use scissor rectangle instead of pixel-shader clipping

			kEditorShowAnimSelecter = 47,
			kEditorShowRolloverInfo = 48,
			kEditorAutoZoomCameraEnabled = 49,
			kEditorDebugDrawRigblockAxis = 50,
			kEditorDebugDrawModel = 51,
			kEditorDebugDrawRigblockNames = 52,
			kEditorDebugDrawHierarchy = 53,
			kEditorDebugDrawBoneCount = 54,
			kEditorAnimateWhileEditing = 55,

			kAlphaThreshold = 56,  /// the alpha threshold below which to simply not render a model/quad/whatever

			kEditorAutoCollapsePalette = 57,  /// False == Manual Collapse mode, True == Auto Collapse
			kDumpBaketimeTextures = 58,  /// If true, it will save ambient occlusion, splatter and composite textures to Data dir
			kEditorDebugDrawPhysicsHulls = 59,

			kDisableBoneUploads = 60,  /// whether to disable uploading bone constants
			kSporeLiteIsOnlineHost = 61,
			kSporeLiteIsOnlineEnable = 62,
			kPlayModeOn = 63,
			kEditorNewPalettes = 64,
			kEditorNewDataFiles = 65,
			kPaletteFeedMaxItems = 66,

			kEditorDisplayAnimInfo = 67,

			kRenderTargetCorrection = 68,  /// whether to apply a half-destination-texel correction to the projection matrix for DX

			kEditorEnablePanning = 69,

			kIsCSAApp = 70,

			kShowTextLocations = 71,

			kShowObstacleRadii = 72,

			kEditorDebugDrawRigblockForZCorp = 74,

			kThrottleTime = 75,  /// ms to throttle game by when it is in the background

			kExcludeSecondaryTextures = 76,  /// whether to avoid loading secondary textures such as normal maps and spec maps

			kGarbageDeletionScale = 77,
			kGarbageDeletionDiv = 78,
			kGarbageDeletionMin = 79,  /// min to delete per frame
			kGarbageDeletionMax = 80,  /// maximum we will hold on to, after this we will flush them all

			kWireframe = 81

		};

		const size_t kAppPropertiesCount = 0x52;
	}
}
