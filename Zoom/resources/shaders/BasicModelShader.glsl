#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_UvCoord;

uniform mat4 uMVPMatrix;

out vec2 UV;

void main(){

    gl_Position = uMVPMatrix * vec4(a_Position, 1.0);
	
	UV = a_UvCoord;
}

#type fragment
#version 330 core

in vec2 UV;

out vec4 color;

uniform sampler2D u_Textures[32];

void main(){

    vec4 texColor = vec4(1,1,1,1);
    int v_TexIndex = 0;
    vec2 test = vec2(1,1);
    switch(int(v_TexIndex))
    {
        case  0: texColor *= texture(u_Textures[ 0], UV); break;
        case  1: texColor *= texture(u_Textures[ 1], UV); break;
        case  2: texColor *= texture(u_Textures[ 2], UV); break;
        case  3: texColor *= texture(u_Textures[ 3], UV); break;
        case  4: texColor *= texture(u_Textures[ 4], UV); break;
        case  5: texColor *= texture(u_Textures[ 5], UV); break;
        case  6: texColor *= texture(u_Textures[ 6], UV); break;
        case  7: texColor *= texture(u_Textures[ 7], UV); break;
        case  8: texColor *= texture(u_Textures[ 8], UV); break;
        case  9: texColor *= texture(u_Textures[ 9], UV); break;
        case 10: texColor *= texture(u_Textures[10], UV); break;
        case 11: texColor *= texture(u_Textures[11], UV); break;
        case 12: texColor *= texture(u_Textures[12], UV); break;
        case 13: texColor *= texture(u_Textures[13], UV); break;
        case 14: texColor *= texture(u_Textures[14], UV); break;
        case 15: texColor *= texture(u_Textures[15], UV); break;
        case 16: texColor *= texture(u_Textures[16], UV); break;
        case 17: texColor *= texture(u_Textures[17], UV); break;
        case 18: texColor *= texture(u_Textures[18], UV); break;
        case 19: texColor *= texture(u_Textures[19], UV); break;
        case 20: texColor *= texture(u_Textures[20], UV); break;
        case 21: texColor *= texture(u_Textures[21], UV); break;
        case 22: texColor *= texture(u_Textures[22], UV); break;
        case 23: texColor *= texture(u_Textures[23], UV); break;
        case 24: texColor *= texture(u_Textures[24], UV); break;
        case 25: texColor *= texture(u_Textures[25], UV); break;
        case 26: texColor *= texture(u_Textures[26], UV); break;
        case 27: texColor *= texture(u_Textures[27], UV); break;
        case 28: texColor *= texture(u_Textures[28], UV); break;
        case 29: texColor *= texture(u_Textures[29], UV); break;
        case 30: texColor *= texture(u_Textures[30], UV); break;
        case 31: texColor *= texture(u_Textures[31], UV); break;
    }
    color = texColor;
}