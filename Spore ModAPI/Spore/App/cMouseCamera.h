#pragma once

#include <Spore\App\ICamera.h>
#include <Spore\App\IMessageListener.h>

namespace App
{
	class cMouseCamera
		: public ICamera
		, public App::IMessageListener
		, public IVirtual
	{
	public:
		void CalculateViewTransform(Transform& transform);

		virtual void Update(int deltaTime, cViewer* pViewer) override;
		virtual bool OnKeyDown(int virtualKey, KeyModifiers modifiers) override;
		virtual bool OnMouseDown(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState) override;
		virtual bool OnMouseUp(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState) override;
		virtual bool OnMouseMove(float mouseX, float mouseY, MouseState mouseState) override;
		virtual bool OnMouseWheel(int wheelDelta, float mouseX, float mouseY, MouseState mouseState) override;
		virtual void Initialize() override;
		virtual void func54h(Vector3& dst) override;
		virtual bool HandleMessage(uint32_t messageID, void* pMessage) override;

	public:
		/* 0Ch */	int mnRefCount;
		/* 10h */	bool mCameraIsMayaStyle;
		/* 11h */	bool mCameraExponential;
		/* 12h */	bool mCameraPanSubjectPos;
		/* 14h */	int field_14;
		/* 18h */	int field_18;
		/* 1Ch */	int field_1C;
		/* 20h */	int field_20;
		/* 24h */	App::PropertyList* mpPropList;
		/* 28h */	float mCameraZoomScale;  // 1.0
		/* 2Ch */	float mCameraWheelZoomScale;  // 1.0
		/* 30h */	float mCameraTranslateScale;  // 1.0
		/* 34h */	float mCameraExpPanScale;  // 1.0
		/* 38h */	float mCameraRotateScale;  // 1.0
		/// Last position of the mouse after OnMouseDown()
		/* 3Ch */	Math::Point mLastMouseDown;
		/* 44h */	bool field_44;  // true
		/// Camera rotation on Z axis, also known as 'yaw'
		/* 48h */	float mCameraHeading;
		/* 4Ch */	float mCameraInitialHeading;
		/* 50h */	int field_50;  // 20
		/* 54h */	float field_54;  // 0.001
		/// Camera rotation on X axis
		/* 58h */	float mCameraPitch;
		/* 5Ch */	float mCameraInitialPitch;
		/* 60h */	int field_60;  // 20
		/* 64h */	float field_64;  // 0.001
		/// Camera rotation on Y axis
		/* 68h */	float mCameraRoll;
		/* 6Ch */	float field_6C;  // camera initial roll? always starts as 0
		/* 70h */	int field_70;  // 20
		/* 74h */	float field_74;  // 0.001
		/* 78h */	Math::Matrix3 mBaseRotation;
		/* 9Ch */	Math::Vector3 mBaseOffset;
		/* A8h */	Math::Vector3 field_A8;
		/* B4h */	int field_B4;  // 20
		/* B8h */	float field_B8;  // 0.001
		/* BCh */	float mCameraFOV;  // -1.0
		/* C0h */	float field_C0;  // -1.0
		/* C4h */	int field_C4;  // 20
		/* C8h */	float field_C8;  // 0.001
		/* CCh */	float mCameraOffsetX;
		/* D0h */	float mCameraOffsetY;
		/* D4h */	float mCameraZoom;  // 10.0
		/* D8h */	float mCameraInitialOffsetX;
		/* DCh */	float mCameraInitialOffsetY;
		/* E0h */	float mCameraInitialZoom;  // 10.0
		/* E4h */	int field_E4;  // 20
		/* E8h */	int field_E8;  // 0.001
		/* ECh */	float field_EC;
		/* F0h */	float field_F0;
		/* F4h */	float field_F4;
		/* F8h */	float field_F8;
		/* FCh */	float field_FC;
		/* 100h */	Math::Vector3 field_100;  // not initialized
		/* 10Ch */	float mCameraMinZoomDistance;  // 1.0
		/* 110h */	float mCameraMaxZoomDistance;  // 10000.0
		/* 114h */	float mCameraMinPitch;  // -PI/2
		/* 118h */	float mCameraMaxPitch;  // PI/2
		/* 11Ch */	float mCameraNearClip;  // -1.0
		/* 120h */	float mCameraFarClip;  // -1.0
	};
	ASSERT_SIZE(cMouseCamera, 0x124);

	namespace Addresses(cMouseCamera)
	{
		DeclareAddress(Update);  // 0x7DAF30 0x7DAAB0
		DeclareAddress(OnKeyDown);  // 0x7D9890 0x7D9410
		DeclareAddress(OnMouseDown);  // 0x7DA110 0x7D9C90
		DeclareAddress(OnMouseUp);  // 0x7F5AC0 0x5A9C70
		DeclareAddress(OnMouseMove);  // 0x7DAD40 0x7DA8C0
		DeclareAddress(OnMouseWheel);  // 0x7DAE50 0x7DA9D0
		DeclareAddress(Initialize);  // 0x7D99A0 0x7D9520
		DeclareAddress(func54h);  // 0x7D9970 0x7D94F0
		DeclareAddress(HandleMessage);  // 0x7DA180 0x7D9D00
		DeclareAddress(CalculateViewTransform);  // 0x7DAB30 0x7DA6B0
	}
}
