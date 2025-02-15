#include "Include.h"


// (Will be used to convert 3D coordinates to 2D screen coordinates)

//FVector GetBone(DWORD_PTR mesh, int id)
//{
//	DWORD_PTR array = Read<uintptr_t>(mesh + 0x0);
//	if (!array)
//		array = Read<uintptr_t>(mesh + 0x0);
//
//	FTransform bone = Read<FTransform>(array + (id * 0x60));
//	FTransform ComponentToWorld = Read<FTransform>(mesh + 0x0);
//	D3DMATRIX Matrix;
//	Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
//	return FVector(Matrix._41, Matrix._42, Matrix._43);
//}
//
//FVector WorldToScreen(FVector WorldLocation)
//{
//	FVector Screenlocation = FVector(0, 0, 0);
//	auto CameraInfo = Read<FMinimalViewInfo>(Data.APlayerCamera + 0x0);
//
//	FVector CameraLocation = CameraInfo.Location;
//	FVector CameraRotation = CameraInfo.Rotation;
//
//	D3DMATRIX tempMatrix = Matrix(CameraRotation, FVector(0, 0, 0));
//	FVector vAxisX = FVector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]),
//		vAxisY = FVector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]),
//		vAxisZ = FVector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
//
//	FVector vDelta = WorldLocation - CameraLocation;
//	FVector vTransformed = FVector(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));
//
//	if (vTransformed.z < 1.f)
//		vTransformed.z = 1.f;
//
//	float FovAngle = CameraInfo.FOV;
//
//	float ScreenCenterX = Settings::Width / 2.0f;
//	float ScreenCenterY = Settings::Height / 2.0f;
//	Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)3.14159265358979323846264338327950288419716939937410 / 360.f)) / vTransformed.z;
//	Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)3.14159265358979323846264338327950288419716939937410 / 360.f)) / vTransformed.z;
//
//	return Screenlocation;
//}

//(MAKE SURE YOU UPDATE THE OFFSETS) 
namespace Offsets { 
	uintptr_t UWorld = 0xDE37EE0;
	uintptr_t GameInstance = 0x270;
	uintptr_t LocalPlayers = 0x40;
	uintptr_t PlayerController = 0x38; //Inside UPlayer
	uintptr_t LocalPawn = 0x550; //AcknowledgedPawn
	uintptr_t GameState = 0x210;
	uintptr_t PlayerArray = 0x4a8;
	uintptr_t PawnPrivate = 0x518;//
	uintptr_t ChildActorComponent = 0x530; //UChildActorComponent
	uintptr_t ChildActor = 0x478; //UChildActorComponent
	uintptr_t Mesh = 0x490; //USkeletalMeshComponent->Mesh  constexpr auto MeshComp = 0x490;  // Size: 0x8, Type: UStaticMeshComponent
	uintptr_t RootComponent = 0x2b8;
	uintptr_t ComponentVelocity = 0x1d0; //USceneComponent->CompenentVelocity
	uintptr_t RelativeLocation = 0x188;
	uintptr_t PlayerState = 0x4c8; //APawn->PlayerState
	uintptr_t TeamID = 0x5C0; //int32 TeamID; // 0x05C0 //class AMarvelPlayerState : public APlayerState
	uintptr_t IsAlive = 0x5D0;  //bool   bIsAlive;  // 0x05D0 //class AMarvelPlayerState : public APlayerState
	uintptr_t SelectedHeroID = 0x628;  //int32 SelectedHeroID;   // 0x0628 //class AMarvelPlayerState : public APlayerState
	uintptr_t UReactivePropertyComponent = 0x12b8; //class UReactivePropertyComponent*             ReactivePropertyComponent;                         // 0x1298 // AMarvelBaseCharacter
	uintptr_t CachedAttributeSet = 0x1820; 	//class UMarvelBaseAttributeSet*                CachedAttributeSet;                                // 0x1820
	uintptr_t Health = 0x40; //UMarvelBaseAttributeSet Health 0x40

	//Array
	uintptr_t BoneArray = 0x908;
	uintptr_t ComponentToWorld = 0x2E0;

	//Camera
	uintptr_t APlayerCameraManager = 0x560; //APlayerController->PlayerCameraManager
	uintptr_t CameraCache = 0x1a50; //FCameraCacheEntry CameraCachePrivate
}

namespace ImGuiMenu {
	bool ShowMenu = 0;
}
