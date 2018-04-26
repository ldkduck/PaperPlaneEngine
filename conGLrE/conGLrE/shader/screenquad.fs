#version 330  
out vec4 color;  
in vec2 TexCoord0;  
 
uniform sampler2D hdrBuffer;  
  
void main()  
{           
    vec3 hdrColor = texture(hdrBuffer, vec2(1-TexCoord0.x,1-TexCoord0.y)).rgb;  
     // 曝光色调映射  
    vec3 mapped = hdrColor;  
  	//mapped = vec3(1.0) - exp(-hdrColor * 1.5); 
	//mapped *= 0.6;
    color = vec4(mapped, 1.0); 
	
}   