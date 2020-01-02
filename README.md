# Application-Framework

A simple application framework built upon GLFW window creation and input detection.

## Features

Features easy creation of states, input contexts, and mapping of keys, mouse buttons and mouse movement using the command pattern.
The states are handled statemachine style, with support for stacking of states, pushing and popping. 
A state contains one or more input contexts, handled for each state in a way similar to how all the states are handled for each application.
The input contexts come in two types, cursor enabled, for menu navigation etc., and cursor disabled, useful when handling a 3D camera.
Buttons, keys and mouse movement, separated into the two axis when cursor is disabled, are all fully mappable to customly created commands which are automatically executed every frame. 

The source code is showed in the form of a runnable Visual Studio Solution, to enable anyone to add support for OpenGL or similar.

## Usage

Creation of applications, states, input contexts, and commands all follow the same pattern. Define a class that inherits from the base class `Application`, `ApplicationState`, `Context_cursor_enabled` or `Context_cursor_disabled`, and `Command` or `WeightedCommand` respectively.
Define the functions that are virtual in the corresponding base class.

For `Application` those are:
  - `void init_states()` : Called during `init()`

For `ApplicationState` those are:
  - `void init()` : Called when the state is changed to or pushed onto the state stack
  - `void cleanup()` : Called when the state is changed from
  - `void pause()` : Called when another state is pushed on top of this
  - `void resume()` : Called when the state above this becomes the top state in the stack after a pop
  - `void get_events()` : Called immediately after `glfwPollEvents`
  - `void update()` : Called after `get_events()`
  - `void display()` : Called after `update()`
  - `const char* get_name()` : Called by the logging library when this state is changed to
  
For `Context` those are:
  - `void init()` : Called when this is changed to or pushed onto the context stack
  - `void cleanup()` : Called when this is popped from the contex stack
  
For `Command` those are:
  - `void execute()` : Called during active states `get_events()` call
  
For `WeightedCommand those are`
  - `void execute(double weight)` : Called during active states `get_events()` call
  

### The main function
  
To actually create an `Application` object and get it running only these three lines are required in your main function:

```
std::shared_ptr<MyApplication> a = std::make_shared<MyApplication>();

a->init();
a->run();
```

Where `MyApplication` inherits from `Application`.

### The Application object

In the definition of the function `MyApplication::init_states()` you can create the states you want you application to have. 
This is done with a call to `create_state<StateType>(Args... args)` where `StateType` is one of your custom created state classes that inherits from `ApplicationState`, and args are the constructor arguments you need you state to have.
After you have created all the states you need to get your app running, you finish with a call to `change_to_state(int stateindex)` where stateindex is the index of your state. States are indexed in the order they are created, so the first call to `create_state` creates a state with index 0;
For an example on how this can look see: [MyApplication.h](https://github.com/lyktstolpe/Application-Framework/blob/master/Application%20OpenGL/MyApplication.h)

### Creation of contexts

The procedure is similar inside `MyState::init()` for the creation of input contexts. You create a context with a call to `create_context<ContextType>(Args... args)`.
Finish of by calling `change_to_context(int contextindex)`. The same rules as for state creation apply.
For an example on how this can look see: [MainState.h](https://github.com/lyktstolpe/Application-Framework/blob/master/Application%20OpenGL/MainState/MainState.h)

### Mapping of keys and mouse actions

In the function `Context::init()` you can bind the keys relevant dor that context. 

Call `map_key<InvokerType, CommandType>(int key, Args... args)` to map the key with the code `key` to the command type `CommandType`. `args` is forwarded to the creation of the Command object.
`InvokerType` specifies how the command is executed. For keys this can be `Action`, the command is executed on key press, or `State`, the command is executed once every frame until key release.
An alternative is `map_key<InvokerType>(int key, Command command)` where `command` is a `std::unique_ptr<CommandType>` you created beforehand.

Call `map_mouse<InvokerType, CommandType(int button, glm::vec2 bounds, Args... args)` to map the mouse button `button` to execute the command if the mouse is positioned within the bounds specified by `bounds`. 
The bounds are coordinates of screen-space ranging from `(-1, -1)` in the bottom left to `(1, 1)` in the top right. Bounds are specified bottom left corner first, top right corner second. For example, the bottom left quadrant of the screen is bound by `(-1, -1)` and `(0, 0)`.
This only works in a context where the cursor is enabled.
Here `InvokerType` can be `VectorAction` or `VectorState`.

Call `map_hover<CommandType>(glm::vec2 bounds, Args... args)` to have your command execute every frame if the cursors position is within `Bounds`.

Call `map_mouse_x<WeightedCommandType>()` to have the command of type `WeightedCommandType` to be called with the weight as the cursors current simulated x position, which can be any double value, every time the mouses x position changes..
The same applies for `map_mouse_y<WeightedCommandType>()`.

`map_mouse<InvokerType, CommandType>(int key, Args... args)` works in cursor disabled context and will bind the action to the mouse button the same way `map_key` would to a keyboard button. It always executes regardless of cursor coordinates.

For an example on how this can look see [MainStateContexts.cpp](https://github.com/lyktstolpe/Application-Framework/blob/master/Application%20OpenGL/MainState/Contexts/MainStateContexts.cpp)

At least one state containg at least one context needs to be created if the application is to do anything other than showing a blank screen.

