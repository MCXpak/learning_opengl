#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;
uniform float offset = 0;
void main(){
   vec3 aPosPlusOffset = vec3(aPos.x + offset, aPos.y, aPos.z);
   gl_Position = vec4(aPosPlusOffset, 1.0);
   ourColor = vec3(aColor);
}