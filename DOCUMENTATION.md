## Patchwork Main Framework
main function is located inside `EntryPoint.cpp`
* * *
## Patchwork `namespace Patchwork`
- *<span style="color: #7f7f7f;">Math</span>*
    - **V2** `struct V2`
- *<span style="color: #7f7f7f;">Utility</span>*
    - **UniqueID** `namespace UniqueID`
* * *
- **Component** `class Component` : Component interface class for creating components. GetType() is a pure virtual function. All derived classes must implement it.
	- **Transform** `class Transform : public Component` : Holds the position and rotation of a GameObject. Every GameObject must have a transform component. 
- **GameObject** `class GameObject` : Every entity in the scene is a GameObject. You can add functionality to the GameObjects by using components. All GameObjects must have a Transform component.
* * *
- **Application** `class Application` : Engine creates application instance when it starts. Then calls the `void Application::Run()` function to initialize the application.
