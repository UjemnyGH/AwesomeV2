# AwesomeV2 made by UjemnyGH
Awesome engine v2

![Awesome image logo](AwesomeV2/data/textures/awesomev2.png)

This is basicly comtinuation Awesome engine, but instead rewriting old engine I am writing new one.

# Libs I used:
- GLFW
- GLEW
- GLM
- STB Image
- CGLTF (I hope I use it)

### Changes
	> - 30.05.2022
	> So now we have half working rotations becouse bug in NormalizeVector function
	> Also you can now use global "FILE* __debug_file" to write debug from where you want
	> And also I added couple new functions to convert matrix3x3 to angle and vice versa to make rotation easier(i don`t know if it really tha easier but you know, it should be)
	> - 12.04.2022
	> I added custom dynamic vector type (unused)
	> I made better (in engine case) user input
	> I added another sorting algorithm
	> I added some functions for rotation to try things out
	> Also I rewrite every function using glm::vec3 to aws::Vector to make things easier
	> And also I added converting aws::Vector to glm::vec<ANY_SIZE> and function to convert float into aws::Vector(neaded to multiply aws::Vector by float at this time)
	> ------------------------------
	> - 5.04.2022
	> I added commenst on every function to make it easier to use
	> I added inverted atan2 function
	> You cam now get parameters of batched objects by ID
	> ------------------------------
	> - 2.04.2022
	> Model loader for .obj files now work properly
	> Shader now can be loaded from file
	> I added window class
	> AABB collisions work as intended


### To fix:
	> AABB Collisions inside Renderer class doesn`t work properly
	> Adding new objects in batch adds weird things
	> Normalization of rotation of batched object