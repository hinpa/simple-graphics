#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
noperspective out vec3 dist;
vec4 v1;
vec4 v2;
vec4 v3;

// float mydistance(vec2 v1, vec2 v2, vec2 point)
// {
// 	float ret = abs((v2[0] - v1[0])*(v1[1]-point[1]) - (v1[0] - point[0])*(v2[1]-v1[1]));
// 	return ret;
// }

void main()
{
	vec2 p0 = gl_in[0].gl_Position.xy / gl_in[0].gl_Position.w ;
  	vec2 p1	= gl_in[1].gl_Position.xy / gl_in[1].gl_Position.w ;
  	vec2 p2 = gl_in[2].gl_Position.xy / gl_in[2].gl_Position.w ;


	
	vec2 v0 = p2 - p1;
	vec2 v1 = p2 - p0;
	vec2 v2 = p1 - p0;


	float area = abs(v1.x * v2.y - v1.y * v2.x);

  	dist = vec3(area/length(v0),0,0);
 	gl_Position = gl_in[0].gl_Position;
  	EmitVertex();
	
  	dist = vec3(0,area/length(v1),0);
  	gl_Position = gl_in[1].gl_Position;
  	EmitVertex();

  	dist = vec3(0,0,area/length(v2));
  	gl_Position = gl_in[2].gl_Position;
  	EmitVertex();


  	EndPrimitive();

}