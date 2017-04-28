#version 330 core

// This is an example vertex shader. GLSL is very similar to C.
// You can define extra functions if needed, and the main() function is
// called when the vertex shader gets run.
// The vertex shader gets called once per vertex.

//layout (location = 0) in vec3 vert;
layout (location = 1) in vec3 vertNormal;
layout (location = 0) in vec3 position;

uniform mat4 MVP;
uniform mat4 camera;
uniform mat4 model;
uniform mat4 projection;

//out vec3 fragVert;
out vec3 fragNormal;
out vec3 view_direction;

//out vec3 Normal;
//out vec3 FragPos;

void main()
{
    vec3 FragPos = vec3(model * vec4(position, 1.0f));
    vec3 Normal = mat3(transpose(inverse(model))) * vertNormal;
    
    // Pass some variables to the fragment shader
    fragNormal = Normal;
   // fragVert = FragPos;
    view_direction = vec3(normalize(-((camera * model) * vec4(position, 1.0))));
    
    gl_Position = projection * camera *  model * vec4(position, 1.0f);
}
