// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealMiddleRenderSetupSystem.h"
#include <imgui.h>
#include "Kismet/KismetMathLibrary.h"

UnrealMiddleRenderSetupSystem::UnrealMiddleRenderSetupSystem()
{
}

UnrealMiddleRenderSetupSystem::~UnrealMiddleRenderSetupSystem()
{
}

static void translateCall(int i, const middle::MiddleOutputState* const middleState, middle::MiddleInputState* inputState) {
	auto copyCall = middleState->uiCalls[i];
	switch (copyCall.type) {
	case(middleUI::Begin):
		ImGui::Begin(copyCall.label);
		break;
	case(middleUI::End):
		ImGui::End();
		break;
	case(middleUI::Text):
		ImGui::Text(copyCall.stringVal);
		break;
	case(middleUI::Button):
		copyCall.boolVal = ImGui::Button(copyCall.label);
		break;
	case(middleUI::Checkbox):
		ImGui::Checkbox(copyCall.label, &copyCall.boolVal);
		break;
	case(middleUI::Combo):
		ImGui::Combo(copyCall.label, &copyCall.intVal, copyCall.items, copyCall.size);
		break;
	case(middleUI::BeginPopup):
		copyCall.boolVal = ImGui::BeginPopup(copyCall.label);
		break;
	case(middleUI::EndPopup):
		ImGui::EndPopup();
		break;
	case(middleUI::OpenPopup):
		ImGui::OpenPopup(copyCall.label);
		break;
	case(middleUI::CloseCurrentPopup):
		ImGui::CloseCurrentPopup();
		break;
	case(middleUI::CollapsingHeader):
		ImGui::CollapsingHeader(copyCall.label);
		break;
	case(middleUI::RadioButton):
		copyCall.boolVal = ImGui::RadioButton(copyCall.label, copyCall.active);
		break;
	case(middleUI::InputText):
		// TOOOOOOOOOOOOOOOOOOOOOOOOOOOOODDDDDDDDDOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
		//ImGui::InputText(copyCall.label, copyCall.stringVal, copyCall.size);
		break;
	case(middleUI::SameLine):
		ImGui::SameLine();
		break;
	case(middleUI::Separator):
		ImGui::Separator();
		break;
	case(middleUI::SliderInt):
		ImGui::SliderInt(copyCall.label, &copyCall.intVal, copyCall.min, copyCall.max);
		break;
	}

	inputState->resultUiCalls.push_back(copyCall);
}

FColor toFColor(const midPrimitive::Color& color) {
	return FColor{ color.a, color.b, color.b, color.a };
}
FVector toFVector(const midMath::Vector3& vec) {
	return FVector(vec.x, -vec.y, vec.z);
}
FTransform toFTransform(const midPrimitive::Transform& transform) {
	FVector translation = toFVector(transform.translation);
	FVector scale = toFVector(transform.scale);
	FQuat rotation = { transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w };
	rotation.W = 1;
	return FTransform(rotation, translation, scale);
}

void UnrealMiddleRenderSetupSystem::Update(UWorld* World, const middle::MiddleOutputState* const middleOutputState, middle::MiddleInputState* inputState) 
{

	//set camera pos 
	auto pc = World->GetFirstPlayerController();
	if (pc) {
		auto pawn = pc->GetPawn();
		if (pawn) {
			FVector cameraPos = toFVector(middleOutputState->activeCamera.position);
			FVector targetLookAtPos = toFVector(middleOutputState->activeCamera.target);
			FRotator lookAtRot = UKismetMathLibrary::FindLookAtRotation(cameraPos, targetLookAtPos);
			pawn->SetActorLocation(cameraPos);
			pc->SetControlRotation(lookAtRot);
		}
	}

	for (auto& item : middleOutputState->renderData) {
		if (item.type == middle::RenderItemType::SPHERE) {
			auto pos = item.center;
			DrawDebugSphere(World, FVector{pos.x,pos.y,pos.z}, item.radius, 5, FColor::Cyan);
		}
		if (item.type == middle::RenderItemType::RECTANGLE) {
			float axisX = item.width * 0.5f;
			float axisZ = item.height * 0.5f;
			FVector posA = { -axisX, 0, -axisZ };
			FVector posB = { axisX, 0, -axisZ };
			FVector posC = { axisX, 0, axisZ };
			FVector posD = { -axisX, 0, axisZ };
			FTransform transform = toFTransform(item.transform);
			posA = transform.TransformPosition(posA);
			posB = transform.TransformPosition(posB);
			posC = transform.TransformPosition(posC);
			posD = transform.TransformPosition(posD);
			FColor color = toFColor(item.color);
			DrawDebugLine(World, posA, posB, color);
			DrawDebugLine(World, posB, posC, color);
			DrawDebugLine(World, posC, posD, color);
			DrawDebugLine(World, posD, posA, color);
		}
		if (item.type == middle::RenderItemType::BILLBOARD) {
			float axis = 0.5f;
			FVector posA = { -axis, 0, -axis };
			FVector posB = { axis, 0, -axis };
			FVector posC = { axis, 0, axis };
			FVector posD = { -axis, 0, axis };
			midPrimitive::Transform midT = item.transform;
			midT.scale.x *= item.textureScale;
			midT.scale.y *= item.textureScale;
			midT.scale.z *= item.textureScale;
			FTransform transform = toFTransform(midT);
			posA = transform.TransformPosition(posA);
			posB = transform.TransformPosition(posB);
			posC = transform.TransformPosition(posC);
			posD = transform.TransformPosition(posD);
			FColor color = toFColor(item.color);
			DrawDebugLine(World, posA, posB, color);
			DrawDebugLine(World, posB, posC, color);
			DrawDebugLine(World, posC, posD, color);
			DrawDebugLine(World, posD, posA, color);
		}
	}

	inputState->resultUiCalls.clear();
	const ImGui::FScopedContext ScopedContext;
	if (ScopedContext) {

		for (int i = 0; i < middleOutputState->uiCalls.size(); ++i) {
			translateCall(i, middleOutputState, inputState);
		}
	}
}
