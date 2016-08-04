#version 400 core

in  vec4  vPosition;
uniform mat4 mat_mvp;
void
main()
{
    gl_Position = mat_mvp * vPosition;
}
