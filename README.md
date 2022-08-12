Graphic_Engine
==============
Making my own graphic engine   
Project goal is to make a simple graphic engine
  
https://user-images.githubusercontent.com/44907014/184313456-efaf8141-b791-4007-9eae-60e8d1d1dc5d.mp4
   
requirements
------------
OpenGL (3.3 or higher)   
GLFW 3 (3.3)   
GLM (0.9.9.5)   
   
   
Organization
------------
##### CoreEngine
- core_graphic    
##### ObjectEngine
- geometry
    * geometry
    * geometry_function
- component
- command
    * command_queue   
##### GraphicEngine
- window
    * openGL_window
    * window_setting
- shader
    * openGL_shader
- render
    * openGL_render      
##### PhysicsEngine
- hitbox
    * surface
    * hitbox
- transform
    * transform
    * compute_function
- collision
    * collision
   
   
Need to update
-------------  
object, component class 
physics engine
