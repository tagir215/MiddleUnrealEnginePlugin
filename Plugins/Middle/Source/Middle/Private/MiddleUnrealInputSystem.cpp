// Fill out your copyright notice in the Description page of Project Settings.


#include "MiddleUnrealInputSystem.h"
#include "GameFramework/PlayerController.h"

MiddleUnrealInputSystem::MiddleUnrealInputSystem()
{
}

MiddleUnrealInputSystem::~MiddleUnrealInputSystem()
{
}


bool MiddleUnrealInputSystem::IsDown(FKey key) const
{
    return PlayerController &&
        PlayerController->IsInputKeyDown(key);
}

bool MiddleUnrealInputSystem::WasPressed(FKey key) const
{
    return PlayerController &&
        PlayerController->WasInputKeyJustPressed(key);
}

bool MiddleUnrealInputSystem::WasReleased(FKey key) const
{
    return PlayerController &&
        PlayerController->WasInputKeyJustReleased(key);
}

bool MiddleUnrealInputSystem::KeyboardBlocked(
    const middle::MiddleOutputState* output) const
{
    return false;
}

bool MiddleUnrealInputSystem::MouseBlocked(
    const middle::MiddleOutputState* output) const
{
    return false;
}




void MiddleUnrealInputSystem::Update(UWorld* World, const middle::MiddleOutputState* output,
    middle::MiddleInputState& input)
{
    PlayerController = World->GetFirstPlayerController();

    if (!PlayerController)
        return;

    // Clear all per-frame input.
    input.editorInput = middle::EditorInput();
    input.gameInput = middle::GameInput();
    input.equlabInput = middle::EqulabInput();

    auto& editor = input.editorInput;
    auto& game = input.gameInput;
    auto& equlab = input.equlabInput;

    const bool keyboardBlocked = KeyboardBlocked(output);
    const bool mouseBlocked = MouseBlocked(output);


    // ============================================================
    // MOUSE
    // ============================================================

    float mouseX = 0.0f;
    float mouseY = 0.0f;

    PlayerController->GetMousePosition(mouseX, mouseY);

    editor.mouseX = mouseX;
    editor.mouseY = mouseY;

    if (!mouseBlocked)
    {
        editor.mouseHeld =
            IsDown(EKeys::LeftMouseButton);

        editor.mouseClicked =
            WasPressed(EKeys::LeftMouseButton);

        editor.mouseReleased =
            WasReleased(EKeys::LeftMouseButton);

        editor.newThing =
            editor.mouseClicked;
        
    }


    // ============================================================
    // EDITOR INPUT
    // ============================================================

    if (!keyboardBlocked)
    {
        editor.w = IsDown(EKeys::W);
        editor.s = IsDown(EKeys::S);
        editor.a = IsDown(EKeys::A);
        editor.d = IsDown(EKeys::D);

        editor.q = IsDown(EKeys::Q);
        editor.e = IsDown(EKeys::E);

        editor.altDown =
            IsDown(EKeys::LeftAlt);

        editor.grabDown =
            IsDown(EKeys::G);

        //editor.grabReleased =
        //    WasReleased(EKeys::G);

        //editor.rotatePressed =
        //    WasPressed(EKeys::X);

        //editor.rotateReleased =
        //    WasReleased(EKeys::X);

        //editor.scaleDown =
        //    IsDown(EKeys::Z);

        //editor.scaleReleased =
        //    WasReleased(EKeys::Z);

        //editor.infoClick =
        //    WasPressed(EKeys::I);

        //editor.loopClick =
        //    WasPressed(EKeys::L);

        //editor.selectModeClick =
        //    WasPressed(EKeys::One);

        //editor.sphereModeClick =
        //    WasPressed(EKeys::Two);

        //editor.constraintModeClick =
        //    WasPressed(EKeys::Three);

        //editor.cameraModeClick =
        //    WasPressed(EKeys::Four);

        //editor.loopModeClick =
        //    WasPressed(EKeys::Five);

        //editor.hideClick =
        //    WasPressed(EKeys::H);

        //editor.deleteClick =
        //    WasPressed(EKeys::R);

        //editor.copyClick =
        //    WasPressed(EKeys::C);

        //editor.saveClick =
        //    WasPressed(EKeys::P);

        //editor.navigateToFileClick =
        //    WasPressed(EKeys::SpaceBar);

        //editor.focus =
        //    WasPressed(EKeys::F);

        //editor.reparentClick =
        //    WasPressed(EKeys::E);

        //editor.seaprateFromParentClick =
        //    WasPressed(EKeys::R);

        //editor.nextScene =
        //    WasPressed(EKeys::Tab);
    }


    // ============================================================
    // GAME INPUT
    // ============================================================

    if (!keyboardBlocked)
    {
        game.mouseWheelMove = PlayerController->GetInputAnalogKeyState(EKeys::MouseWheelAxis);

        game.copy =
            WasPressed(EKeys::F);

        game.insertTerm =
            WasPressed(EKeys::T);

        game.pop =
            WasPressed(EKeys::Z);

        game.zoomIn =
            IsDown(EKeys::E);

        game.zoomOut =
            IsDown(EKeys::Q);

        game.panUp =
            IsDown(EKeys::W);

        game.panDown =
            IsDown(EKeys::S);

        game.panLeft =
            IsDown(EKeys::A);

        game.panRight =
            IsDown(EKeys::D);

        game.can =
            WasPressed(EKeys::X);

        game.comp =
            WasPressed(EKeys::C);

        game.mulOne =
            WasPressed(EKeys::V);

        game.undo =
            WasPressed(EKeys::SpaceBar);

        game.one =
            IsDown(EKeys::One);

        game.two =
            IsDown(EKeys::Two);

        game.three =
            IsDown(EKeys::Three);

        game.four =
            IsDown(EKeys::Four);

        game.five =
            IsDown(EKeys::Five);

        game.six =
            IsDown(EKeys::Six);

        game.seven =
            IsDown(EKeys::Seven);

        game.eight =
            IsDown(EKeys::Eight);

        game.nine =
            IsDown(EKeys::Nine);

        game.zero =
            IsDown(EKeys::Zero);

        game.shiftHeld =
            IsDown(EKeys::LeftShift) ||
            IsDown(EKeys::RightShift);
    }


    // ============================================================
    // EQULAB INPUT
    // ============================================================

    if (!keyboardBlocked)
    {
        //equlab.oneClicked =
        //    WasPressed(EKeys::One);

        //equlab.twoClicked =
        //    WasPressed(EKeys::Two);

        //equlab.threeClicked =
        //    WasPressed(EKeys::Three);

        //equlab.fourClicked =
        //    WasPressed(EKeys::Four);

        //equlab.fiveClicked =
        //    WasPressed(EKeys::Five);

        //equlab.sixClicked =
        //    WasPressed(EKeys::Six);

        //equlab.sevenClicked =
        //    WasPressed(EKeys::Seven);

        //equlab.eightClicked =
        //    WasPressed(EKeys::Eight);

        //equlab.nineClicked =
        //    WasPressed(EKeys::Nine);

        //equlab.zeroClicked =
        //    WasPressed(EKeys::Zero);


        //equlab.f1Clicked =
        //    WasPressed(EKeys::F1);

        //equlab.f2Clicked =
        //    WasPressed(EKeys::F2);

        //equlab.f3Clicked =
        //    WasPressed(EKeys::F3);

        //equlab.f4Clicked =
        //    WasPressed(EKeys::F4);

        //equlab.f5Clicked =
        //    WasPressed(EKeys::F5);

        //equlab.f6Clicked =
        //    WasPressed(EKeys::F6);

        //equlab.f7Clicked =
        //    WasPressed(EKeys::F7);

        //equlab.f8Clicked =
        //    WasPressed(EKeys::F8);

        //equlab.f9Clicked =
        //    WasPressed(EKeys::F9);

        //equlab.f10Clicked =
        //    WasPressed(EKeys::F10);

        //equlab.f11Clicked =
        //    WasPressed(EKeys::F11);

        //equlab.f12Clicked =
        //    WasPressed(EKeys::F12);


        //equlab.leftHeld =
        //    IsDown(EKeys::Left);

        //equlab.rightHeld =
        //    IsDown(EKeys::Right);

        //equlab.upHeld =
        //    IsDown(EKeys::Up);

        //equlab.downHeld =
        //    IsDown(EKeys::Down);


        //equlab.shiftHeld =
        //    IsDown(EKeys::LeftShift) ||
        //    IsDown(EKeys::RightShift);

        //equlab.ctrlHeld =
        //    IsDown(EKeys::LeftControl) ||
        //    IsDown(EKeys::RightControl);

        //equlab.altHeld =
        //    IsDown(EKeys::LeftAlt) ||
        //    IsDown(EKeys::RightAlt);


        //equlab.aClicked =
        //    WasPressed(EKeys::A);

        //equlab.bClicked =
        //    WasPressed(EKeys::B);

        //equlab.cClicked =
        //    WasPressed(EKeys::C);

        //equlab.dClicked =
        //    WasPressed(EKeys::D);

        //equlab.eClicked =
        //    WasPressed(EKeys::E);

        //equlab.fClicked =
        //    WasPressed(EKeys::F);

        //equlab.gClicked =
        //    WasPressed(EKeys::G);

        //equlab.hClicked =
        //    WasPressed(EKeys::H);

        //equlab.iClicked =
        //    WasPressed(EKeys::I);

        //equlab.jClicked =
        //    WasPressed(EKeys::J);

        //equlab.kClicked =
        //    WasPressed(EKeys::K);

        //equlab.lClicked =
        //    WasPressed(EKeys::L);

        //equlab.mClicked =
        //    WasPressed(EKeys::M);

        //equlab.nClicked =
        //    WasPressed(EKeys::N);

        //equlab.oClicked =
        //    WasPressed(EKeys::O);

        //equlab.pClicked =
        //    WasPressed(EKeys::P);

        //equlab.qClicked =
        //    WasPressed(EKeys::Q);

        //equlab.rClicked =
        //    WasPressed(EKeys::R);

        //equlab.sClicked =
        //    WasPressed(EKeys::S);

        //equlab.tClicked =
        //    WasPressed(EKeys::T);

        //equlab.uClicked =
        //    WasPressed(EKeys::U);

        //equlab.vClicked =
        //    WasPressed(EKeys::V);

        //equlab.wClicked =
        //    WasPressed(EKeys::W);

        //equlab.xClicked =
        //    WasPressed(EKeys::X);

        //equlab.yClicked =
        //    WasPressed(EKeys::Y);

        //equlab.zClicked =
        //    WasPressed(EKeys::Z);
    }
}



