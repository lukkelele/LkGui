#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
    gl_Position = position;
}


#shader fragment
#version 330 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(0.0, 0.0, 0.0, 1.0);  
}

