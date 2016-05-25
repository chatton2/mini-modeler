How To Use:

--To draw a mesh, set the width, depth, row number, and column number, then press the "Draw" button.  To change the color of the mesh,
select a color with the color picker and press the "Color" button.  To change the "Snow Cap" height, use the slider marked "Cap Height."
The slider goes from -30 to 30.
--Press the "A" and "D" keys to rotate the camera horizontally, and "W" and "S" to rotate it vertically.
To zoom in, press "E" and to zoom out press "F".  If you zoom into the center of the mesh, the "E" and
"F" key functions will be reversed.  There is also a view of the mesh as a flat grid in the bottom right corner.  Use P to zoom in and L to 
zoom out.  These will be reversed if you zoom all the way through.  The "Top" and "Front" buttons shift the camera to those viewpoints.
--To select a vertex, use the X and Y spinners to select the vertex at that coordinates.  The selected vertex will be colored yellow in both 
the mesh and the flat version of the mesh.  To change that vertexes height, select the Z value you want to change it by using the "Z" spinner,
and click transform.  To toggle through showing the wireframe, the faces, or both, click the "Grid" button.
--To fractalize your mesh, click the "Fractalize" buttom  

Design:

--The mesh is actually a list of "faces", and the faces are actually mat4's with each vec4 representing a vertex.  When drawing, the program iterates
through the list and draws the vertices as quads, polylines, or both. 
--The UI class has pointers to it's various widgets and other things, the same as with previous projects.  It has a Controller pointer, which points
to the mesh's window, which points to the heightField class (Containg the vertices and mesh manipulatory function), which has a camera.  The flatView
of the mesh class has pointer to the same heightField, but has it's own camera.  The flatView draws in a similar way to the regular mesh.
--To fractalize the mesh, the function iterates through the list of mat4's, and divides it up into 4 new mat4's, displacing what would be the new vertices
by a random amount within a certain range and determined by the number of times the mesh has already been fractalized (the random() function I wrote does
this).  It adds all of these new mat4's to a new list of mat4's.  Once it gets to the end of the iteration, it frees the heightField's old list of mat4's,
and makes the new list it's list.  The first time it draws the mesh after it's been fractalized, it calls the function searchHeight().  searchHeight() 
iterates through the list of vertices to find the height of the first vertex with that given x and y value.  This is to ensure that the mesh has no holes
in it.  It makes the returned value that points height.  After the first time, draw() doesn't call searchHeight() until the mesh is fractalized again.
--I chose to use a button and spinner instead of a slider for transforming a point because this way the program doesn't have to remember a point's original 
height in order to displace it.  It also allows the user to undo transforms more easily.

Difficulties:

--The first challenge was drawing the mesh.  I had to be very precise with the math to calculate the vertices, which took a lot of trial and error.
--I tried to get 3D/2D picking to work (Using the flat view of the mesh), but I couldn't figure out how the the coordinates I was clicking (I printed
the values out), related to the coordinates on the mesh, so I went with a different way to select a vertex.
--Another problem that I has was getting the mesh to not have holes after it was fractalized.  At first I had the random displacement reliant on the points
x and y value, but that didn't lead to good looking fractalization.  Than I had it add each unique point to a list, and a repeated point would search through 
that list to find the correct height, but that led to occasional gaps in the mesh for reasons I could not figure out.  Then I had it search through the entire
list of vertices at draw time, which meant their were no holes, but that made the camera slow when their were a lot of faces.  Finally I have it at the current
set up, which has no holes and a speedy camera movements.

Bugs:

The hole bug happened only occasionally, but after got the program to it's current state, I never saw a hole again.  How ever, since the bug only happened
sometimes, I can't be 100% sure it isn't there.