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
