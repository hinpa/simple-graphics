#version 330 core


out vec4 color;
    
uniform vec4 u_Color;
// in vec2 v_TextCoord;
noperspective in vec3 dist;
flat in vec3 factor;
uniform sampler2D u_Texture;


void main()
{
	float d = min(dist[0],min(dist[1],dist[2]));
	if (d < 0.001)
	{
		float val = 1. - d * 250;
		color = vec4(val,val,val,1.);
	}
	else
	{
		color = vec4(0.6,0.6,0.6,1.);
	}
}