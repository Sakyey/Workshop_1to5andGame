# DA376B_Workshop1

## This repo contains my Workshop 1-5 deliverables for the DA376B course

## Workshop 1

### Objective

- Get familiar with the Unreal Editor UI
- Create a new blank C++ project
- Save a basic level and place a Cube actor
- Create a C++ Character class and turn it into a Blueprint
- Initialize Git source control

### Steps

1. **Project Creation**

   - Engine version: Unreal Engine 5.4
   - Project type: Blank (C++), no Starter Content
   - Folder: `D:\UnrealProjects\DA376B_Workshop1`

2. **Level Setup**

   - Created new level via **File → New Level → Basic**
   - Saved as `Content/Maps/Workshop1_Level.umap`

3. **Cube Placement**

   - Dragged **Cube** from Place Actors panel into scene
   - Adjusted Transform:
     - Location: (X=0, Y=0, Z=50)
     - Rotation: (0, 45, 0)
     - Scale: (1.5, 1.5, 1.5)

4. **C++ Class & Blueprint**

   - Generated `PlayerCharacter` (subclass of ACharacter) via **Tools → New C++ Class**
   - Built project in VS Code
   - Created Blueprint `BP_PlayerCharacter` based on `PlayerCharacter` in `/Content/Blueprints/`

5. **Editor Integration**

   - Set VS Code as Source Code Editor under **Editor Preferences**
   - Generated VS Code project files via **File → Generate Visual Studio Code project**
   - Enabled Live Coding in **Editor Preferences**

6. **Git Initialization**

- Done through guthub Desktop: File -> Create New Repository ->
- Verified in-editor Git (Git Beta plugin) was connected

### Deliverables

- **Project folder** under Git: [`main` branch on GitHub](<[https://github.com/yourusername/DA376B_Workshop1](https://github.com/Sakyey/Workshop_1to5andGame.git)>)
- **Level**: `Workshop1_Level.umap` showing the placed cube
- **C++ class**: `Source/DA376B_Workshop1/PlayerCharacter.*`
- **Blueprint**: `Content/Blueprints/BP_PlayerCharacter.uasset`
- **Screenshot**: GitHub commit history after initial push (see ![Initial commit history](Source/Workshop_1to5andGame/docs/githistriy.png))

---

## Workshop 2

### Objective

- Add a third‐person camera and character movement using Unreal’s Enhanced Input system
- Bind WASD for movement, Mouse X/Y for camera look, and Space Bar for jump
- Extend the `PlayerCharacter` C++ class to include a spring arm, follow camera, and Enhanced Input setup
- Create a new level demonstrating these controls

### Steps

1. **Enable Enhanced Input Plugin**

   - In the Editor, go to **Edit → Plugins**, enable **Enhanced Input**, then restart Unreal.

2. **Create Input Assets**

   - In the **Content Browser**, create an `Input/` folder.
   - Right‐click → **Input → Input Action** to create:
     - `IA_Move` (Value Type = Vector2D)
     - Duplicate to make `IA_Look` (Value Type = Vector2D)
     - Create `IA_Jump` (Value Type = Boolean)
   - Right‐click → **Input → Input Mapping Context** to create `IMC_Player`.
   - Open `IMC_Player` and under **Mappings**, add these entries:
     1. **IA_Move → W** with a **Swizzle (YXZ)** modifier and **Scale (Y=+1)**
     2. **IA_Move → S** with **Swizzle (YXZ)** + **Negate (Y)**
     3. **IA_Move → D** with **Scale (X=+1)** (no modifiers)
     4. **IA_Move → A** with **Negate (X)**
     5. **IA_Look → Mouse X** with **Scale (X=+1)**
     6. **IA_Look → Mouse Y** with **Negate (Y)**
     7. **IA_Jump → Space Bar** (Boolean, no modifiers)

3. **Update C++ Character Class**

   - **New Variables in `PlayerCharacter.h`** (all marked `UPROPERTY`):

     - `USpringArmComponent* SpringArm` – the “camera boom” that holds the camera away from the character
     - `UCameraComponent* FollowCamera` – the actual camera attached to the spring arm
     - `UInputAction* IA_Move`, `UInputAction* IA_Look`, `UInputAction* IA_Jump` – pointers to the three InputAction assets
     - `UInputMappingContext* IMC_Player` – pointer to the mapping context asset

   - **New/Overridden Methods:**

     - `BeginPlay()` – override to grab the local player’s `UEnhancedInputLocalPlayerSubsystem` and call `AddMappingContext(IMC_Player, 0)`, activating the input mappings at runtime
     - `SetupPlayerInputComponent(UInputComponent* InputComponent)` – override to cast to `UEnhancedInputComponent` and bind:
       - `IA_Move` → `APlayerCharacter::Move(const FInputActionValue&)`
       - `IA_Look` → `APlayerCharacter::Look(const FInputActionValue&)`
       - `IA_Jump` → `ACharacter::Jump()` on “Started” and `ACharacter::StopJumping()` on “Completed”
     - `void Move(const FInputActionValue& Value)` – handler that extracts a Vector2D (X = strafe, Y = forward) and calls `AddMovementInput()` accordingly
     - `void Look(const FInputActionValue& Value)` – handler that extracts a Vector2D (X = yaw, Y = pitch) and calls `AddControllerYawInput()` and `AddControllerPitchInput()`

   - **Constructor Changes in `.cpp`**:
     - Instantiate and attach `SpringArm` to the root component, set `TargetArmLength = 300.f` and `bUsePawnControlRotation = true`
     - Instantiate and attach `FollowCamera` to the spring arm’s socket, set `bUsePawnControlRotation = false`

4. **Compile & Resolve Errors**

   - Save the modified `.h` and `.cpp`, then in the Unreal Editor click **Compile** (or press **Ctrl + Alt + F11** for Live Coding).
   - If build errors occur, verify:
     - The `Category="Camera"` spelling is correct on both camera properties
     - Method signatures match exactly (e.g., `SetupPlayerInputComponent(UInputComponent*)`)
     - All necessary includes are present:
       ```cpp
       #include "Camera/CameraComponent.h"
       #include "GameFramework/SpringArmComponent.h"
       #include "EnhancedInputComponent.h"
       #include "EnhancedInputSubsystems.h"
       #include "InputAction.h"
       #include "InputMappingContext.h"
       #include "GameFramework/PlayerController.h"
       ```

5. **Hook Up BP_PlayerCharacter**

   - Open `BP_PlayerCharacter` (subclass of `APlayerCharacter`) in `/Content/Blueprints/`.
   - In **Class Defaults → Input**, assign:
     - **IA_Move** → `/Input/IA_Move`
     - **IA_Look** → `/Input/IA_Look`
     - **IA_Jump** → `/Input/IA_Jump`
     - **IMC_Player** → `/Input/IMC_Player`
   - (Optional) Add a skeletal mesh and basic animation to visually confirm movement.

6. **Create & Configure Workshop2_Level**

   - **File → New Level → Basic**, then **Save As** → `Workshop2_Level.umap` (in `Content/Maps/`).
   - Drag a **Player Start** into the scene.
   - In **Project Settings → Maps & Modes**, set:
     - **Editor Startup Map** = `Workshop2_Level`
     - **Game Default Map** = `Workshop2_Level`
     - **Default GameMode Class** = your custom `BP_GameMode` (with Default Pawn Class = `BP_PlayerCharacter`).

7. **Test in Play-In-Editor**
   - Click **Play**:
     - **W/A/S/D** moves the character forward/back/strafe left/right
     - **Mouse X** rotates the camera around (yaw); **Mouse Y** pitches the camera up/down
     - **Space Bar** makes the character jump
   - If a mesh + animation are assigned, verify that walking/running animations play as the character moves.

### Deliverables

- **Input Assets** in `Content/Input/`:
  - `IA_Move.uasset` (Vector2D action for movement)
  - `IA_Look.uasset` (Vector2D action for camera look)
  - `IA_Jump.uasset` (Boolean action for jump)
  - `IMC_Player.uasset` (Mapping Context with seven mappings: W, A, S, D, Mouse X, Mouse Y, Space Bar)
- **C++ Changes**:
  - New properties added to `PlayerCharacter.h`:
    - `SpringArm`, `FollowCamera`, `IA_Move`, `IA_Look`, `IA_Jump`, `IMC_Player`
  - Overridden methods:
    - `BeginPlay()` registers the mapping context
    - `SetupPlayerInputComponent(...)` binds input actions to `Move()`, `Look()`, and built-in Jump/StopJumping
  - New handler methods in `PlayerCharacter.cpp`:
    - `Move(const FInputActionValue&)` for Vector2D movement
    - `Look(const FInputActionValue&)` for camera rotation
  - Constructor now creates and configures the spring arm and follow camera components
- **Blueprint**:
  - `Content/Blueprints/BP_PlayerCharacter.uasset` (with mesh, Enhanced Input references, and optionally basic animations)
  - `Content/Blueprints/BP_GameMode.uasset` (Default Pawn Class set to `BP_PlayerCharacter`)
- **Level**:
  - `Content/Maps/Workshop2_Level.umap` demonstrating movement, camera look, and jump
- **Video**:  
  ![Workshop 2 Gameplay](Source/Workshop_1to5andGame/docs/workshop2gif.gif)  
  _(Play-In-Editor capture showing character moving/rotating)_
- **GitHub**:  
  All new assets and code committed to the repository (e.g., [`https://github.com/Sakyey/Workshop_1to5andGame/tree/main`](https://github.com/Sakyey/Workshop_1to5andGame/tree/main))

## Workshop 3

### Objective

- Build a Main Menu (Start / Quit) using UMG
- Create an in‐game Score HUD that displays a `Score` variable from `BP_PlayerCharacter` and updates at runtime
- Learn to bind Blueprint UI widgets to character data and switch input modes between UI and game

### Steps

1. **Create “UI” Folder**

   - In the Content Browser, right-click → **New Folder** → name it `UI`.
   - All Widget Blueprints for Workshop 3 will live here.

2. **Main Menu Widget (`WBP_MainMenu`)**

   1. In `Content/UI`, right-click → **User Interface → Widget Blueprint** → name it `WBP_MainMenu`.
   2. **Designer**:
      - Drag a **Canvas Panel** (if not already present).
      - Inside the Canvas, add two **Button** widgets, anchor both to center.
        - Rename them to `Button_Start` and `Button_Quit`.
        - Inside each Button, place a **Text** block (set Text to “Start” and “Quit” respectively).
        - Set **Is Variable = true** on both Buttons.
   3. **Graph (Event Construct)**:
      - From **Event Construct**, call **Set Input Mode UI Only** (Target = **Get Owning Player**).
      - In **Set Input Mode UI Only** details, check **Show Mouse Cursor**.
   4. **Graph (Button Logic)**:
      - **OnClicked (Button_Start)** → **Open Level (“Workshop2_Level”)** → **Set Input Mode Game Only** (Target = **Get Owning Player**).
      - **OnClicked (Button_Quit)** → **Quit Game** (Target = **Get Owning Player**).
   5. **Compile & Save** `WBP_MainMenu`.

3. **Create Main Menu Level (`Workshop3_MainMenu`)**

   1. **File → New Level → Default** → **Save As** → `Content/Maps/Workshop3_MainMenu.umap`.
   2. **Level Blueprint** (Open Level Blueprint):
      - **Event BeginPlay** → **Create Widget (Class = WBP_MainMenu)** → **Add to Viewport**.
      - **Get Player Controller (0)** → **Set Show Mouse Cursor = true**.
   3. **World Settings (MainMenu_Level)**:
      - Under **GameMode Override**, set to `GM_MainMenu` (Default Pawn = None).
   4. **Project Settings → Maps & Modes** (or override per-map):
      - **Editor Startup Map** = `Workshop3_MainMenu`
      - **Game Default Map** = `Workshop3_MainMenu`
      - **Default GameMode** for `Workshop3_MainMenu` = `GM_MainMenu`

4. **BP_MainMenuGameMode**

   - In `Content/Blueprints`, create a **Blueprint Class → GameModeBase** → name it `GM_MainMenu`.
   - **Class Defaults**: set **Default Pawn Class = None** (no player pawn in the Main Menu).

5. **Workshop 2 Level Configuration**

   - Open `Content/Maps/Workshop2_Level.umap`.
   - In **World Settings**, set **GameMode Override** to `GM_Workshop` (the Workshop 2 GameMode with Default Pawn = `BP_PlayerCharacter`).
   - Save the level.

6. **Score HUD Widget (`WBP_Score`)**

   1. In `Content/UI`, right-click → **User Interface → Widget Blueprint** → name it `WBP_Score`.
   2. **Designer**:
      - Drag a **Text** widget onto the Canvas, anchor to top-left, set **Position (X=10, Y=10)**.
      - Set the Text’s default content to “Score: 0” and check **Is Variable**.
      - Rename it to `Text_ScoreLabel`.
   3. **Graph (Binding Text)**:
      - Select `Text_ScoreLabel` → in Details → **Content → Bind → Create Binding**.
      - In the generated function (`Get_Text_ScoreLabel_Text_0`):
        - **Get Owning Player Pawn** → **Cast to BP_PlayerCharacter** → **Get Score** → **Conv_IntToText** → **Append (“Score: ”)** → **Return**.
   4. **Compile & Save** `WBP_Score`.

7. **Expose `Score` in BP_PlayerCharacter**

   1. Open `BP_PlayerCharacter` in `/Content/Blueprints/`.
   2. Under **My Blueprint → Variables**, click **+** → name it `Score` → set **Type = Integer** → **Default Value = 0**.
   3. **Compile & Save** `BP_PlayerCharacter`.

8. **Add HUD to Player Character**

   1. In `BP_PlayerCharacter → Event Graph`, locate **Event BeginPlay** (or add one).
   2. From **Event BeginPlay** → **Create Widget (Class = WBP_ScoreHUD)** → **Add to Viewport**.
   3. **Compile & Save** the Blueprint.

9. **Increment Score at Runtime** (Test)
   1. In `BP_PlayerCharacter → Event Graph`, right-click → type **Key P** → select **Keyboard P** (Legacy).
   2. From **P (Pressed)** → **Get Score** → **Integer + Integer (Get Score, +1)** → **Set Score**.
   3. **Compile & Save**.
   4. **Play** `Workshop2_Level` → press **P** and verify the HUD text changes:
      ```
      Score: 0 → Score: 1 → Score: 2 → …
      ```

### Deliverables

- **Widget Blueprints (Content/UI/)**
  - `WBP_MainMenu.uasset` (Main Menu with Start/Quit logic)
  - `WBP_Score.uasset` (HUD Text bound to `BP_PlayerCharacter.Score`)
- **Levels (Content/Maps/)**
  - `Workshop3_MainMenu.umap` (Main Menu world, Level Blueprint spawns `WBP_MainMenu`)
  - `Workshop2_Level.umap` (Workshop 2 level, set to `BP_GameMode_Workshop`)
- **Blueprints (Content/Blueprints/)**
  - `GM_MainMenu.uasset` (GameModeBase, Default Pawn None)
  - `BP_PlayerCharacter.uasset` (updated to expose `Score`, create HUD widget, bind input context)
- **Input & Mapping (Content/Input/)**
  - `IA_Move`, `IA_Look`, `IA_Jump`, `IMC_Player` (from Workshop 2)
- **Screenshots / GIF**:
  - ![Main Menu on screen (buttons + visible cursor)](Source/Workshop_1to5andGame/docs/workshop3mainmenyvideo.gif)
  - ![In-game HUD displaying “Score: X” and updating](Source/Workshop_1to5andGame/docs/workshop3scoreincrement.gif)
- **GitHub**:
  - All new assets committed (branch `main`):  
    [`https://github.com/Sakyey/Workshop_1to5andGame`](https://github.com/Sakyey/Workshop_1to5andGame) (verify Workshop 3 commits present)
