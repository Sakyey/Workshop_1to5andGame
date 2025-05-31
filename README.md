# DA376B_Workshop1

This repo contains my Workshop 1-5 deliverables for the DA376B course
---

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

- **Project folder** under Git: [`main` branch on GitHub](https://github.com/yourusername/DA376B_Workshop1)  
- **Level**: `Workshop1_Level.umap` showing the placed cube  
- **C++ class**: `Source/DA376B_Workshop1/PlayerCharacter.*`  
- **Blueprint**: `Content/Blueprints/BP_PlayerCharacter.uasset`  
- **Screenshot**: GitHub commit history after initial push (see `![githistriy](https://github.com/user-attachments/assets/b6fa1c65-c920-4bbe-9f91-01f010b62ca6)`)

---

